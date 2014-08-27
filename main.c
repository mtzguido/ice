#include "ai.h"
#include "board.h"
#include "pgn.h"
#include "mem.h"
#include "ztable.h"
#include "succs.h"
#include "user_input.h"
#include "common.h"
#include "opts.h"
#include "autoversion.h"

#include <syslog.h>
#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static game startingGame2() {
	game g;

	if (copts.custom_start) {
		g = fromstr(copts.custom_start_str);
		printBoard(g);
	} else {
		g = startingGame();
	}

	return g;
}

static int nmoves() {
	int i;
	game g;
	move m;

	init_mem();
	g = startingGame2();
	mark(g);

	for (i=0; i<copts.nmoves; i++) {

		if (isFinished(g) != -1)
			break;

		assert(ply == 0);
		m = machineMove(g);
		assert(ply == 0);
		doMove(g, m);
		mark(g);
		printBoard(g);
		printMove(stdout, m);

		dbg("Moves %i/%i\n", i+1, copts.nmoves);
	}

	return 0;
};

static int board_eval_mode() {
	game g = startingGame2();
	dbg("Board evaluation: %i\n", boardEval(g));
	return 0;
}

static int checkMove(game g, move m) {
	game ng;
	int i;

	/*
	 * Fix promotions to Knights or Queens,
	 * we don't care about not generating rook/bishop
	 * promotions. Fairymax doesn't even care about
	 * knights so we're being extra kind here.
	 */
	if (isPromotion(g, m) && m.promote != WKNIGHT)
		m.promote = WQUEEN;

	ng = copyGame(g);
	int rc = doMove(ng, m);
	freeGame(ng);

	if (rc != true)
		return 1;

	if (isCapture(g, m) || isPromotion(g, m))
		genCaps(g);
	else
		genSuccs(g);

	for (i=first_succ[ply]; i<first_succ[ply+1]; i++) {
		if (equalMove(m, gsuccs[i].m))
			return 0;
	}

	/*
	 * We didn't anticipate that move, just call it illegal
	 * like a good proud player and try to carry on
	 */
	printf("Illegal move\n");
	return 1;
}

__unused
static void logToBook(game g, move m) {
	static FILE *game_log = NULL;
	static int movenum = 1;
	struct pgn pp;
	char mbuf[10];

	if (!copts.log)
		return;

	if (game_log == NULL)
		game_log = fopen("gamelog", "w");

	pp = toPGN(g, m);
	stringPGN(mbuf, pp);

	fprintf(game_log, "%i. %s ", movenum, mbuf);

	if (movenum % 2 == 0)
		fprintf(game_log, "\n");

	movenum++;
}

static void xboard_printmove(move m) {
	printMove(stdout, m);
}

static void sigterm(__unused int n) {
	dbg("Received SIGTERM!\n");
}

static void xboard_main() {
	int curPlayer = WHITE;
	int ourPlayer = BLACK;
	char buf[500];
	char cmd[500];
	game g;

	/* Ignore SIGINT, because xboard is a crappy protocol */
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, sigterm);

	printf("tellics say dogui's chess engine\n");
	printf("tellics say Written by Guido Martínez, 2014\n");

	init_mem();
	g = startingGame();
	mark(g);

	for (;;) {
		if (isFinished(g) == -1 && curPlayer == ourPlayer) {
			__unused bool check;
			move m = machineMove(g);

			check = doMove(g, m);
			mark(g);
			assert(check);

			xboard_printmove(m);
			curPlayer = flipTurn(curPlayer);
			continue;
		}

		printBoard(g);
		dbg("expecting input...\n");

		if (!fgets(buf, sizeof buf, stdin)) {
			fprintf(stderr, "Unexpected end of input\n");
			exit(1);
		}

		if (buf[0] == '\n')
			continue;

		sscanf(buf, "%s", cmd);

		if (buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;

		dbg("received: <%s>, cmd = %s\n", buf, cmd);

		if (!strcmp("new", cmd)) {
			freeGame(g);
			g = startingGame();
		} else if (!strcmp("go", cmd)) {
			ourPlayer = curPlayer;
		} else if (!strcmp("black", cmd)) {
		} else if (!strcmp("computer", cmd)) {
		} else if (!strcmp("easy", cmd)) {
		} else if (!strcmp("force", cmd)) {
			ourPlayer = 2; /* No one */
		} else if (!strcmp("hard", cmd)) {
		} else if (!strcmp("level", cmd)) {
		} else if (!strcmp("nopost", cmd)) {
		} else if (!strcmp("otim", cmd)) {
		} else if (!strcmp("post", cmd)) {
		} else if (!strcmp("protver", cmd)) {
		} else if (!strcmp("st", cmd)) {
		} else if (!strcmp("quit", cmd)) {
			break;
		} else if (!strcmp("random", cmd)) {
		} else if (!strcmp("result", cmd)) {
		} else if (!strcmp("undo", cmd)) {
			dbg("Ignoring undo command\n");
		} else if (!strcmp("white", cmd)) {
		} else if (!strcmp("white", cmd)) {
		} else if (!strcmp("xboard", cmd)) {
		} else if (!strcmp("?", cmd)) {
		} else {
			__unused bool check;
			/* It's likely a move, try to parse it */
			dbg("is it a move?\n");
			move m = parseMove(g, buf);

			/* Couldn't parse it */
			if (m.move_type == MOVE_INVAL) {
				printf("Error (unknown command): %s\n", buf);
				continue;
			}

			if (checkMove(g, m)) {
				printf("Error (illegal move): %s\n", buf);
				continue;
			}

			check = doMove(g, m);
			assert(check);
			mark(g);
			curPlayer = flipTurn(curPlayer);
		}
	}
}

int main(int argc, char **argv) {
	if (!parse_opt(argc, argv)) {
		fprintf(stderr, "FATAL: could not parse options\n");
		exit(1);
	}

	dbg("random seed: %u\n", copts.seed);
	srand(copts.seed);

	switch (copts.mode) {
	case xboard:
		xboard_main();
		break;

	case moves:
		nmoves();
		break;

	case board_eval:
		board_eval_mode();
		break;

	case version:
		print_version();
		exit(0);
		break;

	case help:
		print_help(argv[0]);
		exit(0);
		break;
	}

	dbg("Total nodes: %lld\n", stats.totalopen);
	dbg("Total time: %lldms\n", stats.totalms);
	return 0;
}
