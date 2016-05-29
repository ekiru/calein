#include <stdbool.h>
#include <stdio.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"
#include "value.h"

enum definition_kind {
	definition_kind_primitive,
	definition_kind_action,
	definition_kind_value,
};

struct definition {
	enum definition_kind kind;
	struct action pattern;
	struct value *(*primitive)(const struct action *action);
	struct definition *previous;
	struct syntax_tree *body;
	struct value *value;
};

static struct definition *environment;

static struct value *eval(struct syntax_tree *tree);
static struct definition *lookup(const struct action *action);

#define ARITH_PRIM(name, op) struct value *primitive_ ## name(const struct action *action) { \
	return value_make_number(value_number_value(eval(action->args[0])) op value_number_value(eval(action->args[1]))); \
}

ARITH_PRIM(add, +)
ARITH_PRIM(subtract, -)
ARITH_PRIM(multiply, *)
ARITH_PRIM(divide, /)
ARITH_PRIM(mod, %)

#undef ARITH_PRIM

static struct value *primitive_pair(const struct action *action) {
	return value_make_pair(eval(action->args[0]), eval(action->args[1]));
}

static struct value *primitive_first(const struct action *action) {
	return value_pair_first(eval(action->args[0]));
}

static struct value *primitive_second(const struct action *action) {
	return value_pair_second(eval(action->args[0]));
}


static struct value *primitive_write(const struct action *action) {
	value_write(eval(action->args[0]));
	return 0;
}

static struct value *primitive_write_line(const struct action *action) {
	primitive_write(action);
	puts("");
	return 0;
}

static struct value *primitive_read_character(const struct action *action) {
	int c = getchar();
	if (c == EOF) {
		return value_make_boolean(false);
	} else {
		return value_make_number((int64_t) c);
	}
}

static struct value *primitive_append_character_to(const struct action *action) {
	struct value *c = eval(action->args[0]);
	struct value *s = eval(action->args[1]);
	if (!string_add_character(value_string_value(s), (char) value_number_value(c))) {
		log_error ("Error appending to string.");
	}
	return 0;
}

static struct value *primitive_trim_right(const struct action *action) {
	struct value *s = eval(action->args[0]);
	string_trim_right(value_string_value(s));
	return 0;
}

static struct value *primitive_length(const struct action *action) {
	struct value *s = eval(action->args[0]);
	return value_make_number(value_string_value(s)->length);
}

static struct value *primitive_character_at_of(const struct action *action) {
	int64_t i = value_number_value(eval(action->args[0]));
	struct string *s = value_string_value(eval(action->args[1]));
	if (i < 0 || i >= s->length) {
		log_error("Index out of bounds for string");
		return 0;
	}
	return value_make_number(s->data[i]);
}

static struct value *primitive_not(const struct action *action) {
	return value_make_boolean(!value_boolean_is_true(eval(action->args[0])));
}

static struct value *primitive_is_equal_to(const struct action *action) {
	return value_make_boolean(value_is_equal_to(eval(action->args[0]), eval(action->args[1])));
}

static struct value *primitive_if_then_else(const struct action *action) {
	if (value_boolean_is_true(eval(action->args[0]))) {
		// a non-null non-boolean is always true.
		return eval(action->args[1]);
	} else {
		return eval(action->args[2]);
	}
}

static struct value *primitive_while_do(const struct action *action) {
	for (;;) {
		if (!value_boolean_is_true(eval(action->args[0]))) {
			return 0;
		}
		eval(action->args[1]);
	}
}

