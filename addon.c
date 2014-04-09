#include "addon.h"
#include <assert.h>

#define MAX_ADDON 10

struct addon enabled_addons[MAX_ADDON] = {{ NULL }};
unsigned n_addon = 0;

void addon_register(struct addon sa) {
	assert(n_addon < MAX_ADDON);
	enabled_addons[n_addon++] = sa;
}

void addon_reset() {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.reset != NULL)
			a.reset();
	}
}

void addon_notify_return(game g, move m, score s, int depth) {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.notify_return != NULL)
			a.notify_return(g, m, s, depth);
	}
}

bool addon_notify_entry(game g, int depth, score *ret) {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.notify_entry != NULL)
			if (a.notify_entry(g, depth, ret))
				return true;
	}

	return false;
}

void addon_notify_cut(game g, move m, int depth) {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.notify_cut != NULL)
			a.notify_cut(g, m, depth);
	}
}

void addon_score_succs(game g, const game *succs,
		       score *vals, int nsucc, int depth) {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.score_succs != NULL)
			a.score_succs(g, succs, vals, nsucc, depth);
	}
}

void addon_free_mem() {
	int i;

	for (i=0; i<n_addon; i++) {
		struct addon a = enabled_addons[i];

		if (a.free_mem != NULL)
			a.free_mem();
	}
}