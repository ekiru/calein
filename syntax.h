#ifndef CLN_SYNTAX_H
#define CLN_SYNTAX_H

#include <stdlib.h>

#include "str.h"

enum syntax_tree_kind {
	syntax_tree_kind_invalid,
	syntax_tree_kind_literal,
	syntax_tree_kind_action,
};

static const size_t syntax_tree_max_args = 10;

struct action {
	struct string selector;
	size_t arg_count;
	size_t arg_indexes[syntax_tree_max_args];
	struct syntax_tree *args[syntax_tree_max_args];
};

struct syntax_tree {
	enum syntax_tree_kind kind;
	union {
		struct string literal;
		struct action action;
	} u;
};

struct syntax_tree *syntax_tree_new(enum syntax_tree_kind kind);
void syntax_tree_free(struct syntax_tree *tree);

void syntax_tree_display(const struct syntax_tree *tree);

#endif
