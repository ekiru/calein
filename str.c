#include "str.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *empty = "";

void string_init_empty(struct string *s) {
	s->capacity = s->length = 0;
	s->data = empty;
}

void string_finish(struct string *s) {
	if (s->data != empty) {
		free(s->data);
	}
}

struct string *string_new_empty(void) {
	struct string *s = calloc(1, sizeof *s);
	if (s) {
		string_init_empty(s);
	}
	return s;
}

void string_free(struct string *s) {
	if (s) {
		string_finish(s);
		free(s);
	}
}

bool string_copy(struct string *copy, const struct string *s) {
	string_init_empty(copy);
	return string_add_characters(copy, s->data, s->length);
}

struct string *string_clone(const struct string *s) {
	struct string *clone = string_new_empty();
	if (clone) {
		string_add_characters(clone, s->data, s->length);
	}
	return clone;
}

bool string_equals(const struct string *s, const struct string *t) {
	return s->length == t->length && memcmp(s->data, t->data, s->length) == 0;
}

bool string_add_character(struct string *s, char c) {
	if (s->capacity == s->length) {
		size_t new_size = s->capacity * 2;
		if (s->data == empty) {
			s->data = 0;
			new_size = 10;
		}
		char *new_data = realloc(s->data, new_size + 1);
		if (!new_data) {
			return false;
		}
		s->data = new_data;
		s->capacity = new_size;
	}
	s->data[s->length] = c;
	s->length++;
	s->data[s->length] = 0;
	return true;
}

bool string_add_characters(struct string *s, const char *cs, size_t n) {
	size_t len = s->length;
	for (size_t i = 0; i < n; i++) {
		if (!string_add_character(s, cs[i])) {
			s->length = len;
			return false;
		}
	}
	return true;
}

bool string_add_c_string(struct string *s, const char *cs) {
	size_t len = s->length;
	while (*cs) {
		if (!string_add_character(s, *cs)) {
			s->length = len;
			return false;
		}
		cs++;
	}
	return true;
}

void string_trim_right(struct string *s) {
	while (s->length != 0 && isspace(s->data[s->length-1])) {
		s->length--;
	};
}
