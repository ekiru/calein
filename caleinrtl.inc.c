#include <stdio.h>

#include "str.h"
#include "value.h"

static void calein_write_SPACEline_ARG(struct value *s) {
	value_write(s);
	putchar('\n');
};

#define NUMBER_BINOP(name, op) \
	static struct value *calein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		return value_make_number(value_number_value(x) op value_number_value(y)); \
	}

NUMBER_BINOP(_PLUS, +)
NUMBER_BINOP(_DASH, -)
NUMBER_BINOP(_STAR, *)
NUMBER_BINOP(_SLASH, /)
NUMBER_BINOP(mod, %)

#undef NUMBER_BINOP
