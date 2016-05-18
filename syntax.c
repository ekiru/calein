#include "syntax.h"

#include <stdlib.h>
#include <stdio.h>

#include "err.h"

struct syntax_tree *syntax_tree_new(enum syntax_tree_kind kind) {
	struct syntax_tree *tree = calloc(1, sizeof *tree);
	if (tree) {
		tree->kind = kind;
	} else {
		log_error("Failed to allocate memory for syntax tree");
	}
	return tree;
}

void syntax_tree_free(struct syntax_tree *tree) {
	if (tree) {
		if (tree->kind == syntax_tree_kind_literal) {
			string_finish(&tree->u.literal);
		} else if (tree->kind == syntax_tree_kind_action) {
			string_finish(&tree->u.action.selector);
			for (int i = 0; i < tree->u.action.arg_count; i++) {
				syntax_tree_free(tree->u.action.args[i]);
			}
		}
		free(tree);
	}
}

struct syntax_tree *syntax_tree_clone(const struct syntax_tree *tree) {
	struct syntax_tree *copy = calloc(1, sizeof *copy);
	if (copy) {
		switch (tree->kind) {
		case syntax_tree_kind_literal:
			copy->kind = syntax_tree_kind_literal;
			if (!string_copy(&copy->u.literal, &tree->u.literal)) {
				free(copy);
				return 0;
			}
			break;
		case syntax_tree_kind_action:
			copy->kind = syntax_tree_kind_action;
			if (!string_copy(&copy->u.action.selector, &tree->u.action.selector)) {
				free(copy);
				return 0;
			}
			for (size_t i = 0; i < tree->u.action.arg_count; i++) {
				copy->u.action.args[i] = syntax_tree_clone(tree->u.action.args[i]);
				if (!copy->u.action.args[i]) {
					syntax_tree_free(copy);
					return 0;
				}
				copy->u.action.arg_indexes[i] = tree->u.action.arg_indexes[i];
				copy->u.action.arg_count++;
			}
			break;
		default:
			break;
		}
	}
	return copy;
}

static void print_indent(size_t times) {
	for (;times; times--) {
		putchar('\t');
	}
}

static void display_with_indent(const struct syntax_tree *tree, size_t indent) {
	switch (tree->kind) {
	case syntax_tree_kind_literal:
		print_indent(indent);
		printf("String literal: %*s\n", (int) tree->u.literal.length, tree->u.literal.data);
		break;
	case syntax_tree_kind_action:
		print_indent(indent);
		printf("Action: ");
		size_t current_arg = 0;
		for (size_t i = 0; i < tree->u.action.selector.length; i++) {
			if (current_arg < tree->u.action.arg_count &&
			    i == tree->u.action.arg_indexes[current_arg]) {
				printf("$%lu", current_arg + 1);
				current_arg++;
			}
			putchar(tree->u.action.selector.data[i]);
		}
		if (current_arg < tree->u.action.arg_count &&
			tree->u.action.selector.length == tree->u.action.arg_indexes[current_arg]) {
			printf("$%lu", current_arg + 1);
			current_arg++;
		}
		putchar('\n');
		for (size_t i = 0; i < tree->u.action.arg_count; i++) {
			display_with_indent(tree->u.action.args[i], indent+1);
		}
		break;
	default:
		print_indent(indent);
		printf("Unrecognized kind %d\n", tree->kind);
	}
}

void syntax_tree_display(const struct syntax_tree *tree) {
	display_with_indent(tree, 0);
}
