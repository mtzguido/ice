#ifndef __AI_H
#define __AI_H

#include "board.h"

extern struct stats {
	long long depthsn[100];
	long long picked[100];
	long long nopen_s;
	long long nopen_q;
	long long nall;
	long long ngen;
	long long totalopen;
	long long totalms;
	long long null_cuts;
	long long null_tries;
	long long tt_hits;
	long long tt_collision;
	long long lmrs;
	long long lmrs_ok;
} stats;

move machineMove(game start, unsigned long long maxms);

score boardEval(game g);

/* Board evaluation scores */
#define ROOK_OPEN_FILE		15
#define ROOK_SEMI_OPEN_FILE	10
#define DOUBLED_PAWN		(-10)
#define ISOLATED_PAWN		(-20)
#define BACKWARDS_PAWN		(-8)
#define PASSED_PAWN		20
#define INCHECK			(-100)
#define DOUBLE_BISHOP		15
#define KNIGHT_ENDGAME		(-10)

/* Define a fuzzy threshold for boards near 50 idle moves */
#define FIFTYMOVE_THRESHOLD	32

/* Castling penalties */
#define CASTLE_NN		(-15)
#define CASTLE_NY		(-12)
#define CASTLE_YN		(-8)
#define CASTLE_YY		(-5)

/* Move ordering scores */
#define CAPT_SCORE		200
#define PROMOTE_SCORE		300
#define CM_SCORE		500
#define KILLER_SCORE		1000
#define TRANS_SCORE		10000

/* Heuristics config */
#define NMH_THRESHOLD		1500
#define ASPIRATION_WINDOW	25

/* Misc tunables */
#define SORT_DEPTH_THRESHOLD	0

#endif
