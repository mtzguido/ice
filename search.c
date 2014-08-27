#include "search.h"
#include "board.h"
#include "addon.h"
#include "ztable.h"
#include "common.h"
#include "ai.h"
#include <stdbool.h>

static bool doing_null_move;
static bool doing_lmr;

score negamax(game g, int curDepth, int maxDepth, move *mm, score alpha, score beta);

static inline void genCaps_wrap(game g, int depth) {
	genCaps(g);
	stats.ngen += first_succ[ply+1] - first_succ[ply];

	addon_score_succs(g, depth);
}

static inline void shuffle_succs() {
	struct MS swap;
	const int lo = first_succ[ply];
	const int hi = first_succ[ply+1];
	int i, j;

	if (!copts.shuffle)
		return ;

	for (i=lo; i<hi-1; i++) {
		j = i + rand() % (hi-i);

		if (i == j)
			continue;

		swap = gsuccs[j];
		gsuccs[j] = gsuccs[i];
		gsuccs[i] = swap;
	}
}

static inline void genSuccs_wrap(game g, int depth) {
	/* Generar sucesores */
	genSuccs(g);
	stats.ngen += first_succ[ply+1] - first_succ[ply];

	addon_score_succs(g, depth);

	/* Mezclarlos si es necesario */
	shuffle_succs();
}

/*
 * Ordena el arreglo de sucesores de manera lazy.
 * Deja en arr[i] el sucesor correcto, asume que arr[0..i-1] ya
 * está ordenado.
 */
static inline void sort_succ(game g, int i, int depth_rem) {
	if (!copts.sort)
		return;

	if (i == first_succ[ply+1] - 1) {
		/* Nada para hacer */
		return;
	}

	assert(gsuccs[i].m.who == g->turn);

	/* Ordenarlos si es necesario */
	if (depth_rem > SORT_DEPTH_THRESHOLD) {
		int j;
		int best = i;
		score s = gsuccs[i].s;

		for (j=i+1; j<first_succ[ply+1]; j++) {
			assert(gsuccs[j].m.who == g->turn);
			if (gsuccs[j].s > s) {
				best = j;
				s = gsuccs[j].s;
			}
		}

		if (best != i) {
			struct MS swap;

			swap = gsuccs[best];
			gsuccs[best] = gsuccs[i];
			gsuccs[i] = swap;
		}
	}

	assert(gsuccs[i].m.who == g->turn);
	assert(gsuccs[i].m.move_type != MOVE_INVAL);
	assert(gsuccs[i].s >= 0);
}

static inline int calcExtension(const game g, int maxDepth, int curDepth) {
	int ret = 0;

	if (inCheck(g, g->turn) || g->lastmove.promote != EMPTY)
		ret++;

	return ret;
}

static inline score null_move_score(game g, int curDepth, int maxDepth,
				    score alpha, score beta) {
	score t;
	game ng;
	move m = { .move_type = MOVE_NULL, .who = g->turn };

	if (!copts.null)
		goto dont;

	/* Dont do two null moves in the same variation */
	if (doing_null_move)
		goto dont;

	/*
	 * Dont null-move when in check or when low in material since
	 * we're likely to be in Zugzwang
	 */
	if (inCheck(g, g->turn) || g->pieceScore[g->turn] <= NMH_THRESHOLD)
		goto dont;

	/* Not even worth it */
	if (maxDepth - curDepth <= 1)
		goto dont;

	ng = copyGame(g);
	if (doMove(ng, m)) {
		stats.null_tries++;

		mark(ng);
		doing_null_move = true;
		t = -negamax(ng, maxDepth-3, curDepth+1, NULL, -beta, -alpha);
		doing_null_move = false;
		unmark(ng);
	} else {
		/*
		 * doMoveNull's only restriction is not being in check
		 * and we already provided a case for that so this
		 * should never be reached
		 */
		assert(0);
		t = minScore;
	}

	freeGame(ng);
	return t;

dont:
	return alpha;
}

