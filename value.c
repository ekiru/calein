#include "value.h"

#include <stdlib.h>
#include <stdio.h>

#include "err.h"

static size_t allocated_objects = 0;

size_t value_allocated_object_count(void) {
	return allocated_objects;
}

struct value *value_add_reference(struct value *v) {
	if (v) {
		if (v->floating) {
			v->floating = false;
		} else {
			v->ref_count++;
		}
	}
	return v;
}

bool value_remove_reference(struct value *v) {
	if (v) {
#ifdef CALEIN_REF_DEBUG
		if (!v->ref_count) {
			log_error("Tried to double free.");
			exit(1);
		}
#endif
		if (v->floating) {
			v->ref_count = 0;
		} else {
			v->ref_count--;
		}
		if (!v->ref_count) {
			switch (v->kind) {
			case value_kind_string:
				string_finish(&v->u.string);
				break;
			case value_kind_pair:
				value_remove_reference(v->u.pair[0]);
				value_remove_reference(v->u.pair[1]);
				break;
			default:
				// booleans and numbers have no extra memory and reference nothing.
				break;
			}
#ifndef CALEIN_REF_DEBUG
			free(v);
#endif
			allocated_objects--;
		}
	}
	return true;
}

static void check_value(struct value *v) {
#ifdef CALEIN_REF_DEBUG
	if (!v->ref_count) {
		log_error("Use after free.");
		exit(1);
	}
#endif
}

static struct value *allocate(enum value_kind kind) {
	struct value *res = calloc(1, sizeof *res);
	if (!res) {
		log_error("Failed to allocate memory for value.");
		exit(1);
	}
	res->kind = kind;
	res->ref_count = 1;
	res->floating = true;
	allocated_objects++;
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

struct value *value_make_string_from_c_string(const char *s) {
	struct value *v = allocate(value_kind_string);
	string_init_empty(&v->u.string);
	if (!string_add_c_string(&v->u.string, s)) {
		log_error("Failed to create string.");
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
	check_value(v);
	return v && (v->kind != value_kind_boolean || v->u.boolean);
}

bool value_boolean_is_true_remove_floating_reference(struct value *v) {
	check_value(v);
	bool result = value_boolean_is_true(v);
	if (v->floating) {
		value_remove_reference(v);
	}
	return result;
}

struct value *value_make_number(int64_t i) {
	struct value *res = allocate(value_kind_number);
	res->u.number = i;
	return res;
}

int64_t value_number_value(struct value *v) {
	check_value(v);
	if (!v || v->kind != value_kind_number) {
		log_error("Tried to use non-number as number");
		exit(1);
	}
	return v->u.number;
}

struct value *value_make_pair(struct value *x, struct value *y) {
	check_value(x);
	check_value(y);
	value_add_reference(x);
	value_add_reference(y);
	struct value *p = allocate(value_kind_pair);
	p->u.pair[0] = x;
	p->u.pair[1] = y;
	return p;
}

struct value *value_pair_first(struct value *pair) {
	check_value(pair);
	if (pair && pair->kind == value_kind_pair) {
		return pair->u.pair[0];
	} else {
		log_error("Cannot take first of non-pair.");
		exit(1);
	}
}

struct value *value_pair_second(struct value *pair) {
	check_value(pair);
	if (pair && pair->kind == value_kind_pair) {
		return pair->u.pair[1];
	} else {
		log_error("Cannot take second of non-pair.");
		exit(1);
	}
}

void value_write(struct value *v) {
	check_value(v);
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

bool value_is_equal_to(struct value *x, struct value *y) {
	check_value(x);
	check_value(y);
	if (x->kind == y->kind) {
		switch (x->kind) {
		case value_kind_boolean:
			return x->u.boolean == y->u.boolean;
			break;
		case value_kind_string:
			return string_equals(&x->u.string, &y->u.string);
			break;
		case value_kind_number:
			return x->u.number == y->u.number;
			break;
		case value_kind_pair:
			return value_is_equal_to(x->u.pair[0], y->u.pair[0])
				&& value_is_equal_to(x->u.pair[1], y->u.pair[1]);
			break;
		default:
			log_error("Unrecognized kind %d in (x) is equal to (y).", x->kind);
			return false;
			break;
		}
	} else {
		return false;
	}
}

