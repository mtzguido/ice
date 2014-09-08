#include "search.h"
#include "board.h"
#include "addon.h"
#include "ztable.h"
#include "common.h"
#include "ai.h"
#include "eval.h"
#include <stdbool.h>

score negamax(int curDepth, int maxDepth, move *mm, score alpha, score beta);
score _negamax(int curDepth, int maxDepth, move *mm, score alpha, score beta);

static inline void shuffle_succs() {
	struct MS swap;
	const int lo = first_succ[ply];
	const int hi = first_succ[ply+1];
	int i, j;

	if (!copts.shuffle)
		return;

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
	game bak = G;
	G = g;

	/* Generar sucesores */
	genSuccs(g);
	stats.ngen += first_succ[ply+1] - first_succ[ply];

	addon_score_succs(depth);

	/* Mezclarlos si es necesario */
	shuffle_succs();
	G = bak;
}

static inline void genCaps_wrap(game g, int depth) {
	game bak = G;
	G = g;

	genCaps(g);
	stats.ngen += first_succ[ply+1] - first_succ[ply];

	addon_score_succs(depth);
	G = bak;
}


/*
 * Ordena el arreglo de sucesores de manera lazy.
 * Deja en arr[i] el sucesor correcto, asume que arr[0..i-1] ya
 * está ordenado.
 */
static inline void sort_succ(game g, int i) {
	int j;
	int best;

	assert(gsuccs[i].m.who == g->turn);
	assert(i >= first_succ[ply]);
	assert(i < first_succ[ply+1]);

	score s = gsuccs[i].s;
	best = i;

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

	assert(gsuccs[i].m.who == g->turn);
	assert(gsuccs[i].m.move_type != MOVE_INVAL);
	assert(gsuccs[i].s >= 0);
}

static inline int calcExtension(int maxDepth, int curDepth) {
	int ret = 0;

	if (inCheck(G, G->turn) || G->lastmove.promote != EMPTY)
		ret++;

	return ret;
}

static inline score null_move_score(game g, int curDepth, int maxDepth,
				    score alpha, score beta) {
	static bool doing_null_move = false;
	score t;
	game ng;
	game bak;
	move m = { .move_type = MOVE_NULL, .who = g->turn };
	__unused bool check;

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
	if (maxDepth - curDepth <= NMH_REDUCTION)
		goto dont;

	bak = G;
	ng = copyGame(g);
	G = ng;
	check = doMove(ng, m);

	/*
	 * doMoveNull's only restriction is not being in check and we already
	 * provided a case for that so this should never fail
	 */
	assert(check);

	stats.null_tries++;

	mark(ng);
	first_succ[ply+1] = first_succ[ply];
	ply++;
	doing_null_move = true;

	t = -negamax(maxDepth - NMH_REDUCTION, curDepth+1, NULL, -beta, -alpha);

	doing_null_move = false;

	ply--;
	unmark(ng);

	freeGame(ng);
	G = bak;
	return t;

dont:
	return alpha;
}

