#include "value.h"

#include <stdlib.h>
#include <stdio.h>

#include "err.h"


static struct value *allocate(enum value_kind kind) {
	struct value *res = calloc(1, sizeof *res);
	if (!res) {
		log_error("Failed to allocate memory for value.");
		exit(1);
	}
	res->kind = kind;
	return res;
}

struct value *value_make_string(const struct string *s) {
	struct value *v = allocate(value_kind_string);
	if (!string_copy(&v->u.string, s)) {
		log_error("Failed to copy string.");
		exit(1);
	}
	return v;
}

struct string *value_string_value(struct value *v) {
	if (!v || v->kind != value_kind_string) {
		log_error("Attempt to use non-string as string.");
		exit(1);
	}
	return &v->u.string;
}

struct value *value_make_boolean(bool b) {
	struct value *res = allocate(value_kind_boolean);
	res->u.boolean = b;
	return res;
}

bool value_boolean_is_true(struct value *v) {
	return v && (v->kind != value_kind_boolean || v->u.boolean);
}

struct value *value_make_number(int64_t i) {
	struct value *res = allocate(value_kind_number);
	res->u.number = i;
	return res;
}

int64_t value_number_value(struct value *v) {
	if (!v || v->kind != value_kind_number) {
		log_error("Tried to use non-number as number");
		exit(1);
	}
	return v->u.number;
}

struct value *value_make_pair(struct value *x, struct value *y) {
	struct value *p = allocate(value_kind_pair);
	p->u.pair[0] = x;
	p->u.pair[1] = y;
	return p;
}

struct value *value_pair_first(struct value *pair) {
	if (pair && pair->kind == value_kind_pair) {
		return pair->u.pair[0];
	} else {
		log_error("Cannot take first of non-pair.");
		return 0;
	}
}

struct value *value_pair_second(struct value *pair) {
	if (pair && pair->kind == value_kind_pair) {
		return pair->u.pair[1];
	} else {
		log_error("Cannot take second of non-pair.");
		return 0;
	}
}

void value_write(struct value *v) {
	switch (v->kind) {
	case value_kind_string:
		printf("%.*s", (int) v->u.string.length, v->u.string.data);
		break;
	case value_kind_boolean:
		if (v->u.boolean) {
			printf("true");
		} else {
			printf("false");
		}
		break;
	case value_kind_number:
		printf("%lld", v->u.number);
		break;
	case value_kind_pair:
		value_write(v->u.pair[0]);
		printf(", ");
		value_write(v->u.pair[1]);
		break;
	default:
		log_error("Unrecognized value kind %d", v->kind);
	}
}
