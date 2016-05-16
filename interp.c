#include <stdbool.h>
#include <stdio.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"

struct definition {
	struct string pattern;
	bool is_primitive;
	struct string *(*primitive)(const struct action *action);
	struct definition *previous;
};

static struct string *eval(struct syntax_tree *tree);

static struct string *primitive_write_line(const struct action *action) {
	struct string *s = eval(action->args[0]);
	printf("%*s\n", (int) s->length, s->data);
	string_free(s);
	return 0;
}

static struct string *primitive_write(const struct action *action) {
	struct string *s = eval(action->args[0]);
	printf("%*s", (int) s->length, s->data);
	string_free(s);
	return 0;
}

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


static struct definition *environment;

static struct string *eval(struct syntax_tree *tree) {
	switch (tree->kind) {
	case syntax_tree_kind_literal:
		return string_clone(&tree->u.literal);
		break;
	case syntax_tree_kind_action:
		for (struct definition *def = environment; def; def = def->previous) {
			if (selector_matches(&def->pattern, &tree->u.action)) {
				if (def->is_primitive) {
					return def->primitive(&tree->u.action);
				} else {
					//return apply(def->body, &tree->u.action);
					log_error("Non-primitive actions not yet implemented.");
					return 0;
				}
			}
		}
		log_error("Unrecognized selector %*s", (int) tree->u.action.selector.length, tree->u.action.selector.data);
		return 0;
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
	struct definition write_line_definition;
	write_line_definition.previous = 0;
	write_line_definition.is_primitive = true;
	write_line_definition.primitive = primitive_write_line;
	string_init_empty(&write_line_definition.pattern);
	string_add_c_string(&write_line_definition.pattern, "write line $1");
	struct definition write_definition;
	write_definition.previous = &write_line_definition;
	write_definition.is_primitive = true;
	write_definition.primitive = primitive_write;
	string_init_empty(&write_definition.pattern);
	string_add_c_string(&write_definition.pattern, "write $1");

	environment = &write_definition;
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
