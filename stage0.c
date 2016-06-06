#include <stdio.h>

#include "err.h"
#include "str.h"
#include "value.h"

static struct value *global_SCOPEcalein__COMMA_ARG_ARG(struct value *x, struct value *y) {
	return value_make_pair(x, y);
}

static struct value *global_SCOPEcalein_first_ARG(struct value *p) {
	struct value *res = value_pair_first(p);
	value_add_reference(res);
	value_remove_reference(p);
	return res;
}

static struct value *global_SCOPEcalein_second_ARG(struct value *p) {
	struct value *res = value_pair_second(p);
	value_add_reference(res);
	value_remove_reference(p);
	return res;
}

static struct value *global_SCOPEcalein_not_ARG(struct value *b) {
	struct value *res = value_make_boolean(!value_boolean_is_true(b));
	value_remove_reference(b);
	return res;
}

static struct value *global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(struct value *x, struct value *y) {
	struct value *res = value_make_boolean(value_is_equal_to(x, y));
	value_remove_reference(x);
	value_remove_reference(y);
	return res;
}

static struct value *global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(struct value *c, struct value *s) {
	if (!string_add_character(value_string_value(s), (char) value_number_value(c))) {
		log_error("Failed to append character");
		exit(1);
	}
	value_remove_reference(c);
	value_remove_reference(s);
	return 0;
}

static struct value *global_SCOPEcalein_trim_SPACEright_ARG(struct value *s) {
	string_trim_right(value_string_value(s));
	value_remove_reference(s);
	return s;
}

static struct value *global_SCOPEcalein_length_ARG(struct value *s) {
	struct value *res = value_make_number(value_string_value(s)->length);
	value_remove_reference(s);
	return res;
}

static struct value *global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(struct value *iv, struct value *sv) {
	int64_t i = value_number_value(iv);
	struct string *s = value_string_value(sv);
	if (i < 0 || i >= s->length) {
		log_error("Index out of bounds for string");
		return 0;
	}
	struct value *res = value_make_number(s->data[i]);
	value_remove_reference(iv);
	value_remove_reference(sv);
	return res;
}

static struct value *global_SCOPEcalein_write_ARG(struct value *s) {
	value_write(s);
	value_remove_reference(s);
	return 0;
};

static struct value *global_SCOPEcalein_write_SPACEline_ARG(struct value *s) {
	value_write(s);
	puts("");
	fflush(stdout);
	value_remove_reference(s);
	return 0;
};

static struct value *char_of_int(int c) {
	if (c == EOF ) {
		return value_make_boolean(false);
	} else {
		return value_make_number(c);
	}
}

static struct value *global_SCOPEcalein_read_SPACEcharacter(void) {
	return char_of_int(getchar());
}

static struct value *global_SCOPEcalein_read_SPACEcharacter_SPACEfrom_ARG(struct value *f) {
	return char_of_int(getc(value_file_value(f)));
}

static struct value *global_SCOPEcalein_open_SPACEfile_SPACE_SPACE_ARGfor_SPACEreading(struct value *name) {
	return value_make_file(fopen(value_string_value(name)->data, "r"));
}

static struct value *global_SCOPEcalein_close_SPACEfile_ARG(struct value *f) {
	fclose(value_file_value(f));
	return 0;
}

static struct value *global_SCOPEcalein_standard_SPACEinput(void) {
	static struct value *stdin_value = 0;
	if (!stdin_value) {
		stdin_value = value_make_file(stdin);
	}
	return value_add_reference(stdin_value);
}

#define NUMBER_BINOP(name, op) \
	static struct value *global_SCOPEcalein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		struct value *res = value_make_number(value_number_value(x) op value_number_value(y)); \
		value_remove_reference(x); \
		value_remove_reference(y); \
		return res; \
	}

NUMBER_BINOP(_PLUS, +)
NUMBER_BINOP(_DASH, -)
NUMBER_BINOP(_STAR, *)
NUMBER_BINOP(_SLASH, /)
NUMBER_BINOP(mod, %)

