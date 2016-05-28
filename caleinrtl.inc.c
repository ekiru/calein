#include <stdio.h>

#include "str.h"
#include "value.h"

static void calein_write_SPACEline_ARG(struct value *s) {
	value_write(s);
	putchar('\n');
};
