#include <stdbool.h>
#include <stdio.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"

static bool selector_matches(const struct string *pattern, const struct action *action) {
	size_t p = 0, s = 0;
	size_t current_arg = 0;
	const struct string *selector = &action->selector;
	while (p < pattern->length) {
		if (pattern->data[p] == '$') {
			if (current_arg == action->arg_count || action->arg_indexes[current_arg] != s) {
				return false;
			}
			while (p < pattern->length && pattern->data[p] != ' ') {
				p++;
			}
			current_arg++;
		} else if (s < selector->length) {
			if (pattern->data[p] != selector->data[s]) {
				return false;
			}
			p++;
			s++;
		} else {
			break;
		}
	}
	return p == pattern->length && s == selector->length;
}

static struct string write_line_selector;

static struct string *eval(struct syntax_tree *tree) {
	switch (tree->kind) {
	case syntax_tree_kind_literal:
		return string_clone(&tree->u.literal);
		break;
	case syntax_tree_kind_action:
		if (selector_matches(&write_line_selector, &tree->u.action)) {
			struct string *s = eval(tree->u.action.args[0]);
			printf("%*s\n", (int) s->length, s->data);
			string_free(s);
			return 0;
		} else {
			log_error("Unrecognized selector %*s", (int) tree->u.action.selector.length, tree->u.action.selector.data);
			return 0;
		}
		break;
	default:
		log_error("Unrecognized kind %d", tree->kind);
		return 0;
	}
}

static void interp(struct syntax_tree *tree) {
	string_free(eval(tree));
}

int main() {
	string_init_empty(&write_line_selector);
	string_add_c_string(&write_line_selector, "write line $1");
	for (;;) {
		struct syntax_tree *tree = parse();
		if (tree) {
			interp(tree);
			syntax_tree_free(tree);
		} else {
			break;
		}
	}	
}