#undef NUMBER_BINOP
struct global_SCOPEcalein__SPACE_ARGat_ARG_local_vars {
struct value *calein_list;
struct value *calein_index;
};
struct value *global_SCOPEcalein__SPACE_ARGat_ARG(struct value *calein_list, struct value *calein_index);
struct global_SCOPEcalein__SPACE_ARGor_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
};
struct value *global_SCOPEcalein__SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b);
struct global_SCOPEcalein__SPACE_ARGand_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
};
struct value *global_SCOPEcalein__SPACE_ARGand_ARG(struct value *calein_a, struct value *calein_b);
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
struct value *calein_c;
};
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c);
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
struct value *calein_c;
struct value *calein_d;
};
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d);
struct global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG_local_vars {
struct value *calein_x;
struct value *calein_a;
struct value *calein_b;
struct value *calein_found;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG(struct value *calein_x, struct value *calein_a, struct value *calein_b);
struct global_SCOPEcalein_reverse_SPACEstring_ARG_local_vars {
struct value *calein_s;
struct value *calein_rev;
struct value *calein_i;
};
struct value *global_SCOPEcalein_reverse_SPACEstring_ARG(struct value *calein_s);
struct global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG_local_vars {
struct value *calein_number;
struct value *calein_s;
};
struct value *global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(struct value *calein_number);
struct global_SCOPEcalein__SPACE_ARGis_SPACEdigit_local_vars {
struct value *calein_c;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEdigit(struct value *calein_c);
struct global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace_local_vars {
struct value *calein_c;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(struct value *calein_c);
struct global_SCOPEcalein_get_SPACEcharacter_local_vars {
struct value *calein_tmp;
};
struct value *global_SCOPEcalein_get_SPACEcharacter(void);
struct global_SCOPEcalein_unget_SPACEcharacter_ARG_local_vars {
struct value *calein_c;
};
struct value *global_SCOPEcalein_unget_SPACEcharacter_ARG(struct value *calein_c);
struct global_SCOPEcalein_reverse_SPACElist_ARG_local_vars {
struct value *calein_list;
struct value *calein_acc;
};
struct value *global_SCOPEcalein_reverse_SPACElist_ARG(struct value *calein_list);
struct global_SCOPEcalein_make_SPACEliteral_ARG_local_vars {
struct value *calein_val;
};
struct value *global_SCOPEcalein_make_SPACEliteral_ARG(struct value *calein_val);
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral_local_vars {
struct value *calein_p;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(struct value *calein_p);
struct global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG_local_vars {
struct value *calein_lit;
};
struct value *global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(struct value *calein_lit);
struct global_SCOPEcalein_make_SPACEnumber_ARG_local_vars {
struct value *calein_val;
};
struct value *global_SCOPEcalein_make_SPACEnumber_ARG(struct value *calein_val);
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber_local_vars {
struct value *calein_p;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(struct value *calein_p);
struct global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG_local_vars {
struct value *calein_num;
};
struct value *global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(struct value *calein_num);
struct global_SCOPEcalein_make_SPACEsequence_ARG_local_vars {
struct value *calein_list;
};
struct value *global_SCOPEcalein_make_SPACEsequence_ARG(struct value *calein_list);
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence_local_vars {
struct value *calein_p;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(struct value *calein_p);
struct global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG_local_vars {
struct value *calein_seq;
};
struct value *global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(struct value *calein_seq);
struct global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars {
struct value *calein_name;
struct value *calein_args;
};
struct value *global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction_local_vars {
struct value *calein_p;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(struct value *calein_p);
struct global_SCOPEcalein_name_SPACEof_SPACEaction_ARG_local_vars {
struct value *calein_action;
};
struct value *global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(struct value *calein_action);
struct global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG_local_vars {
struct value *calein_action;
};
struct value *global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(struct value *calein_action);
struct global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes_local_vars {
struct value *calein_n;
};
struct value *global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(struct value *calein_n);
struct global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG_local_vars {
struct value *calein_tree;
struct value *calein_indent;
struct value *calein_items;
struct value *calein_args;
};
struct value *global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(struct value *calein_tree, struct value *calein_indent);
struct global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG_local_vars {
struct value *calein_s;
};
struct value *global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG(struct value *calein_s);
struct global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG_local_vars {
struct value *calein_c;
struct value *calein_c_SPACE1;
struct value *calein_c_SPACE2;
struct value *calein_c_SPACE3;
struct value *calein_c_SPACE4;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG(struct value *calein_c, struct value *calein_c_SPACE1, struct value *calein_c_SPACE2, struct value *calein_c_SPACE3, struct value *calein_c_SPACE4);
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars {
struct value *calein_first_SPACEchild;
struct value *calein_tree;
struct value *calein_again_SPACEin_SPACEaction;
struct value *calein_children;
struct value *calein_literal;
struct value *calein_paren;
struct value *calein_child;
struct value *calein_c;
};
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG_local_vars {
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars;
struct value *calein_msg;
};
struct value *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars, struct value *calein_msg);
struct value *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(struct value *calein_first_SPACEchild);
struct global_SCOPEcalein_parse_ARG_local_vars {
struct value *calein_at_SPACEstart_SPACEof_SPACEexpression;
struct value *calein_again;
struct value *calein_literal;
struct value *calein_in_SPACEescape;
struct value *calein_again_SPACEin_SPACEliteral;
struct value *calein_again_SPACEin_SPACEsequence;
struct value *calein_at_SPACEstart_SPACEof_SPACEliteral;
struct value *calein_children;
struct value *calein_c;
struct value *calein_tree;
struct value *calein_child;
};
struct global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG_local_vars {
struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars;
struct value *calein_msg;
};
struct value *global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars, struct value *calein_msg);
struct value *global_SCOPEcalein_parse_ARG(struct value *calein_at_SPACEstart_SPACEof_SPACEexpression);
struct global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG_local_vars {
struct value *calein_t;
struct value *calein_s;
struct value *calein_i;
};
struct value *global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(struct value *calein_t, struct value *calein_s);
struct global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG_local_vars {
struct value *calein_s;
struct value *calein_t;
struct value *calein_u;
};
struct value *global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(struct value *calein_s, struct value *calein_t);
struct global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG_local_vars {
struct value *calein_str;
struct value *calein_c;
};
struct value *global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(struct value *calein_str, struct value *calein_c);
struct global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG_local_vars {
struct value *calein_action;
struct value *calein_name;
struct value *calein_args;
struct value *calein_ident;
struct value *calein_i;
struct value *calein_c;
struct value *calein_added;
struct value *calein_substitutions;
};
struct value *global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(struct value *calein_action);
struct global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG_local_vars {
struct value *calein_literal;
struct value *calein_string;
struct value *calein_i;
struct value *calein_c;
};
struct value *global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(struct value *calein_literal);
struct global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars {
struct value *calein_name;
struct value *calein_args;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall(struct value *calein_ir);
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG(struct value *calein_ir);
struct global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_ARG_local_vars {
struct value *calein_name;
struct value *calein_body;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_ARG(struct value *calein_name, struct value *calein_body);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure(struct value *calein_ir);
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *calein_ir);
struct global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEsequence_ARG_local_vars {
struct value *calein_items;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEsequence_ARG(struct value *calein_items);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence(struct value *calein_ir);
struct global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_ARG_local_vars {
struct value *calein_condition;
struct value *calein_then;
struct value *calein_else;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_ARG(struct value *calein_condition, struct value *calein_then, struct value *calein_else);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif(struct value *calein_ir);
struct global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir);
struct global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir);
struct global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_ARG_local_vars {
struct value *calein_condition;
struct value *calein_body;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_ARG(struct value *calein_condition, struct value *calein_body);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile(struct value *calein_ir);
struct global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(struct value *calein_ir);
struct global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_ARG_local_vars {
struct value *calein_name;
struct value *calein_initial_SPACEvalue;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_ARG(struct value *calein_name, struct value *calein_initial_SPACEvalue);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable(struct value *calein_ir);
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(struct value *calein_ir);
struct global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_ARG_local_vars {
struct value *calein_name;
struct value *calein_value;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_ARG(struct value *calein_name, struct value *calein_value);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment(struct value *calein_ir);
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(struct value *calein_ir);
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEliteral_ARG_local_vars {
struct value *calein_literal;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEliteral_ARG(struct value *calein_literal);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral(struct value *calein_ir);
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG(struct value *calein_ir);
struct global_SCOPEcalein_make_SPACEir_SPACEnumber_ARG_local_vars {
struct value *calein_number;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEnumber_ARG(struct value *calein_number);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber(struct value *calein_ir);
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG_local_vars {
struct value *calein_ir;
};
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG(struct value *calein_ir);
struct global_SCOPEcalein__SPACE_ARGcontains_ARG_local_vars {
struct value *calein_list;
struct value *calein_elem;
struct value *calein_found;
};
struct value *global_SCOPEcalein__SPACE_ARGcontains_ARG(struct value *calein_list, struct value *calein_elem);
struct global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG_local_vars {
struct value *calein_key;
struct value *calein_alist;
struct value *calein_found;
};
struct value *global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(struct value *calein_key, struct value *calein_alist);
struct global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG_local_vars {
struct value *calein_var;
struct value *calein_scope;
struct value *calein_old_SPACEscope;
};
struct value *global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(struct value *calein_var, struct value *calein_scope);
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation_local_vars {
struct value *calein_context;
};
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(struct value *calein_context);
struct global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG_local_vars {
struct value *calein_name;
struct value *calein_var_SPACEscope;
struct value *calein_scope;
struct value *calein_out;
};
struct value *global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(struct value *calein_name, struct value *calein_var_SPACEscope, struct value *calein_scope, struct value *calein_out);
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG_local_vars {
struct value *calein_proc_SPACEname;
struct value *calein_out;
};
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(struct value *calein_proc_SPACEname, struct value *calein_out);
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars {
struct value *calein_ir;
struct value *calein_proc_SPACEname;
struct value *calein_out;
struct value *calein_scope;
struct value *calein_args;
struct value *calein_ident;
};
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_ir, struct value *calein_proc_SPACEname, struct value *calein_out, struct value *calein_scope);
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars {
struct value *calein_proc_SPACEname;
struct value *calein_out;
struct value *calein_scope;
};
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_proc_SPACEname, struct value *calein_out, struct value *calein_scope);
struct global_SCOPEcalein_compile_SPACEerror_ARG_local_vars {
struct value *calein_msg;
};
struct value *global_SCOPEcalein_compile_SPACEerror_ARG(struct value *calein_msg);
struct global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG_local_vars {
struct value *calein_ir;
struct value *calein_out;
struct value *calein_context;
struct value *calein_scope;
struct value *calein_args;
struct value *calein_var_SPACEscope;
struct value *calein_sep;
struct value *calein_name;
struct value *calein_function_SPACEinfo;
struct value *calein_proc_SPACEname;
struct value *calein_adjusted_SPACEproc_SPACEname;
struct value *calein_old_SPACEfunction_SPACElist;
struct value *calein_old_SPACEvariable_SPACElist;
struct value *calein_ident;
struct value *calein_vars;
struct value *calein_items;
struct value *calein_expected_SPACEsep;
struct value *calein_old_SPACElength;
};
struct value *global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(struct value *calein_ir, struct value *calein_out, struct value *calein_context, struct value *calein_scope);
struct global_SCOPEcalein_compile_ARG_local_vars {
struct value *calein_tree;
struct value *calein_ir_SPACEargs;
struct value *calein_args;
struct value *calein_ir_SPACEitems;
struct value *calein_items;
};
struct value *global_SCOPEcalein_compile_ARG(struct value *calein_tree);

struct value *calein_true;
struct value *calein_false;
struct value *calein_tab;
struct value *calein_tab_SPACEstring;
struct value *calein_new_SPACEline;
struct value *calein_space;
struct value *calein_quote;
struct value *calein_number_SPACEsigil;
struct value *calein_open_SPACEparen;
struct value *calein_close_SPACEparen;
struct value *calein_star;
struct value *calein_plus;
struct value *calein_comma;
struct value *calein_minus;
struct value *calein_dot;
struct value *calein_slash;
struct value *calein_character_SPACE0;
struct value *calein_backslash;
struct value *calein_underscore;
struct value *calein_character_SPACEn;
struct value *calein_open_SPACEbrace;
struct value *calein_close_SPACEbrace;
struct value *global_SCOPEcalein__SPACE_ARGat_ARG(struct value *calein_list, struct value *calein_index){
struct global_SCOPEcalein__SPACE_ARGat_ARG_local_vars local_vars;
local_vars.calein_list = calein_list;
local_vars.calein_index = calein_index;
struct value *tmp_for_derefs = 0;
struct value *result = (({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_index),value_add_reference(value_make_number(0))))))) {
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);
(tmp_for_derefs = local_vars.calein_index, local_vars.calein_index = value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(local_vars.calein_index),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_index);

}
 0; }), global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_list)));
value_add_reference(result);
value_remove_reference(local_vars.calein_index);value_remove_reference(local_vars.calein_list);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = (value_boolean_is_true_remove_floating_reference(local_vars.calein_a) ? (local_vars.calein_a) : (local_vars.calein_b));
value_add_reference(result);
value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGand_ARG(struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = (value_boolean_is_true_remove_floating_reference(local_vars.calein_a) ? (local_vars.calein_b) : (local_vars.calein_a));
value_add_reference(result);
value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(local_vars.calein_a),value_add_reference(local_vars.calein_b))),value_add_reference(local_vars.calein_c));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
local_vars.calein_d = calein_d;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(local_vars.calein_a),value_add_reference(local_vars.calein_b))),value_add_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_d))));
value_add_reference(result);
value_remove_reference(local_vars.calein_d);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG(struct value *calein_x, struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_x = calein_x;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_a),value_add_reference(local_vars.calein_b)))))) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_a),value_add_reference(local_vars.calein_x)))) {
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_a, local_vars.calein_a = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_a),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_a);

}
 0; }), local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_remove_reference(local_vars.calein_x);return result;
}
struct value *global_SCOPEcalein_reverse_SPACEstring_ARG(struct value *calein_s){
struct global_SCOPEcalein_reverse_SPACEstring_ARG_local_vars local_vars;
local_vars.calein_rev = 0;
local_vars.calein_i = 0;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_rev = value_add_reference(value_make_string_from_c_string(""))), (local_vars.calein_i = value_add_reference(value_make_number(0))), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_i),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_s)))))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_s))),value_add_reference(local_vars.calein_i))),value_add_reference(value_make_number(1)))),value_add_reference(local_vars.calein_s))),value_add_reference(local_vars.calein_rev));
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_i),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), local_vars.calein_rev);
value_add_reference(result);
value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_rev);value_remove_reference(local_vars.calein_s);return result;
}
struct value *global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(struct value *calein_number){
struct global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_s = 0;
local_vars.calein_number = calein_number;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_s = value_add_reference(value_make_string_from_c_string(""))), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_number),value_add_reference(value_make_number(0))))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGmod_ARG(value_add_reference(local_vars.calein_number),value_add_reference(value_make_number(10)))),value_add_reference(calein_character_SPACE0))),value_add_reference(local_vars.calein_s));
(tmp_for_derefs = local_vars.calein_number, local_vars.calein_number = value_add_reference(global_SCOPEcalein__SPACE_ARG_SLASH_ARG(value_add_reference(local_vars.calein_number),value_add_reference(value_make_number(10)))), value_remove_reference(tmp_for_derefs),local_vars.calein_number);

}
 0; }), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_s),value_add_reference(value_make_string_from_c_string("")))) ? (value_make_string_from_c_string("0")) : (global_SCOPEcalein_reverse_SPACEstring_ARG(value_add_reference(local_vars.calein_s)))));
