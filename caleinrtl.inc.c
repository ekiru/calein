#include <stdio.h>

#include "err.h"
#include "str.h"
#include "value.h"

static struct value *global_SCOPEcalein__COMMA_ARG_ARG(struct value *x, struct value *y) {
	return value_make_pair(x, y);
}

static struct value *global_SCOPEcalein_first_ARG(struct value *p) {
	return value_pair_first(p);
}

static struct value *global_SCOPEcalein_second_ARG(struct value *p) {
	return value_pair_second(p);
}

static struct value *global_SCOPEcalein_not_ARG(struct value *b) {
	return value_make_boolean(!value_boolean_is_true(b));
}

static struct value *global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(struct value *x, struct value *y) {
	return value_make_boolean(value_is_equal_to(x, y));
}

static struct value *global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(struct value *c, struct value *s) {
	if (!string_add_character(value_string_value(s), (char) value_number_value(c))) {
		log_error("Failed to append character");
		exit(1);
	}
	return 0;
}

static struct value *global_SCOPEcalein_trim_SPACEright_ARG(struct value *s) {
	string_trim_right(value_string_value(s));
	return s;
}

static struct value *global_SCOPEcalein_length_ARG(struct value *s) {
	return value_make_number(value_string_value(s)->length);
}

static struct value *global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(struct value *iv, struct value *sv) {
	int64_t i = value_number_value(iv);
	struct string *s = value_string_value(sv);
	if (i < 0 || i >= s->length) {
		log_error("Index out of bounds for string");
		return 0;
	}
	return value_make_number(s->data[i]);
}

static struct value *global_SCOPEcalein_write_ARG(struct value *s) {
	value_write(s);
	return 0;
};

static struct value *global_SCOPEcalein_write_SPACEline_ARG(struct value *s) {
	value_write(s);
	puts("");
	fflush(stdout);
	return 0;
};

static struct value *global_SCOPEcalein_read_SPACEcharacter(void) {
	int c = getchar();
	if (c == EOF ) {
		return value_make_boolean(false);
	} else {
		return value_make_number(c);
	}
}

#define NUMBER_BINOP(name, op) \
	static struct value *global_SCOPEcalein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		return value_make_number(value_number_value(x) op value_number_value(y)); \
	}

NUMBER_BINOP(_PLUS, +)
NUMBER_BINOP(_DASH, -)
NUMBER_BINOP(_STAR, *)
NUMBER_BINOP(_SLASH, /)
NUMBER_BINOP(mod, %)

#undef NUMBER_BINOP
