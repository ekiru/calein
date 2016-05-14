#ifndef CLN_STR_H
#define CLN_STR_H

#include <stdbool.h>
#include <stdlib.h>

struct string {
	size_t capacity;
	size_t length;
	char *data;
};

void string_init_empty(struct string *s);
void string_finish(struct string *s);

bool string_add_character(struct string *s, char c);
void string_trim_right(struct string *s);

#endif
