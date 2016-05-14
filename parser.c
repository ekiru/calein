#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#include "err.h"
#include "str.h"
#include "syntax.h"

struct syntax_tree *parse(void) {
	int c;
	for (;;) {
		c = getc(stdin);
		if (c == EOF) {
			return 0;
		}
		if (c == '"') {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_literal); 
			if (!tree) {
				return 0;
			}
			string_init_empty(&tree->u.literal);
			
			bool in_escape = false;
			for (;;) {
				c = getc(stdin);
				if (c == EOF) {
					log_error("Parse error: unterminated string literal.");
					goto literal_err;
				}
				if (in_escape) {
					if (c == '\\' || c == '"') {
						if (!string_add_character(&tree->u.literal, c)) {
							goto literal_err;
						}
					} else if (c == 'n') {
						if (!string_add_character(&tree->u.literal, '\n')) {
							goto literal_err;
						}
					} else {
						log_error("Parse error: undefine escape sequence \\%c",
							c);
						goto literal_err;
					}
					in_escape = false;
				} else if (c == '\\') {
					in_escape = true;
				} else if (c == '"') {
					return tree;
				} else {
					if (!string_add_character(&tree->u.literal, c)) {
						goto literal_err;
					}
				}
			}
		literal_err:
			syntax_tree_free(tree);
			return 0;
		} else if (isspace(c)) {
			continue;
		} else {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_action);
			string_init_empty(&tree->u.action.selector);
			ungetc(c, stdin);
			for (;;) {
				c = getc(stdin);
				if (c == EOF || c == '.' || c == ')') {
					if (tree->u.action.arg_count == 0 || tree->u.action.arg_indexes[tree->u.action.arg_count-1] < tree->u.action.selector.length) {
						string_trim_right(&tree->u.action.selector);
					}
					if (c == ')') {
						ungetc(c, stdin);
					}
					return tree;
				} else if (c == '"' || c == '(') {
					bool paren = c == '(';
					if (tree->u.action.arg_count == syntax_tree_max_args) {
						log_error("Parse error: exceed max arg count %d",
							syntax_tree_max_args);
						goto action_err;
					}
					if (c == '"') {
						ungetc(c, stdin);
					}
					struct syntax_tree *child = parse();
					if (!child) {
						log_error("Parse error: expected argument");
						goto action_err;
					}
					//printf("Adding arg %lu at %lu\n", tree->u.action.arg_count, tree->u.action.selector.length);
					tree->u.action.arg_indexes[tree->u.action.arg_count] =
						tree->u.action.selector.length;
					tree->u.action.args[tree->u.action.arg_count] = child;
					tree->u.action.arg_count++;
					if (paren && getc(stdin) != ')') {
						log_error("Subexpression had no close paren.");
						goto action_err;
					}
				} else if (isspace(c)) {
					if (tree->u.action.selector.length == 0 || tree->u.action.selector.data[tree->u.action.selector.length-1] != ' '
					    || (tree->u.action.arg_count != 0 && tree->u.action.selector.length == tree->u.action.arg_indexes[tree->u.action.arg_count-1])) {
						if (!string_add_character(&tree->u.action.selector, ' ')) {
							goto action_err;
						}
					}
				} else {
					if (!string_add_character(&tree->u.action.selector, c)) {
						goto action_err;
					}
				}
			}
		action_err:
			syntax_tree_free(tree);
			return 0;
		}
	}
}