value_add_reference(result);
value_remove_reference(local_vars.calein_s);value_remove_reference(local_vars.calein_number);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEdigit(struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGis_SPACEdigit_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG(value_add_reference(local_vars.calein_c),value_add_reference(value_make_number(48)),value_add_reference(value_make_number(58)));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_space))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_tab))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_new_SPACEline))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);return result;
}
struct value *calein_line_SPACEnumber;
struct value *calein_column_SPACEnumber;
struct value *calein_ungotten_SPACEcharacter;
struct value *global_SCOPEcalein_get_SPACEcharacter(void){
struct global_SCOPEcalein_get_SPACEcharacter_local_vars local_vars;
local_vars.calein_tmp = 0;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_tmp = value_add_reference(calein_false)), (value_boolean_is_true_remove_floating_reference(calein_ungotten_SPACEcharacter) ? (((tmp_for_derefs = local_vars.calein_tmp, local_vars.calein_tmp = value_add_reference(calein_ungotten_SPACEcharacter), value_remove_reference(tmp_for_derefs),local_vars.calein_tmp), (tmp_for_derefs = calein_ungotten_SPACEcharacter, calein_ungotten_SPACEcharacter = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),calein_ungotten_SPACEcharacter))) : ((tmp_for_derefs = local_vars.calein_tmp, local_vars.calein_tmp = value_add_reference(global_SCOPEcalein_read_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_tmp))), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_tmp),value_add_reference(calein_new_SPACEline))) ? (((tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(calein_line_SPACEnumber),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), (tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(value_make_number(1)), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))) : ((tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(calein_column_SPACEnumber),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))), local_vars.calein_tmp);
value_add_reference(result);
value_remove_reference(local_vars.calein_tmp);return result;
}
struct value *global_SCOPEcalein_unget_SPACEcharacter_ARG(struct value *calein_c){
struct global_SCOPEcalein_unget_SPACEcharacter_ARG_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = ((tmp_for_derefs = calein_ungotten_SPACEcharacter, calein_ungotten_SPACEcharacter = value_add_reference(local_vars.calein_c), value_remove_reference(tmp_for_derefs),calein_ungotten_SPACEcharacter), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_new_SPACEline))) ? (((tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(calein_line_SPACEnumber),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), (tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(value_make_number(0)),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))) : ((tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(calein_column_SPACEnumber),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);return result;
}
struct value *global_SCOPEcalein_reverse_SPACElist_ARG(struct value *calein_list){
struct global_SCOPEcalein_reverse_SPACElist_ARG_local_vars local_vars;
local_vars.calein_acc = 0;
local_vars.calein_list = calein_list;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_acc = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_list)) {
(tmp_for_derefs = local_vars.calein_acc, local_vars.calein_acc = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_list))),value_add_reference(local_vars.calein_acc))), value_remove_reference(tmp_for_derefs),local_vars.calein_acc);
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);

}
 0; }), local_vars.calein_acc);
value_add_reference(result);
value_remove_reference(local_vars.calein_acc);value_remove_reference(local_vars.calein_list);return result;
}
struct value *calein_literal_SPACEkind;
struct value *calein_number_SPACEkind;
struct value *calein_sequence_SPACEkind;
struct value *calein_action_SPACEkind;
struct value *global_SCOPEcalein_make_SPACEliteral_ARG(struct value *calein_val){
struct global_SCOPEcalein_make_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_val = calein_val;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_literal_SPACEkind),value_add_reference(local_vars.calein_val));
value_add_reference(result);
value_remove_reference(local_vars.calein_val);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(struct value *calein_p){
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral_local_vars local_vars;
local_vars.calein_p = calein_p;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_p))),value_add_reference(calein_literal_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_p);return result;
}
struct value *global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(struct value *calein_lit){
struct global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_lit = calein_lit;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_lit));
value_add_reference(result);
value_remove_reference(local_vars.calein_lit);return result;
}
struct value *global_SCOPEcalein_make_SPACEnumber_ARG(struct value *calein_val){
struct global_SCOPEcalein_make_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_val = calein_val;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_number_SPACEkind),value_add_reference(local_vars.calein_val));
value_add_reference(result);
value_remove_reference(local_vars.calein_val);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(struct value *calein_p){
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber_local_vars local_vars;
local_vars.calein_p = calein_p;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_p))),value_add_reference(calein_number_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_p);return result;
}
struct value *global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(struct value *calein_num){
struct global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_num = calein_num;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_num));
value_add_reference(result);
value_remove_reference(local_vars.calein_num);return result;
}
struct value *global_SCOPEcalein_make_SPACEsequence_ARG(struct value *calein_list){
struct global_SCOPEcalein_make_SPACEsequence_ARG_local_vars local_vars;
local_vars.calein_list = calein_list;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_sequence_SPACEkind),value_add_reference(local_vars.calein_list));
value_add_reference(result);
value_remove_reference(local_vars.calein_list);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(struct value *calein_p){
struct global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence_local_vars local_vars;
local_vars.calein_p = calein_p;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_p))),value_add_reference(calein_sequence_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_p);return result;
}
struct value *global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(struct value *calein_seq){
struct global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG_local_vars local_vars;
local_vars.calein_seq = calein_seq;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_seq));
value_add_reference(result);
value_remove_reference(local_vars.calein_seq);return result;
}
struct value *global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args){
struct global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_args = calein_args;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_action_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_args))));
value_add_reference(result);
value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(struct value *calein_p){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction_local_vars local_vars;
local_vars.calein_p = calein_p;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_p))),value_add_reference(calein_action_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_p);return result;
}
struct value *global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(struct value *calein_action){
struct global_SCOPEcalein_name_SPACEof_SPACEaction_ARG_local_vars local_vars;
local_vars.calein_action = calein_action;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_action))));
value_add_reference(result);
value_remove_reference(local_vars.calein_action);return result;
}
struct value *global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(struct value *calein_action){
struct global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG_local_vars local_vars;
local_vars.calein_action = calein_action;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_action))));
value_add_reference(result);
value_remove_reference(local_vars.calein_action);return result;
}
struct value *global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(struct value *calein_n){
struct global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes_local_vars local_vars;
local_vars.calein_n = calein_n;
struct value *tmp_for_derefs = 0;
struct value *result = (({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_n),value_add_reference(value_make_number(0))))))) {
global_SCOPEcalein_write_ARG(value_add_reference(calein_tab_SPACEstring));
(tmp_for_derefs = local_vars.calein_n, local_vars.calein_n = value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(local_vars.calein_n),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_n);

}
 0; }));