static inline score quiesce(game g, score alpha, score beta, int curDepth,
			    int maxDepth) {
	int nvalid, i;
	int ext, onlymove;
	game ng;
	score ret, t;
	score alpha_orig;

	if (isDraw(g) || reps(g) >= 2)
		return 0;

	stats.nopen_q++;

	t = boardEval(g);

	if (t >= beta)
		return beta;

	if (copts.delta_prune) {
		score delta = scoreOf(WQUEEN) - scoreOf(WPAWN);

		if (g->lastmove.promote != EMPTY)
			delta += scoreOf(WQUEEN);

		if (t + delta < alpha)
			return alpha;
	}

	if (t > alpha)
		alpha = t;

	if (ply >= MAX_PLY-1)
		return t;

	ext = calcExtension(g, maxDepth, curDepth);
	maxDepth += ext;
	if (curDepth >= maxDepth)
		return t;

	if (timelimited && !timeup) {
		ticks++;

		if ((ticks & 0xfff) == 0) {
			if (getms() >= timelimit)
				timeup = true;
		}
	}
	if (timeup) {
		return t;
	}

	alpha_orig = alpha;
	ng = copyGame(g);
	genCaps_wrap(g, curDepth);
	nvalid = 0;
	for (i=first_succ[ply]; i<first_succ[ply+1]; i++) {
		sort_succ(g, i, maxDepth - curDepth);

		assert(gsuccs[i].m.move_type == MOVE_REGULAR);

		/* We only consider captures and promotions */
		assert(isCapture(g, gsuccs[i].m)
				|| isPromotion(g, gsuccs[i].m));

		if (!doMove_unchecked(ng, gsuccs[i].m))
			continue;

		nvalid++;
		onlymove = i;

		mark(ng);
		ply++;
		t = -quiesce(ng, -beta, -alpha, curDepth+1, maxDepth);
		ply--;
		unmark(ng);
		*ng = *g;

		if (t > alpha) {
			if (t >= beta) {
				ret = beta;
				goto out;
			}

			alpha = t;
		}
	}

	if (nvalid == 0) {
		ret = t;
	} else if (nvalid == 1 && alpha < beta && copts.forced_extend) {
		__unused bool check;
		check = doMove_unchecked(ng, gsuccs[onlymove].m);
		assert(check);

		/*
		 * If only one move was valid, we're in a forced position,
		 * so re-search everything with +1 to the depth
		 */

		alpha = alpha_orig;

		mark(ng);
		ply++;
		t = -quiesce(ng, -beta, -alpha, curDepth+1, maxDepth+1);
		ply--;
		unmark(ng);

		if (t > alpha)
			alpha = t;

		ret = alpha;
	} else {
		ret = alpha;
	}

out:
	freeGame(ng);

	assert(timeup || ret > minScore);
	assert(timeup || ret < maxScore);

	return ret;
}

