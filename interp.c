#include <stdbool.h>
#include <stdio.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"

enum definition_kind {
	definition_kind_primitive,
	definition_kind_action,
	definition_kind_value,
};

struct definition {
	enum definition_kind kind;
	struct action pattern;
	struct string *(*primitive)(const struct action *action);
	struct definition *previous;
	struct syntax_tree *body;
	struct string *value;
};

static struct definition *environment;

static struct string *eval(struct syntax_tree *tree);
static struct definition *lookup(const struct action *action);

static struct string *primitive_write_line(const struct action *action) {
	struct string *s = eval(action->args[0]);
	printf("%*s\n", (int) s->length, s->data);
	return 0;
}

static struct string *primitive_write(const struct action *action) {
	struct string *s = eval(action->args[0]);
	printf("%*s", (int) s->length, s->data);
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
			return 0;
		}
		def->previous = environment;
		def->kind = definition_kind_action;
		environment = def;
	} else {
		log_error("Failed to allocate memory to define procedure.");
	}
	return 0;
}

static struct string *primitive_define_global_variable(const struct action *action) {
	struct definition *def = calloc(1, sizeof *def);
	if (def) {
		if (!action_copy(&def->pattern, &action->args[0]->u.action)) {
			free(def);
			return 0;
		}
		def->value = eval(action->args[1]);
		def->previous = environment;
		def->kind = definition_kind_value;
		environment = def;
	} else {
		log_error("Failed to allocate memory to define variable.");
	}
	return 0;
}

static struct string *primitive_set(const struct action *action) {
	struct definition *def = lookup(&action->args[0]->u.action);
	if (def) {
		if (def->kind == definition_kind_value) {
			string_free(def->value);
			def->value = eval(action->args[1]);
		} else {
			log_error("Cannot set non-variable names.");
		}
	} else {
		const struct string *name = &action->args[0]->u.action.selector;
		log_error("No such variable %*s", (int) name->length, name->data);
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

static struct definition *lookup(const struct action *action) {
	for (struct definition *def = environment; def; def = def->previous) {
		if (selector_matches(&def->pattern, action)) {
			return def;
		}
	}
	return 0;
}

static struct string *apply(struct definition *def, struct action *args) {
	struct definition *old_env = environment;
	struct definition arg_definitions[syntax_tree_max_args];
	struct definition *new_env = environment;
	for (size_t i = 0; i < def->pattern.arg_count; i++) {
		arg_definitions[i].previous = new_env;
		new_env = &arg_definitions[i];
		if (!action_copy(&new_env->pattern,
		                 &def->pattern.args[i]->u.action)) {
			log_error("Unable to save parameter in application");
		}
		new_env->kind = definition_kind_value;
		new_env->value = eval(args->args[i]);
	}
	environment = new_env;
	struct string *result = eval(def->body);
	environment = old_env;
	return result;
}

static struct string *eval(struct syntax_tree *tree) {
	struct definition *def;
	switch (tree->kind) {
	case syntax_tree_kind_literal:
		return string_clone(&tree->u.literal);
		break;
	case syntax_tree_kind_action:
		def = lookup(&tree->u.action);
		if (def) {
			if (def->kind == definition_kind_primitive) {
				return def->primitive(&tree->u.action);
			} else if (def->kind == definition_kind_value) {
				return def->value;
			} else if (def->pattern.arg_count != tree->u.action.arg_count) {
				log_error("Incorrect argument count: expected %d, got %d",
						  def->pattern.arg_count, tree->u.action.arg_count);
				return 0;
			} else {
				return apply(def, &tree->u.action);
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
		def->kind = definition_kind_primitive;
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
	struct definition define_global_variable_definition;
	struct definition set_definition;
	if (!define_primitive(&write_line_definition, "write line (msg)", primitive_write_line)
	    || !define_primitive(&write_definition, "write (msg)", primitive_write)
	    || !define_primitive(&define_procedure_definition, "define procedure (pattern) to do (body)", primitive_define_procedure)
	    || !define_primitive(&define_global_variable_definition, "define global variable (name) with initial value (value)", primitive_define_global_variable)
	    || !define_primitive(&set_definition, "set (name) to (value)", primitive_set)
	    || false) {
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