value_add_reference(result);
value_remove_reference(local_vars.calein_n);return result;
}
struct value *global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(struct value *calein_tree, struct value *calein_indent){
struct global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG_local_vars local_vars;
local_vars.calein_items = 0;
local_vars.calein_args = 0;
local_vars.calein_tree = calein_tree;
local_vars.calein_indent = calein_indent;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(local_vars.calein_indent)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("String: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(value_add_reference(local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(local_vars.calein_indent)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("Number: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(value_add_reference(local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(local_vars.calein_indent)), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("Sequence:"))), (local_vars.calein_items = value_add_reference(global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(value_add_reference(local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_items)) {
global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_items))),value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_indent),value_add_reference(value_make_number(1)))));
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(local_vars.calein_indent)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("Action: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree)))), (local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_indent),value_add_reference(value_make_number(1)))));
global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("Arg at ")));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))));
global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))),value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_indent),value_add_reference(value_make_number(1)))));
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }))) : ((global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(local_vars.calein_indent)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("unrecognized kind of tree: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_tree))))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_indent);value_remove_reference(local_vars.calein_tree);return result;
}
struct value *global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG(struct value *calein_s){
struct global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG_local_vars local_vars;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_s))),value_add_reference(value_make_number(1)))),value_add_reference(local_vars.calein_s));
value_add_reference(result);
value_remove_reference(local_vars.calein_s);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG(struct value *calein_c, struct value *calein_c_SPACE1, struct value *calein_c_SPACE2, struct value *calein_c_SPACE3, struct value *calein_c_SPACE4){
struct global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG_local_vars local_vars;
local_vars.calein_c = calein_c;
local_vars.calein_c_SPACE1 = calein_c_SPACE1;
local_vars.calein_c_SPACE2 = calein_c_SPACE2;
local_vars.calein_c_SPACE3 = calein_c_SPACE3;
local_vars.calein_c_SPACE4 = calein_c_SPACE4;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_c_SPACE1))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_c_SPACE2))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_c_SPACE3))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_c_SPACE4))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c_SPACE4);value_remove_reference(local_vars.calein_c_SPACE3);value_remove_reference(local_vars.calein_c_SPACE2);value_remove_reference(local_vars.calein_c_SPACE1);value_remove_reference(local_vars.calein_c);return result;
}
struct value *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars, struct value *calein_msg){
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG_local_vars local_vars;
local_vars.global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars = global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("Parse error at line "))), global_SCOPEcalein_write_ARG(value_add_reference(calein_line_SPACEnumber)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string(", column "))), global_SCOPEcalein_write_ARG(value_add_reference(calein_column_SPACEnumber)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string(": "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(local_vars.calein_msg)), (tmp_for_derefs = global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);return result;
}
struct value *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(struct value *calein_first_SPACEchild){
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars local_vars;
local_vars.calein_tree = 0;
local_vars.calein_again_SPACEin_SPACEaction = 0;
local_vars.calein_children = 0;
local_vars.calein_literal = 0;
local_vars.calein_paren = 0;
local_vars.calein_child = 0;
local_vars.calein_c = 0;
local_vars.calein_first_SPACEchild = calein_first_SPACEchild;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_tree = value_add_reference(calein_false)), (local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(calein_true)), (local_vars.calein_children = value_add_reference(calein_false)), (local_vars.calein_literal = value_add_reference(value_make_string_from_c_string(""))), (local_vars.calein_paren = value_add_reference(calein_false)), (local_vars.calein_child = value_add_reference(calein_false)), (local_vars.calein_c = value_add_reference(value_make_number(0))), (value_boolean_is_true_remove_floating_reference(local_vars.calein_first_SPACEchild) ? ((tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(value_make_number(0)),value_add_reference(local_vars.calein_first_SPACEchild))),value_add_reference(local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children)) : (calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_again_SPACEin_SPACEaction)) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_c))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_dot))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEparen))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEbrace)))))) {
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEaction, local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEaction);
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_children)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_children))))),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal)))))) {
global_SCOPEcalein_trim_SPACEright_ARG(value_add_reference(local_vars.calein_literal));

} else {
calein_false;
}
} else {
global_SCOPEcalein_trim_SPACEright_ARG(value_add_reference(local_vars.calein_literal));
}if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEparen))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEbrace)))))) {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));

} else {
calein_false;
}if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal))),value_add_reference(value_make_number(0))))) {
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(local_vars.calein_first_SPACEchild), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(value_add_reference(local_vars.calein_literal),value_add_reference(global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(local_vars.calein_children))))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
}(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEaction, local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEaction);

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_quote),value_add_reference(calein_number_SPACEsigil),value_add_reference(calein_open_SPACEparen),value_add_reference(calein_open_SPACEbrace)))) {
(tmp_for_derefs = local_vars.calein_paren, local_vars.calein_paren = value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_open_SPACEparen))), value_remove_reference(tmp_for_derefs),local_vars.calein_paren);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_paren)))) {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));

} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_child, local_vars.calein_child = value_add_reference(global_SCOPEcalein_parse_ARG(value_add_reference(local_vars.calein_paren))), value_remove_reference(tmp_for_derefs),local_vars.calein_child);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_child)))) {
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("expected argument")));

} else {
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal))),value_add_reference(local_vars.calein_child))),value_add_reference(local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children);
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_paren)) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEparen)))))) {
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("expected close paren")));

} else {
calein_false;
}
} else {
calein_false;
}}
} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(value_add_reference(local_vars.calein_c)))) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal))),value_add_reference(value_make_number(0))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_space),value_add_reference(local_vars.calein_literal));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG(value_add_reference(local_vars.calein_literal))),value_add_reference(calein_space)))) {
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_children)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_children))))),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal)))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_space),value_add_reference(local_vars.calein_literal));

} else {
calein_false;
}
} else {
calein_false;
}
} else {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_space),value_add_reference(local_vars.calein_literal));
}}
} else {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_literal));
}}}
}
 0; }), local_vars.calein_tree);
value_add_reference(result);
return result;
}
struct value *global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars, struct value *calein_msg){
struct global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG_local_vars local_vars;
local_vars.global_SCOPEcalein_parse_ARG_local_vars = global_SCOPEcalein_parse_ARG_local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("Parse error: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(local_vars.calein_msg)), (tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral, global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral), (tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence, global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence), (tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again, global_SCOPEcalein_parse_ARG_local_vars->calein_again = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);return result;
}
struct value *global_SCOPEcalein_parse_ARG(struct value *calein_at_SPACEstart_SPACEof_SPACEexpression){
struct global_SCOPEcalein_parse_ARG_local_vars local_vars;
local_vars.calein_again = 0;
local_vars.calein_literal = 0;
local_vars.calein_in_SPACEescape = 0;
local_vars.calein_again_SPACEin_SPACEliteral = 0;
local_vars.calein_again_SPACEin_SPACEsequence = 0;
local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = 0;
local_vars.calein_children = 0;
local_vars.calein_c = 0;
local_vars.calein_tree = 0;
local_vars.calein_child = 0;
local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression = calein_at_SPACEstart_SPACEof_SPACEexpression;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_again = value_add_reference(calein_true)), (local_vars.calein_literal = value_add_reference(value_make_number(0))), (local_vars.calein_in_SPACEescape = value_add_reference(calein_false)), (local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(calein_true)), (local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(calein_true)), (local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(calein_false)), (local_vars.calein_children = value_add_reference(calein_false)), (local_vars.calein_c = value_add_reference(value_make_number(0))), (local_vars.calein_tree = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_again)) {
(tmp_for_derefs = local_vars.calein_again, local_vars.calein_again = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again);
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_quote)))) {
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);
(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);
while (value_boolean_is_true_remove_floating_reference(local_vars.calein_again_SPACEin_SPACEliteral)) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_c)))) {
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("unterminated string literal")));

} else {
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_in_SPACEescape)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_backslash))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_quote)))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_literal));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_character_SPACEn)))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_new_SPACEline),value_add_reference(local_vars.calein_literal));

} else {
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("undefined escape sequence")));
}}(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_backslash)))) {
(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_quote)))) {
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_make_SPACEliteral_ARG(value_add_reference(local_vars.calein_literal))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression)) {
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(local_vars.calein_tree))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {
calein_false;
}
} else {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_literal));
}}}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_number_SPACEsigil)))) {
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(value_make_number(0)), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);
(tmp_for_derefs = local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral, local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral);
while (value_boolean_is_true_remove_floating_reference(local_vars.calein_again_SPACEin_SPACEliteral)) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGand_ARG(value_add_reference(local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral),value_add_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_c)))))) {
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("Unexpected EOF at beginning of number")));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEdigit(value_add_reference(local_vars.calein_c)))))) {
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_c)) {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));

} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_make_SPACEnumber_ARG(value_add_reference(local_vars.calein_literal))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression)) {
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(local_vars.calein_tree))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {
calein_false;
}
} else {
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARG_STAR_ARG(value_add_reference(local_vars.calein_literal),value_add_reference(value_make_number(10)))),value_add_reference(global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_character_SPACE0))))), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);
(tmp_for_derefs = local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral, local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral);
}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_open_SPACEbrace)))) {
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_children);
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEsequence, local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEsequence);
while (value_boolean_is_true_remove_floating_reference(local_vars.calein_again_SPACEin_SPACEsequence)) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_c)))) {
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(value_make_string_from_c_string("unexpected EOF in sequence")));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEbrace)))) {
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEsequence, local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEsequence);
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_make_SPACEsequence_ARG(value_add_reference(global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(local_vars.calein_children))))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));
local_vars.calein_child = value_add_reference(global_SCOPEcalein_parse_ARG(value_add_reference(calein_true)));
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_child)) {
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_child),value_add_reference(local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children);

} else {
calein_false;
}}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(value_add_reference(local_vars.calein_c)))) {
(tmp_for_derefs = local_vars.calein_again, local_vars.calein_again = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again);

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_close_SPACEbrace)))) {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));

} else {
if (value_boolean_is_true_remove_floating_reference(local_vars.calein_c)) {
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(local_vars.calein_c));
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(calein_false))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {
calein_false;
}}}}}}
}
 0; }), local_vars.calein_tree);
