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

struct string *string_new_empty(void);
void string_free(struct string *s);

bool string_copy(struct string *copy, const struct string *s);
struct string *string_clone(const struct string *s);

bool string_equals(const struct string *s, const struct string *t);

bool string_add_character(struct string *s, char c);
bool string_add_characters(struct string *s, const char *cs, size_t n);
bool string_add_c_string(struct string *s, const char *cs);
void string_trim_right(struct string *s);

#endif