score negamax(game g, int maxDepth, int curDepth, move *mm, score alpha,
		score beta) {
	score t, ret, best, alpha_orig;
	int i;
	int ext;
	int nvalid = 0;
	game ng;
	int bestmove = -1;

	stats.nall++;
	if (isDraw(g)) {
		ret = 0;
		assert(!mm);
		goto out;
	}

	/*
	 * Si ya pasamos por este tablero, podemos asumir
	 * que vamos a reaccionar igual y vamos a llevar a un empate
	 * por repetición.
	 */
	if (reps(g) >= 2 && !mm) {
		ret = 0;
		goto out;
	}

	ext = calcExtension(g, maxDepth, curDepth);
	maxDepth += ext;

	/*
	 * Corte por profundidad, hacemos búsqueda por quietud, para
	 * mejorar nuestra evaluación de tablero.
	 */
	if (curDepth >= maxDepth) {
		assert(!mm);

		/*
		 * Si esto ocurre, tenemos una recursion mutua
		 * infinita con quiesce. No debería ocurrir nunca,
		 * pero dejamos el assert por las dudas.
		 */
		assert(!inCheck(g, g->turn));

		if (copts.quiesce)
			ret = quiesce(g, alpha, beta, curDepth, 999);
		else
			ret = boardEval(g);

		goto out;
	}

	/*
	 * Only try to null-move if beta was less than maxScore.
	 * Otherwise we will never suceed in the test.
	 */
	if (!mm && beta < maxScore) {
		t = null_move_score(g, curDepth, maxDepth, alpha, beta);
		if  (t > beta) {
			stats.null_cuts++;
			return beta;
		}
	}

	if (!mm)
		addon_notify_entry(g, maxDepth - curDepth, &alpha, &beta);

	if (alpha >= beta && copts.ab) {
		/* Deshabilitado por ahora */
		assert(0);
		ret = alpha;
		assert(!mm);
		goto out;
	}

	if (ply >= MAX_PLY-1)
		return boardEval(g);

	if (timelimited && !timeup) {
		ticks++;

		if ((ticks & 0xfff) == 0) {
			if (getms() >= timelimit)
				timeup = true;
		}
	}
	if (timeup && !mm) {
		return boardEval(g);
	}

	alpha_orig = alpha;
	best = minScore;
	ng = copyGame(g);

	stats.nopen_s++;
	stats.depthsn[curDepth]++;

	genSuccs_wrap(g, curDepth);

	for (i=first_succ[ply]; i<first_succ[ply+1]; i++) {
		sort_succ(g, i, maxDepth - curDepth);

		if (!doMove_unchecked(ng, gsuccs[i].m))
			continue;

		nvalid++;

		mark(ng);

		/* LMR */
		if (copts.lmr
			&& !doing_lmr
			&& i >= 4 + first_succ[ply] /* crap */
			&& curDepth >= 2
			&& gsuccs[i].s*10 < gsuccs[first_succ[ply]].s /* 2x crap */
			&& ext == 0
			&& !inCheck(ng, ng->turn)
			&& !isCapture(g, gsuccs[i].m)
			&& !isPromotion(g, gsuccs[i].m)) {
			stats.lmrs++;

			doing_lmr = true;
			ply++;
			t = -negamax(ng, maxDepth-1, curDepth+1, NULL, -beta, -alpha);
			ply--;
			doing_lmr = false;

			/* Do a full search if it didn't fail low */
			if (t > alpha && t < beta) {
				ply++;
				t = -negamax(ng, maxDepth, curDepth+1, NULL,
					     -beta, -alpha);
				ply--;
			} else {
				stats.lmrs_ok++;
			}
		} else {
			ply++;
			t = -negamax(ng, maxDepth, curDepth+1, NULL, -beta, -alpha);
			ply--;
		}

		unmark(ng);

		/* Ya no necesitamos a ng */
		*ng = *g;

		if (t > best) {
			best = t;
			bestmove = i;
		}

		if (t > alpha)
			alpha = t;

		if (alpha >= beta && copts.ab) {
			addon_notify_cut(g, gsuccs[i].m, curDepth);
			break;
		}
	}

	if (bestmove != -1)
		stats.picked[bestmove - first_succ[ply]]++;
	else
		assert(timeup || nvalid == 0);

	/* Era un tablero terminal? */
	if (nvalid == 0) {
		move dummy = {0};
		assert(!mm);

		if (inCheck(g, g->turn))
			ret = -100000 + curDepth;
		else
			ret = 0; /* Stalemate */

		/*
		 * Lo guardamos en la TT, podría ahorrar unos
		 * pocos ciclos
		 */
		addon_notify_return(g, dummy, 999, ret, FLAG_EXACT);
	} else if (nvalid == 1 && alpha < beta && copts.forced_extend) {
		__unused bool check;
		check = doMove(ng, gsuccs[bestmove].m);
		assert(check);

		alpha = alpha_orig;
		mark(ng);
		ply++;
		t = -negamax(ng, maxDepth+1, curDepth+1, NULL, -beta, -alpha);
		ply--;
		unmark(ng);

		if (t > alpha)
			alpha = t;

		ret = alpha;
	} else {
		flag_t flag;

		assert(bestmove != -1);

		if (mm)
			*mm = gsuccs[bestmove].m;

		/*
		 * Devolver alpha o best es lo mismo (o son ambos menores o
		 * iguales a alpha_orig o son iguales) pero en la TT debemos
		 * guardar ${WHAT} porque ${REASON}
		 */
		assert(best == alpha ||
				(best < alpha_orig && alpha == alpha_orig));

		ret = best;

		if (best <= alpha_orig)
			flag = FLAG_UPPER_BOUND;
		else if (best > beta)
			flag = FLAG_LOWER_BOUND;
		else
			flag = FLAG_EXACT;

		if (maxDepth - curDepth > 1) {
			addon_notify_return(g, gsuccs[bestmove].m,
					    maxDepth - curDepth, ret, flag);
		}
	}

	freeGame(ng);

out:
	if (mm)
		assert(mm->move_type != MOVE_INVAL);

	assert(timeup || ret > minScore);
	assert(timeup || ret < maxScore);

	return ret;
}

score search(game g, int maxDepth, move *mm, score alpha, score beta) {
	return negamax(g, maxDepth, 0, mm, alpha, beta);
}
