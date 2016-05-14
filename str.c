#include "str.h"

#include <ctype.h>
#include <stdlib.h>

void string_init_empty(struct string *s) {
	s->capacity = s->length = 0;
	s->data = 0;
}

void string_finish(struct string *s) {
	free(s->data);
}

bool string_add_character(struct string *s, char c) {
	if (s->capacity == s->length) {
		size_t new_size = s->capacity * 2;
		if (!new_size) {
			new_size = 10;
		}
		char *new_data = realloc(s->data, new_size);
		if (!new_data) {
			return false;
		}
		s->data = new_data;
		s->capacity = new_size;
	}
	s->data[s->length] = c;
	s->length++;
	return true;
}

void string_trim_right(struct string *s) {
	while (s->length != 0 && isspace(s->data[s->length-1])) {
		s->length--;
	};
}
