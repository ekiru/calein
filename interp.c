#include <stdbool.h>
#include <stdio.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"

struct definition {
	struct action pattern;
	bool is_primitive;
	struct string *(*primitive)(const struct action *action);
	struct definition *previous;
	struct syntax_tree *body;
};

static struct definition *environment;

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

static struct string *primitive_define_procedure(const struct action *action) {
	struct definition *def = calloc(1, sizeof *def);
	if (def) {
		if (!action_copy(&def->pattern, &action->args[0]->u.action)
			|| !(def->body = syntax_tree_clone(action->args[1]))) {
			syntax_tree_free(def->body);
			action_finish(&def->pattern);
			free(def);
		}
		def->previous = environment;
		def->is_primitive = false;
		environment = def;
	} else {
		log_error("Failed to allocate memory to define procedure.");
	}
	return 0;
}

static bool selector_matches(const struct action *pattern, const struct action *action) {
	size_t p = 0, s = 0;
	size_t current_arg = 0;
	if (!string_equals(&pattern->selector, &action->selector)
	    || pattern->arg_count != action->arg_count) {
		return false;
	}
	for (size_t i = 0; i < pattern->arg_count; i++) {
		if (pattern->arg_indexes[i] != action->arg_indexes[i]) {
			return false;
		}
	}
	return true;
}

static struct string *apply(struct syntax_tree *body, struct action *args) {
	return eval(body);
}

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
					return apply(def->body, &tree->u.action);
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

static bool define_primitive(
	struct definition *def,
	const char *pattern, 
	struct string *(*f)(const struct action *action)) {
	struct syntax_tree *pattern_tree = parse_string(pattern);
	if (pattern_tree && action_copy(&def->pattern, &pattern_tree->u.action)) {
		def->previous = environment;
		def->is_primitive = true;
		def->primitive = f;
		environment = def;
		syntax_tree_free(pattern_tree);
		return true;
	} else {
		syntax_tree_free(pattern_tree);
		return false;
	}
}

int main() {
	environment = 0;
	struct definition write_line_definition;
	struct definition write_definition;
	struct definition define_procedure_definition;
	if (!define_primitive(&write_line_definition, "write line (msg)", primitive_write_line)
	    || !define_primitive(&write_definition, "write (msg)", primitive_write)
	    || !define_primitive(&define_procedure_definition, "define procedure (pattern) to do (body)", primitive_define_procedure)) {
		log_error("Failed to define primitives.");
		return 1;
	}

	for (;;) {
		struct syntax_tree *tree = parse();
		if (tree) {
			interp(tree);
			syntax_tree_free(tree);
		} else {
			break;
		}
	}	
	return 0;
}
