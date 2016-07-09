#include <stdio.h>
#include <string.h>

#include "err.h"
#include "str.h"
#include "value.h"

static struct value *global_SCOPEcalein__COMMA_ARG_ARG(struct value *x, struct value *y) {
	return value_make_pair(x, y);
}

static struct value *global_SCOPEcalein_first_ARG(struct value *p) {
	struct value *res = value_pair_first(p);
	value_add_reference(res);
	value_remove_reference(p);
	return res;
}

static struct value *global_SCOPEcalein_second_ARG(struct value *p) {
	struct value *res = value_pair_second(p);
	value_add_reference(res);
	value_remove_reference(p);
	return res;
}

static struct value *global_SCOPEcalein_not_ARG(struct value *b) {
	struct value *res = value_make_boolean(!value_boolean_is_true(b));
	value_remove_reference(b);
	return res;
}

static struct value *global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(struct value *x, struct value *y) {
	struct value *res = value_make_boolean(value_is_equal_to(x, y));
	value_remove_reference(x);
	value_remove_reference(y);
	return res;
}

static struct value *global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(struct value *c, struct value *s) {
	if (!string_add_character(value_string_value(s), (char) value_number_value(c))) {
		log_error("Failed to append character");
		exit(1);
	}
	value_remove_reference(c);
	value_remove_reference(s);
	return 0;
}

static struct value *global_SCOPEcalein_trim_SPACEright_ARG(struct value *s) {
	string_trim_right(value_string_value(s));
	value_remove_reference(s);
	return s;
}

static struct value *global_SCOPEcalein_length_ARG(struct value *s) {
	struct value *res = value_make_number(value_string_value(s)->length);
	value_remove_reference(s);
	return res;
}

static struct value *global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(struct value *iv, struct value *sv) {
	int64_t i = value_number_value(iv);
	struct string *s = value_string_value(sv);
	if (i < 0 || i >= s->length) {
		log_error("Index out of bounds for string");
		return 0;
	}
	struct value *res = value_make_number(s->data[i]);
	value_remove_reference(iv);
	value_remove_reference(sv);
	return res;
}

static struct value *global_SCOPEcalein_write_ARG(struct value *s) {
	value_write(s);
	value_remove_reference(s);
	return 0;
};

static struct value *global_SCOPEcalein_write_SPACEline_ARG(struct value *s) {
	value_write(s);
	puts("");
	fflush(stdout);
	value_remove_reference(s);
	return 0;
};

static struct value *char_of_int(int c) {
	if (c == EOF ) {
		return value_make_boolean(false);
	} else {
		return value_make_number(c);
	}
}

static struct value *global_SCOPEcalein_read_SPACEcharacter(void) {
	return char_of_int(getchar());
}

static struct value *global_SCOPEcalein_read_SPACEcharacter_SPACEfrom_ARG(struct value *f) {
	return char_of_int(getc(value_file_value(f)));
}

static struct value *global_SCOPEcalein_open_SPACEfile_SPACE_SPACE_ARGfor_SPACEreading(struct value *name) {
	return value_make_file(fopen(value_string_value(name)->data, "r"));
}

static struct value *global_SCOPEcalein_close_SPACEfile_ARG(struct value *f) {
	fclose(value_file_value(f));
	return 0;
}

static struct value *global_SCOPEcalein_standard_SPACEinput(void) {
	static struct value *stdin_value = 0;
	if (!stdin_value) {
		stdin_value = value_make_file(stdin);
	}
	return value_add_reference(stdin_value);
}

#define NUMBER_BINOP(name, op) \
	static struct value *global_SCOPEcalein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		struct value *res = value_make_number(value_number_value(x) op value_number_value(y)); \
		value_remove_reference(x); \
		value_remove_reference(y); \
		return res; \
	}

NUMBER_BINOP(_PLUS, +)
NUMBER_BINOP(_DASH, -)
NUMBER_BINOP(_STAR, *)
NUMBER_BINOP(_SLASH, /)
NUMBER_BINOP(mod, %)

#undef NUMBER_BINOP

#define NUMBER_RELOP(name, op) \
	static struct value *global_SCOPEcalein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		struct value *res = value_make_boolean(value_number_value(x) op value_number_value(y)); \
		value_remove_reference(x); \
		value_remove_reference(y); \
		return res; \
	}

NUMBER_RELOP(_LESSER, <)
NUMBER_RELOP(_GREATER, >)

#undef NUMBER_RELOP

void caleinmain();

int main(int argc, char **argv) {
	char *memdebug_env = getenv("CALEIN_MEMDEBUG");
	bool memdebug = memdebug_env && 0 == strcmp(memdebug_env, "1");
	caleinmain();
	if (memdebug) {
		fprintf(stderr, "%lu\n", (unsigned long) value_allocated_object_count());
	}
	return 0;
}