static inline score quiesce(game g, score alpha, score beta, int curDepth) {
	int nvalid, i;
	game ng;
	game bak = G;
	score ret, t;

	assert(ply == curDepth);

	if (timeup) {
		ret = 0;
		goto out;
	} else if (timelimited) {
		ticks++;

		if ((ticks & 0xfff) == 0) {
			if (getms() >= timelimit) {
				timeup = true;
				ret = 0;
				goto out;
			}
		}
	}

	if (isDraw(g) || reps(g) >= 2) {
		ret = 0;
		goto out;
	}

	stats.nopen_q++;

	G = g;
	t = boardEval();
	G = bak;

	if (t >= beta) {
		ret = beta;
		goto out;
	}

	if (copts.delta_prune) {
		score delta = QUEEN_SCORE - PAWN_SCORE;

		if (g->lastmove.promote != EMPTY)
			delta += QUEEN_SCORE;

		if (t + delta < alpha) {
			ret = alpha;
			goto out;
		}
	}

	if (t > alpha)
		alpha = t;

	if (ply >= MAX_PLY-1) {
		ret = t;
		goto out;
	}

	ng = copyGame(g);
	genCaps_wrap(g, curDepth);
	nvalid = 0;
	for (i = first_succ[ply]; i < first_succ[ply+1]; i++) {
		sort_succ(g, i);
		const move m = gsuccs[i].m;

		assert(m.move_type == MOVE_REGULAR);

		/* We only consider captures and promotions */
		assert(isCapture(g, m) || isPromotion(g, m));

		if (!doMove_unchecked(ng, m))
			continue;

		nvalid++;

		mark(ng);
		ply++;
		t = -quiesce(ng, -beta, -alpha, curDepth+1);
		ply--;
		unmark(ng);
		*ng = *g;

		if (t > alpha) {
			if (t >= beta) {
				ret = beta;
				freeGame(ng);
				goto out;
			}

			alpha = t;
		}
	}
	freeGame(ng);

	if (nvalid == 0)
		ret = t;
	else
		ret = alpha;

out:

	assert(G == bak);
	assert(timeup || ret > minScore);
	assert(timeup || ret < maxScore);

	return ret;
}

score negamax(int maxDepth, int curDepth, move *mm, score alpha,
		score beta) {
	__unused game bak = G;
	__unused u64 h = G->zobrist;
	score ret;

	ret = _negamax(maxDepth, curDepth, mm, alpha, beta);

	assert(G == bak);
	assert(G->zobrist == h);
	return ret;
}