value_add_reference(result);
return result;
}
struct value *global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(struct value *calein_t, struct value *calein_s){
struct global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_i = 0;
local_vars.calein_t = calein_t;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_i = value_add_reference(value_make_number(0))), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_i),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_t)))))))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(local_vars.calein_i),value_add_reference(local_vars.calein_t))),value_add_reference(local_vars.calein_s));
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_i),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }));
value_add_reference(result);
value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_s);value_remove_reference(local_vars.calein_t);return result;
}
struct value *global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(struct value *calein_s, struct value *calein_t){
struct global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_u = 0;
local_vars.calein_s = calein_s;
local_vars.calein_t = calein_t;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_u = value_add_reference(value_make_string_from_c_string(""))), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_s),value_add_reference(local_vars.calein_u)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_t),value_add_reference(local_vars.calein_u)), local_vars.calein_u);
value_add_reference(result);
value_remove_reference(local_vars.calein_u);value_remove_reference(local_vars.calein_t);value_remove_reference(local_vars.calein_s);return result;
}
struct value *calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers;
struct value *global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(struct value *calein_str, struct value *calein_c){
struct global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG_local_vars local_vars;
local_vars.calein_str = calein_str;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = ((tmp_for_derefs = calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers, calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_str))),value_add_reference(calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers))), value_remove_reference(tmp_for_derefs),calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_str);return result;
}
struct value *global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(struct value *calein_action){
struct global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG_local_vars local_vars;
local_vars.calein_name = 0;
local_vars.calein_args = 0;
local_vars.calein_ident = 0;
local_vars.calein_i = 0;
local_vars.calein_c = 0;
local_vars.calein_added = 0;
local_vars.calein_substitutions = 0;
local_vars.calein_action = calein_action;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_name = value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_action)))), (local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_action)))), (local_vars.calein_ident = value_add_reference(value_make_string_from_c_string("calein_"))), (local_vars.calein_i = value_add_reference(value_make_number(0))), (local_vars.calein_c = value_add_reference(calein_false)), (local_vars.calein_added = value_add_reference(calein_false)), (local_vars.calein_substitutions = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_i),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_name)))))))) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(local_vars.calein_i),value_add_reference(local_vars.calein_name))), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
(tmp_for_derefs = local_vars.calein_added, local_vars.calein_added = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_added);
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);
while (value_boolean_is_true_remove_floating_reference(local_vars.calein_substitutions)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_substitutions)))))))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_substitutions))))),value_add_reference(local_vars.calein_ident));
(tmp_for_derefs = local_vars.calein_added, local_vars.calein_added = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_added);
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);

} else {
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_substitutions))), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);
}
}
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_added)))) {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_ident));

} else {
calein_false;
}if (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_i),value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args)))))))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_ARG")),value_add_reference(local_vars.calein_ident));
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

} else {
calein_false;
}
} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_i),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), (value_boolean_is_true_remove_floating_reference(local_vars.calein_args) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_ARG")),value_add_reference(local_vars.calein_ident))) : (calein_false)), local_vars.calein_ident);
value_add_reference(result);
value_remove_reference(local_vars.calein_substitutions);value_remove_reference(local_vars.calein_added);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_action);return result;
}
struct value *global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(struct value *calein_literal){
struct global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_string = 0;
local_vars.calein_i = 0;
local_vars.calein_c = 0;
local_vars.calein_literal = calein_literal;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_string = value_add_reference(value_make_string_from_c_string("\""))), (local_vars.calein_i = value_add_reference(value_make_number(0))), (local_vars.calein_c = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_i),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_literal)))))))) {
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(local_vars.calein_i),value_add_reference(local_vars.calein_literal))), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_quote)))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("\\\"")),value_add_reference(local_vars.calein_string));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_backslash)))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("\\\\")),value_add_reference(local_vars.calein_string));

} else {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(calein_new_SPACEline)))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("\\n")),value_add_reference(local_vars.calein_string));

} else {
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_c),value_add_reference(local_vars.calein_string));
}}}(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(local_vars.calein_i),value_add_reference(value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_quote),value_add_reference(local_vars.calein_string)), local_vars.calein_string);
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_string);value_remove_reference(local_vars.calein_literal);return result;
}
struct value *calein_ir_SPACEcall_SPACEkind;
struct value *calein_ir_SPACEprocedure_SPACEkind;
struct value *calein_ir_SPACEsequence_SPACEkind;
struct value *calein_ir_SPACEif_SPACEkind;
struct value *calein_ir_SPACEwhile_SPACEkind;
struct value *calein_ir_SPACEvariable_SPACEkind;
struct value *calein_ir_SPACEassignment_SPACEkind;
struct value *calein_ir_SPACEliteral_SPACEkind;
struct value *calein_ir_SPACEnumber_SPACEkind;
struct value *global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args){
struct global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_args = calein_args;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEcall_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_args))));
value_add_reference(result);
value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEcall_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG(struct value *calein_ir){
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG(struct value *calein_ir){
struct global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_ARG(struct value *calein_name, struct value *calein_body){
struct global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_body = calein_body;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEprocedure_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_body))));
value_add_reference(result);
value_remove_reference(local_vars.calein_body);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEprocedure_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *calein_ir){
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *calein_ir){
struct global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEsequence_ARG(struct value *calein_items){
struct global_SCOPEcalein_make_SPACEir_SPACEsequence_ARG_local_vars local_vars;
local_vars.calein_items = calein_items;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEsequence_SPACEkind),value_add_reference(local_vars.calein_items));
value_add_reference(result);
value_remove_reference(local_vars.calein_items);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEsequence_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG(struct value *calein_ir){
struct global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_ARG(struct value *calein_condition, struct value *calein_then, struct value *calein_else){
struct global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_ARG_local_vars local_vars;
local_vars.calein_condition = calein_condition;
local_vars.calein_then = calein_then;
local_vars.calein_else = calein_else;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEif_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_condition),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_then),value_add_reference(local_vars.calein_else))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_else);value_remove_reference(local_vars.calein_then);value_remove_reference(local_vars.calein_condition);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEif_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir){
struct global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir){
struct global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(struct value *calein_ir){
struct global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_ARG(struct value *calein_condition, struct value *calein_body){
struct global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_ARG_local_vars local_vars;
local_vars.calein_condition = calein_condition;
local_vars.calein_body = calein_body;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEwhile_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_condition),value_add_reference(local_vars.calein_body))));
value_add_reference(result);
value_remove_reference(local_vars.calein_body);value_remove_reference(local_vars.calein_condition);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEwhile_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(struct value *calein_ir){
struct global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(struct value *calein_ir){
struct global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_ARG(struct value *calein_name, struct value *calein_initial_SPACEvalue){
struct global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_initial_SPACEvalue = calein_initial_SPACEvalue;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEvariable_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_initial_SPACEvalue))));
value_add_reference(result);
value_remove_reference(local_vars.calein_initial_SPACEvalue);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEvariable_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(struct value *calein_ir){
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(struct value *calein_ir){
struct global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_ARG(struct value *calein_name, struct value *calein_value){
struct global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_value = calein_value;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEassignment_SPACEkind),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_value))));
value_add_reference(result);
value_remove_reference(local_vars.calein_value);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEassignment_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(struct value *calein_ir){
struct global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG(struct value *calein_ir){
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir))));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEliteral_ARG(struct value *calein_literal){
struct global_SCOPEcalein_make_SPACEir_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_literal = calein_literal;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEliteral_SPACEkind),value_add_reference(local_vars.calein_literal));
value_add_reference(result);
value_remove_reference(local_vars.calein_literal);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEliteral_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG(struct value *calein_ir){
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEnumber_ARG(struct value *calein_number){
struct global_SCOPEcalein_make_SPACEir_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_number = calein_number;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(calein_ir_SPACEnumber_SPACEkind),value_add_reference(local_vars.calein_number));
value_add_reference(result);
value_remove_reference(local_vars.calein_number);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber(struct value *calein_ir){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(calein_ir_SPACEnumber_SPACEkind));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG(struct value *calein_ir){
struct global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_ir = calein_ir;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_ir));
value_add_reference(result);
value_remove_reference(local_vars.calein_ir);return result;
}
struct value *calein_expression_SPACEcontext;
struct value *calein_statement_SPACEcontext;
struct value *calein_definition_SPACEcontext;
struct value *calein_declaration_SPACEcontext;
struct value *calein_initializer_SPACEcontext;
struct value *calein_nested_SPACEdefinition_SPACEcontext;
struct value *calein_procedure_SPACEdefinition_SPACEcontext;
struct value *global_SCOPEcalein__SPACE_ARGcontains_ARG(struct value *calein_list, struct value *calein_elem){
struct global_SCOPEcalein__SPACE_ARGcontains_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_list = calein_list;
local_vars.calein_elem = calein_elem;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_list)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_list))),value_add_reference(local_vars.calein_elem)))) {
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_list);
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

} else {
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);
}
}
 0; }), local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_elem);value_remove_reference(local_vars.calein_list);return result;
}
struct value *global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(struct value *calein_key, struct value *calein_alist){
struct global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_key = calein_key;
local_vars.calein_alist = calein_alist;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_alist)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_alist))))),value_add_reference(local_vars.calein_key)))) {
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_alist))))), value_remove_reference(tmp_for_derefs),local_vars.calein_found);
(tmp_for_derefs = local_vars.calein_alist, local_vars.calein_alist = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_alist);

} else {
(tmp_for_derefs = local_vars.calein_alist, local_vars.calein_alist = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_alist))), value_remove_reference(tmp_for_derefs),local_vars.calein_alist);
}
}
 0; }), local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_alist);value_remove_reference(local_vars.calein_key);return result;
}
struct value *calein_variable_SPACElist;
struct value *calein_function_SPACElist;
struct value *global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(struct value *calein_var, struct value *calein_scope){
struct global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG_local_vars local_vars;
local_vars.calein_old_SPACEscope = 0;
local_vars.calein_var = calein_var;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_old_SPACEscope = value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_var),value_add_reference(calein_variable_SPACElist)))), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_old_SPACEscope),value_add_reference(local_vars.calein_scope))))) ? ((tmp_for_derefs = calein_variable_SPACElist, calein_variable_SPACElist = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_var),value_add_reference(local_vars.calein_scope))),value_add_reference(calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),calein_variable_SPACElist)) : (calein_true)));
value_add_reference(result);
value_remove_reference(local_vars.calein_old_SPACEscope);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_var);return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(struct value *calein_context){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation_local_vars local_vars;
local_vars.calein_context = calein_context;
struct value *tmp_for_derefs = 0;
struct value *result = global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_definition_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_initializer_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_nested_SPACEdefinition_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_procedure_SPACEdefinition_SPACEcontext))))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_declaration_SPACEcontext))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_context);return result;
}
struct value *calein_global_SPACEscope;
struct value *global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(struct value *calein_name, struct value *calein_var_SPACEscope, struct value *calein_scope, struct value *calein_out){
struct global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_var_SPACEscope = calein_var_SPACEscope;
local_vars.calein_scope = calein_scope;
local_vars.calein_out = calein_out;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(calein_global_SPACEscope))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_out))) : (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_scope))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("local_vars.")),value_add_reference(local_vars.calein_out)))) : ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_local_vars->")),value_add_reference(local_vars.calein_out))))), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_out))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_var_SPACEscope);value_remove_reference(local_vars.calein_name);return result;
}
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(struct value *calein_proc_SPACEname, struct value *calein_out){
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_proc_SPACEname = calein_proc_SPACEname;
local_vars.calein_out = calein_out;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_local_vars")),value_add_reference(local_vars.calein_out)));
value_add_reference(result);
value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);return result;
}
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_ir, struct value *calein_proc_SPACEname, struct value *calein_out, struct value *calein_scope){
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_args = 0;
local_vars.calein_ident = 0;
local_vars.calein_ir = calein_ir;
local_vars.calein_proc_SPACEname = calein_proc_SPACEname;
local_vars.calein_out = calein_out;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" {\n")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(calein_global_SPACEscope))))) ? ((global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_proc_SPACEname)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out)))) : (calein_false)), (local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir)))))), (local_vars.calein_ident = value_add_reference(calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(calein_variable_SPACElist))),value_add_reference(local_vars.calein_proc_SPACEname)))))) {
global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(local_vars.calein_proc_SPACEname));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out));

} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_nested_SPACEdefinition_SPACEcontext),value_add_reference(local_vars.calein_proc_SPACEname)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("};\n")),value_add_reference(local_vars.calein_out)));
value_add_reference(result);
value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);value_remove_reference(local_vars.calein_ir);return result;
}
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_proc_SPACEname, struct value *calein_out, struct value *calein_scope){
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_proc_SPACEname = calein_proc_SPACEname;
local_vars.calein_out = calein_out;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_scope))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" local_vars")),value_add_reference(local_vars.calein_out)))) : ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" *")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_local_vars")),value_add_reference(local_vars.calein_out))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);return result;
}
struct value *calein_continue;
struct value *global_SCOPEcalein_compile_SPACEerror_ARG(struct value *calein_msg){
struct global_SCOPEcalein_compile_SPACEerror_ARG_local_vars local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("compile error: "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(local_vars.calein_msg)), (tmp_for_derefs = calein_continue, calein_continue = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),calein_continue));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);return result;
}
struct value *global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(struct value *calein_ir, struct value *calein_out, struct value *calein_context, struct value *calein_scope){
struct global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG_local_vars local_vars;
local_vars.calein_args = 0;
local_vars.calein_var_SPACEscope = 0;
local_vars.calein_sep = 0;
local_vars.calein_name = 0;
local_vars.calein_function_SPACEinfo = 0;
local_vars.calein_proc_SPACEname = 0;
local_vars.calein_adjusted_SPACEproc_SPACEname = 0;
local_vars.calein_old_SPACEfunction_SPACElist = 0;
local_vars.calein_old_SPACEvariable_SPACElist = 0;
local_vars.calein_ident = 0;
local_vars.calein_vars = 0;
local_vars.calein_items = 0;
local_vars.calein_expected_SPACEsep = 0;
local_vars.calein_old_SPACElength = 0;
local_vars.calein_ir = calein_ir;
local_vars.calein_out = calein_out;
local_vars.calein_context = calein_context;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_args = value_add_reference(calein_false)), (local_vars.calein_var_SPACEscope = value_add_reference(calein_false)), (local_vars.calein_sep = value_add_reference(calein_false)), (local_vars.calein_name = value_add_reference(calein_false)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall(value_add_reference(local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(local_vars.calein_context))) ? (((tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG(value_add_reference(local_vars.calein_ir))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), (tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG(value_add_reference(local_vars.calein_ir))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), (tmp_for_derefs = local_vars.calein_var_SPACEscope, local_vars.calein_var_SPACEscope = value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_name),value_add_reference(calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),local_vars.calein_var_SPACEscope), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(local_vars.calein_args),value_add_reference(global_SCOPEcalein_not_ARG(value_add_reference(local_vars.calein_var_SPACEscope))))) ? (((local_vars.calein_function_SPACEinfo = value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_name),value_add_reference(calein_function_SPACElist)))), (value_boolean_is_true_remove_floating_reference(local_vars.calein_function_SPACEinfo) ? ((tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_function_SPACEinfo))), value_remove_reference(tmp_for_derefs),local_vars.calein_name)) : ((tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(calein_global_SPACEscope),value_add_reference(global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(value_make_string_from_c_string("_SCOPE")),value_add_reference(local_vars.calein_name))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name))), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(")),value_add_reference(local_vars.calein_out)), (tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (value_boolean_is_true_remove_floating_reference(local_vars.calein_function_SPACEinfo) ? ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_function_SPACEinfo))),value_add_reference(calein_global_SPACEscope))))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("&local_vars")),value_add_reference(local_vars.calein_out)), (tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string(",")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep))) : (calein_false))) : (calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_sep),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("value_add_reference(")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out));
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string(",")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep);
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out))) : (calein_false)))) : ((global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out))) : (calein_false))))))) : (calein_false)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure(value_add_reference(local_vars.calein_ir))) ? (((local_vars.calein_proc_SPACEname = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir)))))), (local_vars.calein_adjusted_SPACEproc_SPACEname = value_add_reference(global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(value_make_string_from_c_string("_SCOPE")),value_add_reference(local_vars.calein_proc_SPACEname)))))), (tmp_for_derefs = calein_function_SPACElist, calein_function_SPACElist = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(local_vars.calein_adjusted_SPACEproc_SPACEname),value_add_reference(local_vars.calein_scope))))),value_add_reference(calein_function_SPACElist))), value_remove_reference(tmp_for_derefs),calein_function_SPACElist), (tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(local_vars.calein_adjusted_SPACEproc_SPACEname), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname), (local_vars.calein_old_SPACEfunction_SPACElist = value_add_reference(calein_function_SPACElist)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_definition_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_procedure_SPACEdefinition_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_declaration_SPACEcontext))))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_declaration_SPACEcontext))) ? ((global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_ir),value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_declaration_SPACEcontext),value_add_reference(local_vars.calein_proc_SPACEname)))) : ((global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_procedure_SPACEdefinition_SPACEcontext),value_add_reference(local_vars.calein_proc_SPACEname))))), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(")),value_add_reference(local_vars.calein_out)), (local_vars.calein_old_SPACEvariable_SPACElist = value_add_reference(calein_variable_SPACElist)), (tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), (tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (local_vars.calein_ident = value_add_reference(calein_false)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(local_vars.calein_args),value_add_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(calein_global_SPACEscope))))))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(calein_global_SPACEscope))))) ? ((global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_proc_SPACEname)), (tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep))) : (calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_sep),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(local_vars.calein_out));
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep);

}
 0; }))) : (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("void")),value_add_reference(local_vars.calein_out)))), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_declaration_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out)))) : ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("{\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_proc_SPACEname)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_initializer_SPACEcontext),value_add_reference(local_vars.calein_proc_SPACEname)), (tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(calein_global_SPACEscope))))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("local_vars.")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_local_vars = ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("_local_vars;\n")),value_add_reference(local_vars.calein_out)))) : (calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("local_vars.")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" = ")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_ident),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out));
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *tmp_for_derefs = 0;\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *result = ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_proc_SPACEname)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\nvalue_add_reference(result);\n")),value_add_reference(local_vars.calein_out)), (local_vars.calein_vars = value_add_reference(calein_variable_SPACElist)), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_vars)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_vars))))),value_add_reference(local_vars.calein_proc_SPACEname)))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("value_remove_reference(")),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_vars))))),value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_proc_SPACEname),value_add_reference(local_vars.calein_out));
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(");")),value_add_reference(local_vars.calein_out));
(tmp_for_derefs = local_vars.calein_vars, local_vars.calein_vars = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_vars))), value_remove_reference(tmp_for_derefs),local_vars.calein_vars);

} else {
(tmp_for_derefs = local_vars.calein_vars, local_vars.calein_vars = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_vars);
}
}
 0; }), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("return result;\n}\n")),value_add_reference(local_vars.calein_out))))), (tmp_for_derefs = calein_variable_SPACElist, calein_variable_SPACElist = value_add_reference(local_vars.calein_old_SPACEvariable_SPACElist), value_remove_reference(tmp_for_derefs),calein_variable_SPACElist))) : (calein_false)), (tmp_for_derefs = calein_function_SPACElist, calein_function_SPACElist = value_add_reference(local_vars.calein_old_SPACEfunction_SPACElist), value_remove_reference(tmp_for_derefs),calein_function_SPACElist))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence(value_add_reference(local_vars.calein_ir))) ? (((local_vars.calein_items = value_add_reference(global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG(value_add_reference(local_vars.calein_ir)))), (local_vars.calein_expected_SPACEsep = value_add_reference(value_make_string_from_c_string(""))), (local_vars.calein_old_SPACElength = value_add_reference(calein_false)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_expression_SPACEcontext))) ? (((tmp_for_derefs = local_vars.calein_expected_SPACEsep, local_vars.calein_expected_SPACEsep = value_add_reference(value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_expected_SPACEsep), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(")),value_add_reference(local_vars.calein_out)))) : (calein_false)), (tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(local_vars.calein_expected_SPACEsep), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (tmp_for_derefs = local_vars.calein_old_SPACElength, local_vars.calein_old_SPACElength = value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_out))), value_remove_reference(tmp_for_derefs),local_vars.calein_old_SPACElength), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_items)) {
if (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_old_SPACElength),value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_out)))))))) {
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_sep),value_add_reference(local_vars.calein_out));

} else {
calein_false;
}(tmp_for_derefs = local_vars.calein_old_SPACElength, local_vars.calein_old_SPACElength = value_add_reference(global_SCOPEcalein_length_ARG(value_add_reference(local_vars.calein_out))), value_remove_reference(tmp_for_derefs),local_vars.calein_old_SPACElength);
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_items))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope));
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_expression_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out))) : (calein_false)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif(value_add_reference(local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_expression_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(value_boolean_is_true_remove_floating_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(") ? (")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(") : (")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("))")),value_add_reference(local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("if (value_boolean_is_true_remove_floating_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")) {\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_statement_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("\n} else {\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_statement_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("}")),value_add_reference(local_vars.calein_out)))) : ((global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile(value_add_reference(local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("while (value_boolean_is_true_remove_floating_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")) {\n")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_statement_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("\n}\n")),value_add_reference(local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_expression_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("({ ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(local_vars.calein_ir),value_add_reference(local_vars.calein_out),value_add_reference(calein_statement_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" 0; })")),value_add_reference(local_vars.calein_out)))) : ((global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(local_vars.calein_context),value_add_reference(local_vars.calein_scope))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable(value_add_reference(local_vars.calein_ir))) ? (((tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein_not_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_name),value_add_reference(calein_variable_SPACElist))),value_add_reference(local_vars.calein_scope))))) ? (global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_scope))) : (calein_false)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_definition_SPACEcontext))),value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_nested_SPACEdefinition_SPACEcontext))))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("struct value *")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? ((global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(local_vars.calein_ir))))),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(");\n")),value_add_reference(local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_expression_SPACEcontext))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(local_vars.calein_ir))))),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("))")),value_add_reference(local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_initializer_SPACEcontext))) ? ((global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(local_vars.calein_ir))))),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" = 0;\n")),value_add_reference(local_vars.calein_out)))) : (calein_false)))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment(value_add_reference(local_vars.calein_ir))) ? (((tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), (tmp_for_derefs = local_vars.calein_var_SPACEscope, local_vars.calein_var_SPACEscope = value_add_reference(global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(local_vars.calein_name),value_add_reference(calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),local_vars.calein_var_SPACEscope), (value_boolean_is_true_remove_floating_reference(local_vars.calein_var_SPACEscope) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(local_vars.calein_context))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("(tmp_for_derefs = ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(", ")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out),value_add_reference(calein_expression_SPACEcontext),value_add_reference(local_vars.calein_scope)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("), value_remove_reference(tmp_for_derefs),")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(local_vars.calein_name),value_add_reference(local_vars.calein_var_SPACEscope),value_add_reference(local_vars.calein_scope),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out))) : (calein_false)))) : (calein_false)))) : ((global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string("error: var "))), global_SCOPEcalein_write_ARG(value_add_reference(local_vars.calein_name)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string(" not in scope in "))), global_SCOPEcalein_write_ARG(value_add_reference(local_vars.calein_context)), global_SCOPEcalein_write_ARG(value_add_reference(value_make_string_from_c_string(" in "))), global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(local_vars.calein_scope))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral(value_add_reference(local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(local_vars.calein_context))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("value_make_string_from_c_string(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG(value_add_reference(local_vars.calein_ir))),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out))) : (calein_false)))) : (calein_false)))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber(value_add_reference(local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(local_vars.calein_context))) ? ((global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string("value_make_number(")),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG(value_add_reference(local_vars.calein_ir))))),value_add_reference(local_vars.calein_out)), global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(")")),value_add_reference(local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(local_vars.calein_context),value_add_reference(calein_statement_SPACEcontext))) ? (global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(value_make_string_from_c_string(";\n")),value_add_reference(local_vars.calein_out))) : (calein_false)))) : (calein_false)))) : (global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(value_make_string_from_c_string("unrecognized ir kind"))))))))))))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_old_SPACElength);value_remove_reference(local_vars.calein_expected_SPACEsep);value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_vars);value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_old_SPACEvariable_SPACElist);value_remove_reference(local_vars.calein_old_SPACEfunction_SPACElist);value_remove_reference(local_vars.calein_adjusted_SPACEproc_SPACEname);value_remove_reference(local_vars.calein_proc_SPACEname);value_remove_reference(local_vars.calein_function_SPACEinfo);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_sep);value_remove_reference(local_vars.calein_var_SPACEscope);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_context);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_ir);return result;
}
struct value *calein_declarations;
struct value *calein_definitions;
struct value *calein_initializers;
struct value *calein_main;
struct value *global_SCOPEcalein_compile_ARG(struct value *calein_tree){
struct global_SCOPEcalein_compile_ARG_local_vars local_vars;
local_vars.calein_ir_SPACEargs = 0;
local_vars.calein_args = 0;
local_vars.calein_ir_SPACEitems = 0;
local_vars.calein_items = 0;
local_vars.calein_tree = calein_tree;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(value_add_reference(local_vars.calein_tree))) ? (((local_vars.calein_ir_SPACEargs = value_add_reference(calein_false)), (local_vars.calein_args = value_add_reference(global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree)))), (value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("note")))) ? (calein_false) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("define procedure  to do")))) ? (global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(0)))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(1)))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("define variable  with initial value")))) ? (global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(0)))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(1)))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("set  to")))) ? (global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(0)))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(1)))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("if  then  else")))) ? (global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_ARG(value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(0)))))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(1)))))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(2)))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(value_make_string_from_c_string("while  do")))) ? (global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_ARG(value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(0)))))))),value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(local_vars.calein_args),value_add_reference(value_make_number(1)))))))))) : ((({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_args)) {
(tmp_for_derefs = local_vars.calein_ir_SPACEargs, local_vars.calein_ir_SPACEargs = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_args))))))),value_add_reference(local_vars.calein_ir_SPACEargs))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir_SPACEargs);
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_ARG(value_add_reference(global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(local_vars.calein_tree))),value_add_reference(global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(local_vars.calein_ir_SPACEargs))))))))))))))))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(value_add_reference(local_vars.calein_tree))) ? (((local_vars.calein_ir_SPACEitems = value_add_reference(calein_false)), (local_vars.calein_items = value_add_reference(global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(value_add_reference(local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(local_vars.calein_items)) {
(tmp_for_derefs = local_vars.calein_ir_SPACEitems, local_vars.calein_ir_SPACEitems = value_add_reference(global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(global_SCOPEcalein_first_ARG(value_add_reference(local_vars.calein_items))))),value_add_reference(local_vars.calein_ir_SPACEitems))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir_SPACEitems);
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(global_SCOPEcalein_second_ARG(value_add_reference(local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }), global_SCOPEcalein_make_SPACEir_SPACEsequence_ARG(value_add_reference(global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(local_vars.calein_ir_SPACEitems)))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_make_SPACEir_SPACEnumber_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(value_add_reference(local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(value_add_reference(local_vars.calein_tree))) ? ((global_SCOPEcalein_make_SPACEir_SPACEliteral_ARG(value_add_reference(global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(value_add_reference(local_vars.calein_tree)))))))) : (global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(value_make_string_from_c_string("unsupported kind of tree"))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_ir_SPACEitems);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_ir_SPACEargs);value_remove_reference(local_vars.calein_tree);return result;
}
struct value *calein_tree;
struct value *calein_ir;

int main() {
struct value *tmp_for_derefs = 0;
calein_true = 0;
calein_false = 0;
calein_tab = 0;
calein_tab_SPACEstring = 0;
calein_new_SPACEline = 0;
calein_space = 0;
calein_quote = 0;
calein_number_SPACEsigil = 0;
calein_open_SPACEparen = 0;
calein_close_SPACEparen = 0;
calein_star = 0;
calein_plus = 0;
calein_comma = 0;
calein_minus = 0;
calein_dot = 0;
calein_slash = 0;
calein_character_SPACE0 = 0;
calein_backslash = 0;
calein_underscore = 0;
calein_character_SPACEn = 0;
calein_open_SPACEbrace = 0;
calein_close_SPACEbrace = 0;
calein_line_SPACEnumber = 0;
calein_column_SPACEnumber = 0;
calein_ungotten_SPACEcharacter = 0;
calein_literal_SPACEkind = 0;
calein_number_SPACEkind = 0;
calein_sequence_SPACEkind = 0;
calein_action_SPACEkind = 0;
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = 0;
calein_ir_SPACEcall_SPACEkind = 0;
calein_ir_SPACEprocedure_SPACEkind = 0;
calein_ir_SPACEsequence_SPACEkind = 0;
calein_ir_SPACEif_SPACEkind = 0;
calein_ir_SPACEwhile_SPACEkind = 0;
calein_ir_SPACEvariable_SPACEkind = 0;
calein_ir_SPACEassignment_SPACEkind = 0;
calein_ir_SPACEliteral_SPACEkind = 0;
calein_ir_SPACEnumber_SPACEkind = 0;
calein_expression_SPACEcontext = 0;
calein_statement_SPACEcontext = 0;
calein_definition_SPACEcontext = 0;
calein_declaration_SPACEcontext = 0;
calein_initializer_SPACEcontext = 0;
calein_nested_SPACEdefinition_SPACEcontext = 0;
calein_procedure_SPACEdefinition_SPACEcontext = 0;
calein_variable_SPACElist = 0;
calein_function_SPACElist = 0;
calein_global_SPACEscope = 0;
calein_continue = 0;
calein_declarations = 0;
calein_definitions = 0;
calein_initializers = 0;
calein_main = 0;
calein_tree = 0;
calein_ir = 0;

calein_true = value_add_reference(global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(value_make_number(0)),value_add_reference(value_make_number(0))));
calein_false = value_add_reference(global_SCOPEcalein_not_ARG(value_add_reference(calein_true)));
calein_tab = value_add_reference(value_make_number(9));
calein_tab_SPACEstring = value_add_reference(value_make_string_from_c_string(""));
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(calein_tab),value_add_reference(calein_tab_SPACEstring));
calein_new_SPACEline = value_add_reference(value_make_number(10));
calein_space = value_add_reference(value_make_number(32));
calein_quote = value_add_reference(value_make_number(34));
calein_number_SPACEsigil = value_add_reference(value_make_number(35));
calein_open_SPACEparen = value_add_reference(value_make_number(40));
calein_close_SPACEparen = value_add_reference(value_make_number(41));
calein_star = value_add_reference(value_make_number(42));
calein_plus = value_add_reference(value_make_number(43));
calein_comma = value_add_reference(value_make_number(44));
calein_minus = value_add_reference(value_make_number(45));
calein_dot = value_add_reference(value_make_number(46));
calein_slash = value_add_reference(value_make_number(47));
calein_character_SPACE0 = value_add_reference(value_make_number(48));
calein_backslash = value_add_reference(value_make_number(92));
calein_underscore = value_add_reference(value_make_number(95));
calein_character_SPACEn = value_add_reference(value_make_number(110));
calein_open_SPACEbrace = value_add_reference(value_make_number(123));
calein_close_SPACEbrace = value_add_reference(value_make_number(125));
calein_line_SPACEnumber = value_add_reference(value_make_number(1));
calein_column_SPACEnumber = value_add_reference(value_make_number(1));
calein_ungotten_SPACEcharacter = value_add_reference(calein_false);
calein_literal_SPACEkind = value_add_reference(value_make_string_from_c_string("literal kind"));
calein_number_SPACEkind = value_add_reference(value_make_string_from_c_string("number kind"));
calein_sequence_SPACEkind = value_add_reference(value_make_string_from_c_string("sequence kind"));
calein_action_SPACEkind = value_add_reference(value_make_string_from_c_string("action kind"));
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = value_add_reference(calein_false);
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_SPACE")),value_add_reference(calein_space));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_UNDERSCORE")),value_add_reference(calein_underscore));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_STAR")),value_add_reference(calein_star));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_PLUS")),value_add_reference(calein_plus));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_DASH")),value_add_reference(calein_minus));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_SLASH")),value_add_reference(calein_slash));
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(value_make_string_from_c_string("_COMMA")),value_add_reference(calein_comma));
calein_ir_SPACEcall_SPACEkind = value_add_reference(value_make_string_from_c_string("ir call kind"));
calein_ir_SPACEprocedure_SPACEkind = value_add_reference(value_make_string_from_c_string("ir procedure kind"));
calein_ir_SPACEsequence_SPACEkind = value_add_reference(value_make_string_from_c_string("ir sequence kind"));
calein_ir_SPACEif_SPACEkind = value_add_reference(value_make_string_from_c_string("ir if kind"));
calein_ir_SPACEwhile_SPACEkind = value_add_reference(value_make_string_from_c_string("ir while kind"));
calein_ir_SPACEvariable_SPACEkind = value_add_reference(value_make_string_from_c_string("ir variable kind"));
calein_ir_SPACEassignment_SPACEkind = value_add_reference(value_make_string_from_c_string("ir assignment kind"));
calein_ir_SPACEliteral_SPACEkind = value_add_reference(value_make_string_from_c_string("ir literal kind"));
calein_ir_SPACEnumber_SPACEkind = value_add_reference(value_make_string_from_c_string("ir number kind"));
calein_expression_SPACEcontext = value_add_reference(value_make_string_from_c_string("expression context"));
calein_statement_SPACEcontext = value_add_reference(value_make_string_from_c_string("statement context"));
calein_definition_SPACEcontext = value_add_reference(value_make_string_from_c_string("definition context"));
calein_declaration_SPACEcontext = value_add_reference(value_make_string_from_c_string("declaration context"));
calein_initializer_SPACEcontext = value_add_reference(value_make_string_from_c_string("initializer context"));
calein_nested_SPACEdefinition_SPACEcontext = value_add_reference(value_make_string_from_c_string("nested definition context"));
calein_procedure_SPACEdefinition_SPACEcontext = value_add_reference(value_make_string_from_c_string("procedure definition context"));
calein_variable_SPACElist = value_add_reference(calein_false);
calein_function_SPACElist = value_add_reference(calein_false);
calein_global_SPACEscope = value_add_reference(value_make_string_from_c_string("global"));
calein_continue = value_add_reference(calein_true);
calein_declarations = value_add_reference(value_make_string_from_c_string(""));
calein_definitions = value_add_reference(value_make_string_from_c_string(""));
calein_initializers = value_add_reference(value_make_string_from_c_string(""));
calein_main = value_add_reference(value_make_string_from_c_string(""));
calein_tree = value_add_reference(calein_false);
calein_ir = value_add_reference(calein_false);
while (value_boolean_is_true_remove_floating_reference(calein_continue)) {
(tmp_for_derefs = calein_tree, calein_tree = value_add_reference(global_SCOPEcalein_parse_ARG(value_add_reference(calein_true))), value_remove_reference(tmp_for_derefs),calein_tree);
if (value_boolean_is_true_remove_floating_reference(calein_tree)) {
(tmp_for_derefs = calein_ir, calein_ir = value_add_reference(global_SCOPEcalein_compile_ARG(value_add_reference(calein_tree))), value_remove_reference(tmp_for_derefs),calein_ir);
if (value_boolean_is_true_remove_floating_reference(calein_ir)) {
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(calein_ir),value_add_reference(calein_declarations),value_add_reference(calein_declaration_SPACEcontext),value_add_reference(calein_global_SPACEscope));
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(calein_ir),value_add_reference(calein_definitions),value_add_reference(calein_definition_SPACEcontext),value_add_reference(calein_global_SPACEscope));
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(calein_ir),value_add_reference(calein_initializers),value_add_reference(calein_initializer_SPACEcontext),value_add_reference(calein_global_SPACEscope));
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(calein_ir),value_add_reference(calein_main),value_add_reference(calein_statement_SPACEcontext),value_add_reference(calein_global_SPACEscope));

} else {
calein_false;
}
} else {
(tmp_for_derefs = calein_continue, calein_continue = value_add_reference(calein_false), value_remove_reference(tmp_for_derefs),calein_continue);
}
}
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("#include \"caleinrtl.inc.c\"")));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(calein_declarations));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(calein_definitions));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("int main() {")));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("struct value *tmp_for_derefs = 0;")));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(calein_initializers));
global_SCOPEcalein_write_ARG(value_add_reference(calein_main));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("return 0;")));
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(value_make_string_from_c_string("}")));
return 0;
}
