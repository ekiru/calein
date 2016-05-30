#ifndef CALEIN_VALUE_H
#define CALEIN_VALUE_H

#include <stdbool.h>
#include <stdint.h>

#include "str.h"

enum value_kind {
	value_kind_string,
	value_kind_boolean,
	value_kind_number,
	value_kind_pair,
};

struct value {
	enum value_kind kind;
	uint32_t ref_count;
	union {
		struct string string;
		bool boolean;
		int64_t number;
		struct value *pair[2];
	} u;
};

size_t value_allocated_object_count(void);
struct value *value_add_reference(struct value *v);
bool value_remove_reference(struct value *v);

struct value *value_make_string(const struct string *s);
struct value *value_make_string_from_c_string(const char *s);
struct string *value_string_value(struct value *v);

struct value *value_make_boolean(bool b);
bool value_boolean_is_true(struct value *v);

struct value *value_make_number(int64_t i);
int64_t value_number_value(struct value *v);

struct value *value_make_pair(struct value *x, struct value *y);
struct value *value_pair_first(struct value *pair);
struct value *value_pair_second(struct value *pair);

void value_write(struct value *v);

bool value_is_equal_to(struct value *x, struct value *y);

#endif