score _negamax(int maxDepth, int curDepth, move *mm, score alpha,
		score beta) {
	static bool doing_lmr = false;
	score t, ret, best, alpha_orig;
	int i;
	int ext;
	int nvalid = 0;
	game ng;
	game bak = G;
	int bestmove = -1;

	stats.nall++;

	assert(ply == curDepth);

	ng = copyGame(G);
	G = ng;

	if (timeup) {
		ret = 0;
		goto out;
	} else if (timelimited) {
		ticks++;

		if ((ticks & 0xfff) == 0) {
			if (getms() >= timelimit) {
				timeup = true;
				ret = 0;
				goto out;
			}
		}
	}

	/*
	 * The absolute best we can ever do is CHECKMATE_SCORE - curDepth -
	 * 1, so use it as a bound. This causes the search to run a lot more
	 * quickly in the final endgame.
	 */
	if (alpha >= CHECKMATE_SCORE - curDepth - 1) {
		ret = alpha;
		goto out;
	}

	if (isDraw(G)) {
		ret = 0;
		goto out;
	}

	/*
	 * Si ya pasamos por este tablero, podemos asumir
	 * que vamos a reaccionar igual y vamos a llevar a un empate
	 * por repetición.
	 */
	if (reps(G) >= 2 && !mm) {
		ret = 0;
		goto out;
	}

	ext = calcExtension(maxDepth, curDepth);
	maxDepth += ext;

	/*
	 * Corte por profundidad, hacemos búsqueda por quietud, para
	 * mejorar nuestra evaluación de tablero.
	 */
	if (curDepth >= maxDepth) {
		assert(!mm);
		assert(curDepth == maxDepth);

		/*
		 * Si esto ocurre, tenemos una recursion mutua
		 * infinita con quiesce. No debería ocurrir nunca,
		 * pero dejamos el assert por las dudas.
		 */
		assert(!inCheck(G, G->turn));

		if (copts.quiesce)
			ret = quiesce(G, alpha, beta, curDepth);
		else
			ret = boardEval();

		goto out;
	}

	/*
	 * Only try to null-move if beta was less than maxScore.
	 * Otherwise we will never suceed in the test.
	 */
	if (!mm && beta < maxScore) {
		t = null_move_score(G, curDepth, maxDepth, alpha, beta);
		if (t >= beta) {
			stats.null_cuts++;
			ret = beta;
			goto out;
		}
	}

	if (!mm)
		addon_notify_entry(maxDepth - curDepth, &alpha, &beta);

	if (alpha >= beta && copts.ab) {
		/* Deshabilitado por ahora */
		assert(0);
		ret = alpha;
		assert(!mm);
		goto out;
	}

	if (ply >= MAX_PLY-1) {
		ret = boardEval();
		goto out;
	}

	alpha_orig = alpha;
	best = minScore;

	stats.nopen_s++;
	stats.depthsn[curDepth]++;

	assert(ng->zobrist == G->zobrist);
	genSuccs_wrap(G, curDepth);

	for (i = first_succ[ply]; i < first_succ[ply+1]; i++) {
		sort_succ(G, i);
		const move m = gsuccs[i].m;

		assert(ng->zobrist == G->zobrist);
		if (!doMove_unchecked(ng, m))
			continue;

		nvalid++;

		mark(ng);

		/* LMR */
		if (copts.lmr
			&& !doing_lmr
			&& i >= first_succ[ply] + LMR_FULL
			&& curDepth >= LMR_MINDEPTH
			&& maxDepth - curDepth >= 2
			&& gsuccs[i].s*10 < gsuccs[first_succ[ply]].s /* 2x crap */
			&& ext == 0
			&& !inCheck(ng, ng->turn)
			&& !isCapture(bak, m)
			&& !isPromotion(bak, m)) {
			stats.lmrs++;

			doing_lmr = true;
			ply++;
			t = -negamax(maxDepth-1, curDepth+1, NULL, -beta, -alpha);
			ply--;
			doing_lmr = false;

			/* Do a full search if it didn't fail low */
			if (t > alpha) {
				ply++;
				t = -negamax(maxDepth, curDepth+1, NULL,
					     -beta, -alpha);
				ply--;
			} else {
				stats.lmrs_ok++;
			}
		} else {
			ply++;
			t = -negamax(maxDepth, curDepth+1, NULL, -beta, -alpha);
			ply--;
		}

		unmark(ng);

		/* Ya no necesitamos a ng */
		*ng = *bak;

		if (t > best) {
			best = t;
			bestmove = i;
		}

		if (t > alpha)
			alpha = t;

		if (alpha >= beta && copts.ab) {
			addon_notify_cut(m, curDepth);
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

		if (inCheck(G, G->turn))
			ret = -CHECKMATE_SCORE + curDepth;
		else
			ret = 0; /* Stalemate */

		/*
		 * Lo guardamos en la TT, podría ahorrar unos
		 * pocos ciclos
		 */
		addon_notify_return(dummy, 999, ret, FLAG_EXACT);
	} else if (nvalid == 1 && alpha < beta && copts.forced_extend) {
		__unused bool check;
		check = doMove(ng, gsuccs[bestmove].m);
		assert(check);

		alpha = alpha_orig;
		mark(ng);
		ply++;
		t = -negamax(maxDepth+1, curDepth+1, NULL, -beta, -alpha);
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
			addon_notify_return(gsuccs[bestmove].m,
					    maxDepth - curDepth, ret, flag);
		}
	}

out:
	freeGame(ng);
	G = bak;

	if (mm)
		assert(mm->move_type != MOVE_INVAL);

	assert(timeup || ret > minScore);
	assert(timeup || ret < maxScore);

	return ret;
}

score search(int maxDepth, move *mm, score alpha, score beta) {
	alpha = clamp(alpha, 1-CHECKMATE_SCORE, CHECKMATE_SCORE-1);
	beta  = clamp(beta , 1-CHECKMATE_SCORE, CHECKMATE_SCORE-1);
	assert(ply == 0);
	return negamax(maxDepth, 0, mm, alpha, beta);
}
