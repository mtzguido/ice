#include "opts.h"
#include "common.h"
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BOOL_OPT2(name, var)					\
	{ #name, no_argument, &copts.var, 1 },			\
	{ "no-" #name, no_argument, &copts.var, 0 }
#define BOOL_OPT(name) BOOL_OPT2(name, name)

#define INT_OPT2(name, name2)					\
	{ #name, required_argument, NULL, OPT_##name2 }

#define INT_OPT(name)	INT_OPT2(name, name)

#define MAYBE_INT_OPT(name)					\
	{ #name, optional_argument, NULL, OPT_##name }

#define MODE_OPT(name, value)					\
	{ #name, no_argument, &copts.mode, value }

enum {
	/* int */
	OPT_base = 5000,
	OPT_depth,
	OPT_seed,
	OPT_limit,
	OPT_lbound,
	OPT_bit_seed,
	OPT_verbose,
	OPT_pps,
};

static const struct option long_opts[] = {
	/* Program modes, totally exclusive */
	MODE_OPT(xboard, xboard),
	{ "moves",	required_argument,	0, 0x1 },
	MODE_OPT(eval, board_eval),
	MODE_OPT(help, help),
	MODE_OPT(version, version),
	MODE_OPT(bench-eval, bench_eval),
	MODE_OPT(bench-search, bench_search),
	MODE_OPT(bench-bits, bench_bits),
	MODE_OPT(11n-table, h11n_table),
	MODE_OPT(print-sizes, print_sizes),

	/* Game parameters */
	{ "init",	required_argument,	0, 0x2 },

	/* Search options */
	INT_OPT(depth),
	INT_OPT(seed),
	INT_OPT(limit),
	INT_OPT(lbound),
	INT_OPT2(bit-seed, bit_seed),
	MAYBE_INT_OPT(verbose),
	INT_OPT(pps),

	BOOL_OPT(lazy),
	BOOL_OPT(shuffle),
	BOOL_OPT(ab),
	BOOL_OPT(quiesce),
	BOOL_OPT(book),
	BOOL_OPT(asp),
	BOOL_OPT2(forced-extend, forced_extend),
	BOOL_OPT2(delta, delta_prune),
	BOOL_OPT2(smart-stop, smart_stop),
	BOOL_OPT(null),
	BOOL_OPT2(11n, h11n),
	BOOL_OPT(lmr),
	BOOL_OPT(syslog),
	{ 0 }
};

static int sanity_check() {
	if (copts.depth < 0) {
		fprintf(stderr, "error: depth can't be negative\n");
		return 0;
	}

	return 1;
}

int parse_opt(int argc, char **argv) {
	int c, idx;

	copts = defopts;
	copts.seed = time(NULL) + getpid();

	while (c = getopt_long(argc, argv, "", long_opts, &idx), c != -1) {
		switch (c) {
		case OPT_depth:
			copts.depth = atoi(optarg);
			break;
		case OPT_seed:
			copts.seed = atoi(optarg);
			break;
		case OPT_limit:
			copts.timelimit = atoi(optarg);
			break;
		case OPT_lbound:
			copts.lbound = atoi(optarg);
			break;
		case OPT_bit_seed:
			copts.bit_seed = strtoul(optarg, NULL, 0);
			break;
		case OPT_verbose:
			if (optarg)
				copts.verbosity = atoi(optarg);
			else
				copts.verbosity = 1;
			break;
		case OPT_pps:
			copts.pps = atoi(optarg);
			break;
		case 0x1:
			copts.mode = moves;
			copts.nmoves = atoi(optarg);
			break;

		case 0x2:
			copts.custom_start = true;
			strcpy(copts.custom_start_str, optarg);
			break;

		/* 0 means the assignment was handled internally */
		case 0:
			break;

		case '?':
		default:
			return 0;
		}
	}

	return sanity_check();
}

void print_help(char *progname) {
	fprintf(stderr, "usage: %s <opts>\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "<opts> can be any combination of:\n");
	fprintf(stderr, "	... etcetera ...\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "if an option appears more than once, or it invalidates another one,\n");
	fprintf(stderr, "only the latter one will be taken into account.\n");
}