static struct value *primitive_define_procedure(const struct action *action) {
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

static struct value *primitive_define_variable(const struct action *action) {
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

static struct value *primitive_set(const struct action *action) {
	struct definition *def = lookup(&action->args[0]->u.action);
	if (def) {
		if (def->kind == definition_kind_value) {
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

static struct value *apply(struct definition *def, struct action *args) {
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
	struct value *result = eval(def->body);
	environment = old_env;
	return result;
}

static struct value *eval(struct syntax_tree *tree) {
	struct definition *def;
	struct value *res = 0;
	switch (tree->kind) {
	case syntax_tree_kind_literal:
		return value_make_string(&tree->u.literal);
		break;
	case syntax_tree_kind_number:
		return value_make_number(tree->u.number);
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
		log_error("Unrecognized selector %.*s", (int) tree->u.action.selector.length, tree->u.action.selector.data);
		exit(1);
		break;
	case syntax_tree_kind_sequence:
		for (size_t i = 0; i < syntax_tree_max_sequence && tree->u.sequence[i]; i++) {
			res = eval(tree->u.sequence[i]);
		}
		return res;
		break;
	default:
		log_error("Unrecognized kind %d", tree->kind);
		return 0;
	}
}

static void interp(struct syntax_tree *tree) {
	eval(tree);
}

static bool define_primitive(
	struct definition *def,
	const char *pattern, 
	struct value *(*f)(const struct action *action)) {
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

int main(int argc, char **argv) {
	environment = 0;
	struct definition pair_definition;
	struct definition first_definition;
	struct definition second_definition;
	struct definition write_line_definition;
	struct definition write_definition;
	struct definition read_character_definition;
	struct definition append_character_to_definition;
	struct definition trim_right_definition;
	struct definition length_definition;
	struct definition character_at_of_definition;
	struct definition add_definition;
	struct definition subtract_definition;
	struct definition multiply_definition;
	struct definition divide_definition;
	struct definition mod_definition;
	struct definition not_definition;
	struct definition is_equal_to_definition;
	struct definition if_then_else_definition;
	struct definition while_do_definition;
	struct definition define_procedure_definition;
	struct definition define_variable_definition;
	struct definition set_definition;
	if (!define_primitive(&pair_definition, "(first), (second)", primitive_pair)
	    || !define_primitive(&first_definition, "first (pair)", primitive_first)
	    || !define_primitive(&second_definition, "second (pair)", primitive_second)
	    || !define_primitive(&write_line_definition, "write line (msg)", primitive_write_line)
	    || !define_primitive(&write_definition, "write (msg)", primitive_write)
	    || !define_primitive(&read_character_definition, "read character", primitive_read_character)
	    || !define_primitive(&append_character_to_definition, "append character (c) to (s)", primitive_append_character_to)
	    || !define_primitive(&trim_right_definition, "trim right (s)", primitive_trim_right)
	    || !define_primitive(&length_definition, "length (s)", primitive_length)
	    || !define_primitive(&character_at_of_definition, "character at (index) of (string)", primitive_character_at_of)
	    || !define_primitive(&add_definition, "(x) + (y)", primitive_add)
	    || !define_primitive(&subtract_definition, "(x) - (y)", primitive_subtract)
	    || !define_primitive(&multiply_definition, "(x) * (y)", primitive_multiply)
	    || !define_primitive(&divide_definition, "(x) / (y)", primitive_divide)
	    || !define_primitive(&mod_definition, "(x) mod (y)", primitive_mod)
	    || !define_primitive(&not_definition, "not (x)", primitive_not)
	    || !define_primitive(&is_equal_to_definition, "(x) is equal to (y)", primitive_is_equal_to)
	    || !define_primitive(&if_then_else_definition, "if (condition) then (then) else (else)", primitive_if_then_else)
	    || !define_primitive(&while_do_definition, "while (condition) do (body)", primitive_while_do)
	    || !define_primitive(&define_procedure_definition, "define procedure (pattern) to do (body)", primitive_define_procedure)
	    || !define_primitive(&define_variable_definition, "define variable (name) with initial value (value)", primitive_define_variable)
	    || !define_primitive(&set_definition, "set (name) to (value)", primitive_set)
	    || false) {
		log_error("Failed to define primitives.");
		return 1;
	}

	FILE *input = 0;
	if (argc == 2) {
		input = fopen(argv[1], "r");
		if (!input) {
			log_error("Unable to open file %s", argv[1]);
			return 1;
		}
	}

	for (;;) {
		struct syntax_tree *tree = input ? parse_from_file(input) : parse();
		if (tree) {
			interp(tree);
			syntax_tree_free(tree);
		} else {
			break;
		}
	}	
	if (input) {
		fclose(input);
	}
	return 0;
}
