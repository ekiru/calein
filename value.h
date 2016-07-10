#ifndef CALEIN_VALUE_H
#define CALEIN_VALUE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "str.h"

enum value_kind {
	value_kind_string,
	value_kind_boolean,
	value_kind_number,
	value_kind_pair,
	value_kind_file,
	value_kind_record,
};

struct value {
	enum value_kind kind;
	bool floating;
	uint32_t ref_count;
#ifdef CALEIN_REF_DEBUG
	struct value *prev, *next;
#endif
	union {
		struct string string;
		bool boolean;
		int64_t number;
		struct value *pair[2];
		FILE *file;
		struct {
			const char *type;
			size_t field_count;
			struct value **fields;
		} record;
	} u;
};

// does nothing unless CALEIN_REF_DEBUG is defined
void value_display_remaining_values(void);

size_t value_allocated_object_count(void);
struct value *value_add_reference(struct value *v);
bool value_remove_reference(struct value *v);
void value_float_result(struct value *v);

struct value *value_make_string(const struct string *s);
struct value *value_make_string_from_c_string(const char *s);
struct string *value_string_value(struct value *v);

struct value *value_make_boolean(bool b);
bool value_boolean_is_true(struct value *v);
bool value_boolean_is_true_remove_floating_reference(struct value *v);

struct value *value_make_number(int64_t i);
int64_t value_number_value(struct value *v);

struct value *value_make_pair(struct value *x, struct value *y);
struct value *value_pair_first(struct value *pair);
struct value *value_pair_second(struct value *pair);

struct value *value_make_file(FILE *f);
FILE *value_file_value(struct value *f);

struct value *value_make_record(const char *type, size_t fields);
struct value *value_record_field(struct value *record, const char *type, size_t field);

void value_write(struct value *v);

bool value_is_equal_to(struct value *x, struct value *y);

#endif
