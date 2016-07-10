#include <stdio.h>
#include <string.h>

#include "err.h"
#include "str.h"
#include "value.h"

static struct value *global_SCOPEcalein__COMMA_ARG_ARG(struct value *x, struct value *y) {
	struct value *res = value_make_pair(x, y);
	value_remove_reference(x);
	value_remove_reference(y);
	return res;
}

static struct value *global_SCOPEcalein_first_ARG(struct value *p) {
	struct value *res = value_pair_first(p);
	value_add_reference(res);
	value_remove_reference(p);
	value_float_result(res);
	return res;
}

static struct value *global_SCOPEcalein_second_ARG(struct value *p) {
	struct value *res = value_pair_second(p);
	value_add_reference(res);
	value_remove_reference(p);
	value_float_result(res);
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
	struct value *res = char_of_int(getc(value_file_value(f)));
	value_remove_reference(f);
	return res;
}

static struct value *global_SCOPEcalein_open_SPACEfile_SPACE_SPACE_ARGfor_SPACEreading(struct value *name) {
	struct value *res = value_make_file(fopen(value_string_value(name)->data, "r"));
	value_remove_reference(name);
	return res;
}

static struct value *global_SCOPEcalein_close_SPACEfile_ARG(struct value *f) {
	fclose(value_file_value(f));
	value_remove_reference(f);
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

#define NUMBER_RELOP(name, op) \
	static struct value *global_SCOPEcalein__SPACE_ARG ## name ## _ARG(struct value *x, struct value *y) { \
		struct value *res = value_make_boolean(value_number_value(x) op value_number_value(y)); \
		value_remove_reference(x); \
		value_remove_reference(y); \
		return res; \
	}

NUMBER_RELOP(_LESSER, <)
NUMBER_RELOP(_GREATER, >)

#undef NUMBER_RELOP

static struct value *calein_program_SPACEarguments = 0;

void caleinmain();

int main(int argc, char **argv) {
	char *memdebug_env = getenv("CALEIN_MEMDEBUG");
	bool memdebug = memdebug_env && 0 == strcmp(memdebug_env, "1");
	calein_program_SPACEarguments = value_make_boolean(false);
	for (int i = argc - 1; i > 0; i--) {
		struct value *arg = value_make_string_from_c_string(argv[i]);
		calein_program_SPACEarguments =
			value_make_pair(arg, calein_program_SPACEarguments);
	}
	value_add_reference(calein_program_SPACEarguments);
	caleinmain();
	if (memdebug) {
		fprintf(stderr, "%lu\n", (unsigned long) value_allocated_object_count());
	}
	return 0;
}

//global_SCOPEcalein__SPACE_ARGor_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGor_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGand_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGand_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGand_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGat_ARG
//	calein_index, global_SCOPEcalein__SPACE_ARGat_ARG
//	calein_list, global_SCOPEcalein__SPACE_ARGat_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_c, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_d, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_c, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_e, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_d, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_c, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_f, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_e, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_d, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_c, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG
//	calein_found, global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG
//	calein_b, global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG
//	calein_a, global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG
//	calein_x, global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_reverse_SPACEstring_ARG
//	calein_i, global_SCOPEcalein_reverse_SPACEstring_ARG
//	calein_rev, global_SCOPEcalein_reverse_SPACEstring_ARG
//	calein_s, global_SCOPEcalein_reverse_SPACEstring_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG
//	calein_negative, global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG
//	calein_s, global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG
//	calein_number, global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGis_SPACEdigit
//	calein_c, global_SCOPEcalein__SPACE_ARGis_SPACEdigit
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace
//	calein_c, global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_reverse_SPACElist_ARG
//	calein_acc, global_SCOPEcalein_reverse_SPACElist_ARG
//	calein_list, global_SCOPEcalein_reverse_SPACElist_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG
//	calein_s, global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_c_SPACE4, global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_c_SPACE3, global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_c_SPACE2, global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_c_SPACE1, global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_c, global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG
//	calein_i, global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG
//	calein_s, global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG
//	calein_t, global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG
//	calein_u, global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG
//	calein_t, global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG
//	calein_s, global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein__SPACE_ARGcontains_ARG
//	calein_found, global_SCOPEcalein__SPACE_ARGcontains_ARG
//	calein_elem, global_SCOPEcalein__SPACE_ARGcontains_ARG
//	calein_list, global_SCOPEcalein__SPACE_ARGcontains_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG
//	calein_found, global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG
//	calein_alist, global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG
//	calein_key, global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_found, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_after, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_before, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_alist, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_value, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_key, global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_close_SPACEbrace, global
//global_SCOPEcalein_get_SPACEcharacter
//	calein_tmp, global_SCOPEcalein_get_SPACEcharacter
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_unget_SPACEcharacter_ARG
//	calein_c, global_SCOPEcalein_unget_SPACEcharacter_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_current_SPACEposition
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_make_SPACEliteral_ARG
//	calein_val, global_SCOPEcalein_make_SPACEliteral_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_make_SPACEnumber_ARG
//	calein_val, global_SCOPEcalein_make_SPACEnumber_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_make_SPACEsequence_ARG
//	calein_items, global_SCOPEcalein_make_SPACEsequence_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG
//	calein_args, global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG
//	calein_name, global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes
//	calein_n, global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG
//	calein_args, global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG
//	calein_items, global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG
//	calein_indent, global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG
//	calein_tree, global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG
//	calein_msg, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG
//	calein_c, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_c, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_child, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_paren, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_literal, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_children, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_again_SPACEin_SPACEaction, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_tree, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_first_SPACEchild, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG
//	calein_msg, global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG
//	calein_child, global_SCOPEcalein_parse_ARG
//global_SCOPEcalein_parse_ARG
//	calein_child, global_SCOPEcalein_parse_ARG
//	calein_negative, global_SCOPEcalein_parse_ARG
//	calein_tree, global_SCOPEcalein_parse_ARG
//	calein_c, global_SCOPEcalein_parse_ARG
//	calein_children, global_SCOPEcalein_parse_ARG
//	calein_at_SPACEstart_SPACEof_SPACEliteral, global_SCOPEcalein_parse_ARG
//	calein_again_SPACEin_SPACEsequence, global_SCOPEcalein_parse_ARG
//	calein_again_SPACEin_SPACEliteral, global_SCOPEcalein_parse_ARG
//	calein_in_SPACEescape, global_SCOPEcalein_parse_ARG
//	calein_literal, global_SCOPEcalein_parse_ARG
//	calein_again, global_SCOPEcalein_parse_ARG
//	calein_at_SPACEstart_SPACEof_SPACEexpression, global_SCOPEcalein_parse_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_tree, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_reversed_SPACEsyntax_SPACEtrees, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_old_SPACEungotten, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_old_SPACEcolumn_SPACEnumber, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_old_SPACEline_SPACEnumber, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_old_SPACEfile_SPACEname, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_old_SPACEfile, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_name, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_f, global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_ungotten_SPACEcharacter, global
//global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG
//	calein_c, global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG
//	calein_str, global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG
//	calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers, global
//global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_substitutions, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_added, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_c, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_i, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_ident, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_args, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_name, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_action, global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG
//	calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers, global
//global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG
//	calein_c, global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG
//	calein_i, global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG
//	calein_string, global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG
//	calein_literal, global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG
//	calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers, global
//global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG
//	calein_out, global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG
//	calein_pos, global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG
//	calein_source_SPACElevel_SPACEdebugging, global
//global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG
//	calein_old_SPACEscope, global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG
//	calein_scope, global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG
//	calein_var, global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG
//	calein_module_SPACElist_SPACEby_SPACEcontext, global
//global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation
//	calein_context, global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation
//	calein_module_SPACElist_SPACEby_SPACEcontext, global
//global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG
//	calein_out, global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG
//	calein_scope, global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG
//	calein_var_SPACEscope, global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG
//	calein_name, global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG
//	calein_global_SPACEscope, global
//global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG
//	calein_out, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG
//	calein_proc_SPACEname, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG
//	calein_global_SPACEscope, global
//global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_ident, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_args, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_scope, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_out, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_proc_SPACEname, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_ir, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_global_SPACEscope, global
//global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_scope, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_out, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_proc_SPACEname, global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG
//	calein_global_SPACEscope, global
//global_SCOPEcalein_compile_SPACEerror_ARG
//	calein_msg, global_SCOPEcalein_compile_SPACEerror_ARG
//	calein_continue, global
//global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_module_SPACElist, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_import_SPACEir, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_old_SPACElength, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_expected_SPACEsep, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_items, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_vars, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_ident, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_old_SPACEvariable_SPACElist, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_old_SPACEfunction_SPACElist, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_adjusted_SPACEproc_SPACEname, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_field_SPACEcount, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_i, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_record_SPACEname, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_function_SPACEinfo, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_proc_SPACEname, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_name, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_sep, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_var_SPACEscope, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_args, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_scope, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_context, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_out, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_ir, global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG
//	calein_continue, global
//global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals
//	calein_s, global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals
//	calein_var, global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals
//	calein_vars, global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals
//	calein_continue, global
//global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG
//	calein_import, global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG
//	calein_f, global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG
//	calein_pos, global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG
//	calein_file_SPACEname, global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG
//	calein_continue, global
//global_SCOPEcalein_compile_ARG
//	calein_items, global_SCOPEcalein_compile_ARG
//	calein_ir_SPACEitems, global_SCOPEcalein_compile_ARG
//	calein_file_SPACEname, global_SCOPEcalein_compile_ARG
//	calein_pos, global_SCOPEcalein_compile_ARG
//	calein_args, global_SCOPEcalein_compile_ARG
//	calein_ir_SPACEargs, global_SCOPEcalein_compile_ARG
//	calein_tree, global_SCOPEcalein_compile_ARG
//	calein_continue, global
//global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG
//	calein_irs, global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG
//	calein_trees, global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG
//	calein_continue, global
//global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_irs, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_ir, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_main, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_initializers, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_definitions, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_declarations, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_name, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_f, global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG
//	calein_continue, global
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
struct global_SCOPEcalein__SPACE_ARGat_ARG_local_vars {
struct value *calein_list;
struct value *calein_index;
};
struct value *global_SCOPEcalein__SPACE_ARGat_ARG(struct value *calein_list, struct value *calein_index);
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
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
struct value *calein_c;
struct value *calein_d;
struct value *calein_e;
};
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d, struct value *calein_e);
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars {
struct value *calein_a;
struct value *calein_b;
struct value *calein_c;
struct value *calein_d;
struct value *calein_e;
struct value *calein_f;
};
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d, struct value *calein_e, struct value *calein_f);
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
struct value *calein_negative;
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
struct global_SCOPEcalein_reverse_SPACElist_ARG_local_vars {
struct value *calein_list;
struct value *calein_acc;
};
struct value *global_SCOPEcalein_reverse_SPACElist_ARG(struct value *calein_list);
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
struct global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars {
struct value *calein_key;
struct value *calein_value;
struct value *calein_alist;
struct value *calein_before;
struct value *calein_after;
struct value *calein_found;
};
struct value *global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_key, struct value *calein_value, struct value *calein_alist);
struct global_SCOPEcalein_get_SPACEcharacter_local_vars {
struct value *calein_tmp;
};
struct value *global_SCOPEcalein_get_SPACEcharacter(void);
struct global_SCOPEcalein_unget_SPACEcharacter_ARG_local_vars {
struct value *calein_c;
};
struct value *global_SCOPEcalein_unget_SPACEcharacter_ARG(struct value *calein_c);
struct value *global_SCOPEcalein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEposition(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_line_SPACEof_SPACEposition_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_file_SPACEof_SPACEposition_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG", 1);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_current_SPACEposition_local_vars {
};
struct value *global_SCOPEcalein_current_SPACEposition(void);
struct value *global_SCOPEcalein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEliteral_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_make_SPACEliteral_ARG_local_vars {
struct value *calein_val;
};
struct value *global_SCOPEcalein_make_SPACEliteral_ARG(struct value *calein_val);
struct value *global_SCOPEcalein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEnumber_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_make_SPACEnumber_ARG_local_vars {
struct value *calein_val;
};
struct value *global_SCOPEcalein_make_SPACEnumber_ARG(struct value *calein_val);
struct value *global_SCOPEcalein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEsequence_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_make_SPACEsequence_ARG_local_vars {
struct value *calein_items;
};
struct value *global_SCOPEcalein_make_SPACEsequence_ARG(struct value *calein_items);
struct value *global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEaction_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars {
struct value *calein_name;
struct value *calein_args;
};
struct value *global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args);
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
struct value *calein_negative;
struct value *calein_child;
};
struct global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG_local_vars {
struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars;
struct value *calein_msg;
};
struct value *global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars, struct value *calein_msg);
struct value *global_SCOPEcalein_parse_ARG(struct value *calein_at_SPACEstart_SPACEof_SPACEexpression);
struct global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG_local_vars {
struct value *calein_f;
struct value *calein_name;
struct value *calein_old_SPACEfile;
struct value *calein_old_SPACEfile_SPACEname;
struct value *calein_old_SPACEline_SPACEnumber;
struct value *calein_old_SPACEcolumn_SPACEnumber;
struct value *calein_old_SPACEungotten;
struct value *calein_reversed_SPACEsyntax_SPACEtrees;
struct value *calein_tree;
};
struct value *global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(struct value *calein_f, struct value *calein_name);
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
struct global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG_local_vars {
struct value *calein_pos;
struct value *calein_out;
};
struct value *global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(struct value *calein_pos, struct value *calein_out);
struct value *global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEcall_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEprocedure_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEsequence_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2, struct value *arg3) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG", 4);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
result->u.record.fields[3] = arg3;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEif_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG", 3);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEwhile_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEvariable_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEassignment_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEliteral_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG", 2);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEnumber_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEimport(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_name_SPACEof_SPACEir_SPACEimport_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_ir_SPACEof_SPACEir_SPACEimport_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACEimport_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG(struct value *arg0, struct value *arg1, struct value *arg2) {
struct value *result = value_make_record("calein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG", 3);
result->u.record.fields[0] = arg0;
result->u.record.fields[1] = arg1;
result->u.record.fields[2] = arg2;
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACErecord(struct value *v) {
struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, "calein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG"));
value_remove_reference(v);
return result;
}struct value *global_SCOPEcalein_definition_SPACEof_SPACEir_SPACErecord_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG", 0);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_predicate_SPACEof_SPACEir_SPACErecord_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG", 1);
value_remove_reference(record);
return result;
}struct value *global_SCOPEcalein_position_SPACEof_SPACEir_SPACErecord_ARG(struct value *record) {
struct value *result = value_record_field(record, "calein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG", 2);
value_remove_reference(record);
return result;
}struct global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG_local_vars {
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
struct value *calein_proc_SPACEname;
struct value *calein_function_SPACEinfo;
struct value *calein_record_SPACEname;
struct value *calein_i;
struct value *calein_field_SPACEcount;
struct value *calein_adjusted_SPACEproc_SPACEname;
struct value *calein_old_SPACEfunction_SPACElist;
struct value *calein_old_SPACEvariable_SPACElist;
struct value *calein_ident;
struct value *calein_vars;
struct value *calein_items;
struct value *calein_expected_SPACEsep;
struct value *calein_old_SPACElength;
struct value *calein_import_SPACEir;
struct value *calein_module_SPACElist;
};
struct value *global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(struct value *calein_ir, struct value *calein_out, struct value *calein_context, struct value *calein_scope);
struct global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals_local_vars {
struct value *calein_vars;
struct value *calein_var;
struct value *calein_s;
};
struct value *global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals(void);
struct global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG_local_vars {
struct value *calein_file_SPACEname;
struct value *calein_pos;
struct value *calein_f;
struct value *calein_import;
};
struct value *global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG(struct value *calein_file_SPACEname, struct value *calein_pos);
struct global_SCOPEcalein_compile_ARG_local_vars {
struct value *calein_tree;
struct value *calein_ir_SPACEargs;
struct value *calein_args;
struct value *calein_pos;
struct value *calein_file_SPACEname;
struct value *calein_ir_SPACEitems;
struct value *calein_items;
};
struct value *global_SCOPEcalein_compile_ARG(struct value *calein_tree);
struct global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG_local_vars {
struct value *calein_trees;
struct value *calein_irs;
};
struct value *global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG(struct value *calein_trees);
struct global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG_local_vars {
struct value *calein_f;
struct value *calein_name;
struct value *calein_declarations;
struct value *calein_definitions;
struct value *calein_initializers;
struct value *calein_main;
struct value *calein_ir;
struct value *calein_irs;
};
struct value *global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(struct value *calein_f, struct value *calein_name);

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
struct value *calein_left_SPACEangle;
struct value *calein_right_SPACEangle;
struct value *calein_backslash;
struct value *calein_underscore;
struct value *calein_character_SPACEn;
struct value *calein_open_SPACEbrace;
struct value *calein_close_SPACEbrace;
struct value *global_SCOPEcalein__SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = (value_boolean_is_true_remove_floating_reference(
#line 28 "prelude.cln"
local_vars.calein_a) ? (
#line 28 "prelude.cln"
local_vars.calein_a) : (
#line 28 "prelude.cln"
local_vars.calein_b));
value_add_reference(result);
value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGand_ARG(struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = (value_boolean_is_true_remove_floating_reference(
#line 30 "prelude.cln"
local_vars.calein_a) ? (
#line 30 "prelude.cln"
local_vars.calein_b) : (
#line 30 "prelude.cln"
local_vars.calein_a));
value_add_reference(result);
value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGat_ARG(struct value *calein_list, struct value *calein_index){
struct global_SCOPEcalein__SPACE_ARGat_ARG_local_vars local_vars;
local_vars.calein_list = calein_list;
local_vars.calein_index = calein_index;
struct value *tmp_for_derefs = 0;
struct value *result = (({ while (value_boolean_is_true_remove_floating_reference(
#line 33 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 33 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 33 "prelude.cln"
local_vars.calein_index),value_add_reference(
#line 33 "prelude.cln"
value_make_number(0))))))) {

#line 34 "prelude.cln"
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(
#line 34 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 34 "prelude.cln"
local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);

#line 35 "prelude.cln"
(tmp_for_derefs = local_vars.calein_index, local_vars.calein_index = value_add_reference(
#line 35 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 35 "prelude.cln"
local_vars.calein_index),value_add_reference(
#line 35 "prelude.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_index);

}
 0; }), 
#line 37 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 37 "prelude.cln"
local_vars.calein_list)));
value_add_reference(result);
value_remove_reference(local_vars.calein_index);value_remove_reference(local_vars.calein_list);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 41 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 41 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 41 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 41 "prelude.cln"
local_vars.calein_b))),value_add_reference(
#line 41 "prelude.cln"
local_vars.calein_c));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
local_vars.calein_d = calein_d;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 43 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 43 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 43 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 43 "prelude.cln"
local_vars.calein_b))),value_add_reference(
#line 43 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 43 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 43 "prelude.cln"
local_vars.calein_d))));
value_add_reference(result);
value_remove_reference(local_vars.calein_d);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d, struct value *calein_e){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
local_vars.calein_d = calein_d;
local_vars.calein_e = calein_e;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 45 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 45 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 45 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 45 "prelude.cln"
local_vars.calein_b),value_add_reference(
#line 45 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 45 "prelude.cln"
local_vars.calein_d))),value_add_reference(
#line 45 "prelude.cln"
local_vars.calein_e));
value_add_reference(result);
value_remove_reference(local_vars.calein_e);value_remove_reference(local_vars.calein_d);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(struct value *calein_a, struct value *calein_b, struct value *calein_c, struct value *calein_d, struct value *calein_e, struct value *calein_f){
struct global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG_local_vars local_vars;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
local_vars.calein_c = calein_c;
local_vars.calein_d = calein_d;
local_vars.calein_e = calein_e;
local_vars.calein_f = calein_f;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 47 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 47 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_b),value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_d))),value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_e),value_add_reference(
#line 47 "prelude.cln"
local_vars.calein_f));
value_add_reference(result);
value_remove_reference(local_vars.calein_f);value_remove_reference(local_vars.calein_e);value_remove_reference(local_vars.calein_d);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG(struct value *calein_x, struct value *calein_a, struct value *calein_b){
struct global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_x = calein_x;
local_vars.calein_a = calein_a;
local_vars.calein_b = calein_b;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(
#line 50 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 51 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 51 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 51 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 51 "prelude.cln"
local_vars.calein_b)))))) {
if (value_boolean_is_true_remove_floating_reference(
#line 52 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 52 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 52 "prelude.cln"
local_vars.calein_x)))) {

#line 53 "prelude.cln"
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(
#line 53 "prelude.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

} else {

#line 54 "prelude.cln"
calein_false;
}
#line 55 "prelude.cln"
(tmp_for_derefs = local_vars.calein_a, local_vars.calein_a = value_add_reference(
#line 55 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 55 "prelude.cln"
local_vars.calein_a),value_add_reference(
#line 55 "prelude.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_a);

}
 0; }), 
#line 57 "prelude.cln"
local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_b);value_remove_reference(local_vars.calein_a);value_remove_reference(local_vars.calein_x);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_reverse_SPACEstring_ARG(struct value *calein_s){
struct global_SCOPEcalein_reverse_SPACEstring_ARG_local_vars local_vars;
local_vars.calein_rev = 0;
local_vars.calein_i = 0;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_rev = value_add_reference(
#line 61 "prelude.cln"
value_make_string_from_c_string(""))), (local_vars.calein_i = value_add_reference(
#line 62 "prelude.cln"
value_make_number(0))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 63 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 63 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 63 "prelude.cln"
local_vars.calein_i),value_add_reference(
#line 63 "prelude.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 63 "prelude.cln"
local_vars.calein_s)))))))) {

#line 65 "prelude.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 64 "prelude.cln"
global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(
#line 64 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 64 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 64 "prelude.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 64 "prelude.cln"
local_vars.calein_s))),value_add_reference(
#line 64 "prelude.cln"
local_vars.calein_i))),value_add_reference(
#line 64 "prelude.cln"
value_make_number(1)))),value_add_reference(
#line 64 "prelude.cln"
local_vars.calein_s))),value_add_reference(
#line 65 "prelude.cln"
local_vars.calein_rev));

#line 66 "prelude.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 66 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 66 "prelude.cln"
local_vars.calein_i),value_add_reference(
#line 66 "prelude.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), 
#line 68 "prelude.cln"
local_vars.calein_rev);
value_add_reference(result);
value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_rev);value_remove_reference(local_vars.calein_s);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(struct value *calein_number){
struct global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_s = 0;
local_vars.calein_negative = 0;
local_vars.calein_number = calein_number;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_s = value_add_reference(
#line 72 "prelude.cln"
value_make_string_from_c_string(""))), (local_vars.calein_negative = value_add_reference(
#line 73 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_LESSER_ARG(value_add_reference(
#line 73 "prelude.cln"
local_vars.calein_number),value_add_reference(
#line 73 "prelude.cln"
value_make_number(0))))), (value_boolean_is_true_remove_floating_reference(
#line 74 "prelude.cln"
local_vars.calein_negative) ? ((
#line 75 "prelude.cln"
(tmp_for_derefs = local_vars.calein_number, local_vars.calein_number = value_add_reference(
#line 75 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 75 "prelude.cln"
value_make_number(0)),value_add_reference(
#line 75 "prelude.cln"
local_vars.calein_number))), value_remove_reference(tmp_for_derefs),local_vars.calein_number))) : (
#line 76 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 77 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 77 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 77 "prelude.cln"
local_vars.calein_number),value_add_reference(
#line 77 "prelude.cln"
value_make_number(0))))))) {

#line 78 "prelude.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 78 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 78 "prelude.cln"
global_SCOPEcalein__SPACE_ARGmod_ARG(value_add_reference(
#line 78 "prelude.cln"
local_vars.calein_number),value_add_reference(
#line 78 "prelude.cln"
value_make_number(10)))),value_add_reference(
#line 78 "prelude.cln"
calein_character_SPACE0))),value_add_reference(
#line 78 "prelude.cln"
local_vars.calein_s));

#line 79 "prelude.cln"
(tmp_for_derefs = local_vars.calein_number, local_vars.calein_number = value_add_reference(
#line 79 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_SLASH_ARG(value_add_reference(
#line 79 "prelude.cln"
local_vars.calein_number),value_add_reference(
#line 79 "prelude.cln"
value_make_number(10)))), value_remove_reference(tmp_for_derefs),local_vars.calein_number);

}
 0; }), (value_boolean_is_true_remove_floating_reference(
#line 81 "prelude.cln"
local_vars.calein_negative) ? (
#line 81 "prelude.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 81 "prelude.cln"
calein_minus),value_add_reference(
#line 81 "prelude.cln"
local_vars.calein_s))) : (
#line 81 "prelude.cln"
calein_false)), (value_boolean_is_true_remove_floating_reference(
#line 82 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 82 "prelude.cln"
local_vars.calein_s),value_add_reference(
#line 82 "prelude.cln"
value_make_string_from_c_string("")))) ? (
#line 83 "prelude.cln"
value_make_string_from_c_string("0")) : (
#line 84 "prelude.cln"
global_SCOPEcalein_reverse_SPACEstring_ARG(value_add_reference(
#line 84 "prelude.cln"
local_vars.calein_s)))));
value_add_reference(result);
value_remove_reference(local_vars.calein_negative);value_remove_reference(local_vars.calein_s);value_remove_reference(local_vars.calein_number);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEdigit(struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGis_SPACEdigit_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 88 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEbetween_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 88 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 88 "prelude.cln"
value_make_number(48)),value_add_reference(
#line 88 "prelude.cln"
value_make_number(58)));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(struct value *calein_c){
struct global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 92 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 90 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 90 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 90 "prelude.cln"
calein_space))),value_add_reference(
#line 91 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 91 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 91 "prelude.cln"
calein_tab))),value_add_reference(
#line 92 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 92 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 92 "prelude.cln"
calein_new_SPACEline))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_reverse_SPACElist_ARG(struct value *calein_list){
struct global_SCOPEcalein_reverse_SPACElist_ARG_local_vars local_vars;
local_vars.calein_acc = 0;
local_vars.calein_list = calein_list;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_acc = value_add_reference(
#line 95 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 96 "prelude.cln"
local_vars.calein_list)) {

#line 97 "prelude.cln"
(tmp_for_derefs = local_vars.calein_acc, local_vars.calein_acc = value_add_reference(
#line 97 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 97 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 97 "prelude.cln"
local_vars.calein_list))),value_add_reference(
#line 97 "prelude.cln"
local_vars.calein_acc))), value_remove_reference(tmp_for_derefs),local_vars.calein_acc);

#line 98 "prelude.cln"
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(
#line 98 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 98 "prelude.cln"
local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);

}
 0; }), 
#line 100 "prelude.cln"
local_vars.calein_acc);
value_add_reference(result);
value_remove_reference(local_vars.calein_acc);value_remove_reference(local_vars.calein_list);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG(struct value *calein_s){
struct global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG_local_vars local_vars;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 104 "prelude.cln"
global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(
#line 104 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 104 "prelude.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 104 "prelude.cln"
local_vars.calein_s))),value_add_reference(
#line 104 "prelude.cln"
value_make_number(1)))),value_add_reference(
#line 104 "prelude.cln"
local_vars.calein_s));
value_add_reference(result);
value_remove_reference(local_vars.calein_s);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG(struct value *calein_c, struct value *calein_c_SPACE1, struct value *calein_c_SPACE2, struct value *calein_c_SPACE3, struct value *calein_c_SPACE4){
struct global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG_local_vars local_vars;
local_vars.calein_c = calein_c;
local_vars.calein_c_SPACE1 = calein_c_SPACE1;
local_vars.calein_c_SPACE2 = calein_c_SPACE2;
local_vars.calein_c_SPACE3 = calein_c_SPACE3;
local_vars.calein_c_SPACE4 = calein_c_SPACE4;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 108 "prelude.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 107 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 107 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 107 "prelude.cln"
local_vars.calein_c_SPACE1))),value_add_reference(
#line 107 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 107 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 107 "prelude.cln"
local_vars.calein_c_SPACE2))),value_add_reference(
#line 108 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 108 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 108 "prelude.cln"
local_vars.calein_c_SPACE3))),value_add_reference(
#line 108 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 108 "prelude.cln"
local_vars.calein_c),value_add_reference(
#line 108 "prelude.cln"
local_vars.calein_c_SPACE4))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c_SPACE4);value_remove_reference(local_vars.calein_c_SPACE3);value_remove_reference(local_vars.calein_c_SPACE2);value_remove_reference(local_vars.calein_c_SPACE1);value_remove_reference(local_vars.calein_c);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(struct value *calein_t, struct value *calein_s){
struct global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_i = 0;
local_vars.calein_t = calein_t;
local_vars.calein_s = calein_s;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_i = value_add_reference(
#line 111 "prelude.cln"
value_make_number(0))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 112 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 112 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 112 "prelude.cln"
local_vars.calein_i),value_add_reference(
#line 112 "prelude.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 112 "prelude.cln"
local_vars.calein_t)))))))) {

#line 113 "prelude.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 113 "prelude.cln"
global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(
#line 113 "prelude.cln"
local_vars.calein_i),value_add_reference(
#line 113 "prelude.cln"
local_vars.calein_t))),value_add_reference(
#line 113 "prelude.cln"
local_vars.calein_s));

#line 114 "prelude.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 114 "prelude.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 114 "prelude.cln"
local_vars.calein_i),value_add_reference(
#line 114 "prelude.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }));
value_add_reference(result);
value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_s);value_remove_reference(local_vars.calein_t);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(struct value *calein_s, struct value *calein_t){
struct global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG_local_vars local_vars;
local_vars.calein_u = 0;
local_vars.calein_s = calein_s;
local_vars.calein_t = calein_t;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_u = value_add_reference(
#line 119 "prelude.cln"
value_make_string_from_c_string(""))), 
#line 120 "prelude.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 120 "prelude.cln"
local_vars.calein_s),value_add_reference(
#line 120 "prelude.cln"
local_vars.calein_u)), 
#line 121 "prelude.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 121 "prelude.cln"
local_vars.calein_t),value_add_reference(
#line 121 "prelude.cln"
local_vars.calein_u)), 
#line 122 "prelude.cln"
local_vars.calein_u);
value_add_reference(result);
value_remove_reference(local_vars.calein_u);value_remove_reference(local_vars.calein_t);value_remove_reference(local_vars.calein_s);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGcontains_ARG(struct value *calein_list, struct value *calein_elem){
struct global_SCOPEcalein__SPACE_ARGcontains_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_list = calein_list;
local_vars.calein_elem = calein_elem;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(
#line 126 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 127 "prelude.cln"
local_vars.calein_list)) {
if (value_boolean_is_true_remove_floating_reference(
#line 128 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 128 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 128 "prelude.cln"
local_vars.calein_list))),value_add_reference(
#line 128 "prelude.cln"
local_vars.calein_elem)))) {

#line 129 "prelude.cln"
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(
#line 129 "prelude.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_list);

#line 130 "prelude.cln"
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(
#line 130 "prelude.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

} else {

#line 131 "prelude.cln"
(tmp_for_derefs = local_vars.calein_list, local_vars.calein_list = value_add_reference(
#line 131 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 131 "prelude.cln"
local_vars.calein_list))), value_remove_reference(tmp_for_derefs),local_vars.calein_list);
}
}
 0; }), 
#line 133 "prelude.cln"
local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_elem);value_remove_reference(local_vars.calein_list);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(struct value *calein_key, struct value *calein_alist){
struct global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_found = 0;
local_vars.calein_key = calein_key;
local_vars.calein_alist = calein_alist;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_found = value_add_reference(
#line 137 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 138 "prelude.cln"
local_vars.calein_alist)) {
if (value_boolean_is_true_remove_floating_reference(
#line 139 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 139 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 139 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 139 "prelude.cln"
local_vars.calein_alist))))),value_add_reference(
#line 139 "prelude.cln"
local_vars.calein_key)))) {

#line 140 "prelude.cln"
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(
#line 140 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 140 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 140 "prelude.cln"
local_vars.calein_alist))))), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

#line 141 "prelude.cln"
(tmp_for_derefs = local_vars.calein_alist, local_vars.calein_alist = value_add_reference(
#line 141 "prelude.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_alist);

} else {

#line 142 "prelude.cln"
(tmp_for_derefs = local_vars.calein_alist, local_vars.calein_alist = value_add_reference(
#line 142 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 142 "prelude.cln"
local_vars.calein_alist))), value_remove_reference(tmp_for_derefs),local_vars.calein_alist);
}
}
 0; }), 
#line 144 "prelude.cln"
local_vars.calein_found);
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_alist);value_remove_reference(local_vars.calein_key);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_key, struct value *calein_value, struct value *calein_alist){
struct global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_before = 0;
local_vars.calein_after = 0;
local_vars.calein_found = 0;
local_vars.calein_key = calein_key;
local_vars.calein_value = calein_value;
local_vars.calein_alist = calein_alist;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_before = value_add_reference(
#line 148 "prelude.cln"
calein_false)), (local_vars.calein_after = value_add_reference(
#line 149 "prelude.cln"
local_vars.calein_alist)), (local_vars.calein_found = value_add_reference(
#line 150 "prelude.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 151 "prelude.cln"
global_SCOPEcalein__SPACE_ARGand_ARG(value_add_reference(
#line 151 "prelude.cln"
local_vars.calein_after),value_add_reference(
#line 151 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 151 "prelude.cln"
local_vars.calein_found)))))) {
if (value_boolean_is_true_remove_floating_reference(
#line 152 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 152 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 152 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 152 "prelude.cln"
local_vars.calein_after))))),value_add_reference(
#line 152 "prelude.cln"
local_vars.calein_key)))) {

#line 153 "prelude.cln"
(tmp_for_derefs = local_vars.calein_found, local_vars.calein_found = value_add_reference(
#line 153 "prelude.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_found);

#line 154 "prelude.cln"
(tmp_for_derefs = local_vars.calein_after, local_vars.calein_after = value_add_reference(
#line 154 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 154 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 154 "prelude.cln"
local_vars.calein_key),value_add_reference(
#line 154 "prelude.cln"
local_vars.calein_value))),value_add_reference(
#line 154 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 154 "prelude.cln"
local_vars.calein_after))))), value_remove_reference(tmp_for_derefs),local_vars.calein_after);

} else {

#line 156 "prelude.cln"
(tmp_for_derefs = local_vars.calein_before, local_vars.calein_before = value_add_reference(
#line 156 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 156 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 156 "prelude.cln"
local_vars.calein_after))),value_add_reference(
#line 156 "prelude.cln"
local_vars.calein_before))), value_remove_reference(tmp_for_derefs),local_vars.calein_before);

#line 157 "prelude.cln"
(tmp_for_derefs = local_vars.calein_after, local_vars.calein_after = value_add_reference(
#line 157 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 157 "prelude.cln"
local_vars.calein_after))), value_remove_reference(tmp_for_derefs),local_vars.calein_after);
}
}
 0; }), (value_boolean_is_true_remove_floating_reference(
#line 160 "prelude.cln"
local_vars.calein_found) ? ((({ while (value_boolean_is_true_remove_floating_reference(
#line 161 "prelude.cln"
local_vars.calein_before)) {

#line 162 "prelude.cln"
(tmp_for_derefs = local_vars.calein_after, local_vars.calein_after = value_add_reference(
#line 162 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 162 "prelude.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 162 "prelude.cln"
local_vars.calein_before))),value_add_reference(
#line 162 "prelude.cln"
local_vars.calein_after))), value_remove_reference(tmp_for_derefs),local_vars.calein_after);

#line 163 "prelude.cln"
(tmp_for_derefs = local_vars.calein_before, local_vars.calein_before = value_add_reference(
#line 163 "prelude.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 163 "prelude.cln"
local_vars.calein_before))), value_remove_reference(tmp_for_derefs),local_vars.calein_before);

}
 0; }), 
#line 165 "prelude.cln"
local_vars.calein_after)) : ((
#line 167 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 167 "prelude.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 167 "prelude.cln"
local_vars.calein_key),value_add_reference(
#line 167 "prelude.cln"
local_vars.calein_value))),value_add_reference(
#line 167 "prelude.cln"
local_vars.calein_alist))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_found);value_remove_reference(local_vars.calein_after);value_remove_reference(local_vars.calein_before);value_remove_reference(local_vars.calein_alist);value_remove_reference(local_vars.calein_value);value_remove_reference(local_vars.calein_key);value_float_result(result);
return result;
}
struct value *calein_line_SPACEnumber;
struct value *calein_column_SPACEnumber;
struct value *calein_file_SPACEname;
struct value *calein_file_SPACEto_SPACEread_SPACEfrom;
struct value *calein_ungotten_SPACEcharacter;
struct value *global_SCOPEcalein_get_SPACEcharacter(void){
struct global_SCOPEcalein_get_SPACEcharacter_local_vars local_vars;
local_vars.calein_tmp = 0;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_tmp = value_add_reference(
#line 8 "parser.cln"
calein_false)), (value_boolean_is_true_remove_floating_reference(
#line 9 "parser.cln"
calein_ungotten_SPACEcharacter) ? ((
#line 10 "parser.cln"
(tmp_for_derefs = local_vars.calein_tmp, local_vars.calein_tmp = value_add_reference(
#line 10 "parser.cln"
calein_ungotten_SPACEcharacter), value_remove_reference(tmp_for_derefs),local_vars.calein_tmp), 
#line 11 "parser.cln"
(tmp_for_derefs = calein_ungotten_SPACEcharacter, calein_ungotten_SPACEcharacter = value_add_reference(
#line 11 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),calein_ungotten_SPACEcharacter))) : (
#line 12 "parser.cln"
(tmp_for_derefs = local_vars.calein_tmp, local_vars.calein_tmp = value_add_reference(
#line 12 "parser.cln"
global_SCOPEcalein_read_SPACEcharacter_SPACEfrom_ARG(value_add_reference(
#line 12 "parser.cln"
calein_file_SPACEto_SPACEread_SPACEfrom))), value_remove_reference(tmp_for_derefs),local_vars.calein_tmp))), (value_boolean_is_true_remove_floating_reference(
#line 13 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 13 "parser.cln"
local_vars.calein_tmp),value_add_reference(
#line 13 "parser.cln"
calein_new_SPACEline))) ? ((
#line 14 "parser.cln"
(tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(
#line 14 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 14 "parser.cln"
calein_line_SPACEnumber),value_add_reference(
#line 14 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), 
#line 15 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 15 "parser.cln"
value_make_number(1)), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))) : (
#line 16 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 16 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 16 "parser.cln"
calein_column_SPACEnumber),value_add_reference(
#line 16 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))), 
#line 17 "parser.cln"
local_vars.calein_tmp);
value_add_reference(result);
value_remove_reference(local_vars.calein_tmp);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_unget_SPACEcharacter_ARG(struct value *calein_c){
struct global_SCOPEcalein_unget_SPACEcharacter_ARG_local_vars local_vars;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 20 "parser.cln"
(tmp_for_derefs = calein_ungotten_SPACEcharacter, calein_ungotten_SPACEcharacter = value_add_reference(
#line 20 "parser.cln"
local_vars.calein_c), value_remove_reference(tmp_for_derefs),calein_ungotten_SPACEcharacter), (value_boolean_is_true_remove_floating_reference(
#line 21 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 21 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 21 "parser.cln"
calein_new_SPACEline))) ? ((
#line 22 "parser.cln"
(tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(
#line 22 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 22 "parser.cln"
calein_line_SPACEnumber),value_add_reference(
#line 22 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), 
#line 23 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 23 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 23 "parser.cln"
value_make_number(0)),value_add_reference(
#line 23 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))) : (
#line 24 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 24 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 24 "parser.cln"
calein_column_SPACEnumber),value_add_reference(
#line 24 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber))));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_current_SPACEposition(void){
struct global_SCOPEcalein_current_SPACEposition_local_vars local_vars;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 30 "parser.cln"
global_SCOPEcalein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG(value_add_reference(
#line 30 "parser.cln"
calein_line_SPACEnumber),value_add_reference(
#line 30 "parser.cln"
calein_file_SPACEname)));
value_add_reference(result);
value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_make_SPACEliteral_ARG(struct value *calein_val){
struct global_SCOPEcalein_make_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_val = calein_val;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 36 "parser.cln"
global_SCOPEcalein_make_SPACEliteral_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 36 "parser.cln"
local_vars.calein_val),value_add_reference(
#line 36 "parser.cln"
global_SCOPEcalein_current_SPACEposition()));
value_add_reference(result);
value_remove_reference(local_vars.calein_val);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_make_SPACEnumber_ARG(struct value *calein_val){
struct global_SCOPEcalein_make_SPACEnumber_ARG_local_vars local_vars;
local_vars.calein_val = calein_val;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 40 "parser.cln"
global_SCOPEcalein_make_SPACEnumber_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 40 "parser.cln"
local_vars.calein_val),value_add_reference(
#line 40 "parser.cln"
global_SCOPEcalein_current_SPACEposition()));
value_add_reference(result);
value_remove_reference(local_vars.calein_val);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_make_SPACEsequence_ARG(struct value *calein_items){
struct global_SCOPEcalein_make_SPACEsequence_ARG_local_vars local_vars;
local_vars.calein_items = calein_items;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 44 "parser.cln"
global_SCOPEcalein_make_SPACEsequence_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 44 "parser.cln"
local_vars.calein_items),value_add_reference(
#line 44 "parser.cln"
global_SCOPEcalein_current_SPACEposition()));
value_add_reference(result);
value_remove_reference(local_vars.calein_items);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(struct value *calein_name, struct value *calein_args){
struct global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_args = calein_args;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 48 "parser.cln"
global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 48 "parser.cln"
local_vars.calein_name),value_add_reference(
#line 48 "parser.cln"
local_vars.calein_args),value_add_reference(
#line 48 "parser.cln"
global_SCOPEcalein_current_SPACEposition()));
value_add_reference(result);
value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_name);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(struct value *calein_n){
struct global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes_local_vars local_vars;
local_vars.calein_n = calein_n;
struct value *tmp_for_derefs = 0;
struct value *result = (({ while (value_boolean_is_true_remove_floating_reference(
#line 51 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 51 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 51 "parser.cln"
local_vars.calein_n),value_add_reference(
#line 51 "parser.cln"
value_make_number(0))))))) {

#line 52 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 52 "parser.cln"
calein_tab_SPACEstring));

#line 53 "parser.cln"
(tmp_for_derefs = local_vars.calein_n, local_vars.calein_n = value_add_reference(
#line 53 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 53 "parser.cln"
local_vars.calein_n),value_add_reference(
#line 53 "parser.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_n);

}
 0; }));
value_add_reference(result);
value_remove_reference(local_vars.calein_n);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(struct value *calein_tree, struct value *calein_indent){
struct global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG_local_vars local_vars;
local_vars.calein_items = 0;
local_vars.calein_args = 0;
local_vars.calein_tree = calein_tree;
local_vars.calein_indent = calein_indent;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(
#line 58 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(value_add_reference(
#line 58 "parser.cln"
local_vars.calein_tree))) ? ((
#line 60 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 60 "parser.cln"
local_vars.calein_indent)), 
#line 61 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 61 "parser.cln"
value_make_string_from_c_string("String: "))), 
#line 62 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 62 "parser.cln"
global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(value_add_reference(
#line 62 "parser.cln"
local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(
#line 63 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(value_add_reference(
#line 63 "parser.cln"
local_vars.calein_tree))) ? ((
#line 64 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 64 "parser.cln"
local_vars.calein_indent)), 
#line 65 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 65 "parser.cln"
value_make_string_from_c_string("Number: "))), 
#line 66 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 66 "parser.cln"
global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 66 "parser.cln"
local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(
#line 67 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(value_add_reference(
#line 67 "parser.cln"
local_vars.calein_tree))) ? ((
#line 68 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 68 "parser.cln"
local_vars.calein_indent)), 
#line 69 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 69 "parser.cln"
value_make_string_from_c_string("Sequence:"))), (local_vars.calein_items = value_add_reference(
#line 71 "parser.cln"
global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(value_add_reference(
#line 71 "parser.cln"
local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 72 "parser.cln"
local_vars.calein_items)) {

#line 73 "parser.cln"
global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(value_add_reference(
#line 73 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 73 "parser.cln"
local_vars.calein_items))),value_add_reference(
#line 73 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 73 "parser.cln"
local_vars.calein_indent),value_add_reference(
#line 73 "parser.cln"
value_make_number(1)))));

#line 74 "parser.cln"
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(
#line 74 "parser.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 74 "parser.cln"
local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }))) : ((value_boolean_is_true_remove_floating_reference(
#line 76 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(value_add_reference(
#line 76 "parser.cln"
local_vars.calein_tree))) ? ((
#line 77 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 77 "parser.cln"
local_vars.calein_indent)), 
#line 78 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 78 "parser.cln"
value_make_string_from_c_string("Action: "))), 
#line 79 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 79 "parser.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 79 "parser.cln"
local_vars.calein_tree)))), (local_vars.calein_args = value_add_reference(
#line 81 "parser.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 81 "parser.cln"
local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 82 "parser.cln"
local_vars.calein_args)) {

#line 83 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 83 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 83 "parser.cln"
local_vars.calein_indent),value_add_reference(
#line 83 "parser.cln"
value_make_number(1)))));

#line 84 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 84 "parser.cln"
value_make_string_from_c_string("Arg at ")));

#line 85 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 85 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 85 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 85 "parser.cln"
local_vars.calein_args))))));

#line 86 "parser.cln"
global_SCOPEcalein_write_SPACEtree_SPACE_SPACE_ARGwith_SPACEindent_ARG(value_add_reference(
#line 86 "parser.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 86 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 86 "parser.cln"
local_vars.calein_args))))),value_add_reference(
#line 86 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 86 "parser.cln"
local_vars.calein_indent),value_add_reference(
#line 86 "parser.cln"
value_make_number(1)))));

#line 87 "parser.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 87 "parser.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 87 "parser.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }))) : ((
#line 90 "parser.cln"
global_SCOPEcalein_indent_SPACE_SPACE_ARGtimes(value_add_reference(
#line 90 "parser.cln"
local_vars.calein_indent)), 
#line 91 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 91 "parser.cln"
value_make_string_from_c_string("unrecognized kind of tree: "))), 
#line 92 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 92 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 92 "parser.cln"
local_vars.calein_tree))))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_indent);value_remove_reference(local_vars.calein_tree);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars *global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars, struct value *calein_msg){
struct global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG_local_vars local_vars;
local_vars.global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars = global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 108 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 108 "parser.cln"
value_make_string_from_c_string("Parse error at line "))), 
#line 109 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 109 "parser.cln"
calein_line_SPACEnumber)), 
#line 110 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 110 "parser.cln"
value_make_string_from_c_string(", column "))), 
#line 111 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 111 "parser.cln"
calein_column_SPACEnumber)), 
#line 112 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 112 "parser.cln"
value_make_string_from_c_string(": "))), 
#line 113 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 113 "parser.cln"
local_vars.calein_msg)), 
#line 114 "parser.cln"
(tmp_for_derefs = global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction, global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction = value_add_reference(
#line 114 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_local_vars->calein_again_SPACEin_SPACEaction));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);value_float_result(result);
return result;
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
struct value *result = ((local_vars.calein_tree = value_add_reference(
#line 97 "parser.cln"
calein_false)), (local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(
#line 98 "parser.cln"
calein_true)), (local_vars.calein_children = value_add_reference(
#line 99 "parser.cln"
calein_false)), (local_vars.calein_literal = value_add_reference(
#line 100 "parser.cln"
value_make_string_from_c_string(""))), (local_vars.calein_paren = value_add_reference(
#line 101 "parser.cln"
calein_false)), (local_vars.calein_child = value_add_reference(
#line 102 "parser.cln"
calein_false)), (local_vars.calein_c = value_add_reference(
#line 104 "parser.cln"
value_make_number(0))), (value_boolean_is_true_remove_floating_reference(
#line 116 "parser.cln"
local_vars.calein_first_SPACEchild) ? (
#line 117 "parser.cln"
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(
#line 117 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 117 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 117 "parser.cln"
value_make_number(0)),value_add_reference(
#line 117 "parser.cln"
local_vars.calein_first_SPACEchild))),value_add_reference(
#line 117 "parser.cln"
local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children)) : (
#line 118 "parser.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 119 "parser.cln"
local_vars.calein_again_SPACEin_SPACEaction)) {

#line 120 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 120 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 123 "parser.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 121 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 121 "parser.cln"
local_vars.calein_c))),value_add_reference(
#line 121 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 121 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 121 "parser.cln"
calein_dot))),value_add_reference(
#line 122 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 122 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 122 "parser.cln"
calein_close_SPACEparen))),value_add_reference(
#line 123 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 123 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 123 "parser.cln"
calein_close_SPACEbrace)))))) {

#line 124 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEaction, local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(
#line 124 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEaction);
if (value_boolean_is_true_remove_floating_reference(
#line 125 "parser.cln"
local_vars.calein_children)) {
if (value_boolean_is_true_remove_floating_reference(
#line 126 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 126 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 126 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 126 "parser.cln"
local_vars.calein_children))))),value_add_reference(
#line 126 "parser.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 126 "parser.cln"
local_vars.calein_literal)))))) {

#line 127 "parser.cln"
global_SCOPEcalein_trim_SPACEright_ARG(value_add_reference(
#line 127 "parser.cln"
local_vars.calein_literal));

} else {

#line 128 "parser.cln"
calein_false;
}
} else {

#line 129 "parser.cln"
global_SCOPEcalein_trim_SPACEright_ARG(value_add_reference(
#line 129 "parser.cln"
local_vars.calein_literal));
}if (value_boolean_is_true_remove_floating_reference(
#line 131 "parser.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 130 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 130 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 130 "parser.cln"
calein_close_SPACEparen))),value_add_reference(
#line 131 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 131 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 131 "parser.cln"
calein_close_SPACEbrace)))))) {

#line 132 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 132 "parser.cln"
local_vars.calein_c));

} else {

#line 133 "parser.cln"
calein_false;
}if (value_boolean_is_true_remove_floating_reference(
#line 134 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 134 "parser.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 134 "parser.cln"
local_vars.calein_literal))),value_add_reference(
#line 134 "parser.cln"
value_make_number(0))))) {

#line 135 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 135 "parser.cln"
local_vars.calein_first_SPACEchild), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {

#line 138 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 138 "parser.cln"
global_SCOPEcalein_make_SPACEaction_SPACE_SPACE_ARGwith_SPACEarguments_ARG(value_add_reference(
#line 137 "parser.cln"
local_vars.calein_literal),value_add_reference(
#line 138 "parser.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 138 "parser.cln"
local_vars.calein_children))))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
}
#line 139 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEaction, local_vars.calein_again_SPACEin_SPACEaction = value_add_reference(
#line 139 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEaction);

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 140 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACE_COMMA_ARG_SPACEor_ARG(value_add_reference(
#line 140 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 140 "parser.cln"
calein_quote),value_add_reference(
#line 140 "parser.cln"
calein_number_SPACEsigil),value_add_reference(
#line 140 "parser.cln"
calein_open_SPACEparen),value_add_reference(
#line 140 "parser.cln"
calein_open_SPACEbrace)))) {

#line 141 "parser.cln"
(tmp_for_derefs = local_vars.calein_paren, local_vars.calein_paren = value_add_reference(
#line 141 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 141 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 141 "parser.cln"
calein_open_SPACEparen))), value_remove_reference(tmp_for_derefs),local_vars.calein_paren);
if (value_boolean_is_true_remove_floating_reference(
#line 142 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 142 "parser.cln"
local_vars.calein_paren)))) {

#line 142 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 142 "parser.cln"
local_vars.calein_c));

} else {

#line 142 "parser.cln"
calein_false;
}
#line 143 "parser.cln"
(tmp_for_derefs = local_vars.calein_child, local_vars.calein_child = value_add_reference(
#line 143 "parser.cln"
global_SCOPEcalein_parse_ARG(value_add_reference(
#line 143 "parser.cln"
local_vars.calein_paren))), value_remove_reference(tmp_for_derefs),local_vars.calein_child);
if (value_boolean_is_true_remove_floating_reference(
#line 144 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 144 "parser.cln"
local_vars.calein_child)))) {

#line 144 "parser.cln"
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 144 "parser.cln"
value_make_string_from_c_string("expected argument")));

} else {

#line 146 "parser.cln"
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(
#line 146 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 146 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 146 "parser.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 146 "parser.cln"
local_vars.calein_literal))),value_add_reference(
#line 146 "parser.cln"
local_vars.calein_child))),value_add_reference(
#line 146 "parser.cln"
local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children);
if (value_boolean_is_true_remove_floating_reference(
#line 147 "parser.cln"
local_vars.calein_paren)) {

#line 148 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 148 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 149 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 149 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 149 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 149 "parser.cln"
calein_close_SPACEparen)))))) {

#line 150 "parser.cln"
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 150 "parser.cln"
value_make_string_from_c_string("expected close paren")));

} else {

#line 151 "parser.cln"
calein_false;
}
} else {

#line 152 "parser.cln"
calein_false;
}}
} else {
if (value_boolean_is_true_remove_floating_reference(
#line 154 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(value_add_reference(
#line 154 "parser.cln"
local_vars.calein_c)))) {
if (value_boolean_is_true_remove_floating_reference(
#line 155 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 155 "parser.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 155 "parser.cln"
local_vars.calein_literal))),value_add_reference(
#line 155 "parser.cln"
value_make_number(0))))) {

#line 156 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 156 "parser.cln"
calein_space),value_add_reference(
#line 156 "parser.cln"
local_vars.calein_literal));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 157 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 157 "parser.cln"
global_SCOPEcalein_last_SPACEcharacter_SPACEof_ARG(value_add_reference(
#line 157 "parser.cln"
local_vars.calein_literal))),value_add_reference(
#line 157 "parser.cln"
calein_space)))) {
if (value_boolean_is_true_remove_floating_reference(
#line 158 "parser.cln"
local_vars.calein_children)) {
if (value_boolean_is_true_remove_floating_reference(
#line 159 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 159 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 159 "parser.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 159 "parser.cln"
local_vars.calein_children))))),value_add_reference(
#line 159 "parser.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 159 "parser.cln"
local_vars.calein_literal)))))) {

#line 160 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 160 "parser.cln"
calein_space),value_add_reference(
#line 160 "parser.cln"
local_vars.calein_literal));

} else {

#line 161 "parser.cln"
calein_false;
}
} else {

#line 162 "parser.cln"
calein_false;
}
} else {

#line 163 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 163 "parser.cln"
calein_space),value_add_reference(
#line 163 "parser.cln"
local_vars.calein_literal));
}}
} else {

#line 164 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 164 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 164 "parser.cln"
local_vars.calein_literal));
}}}
}
 0; }), 
#line 166 "parser.cln"
local_vars.calein_tree);
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_child);value_remove_reference(local_vars.calein_paren);value_remove_reference(local_vars.calein_literal);value_remove_reference(local_vars.calein_children);value_remove_reference(local_vars.calein_again_SPACEin_SPACEaction);value_remove_reference(local_vars.calein_tree);value_remove_reference(local_vars.calein_first_SPACEchild);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(struct global_SCOPEcalein_parse_ARG_local_vars *global_SCOPEcalein_parse_ARG_local_vars, struct value *calein_msg){
struct global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG_local_vars local_vars;
local_vars.global_SCOPEcalein_parse_ARG_local_vars = global_SCOPEcalein_parse_ARG_local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 179 "parser.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 179 "parser.cln"
value_make_string_from_c_string("Parse error: "))), 
#line 180 "parser.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 180 "parser.cln"
local_vars.calein_msg)), 
#line 181 "parser.cln"
(tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral, global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 181 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEliteral), 
#line 182 "parser.cln"
(tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence, global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence = value_add_reference(
#line 182 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again_SPACEin_SPACEsequence), 
#line 183 "parser.cln"
(tmp_for_derefs = global_SCOPEcalein_parse_ARG_local_vars->calein_again, global_SCOPEcalein_parse_ARG_local_vars->calein_again = value_add_reference(
#line 183 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),global_SCOPEcalein_parse_ARG_local_vars->calein_again));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);value_float_result(result);
return result;
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
local_vars.calein_negative = 0;
local_vars.calein_child = 0;
local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression = calein_at_SPACEstart_SPACEof_SPACEexpression;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_again = value_add_reference(
#line 170 "parser.cln"
calein_true)), (local_vars.calein_literal = value_add_reference(
#line 171 "parser.cln"
value_make_number(0))), (local_vars.calein_in_SPACEescape = value_add_reference(
#line 172 "parser.cln"
calein_false)), (local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 173 "parser.cln"
calein_true)), (local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(
#line 174 "parser.cln"
calein_true)), (local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(
#line 175 "parser.cln"
calein_false)), (local_vars.calein_children = value_add_reference(
#line 176 "parser.cln"
calein_false)), (local_vars.calein_c = value_add_reference(
#line 185 "parser.cln"
value_make_number(0))), (local_vars.calein_tree = value_add_reference(
#line 187 "parser.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 188 "parser.cln"
local_vars.calein_again)) {

#line 189 "parser.cln"
(tmp_for_derefs = local_vars.calein_again, local_vars.calein_again = value_add_reference(
#line 189 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again);

#line 190 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 190 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 191 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 191 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 191 "parser.cln"
calein_quote)))) {

#line 192 "parser.cln"
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(
#line 192 "parser.cln"
value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);

#line 193 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 193 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);

#line 194 "parser.cln"
(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(
#line 194 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);
while (value_boolean_is_true_remove_floating_reference(
#line 195 "parser.cln"
local_vars.calein_again_SPACEin_SPACEliteral)) {

#line 196 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 196 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 197 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 197 "parser.cln"
local_vars.calein_c)))) {

#line 198 "parser.cln"
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 198 "parser.cln"
value_make_string_from_c_string("unterminated string literal")));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 199 "parser.cln"
local_vars.calein_in_SPACEescape)) {
if (value_boolean_is_true_remove_floating_reference(
#line 200 "parser.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 200 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 200 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 200 "parser.cln"
calein_backslash))),value_add_reference(
#line 200 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 200 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 200 "parser.cln"
calein_quote)))))) {

#line 201 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 201 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 201 "parser.cln"
local_vars.calein_literal));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 202 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 202 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 202 "parser.cln"
calein_character_SPACEn)))) {

#line 203 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 203 "parser.cln"
calein_new_SPACEline),value_add_reference(
#line 203 "parser.cln"
local_vars.calein_literal));

} else {

#line 204 "parser.cln"
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 204 "parser.cln"
value_make_string_from_c_string("undefined escape sequence")));
}}
#line 205 "parser.cln"
(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(
#line 205 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 207 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 207 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 207 "parser.cln"
calein_backslash)))) {

#line 208 "parser.cln"
(tmp_for_derefs = local_vars.calein_in_SPACEescape, local_vars.calein_in_SPACEescape = value_add_reference(
#line 208 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_in_SPACEescape);

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 209 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 209 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 209 "parser.cln"
calein_quote)))) {

#line 211 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 211 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);

#line 212 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 212 "parser.cln"
global_SCOPEcalein_make_SPACEliteral_ARG(value_add_reference(
#line 212 "parser.cln"
local_vars.calein_literal))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
if (value_boolean_is_true_remove_floating_reference(
#line 213 "parser.cln"
local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression)) {

#line 214 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 214 "parser.cln"
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(
#line 214 "parser.cln"
local_vars.calein_tree))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {

#line 215 "parser.cln"
calein_false;
}
} else {

#line 217 "parser.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 217 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 217 "parser.cln"
local_vars.calein_literal));
}}}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 219 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 219 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 219 "parser.cln"
calein_number_SPACEsigil)))) {

#line 220 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 220 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);

#line 221 "parser.cln"
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(
#line 221 "parser.cln"
value_make_number(0)), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);

#line 222 "parser.cln"
(tmp_for_derefs = local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral, local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(
#line 222 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral);
local_vars.calein_negative = value_add_reference(
#line 223 "parser.cln"
calein_false);
while (value_boolean_is_true_remove_floating_reference(
#line 224 "parser.cln"
local_vars.calein_again_SPACEin_SPACEliteral)) {

#line 225 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 225 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 226 "parser.cln"
global_SCOPEcalein__SPACE_ARGand_ARG(value_add_reference(
#line 226 "parser.cln"
local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral),value_add_reference(
#line 226 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 226 "parser.cln"
local_vars.calein_c)))))) {

#line 227 "parser.cln"
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 227 "parser.cln"
value_make_string_from_c_string("Unexpected EOF at beginning of number")));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 228 "parser.cln"
global_SCOPEcalein__SPACE_ARGand_ARG(value_add_reference(
#line 228 "parser.cln"
local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral),value_add_reference(
#line 228 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 228 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 228 "parser.cln"
calein_minus)))))) {

#line 229 "parser.cln"
(tmp_for_derefs = local_vars.calein_negative, local_vars.calein_negative = value_add_reference(
#line 229 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_negative);

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 230 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 230 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEdigit(value_add_reference(
#line 230 "parser.cln"
local_vars.calein_c)))))) {
if (value_boolean_is_true_remove_floating_reference(
#line 231 "parser.cln"
local_vars.calein_c)) {

#line 231 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 231 "parser.cln"
local_vars.calein_c));

} else {

#line 231 "parser.cln"
calein_false;
}
#line 232 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEliteral, local_vars.calein_again_SPACEin_SPACEliteral = value_add_reference(
#line 232 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEliteral);

#line 234 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 234 "parser.cln"
global_SCOPEcalein_make_SPACEnumber_ARG(value_add_reference((value_boolean_is_true_remove_floating_reference(
#line 234 "parser.cln"
local_vars.calein_negative) ? (
#line 234 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 234 "parser.cln"
value_make_number(0)),value_add_reference(
#line 234 "parser.cln"
local_vars.calein_literal))) : (
#line 234 "parser.cln"
local_vars.calein_literal))))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);
if (value_boolean_is_true_remove_floating_reference(
#line 235 "parser.cln"
local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression)) {

#line 236 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 236 "parser.cln"
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(
#line 236 "parser.cln"
local_vars.calein_tree))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {

#line 237 "parser.cln"
calein_false;
}
} else {

#line 239 "parser.cln"
(tmp_for_derefs = local_vars.calein_literal, local_vars.calein_literal = value_add_reference(
#line 239 "parser.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 239 "parser.cln"
global_SCOPEcalein__SPACE_ARG_STAR_ARG(value_add_reference(
#line 239 "parser.cln"
local_vars.calein_literal),value_add_reference(
#line 239 "parser.cln"
value_make_number(10)))),value_add_reference(
#line 239 "parser.cln"
global_SCOPEcalein__SPACE_ARG_DASH_ARG(value_add_reference(
#line 239 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 239 "parser.cln"
calein_character_SPACE0))))), value_remove_reference(tmp_for_derefs),local_vars.calein_literal);

#line 240 "parser.cln"
(tmp_for_derefs = local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral, local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral = value_add_reference(
#line 240 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral);
}}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 243 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 243 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 243 "parser.cln"
calein_open_SPACEbrace)))) {

#line 244 "parser.cln"
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(
#line 244 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_children);

#line 245 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEsequence, local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(
#line 245 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEsequence);
while (value_boolean_is_true_remove_floating_reference(
#line 246 "parser.cln"
local_vars.calein_again_SPACEin_SPACEsequence)) {

#line 247 "parser.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 247 "parser.cln"
global_SCOPEcalein_get_SPACEcharacter()), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 248 "parser.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 248 "parser.cln"
local_vars.calein_c)))) {

#line 248 "parser.cln"
global_SCOPEcalein_parse_ARG_SCOPEcalein_error_ARG(&local_vars,value_add_reference(
#line 248 "parser.cln"
value_make_string_from_c_string("unexpected EOF in sequence")));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 249 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 249 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 249 "parser.cln"
calein_close_SPACEbrace)))) {

#line 250 "parser.cln"
(tmp_for_derefs = local_vars.calein_again_SPACEin_SPACEsequence, local_vars.calein_again_SPACEin_SPACEsequence = value_add_reference(
#line 250 "parser.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_again_SPACEin_SPACEsequence);

#line 251 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 251 "parser.cln"
global_SCOPEcalein_make_SPACEsequence_ARG(value_add_reference(
#line 251 "parser.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 251 "parser.cln"
local_vars.calein_children))))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {

#line 253 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 253 "parser.cln"
local_vars.calein_c));
local_vars.calein_child = value_add_reference(
#line 254 "parser.cln"
global_SCOPEcalein_parse_ARG(value_add_reference(
#line 254 "parser.cln"
calein_true)));
if (value_boolean_is_true_remove_floating_reference(
#line 255 "parser.cln"
local_vars.calein_child)) {

#line 256 "parser.cln"
(tmp_for_derefs = local_vars.calein_children, local_vars.calein_children = value_add_reference(
#line 256 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 256 "parser.cln"
local_vars.calein_child),value_add_reference(
#line 256 "parser.cln"
local_vars.calein_children))), value_remove_reference(tmp_for_derefs),local_vars.calein_children);

} else {

#line 257 "parser.cln"
calein_false;
}}}
}

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 260 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEwhitespace(value_add_reference(
#line 260 "parser.cln"
local_vars.calein_c)))) {

#line 261 "parser.cln"
(tmp_for_derefs = local_vars.calein_again, local_vars.calein_again = value_add_reference(
#line 261 "parser.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_again);

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 262 "parser.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 262 "parser.cln"
local_vars.calein_c),value_add_reference(
#line 262 "parser.cln"
calein_close_SPACEbrace)))) {

#line 263 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 263 "parser.cln"
local_vars.calein_c));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 264 "parser.cln"
local_vars.calein_c)) {

#line 265 "parser.cln"
global_SCOPEcalein_unget_SPACEcharacter_ARG(value_add_reference(
#line 265 "parser.cln"
local_vars.calein_c));

#line 266 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 266 "parser.cln"
global_SCOPEcalein_try_SPACEparse_SPACEaction_SPACEafter_ARG(value_add_reference(
#line 266 "parser.cln"
calein_false))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree);

} else {

#line 267 "parser.cln"
calein_false;
}}}}}}
}
 0; }), 
#line 269 "parser.cln"
local_vars.calein_tree);
value_add_reference(result);
value_remove_reference(local_vars.calein_child);value_remove_reference(local_vars.calein_negative);value_remove_reference(local_vars.calein_tree);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_children);value_remove_reference(local_vars.calein_at_SPACEstart_SPACEof_SPACEliteral);value_remove_reference(local_vars.calein_again_SPACEin_SPACEsequence);value_remove_reference(local_vars.calein_again_SPACEin_SPACEliteral);value_remove_reference(local_vars.calein_in_SPACEescape);value_remove_reference(local_vars.calein_literal);value_remove_reference(local_vars.calein_again);value_remove_reference(local_vars.calein_at_SPACEstart_SPACEof_SPACEexpression);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(struct value *calein_f, struct value *calein_name){
struct global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG_local_vars local_vars;
local_vars.calein_old_SPACEfile = 0;
local_vars.calein_old_SPACEfile_SPACEname = 0;
local_vars.calein_old_SPACEline_SPACEnumber = 0;
local_vars.calein_old_SPACEcolumn_SPACEnumber = 0;
local_vars.calein_old_SPACEungotten = 0;
local_vars.calein_reversed_SPACEsyntax_SPACEtrees = 0;
local_vars.calein_tree = 0;
local_vars.calein_f = calein_f;
local_vars.calein_name = calein_name;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_old_SPACEfile = value_add_reference(
#line 273 "parser.cln"
calein_file_SPACEto_SPACEread_SPACEfrom)), (local_vars.calein_old_SPACEfile_SPACEname = value_add_reference(
#line 274 "parser.cln"
calein_file_SPACEname)), (local_vars.calein_old_SPACEline_SPACEnumber = value_add_reference(
#line 275 "parser.cln"
calein_line_SPACEnumber)), (local_vars.calein_old_SPACEcolumn_SPACEnumber = value_add_reference(
#line 276 "parser.cln"
calein_column_SPACEnumber)), (local_vars.calein_old_SPACEungotten = value_add_reference(
#line 277 "parser.cln"
calein_ungotten_SPACEcharacter)), (local_vars.calein_reversed_SPACEsyntax_SPACEtrees = value_add_reference(
#line 278 "parser.cln"
calein_false)), (local_vars.calein_tree = value_add_reference(
#line 279 "parser.cln"
calein_false)), 
#line 280 "parser.cln"
(tmp_for_derefs = calein_file_SPACEto_SPACEread_SPACEfrom, calein_file_SPACEto_SPACEread_SPACEfrom = value_add_reference(
#line 280 "parser.cln"
local_vars.calein_f), value_remove_reference(tmp_for_derefs),calein_file_SPACEto_SPACEread_SPACEfrom), 
#line 281 "parser.cln"
(tmp_for_derefs = calein_file_SPACEname, calein_file_SPACEname = value_add_reference(
#line 281 "parser.cln"
local_vars.calein_name), value_remove_reference(tmp_for_derefs),calein_file_SPACEname), 
#line 282 "parser.cln"
(tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(
#line 282 "parser.cln"
value_make_number(1)), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), 
#line 283 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 283 "parser.cln"
value_make_number(1)), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber), ({ while (value_boolean_is_true_remove_floating_reference((
#line 285 "parser.cln"
(tmp_for_derefs = local_vars.calein_tree, local_vars.calein_tree = value_add_reference(
#line 285 "parser.cln"
global_SCOPEcalein_parse_ARG(value_add_reference(
#line 285 "parser.cln"
calein_true))), value_remove_reference(tmp_for_derefs),local_vars.calein_tree), 
#line 286 "parser.cln"
local_vars.calein_tree))) {

#line 288 "parser.cln"
(tmp_for_derefs = local_vars.calein_reversed_SPACEsyntax_SPACEtrees, local_vars.calein_reversed_SPACEsyntax_SPACEtrees = value_add_reference(
#line 288 "parser.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 288 "parser.cln"
local_vars.calein_tree),value_add_reference(
#line 288 "parser.cln"
local_vars.calein_reversed_SPACEsyntax_SPACEtrees))), value_remove_reference(tmp_for_derefs),local_vars.calein_reversed_SPACEsyntax_SPACEtrees);

}
 0; }), 
#line 290 "parser.cln"
(tmp_for_derefs = calein_file_SPACEto_SPACEread_SPACEfrom, calein_file_SPACEto_SPACEread_SPACEfrom = value_add_reference(
#line 290 "parser.cln"
local_vars.calein_old_SPACEfile), value_remove_reference(tmp_for_derefs),calein_file_SPACEto_SPACEread_SPACEfrom), 
#line 291 "parser.cln"
(tmp_for_derefs = calein_file_SPACEname, calein_file_SPACEname = value_add_reference(
#line 291 "parser.cln"
local_vars.calein_old_SPACEfile_SPACEname), value_remove_reference(tmp_for_derefs),calein_file_SPACEname), 
#line 292 "parser.cln"
(tmp_for_derefs = calein_line_SPACEnumber, calein_line_SPACEnumber = value_add_reference(
#line 292 "parser.cln"
local_vars.calein_old_SPACEline_SPACEnumber), value_remove_reference(tmp_for_derefs),calein_line_SPACEnumber), 
#line 293 "parser.cln"
(tmp_for_derefs = calein_column_SPACEnumber, calein_column_SPACEnumber = value_add_reference(
#line 293 "parser.cln"
local_vars.calein_old_SPACEcolumn_SPACEnumber), value_remove_reference(tmp_for_derefs),calein_column_SPACEnumber), 
#line 294 "parser.cln"
(tmp_for_derefs = calein_ungotten_SPACEcharacter, calein_ungotten_SPACEcharacter = value_add_reference(
#line 294 "parser.cln"
local_vars.calein_old_SPACEungotten), value_remove_reference(tmp_for_derefs),calein_ungotten_SPACEcharacter), 
#line 295 "parser.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 295 "parser.cln"
local_vars.calein_reversed_SPACEsyntax_SPACEtrees)));
value_add_reference(result);
value_remove_reference(local_vars.calein_tree);value_remove_reference(local_vars.calein_reversed_SPACEsyntax_SPACEtrees);value_remove_reference(local_vars.calein_old_SPACEungotten);value_remove_reference(local_vars.calein_old_SPACEcolumn_SPACEnumber);value_remove_reference(local_vars.calein_old_SPACEline_SPACEnumber);value_remove_reference(local_vars.calein_old_SPACEfile_SPACEname);value_remove_reference(local_vars.calein_old_SPACEfile);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_f);value_float_result(result);
return result;
}
struct value *calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers;
struct value *global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(struct value *calein_str, struct value *calein_c){
struct global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG_local_vars local_vars;
local_vars.calein_str = calein_str;
local_vars.calein_c = calein_c;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 7 "c-utils.cln"
(tmp_for_derefs = calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers, calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = value_add_reference(
#line 7 "c-utils.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 7 "c-utils.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 7 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 7 "c-utils.cln"
local_vars.calein_str))),value_add_reference(
#line 7 "c-utils.cln"
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers))), value_remove_reference(tmp_for_derefs),calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers));
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_str);value_float_result(result);
return result;
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
struct value *result = ((local_vars.calein_name = value_add_reference(
#line 20 "c-utils.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 20 "c-utils.cln"
local_vars.calein_action)))), (local_vars.calein_args = value_add_reference(
#line 21 "c-utils.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 21 "c-utils.cln"
local_vars.calein_action)))), (local_vars.calein_ident = value_add_reference(
#line 22 "c-utils.cln"
value_make_string_from_c_string("calein_"))), (local_vars.calein_i = value_add_reference(
#line 23 "c-utils.cln"
value_make_number(0))), (local_vars.calein_c = value_add_reference(
#line 24 "c-utils.cln"
calein_false)), (local_vars.calein_added = value_add_reference(
#line 25 "c-utils.cln"
calein_false)), (local_vars.calein_substitutions = value_add_reference(
#line 26 "c-utils.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 27 "c-utils.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 27 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 27 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 27 "c-utils.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 27 "c-utils.cln"
local_vars.calein_name)))))))) {

#line 28 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 28 "c-utils.cln"
global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(
#line 28 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 28 "c-utils.cln"
local_vars.calein_name))), value_remove_reference(tmp_for_derefs),local_vars.calein_c);

#line 29 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_added, local_vars.calein_added = value_add_reference(
#line 29 "c-utils.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_added);

#line 30 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(
#line 30 "c-utils.cln"
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);
while (value_boolean_is_true_remove_floating_reference(
#line 31 "c-utils.cln"
local_vars.calein_substitutions)) {
if (value_boolean_is_true_remove_floating_reference(
#line 32 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 32 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 32 "c-utils.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 32 "c-utils.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 32 "c-utils.cln"
local_vars.calein_substitutions)))))))) {

#line 34 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 34 "c-utils.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 34 "c-utils.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 34 "c-utils.cln"
local_vars.calein_substitutions))))),value_add_reference(
#line 34 "c-utils.cln"
local_vars.calein_ident));

#line 35 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_added, local_vars.calein_added = value_add_reference(
#line 35 "c-utils.cln"
calein_true), value_remove_reference(tmp_for_derefs),local_vars.calein_added);

#line 36 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(
#line 36 "c-utils.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);

} else {

#line 37 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_substitutions, local_vars.calein_substitutions = value_add_reference(
#line 37 "c-utils.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 37 "c-utils.cln"
local_vars.calein_substitutions))), value_remove_reference(tmp_for_derefs),local_vars.calein_substitutions);
}
}
if (value_boolean_is_true_remove_floating_reference(
#line 39 "c-utils.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 39 "c-utils.cln"
local_vars.calein_added)))) {

#line 39 "c-utils.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 39 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 39 "c-utils.cln"
local_vars.calein_ident));

} else {

#line 39 "c-utils.cln"
calein_false;
}if (value_boolean_is_true_remove_floating_reference(
#line 40 "c-utils.cln"
local_vars.calein_args)) {
if (value_boolean_is_true_remove_floating_reference(
#line 40 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 40 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 40 "c-utils.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 40 "c-utils.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 40 "c-utils.cln"
local_vars.calein_args)))))))) {

#line 41 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 41 "c-utils.cln"
value_make_string_from_c_string("_ARG")),value_add_reference(
#line 41 "c-utils.cln"
local_vars.calein_ident));

#line 42 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 42 "c-utils.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 42 "c-utils.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

} else {

#line 43 "c-utils.cln"
calein_false;
}
} else {

#line 43 "c-utils.cln"
calein_false;
}
#line 44 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 44 "c-utils.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 44 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 44 "c-utils.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), (value_boolean_is_true_remove_floating_reference(
#line 46 "c-utils.cln"
local_vars.calein_args) ? (
#line 46 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 46 "c-utils.cln"
value_make_string_from_c_string("_ARG")),value_add_reference(
#line 46 "c-utils.cln"
local_vars.calein_ident))) : (
#line 46 "c-utils.cln"
calein_false)), 
#line 47 "c-utils.cln"
local_vars.calein_ident);
value_add_reference(result);
value_remove_reference(local_vars.calein_substitutions);value_remove_reference(local_vars.calein_added);value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_action);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(struct value *calein_literal){
struct global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG_local_vars local_vars;
local_vars.calein_string = 0;
local_vars.calein_i = 0;
local_vars.calein_c = 0;
local_vars.calein_literal = calein_literal;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_string = value_add_reference(
#line 51 "c-utils.cln"
value_make_string_from_c_string("\""))), (local_vars.calein_i = value_add_reference(
#line 52 "c-utils.cln"
value_make_number(0))), (local_vars.calein_c = value_add_reference(
#line 53 "c-utils.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 54 "c-utils.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 54 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 54 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 54 "c-utils.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 54 "c-utils.cln"
local_vars.calein_literal)))))))) {

#line 55 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_c, local_vars.calein_c = value_add_reference(
#line 55 "c-utils.cln"
global_SCOPEcalein_character_SPACEat_SPACE_SPACE_ARGof_ARG(value_add_reference(
#line 55 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 55 "c-utils.cln"
local_vars.calein_literal))), value_remove_reference(tmp_for_derefs),local_vars.calein_c);
if (value_boolean_is_true_remove_floating_reference(
#line 56 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 56 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 56 "c-utils.cln"
calein_quote)))) {

#line 57 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 57 "c-utils.cln"
value_make_string_from_c_string("\\\"")),value_add_reference(
#line 57 "c-utils.cln"
local_vars.calein_string));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 58 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 58 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 58 "c-utils.cln"
calein_backslash)))) {

#line 59 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 59 "c-utils.cln"
value_make_string_from_c_string("\\\\")),value_add_reference(
#line 59 "c-utils.cln"
local_vars.calein_string));

} else {
if (value_boolean_is_true_remove_floating_reference(
#line 60 "c-utils.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 60 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 60 "c-utils.cln"
calein_new_SPACEline)))) {

#line 61 "c-utils.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 61 "c-utils.cln"
value_make_string_from_c_string("\\n")),value_add_reference(
#line 61 "c-utils.cln"
local_vars.calein_string));

} else {

#line 62 "c-utils.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 62 "c-utils.cln"
local_vars.calein_c),value_add_reference(
#line 62 "c-utils.cln"
local_vars.calein_string));
}}}
#line 63 "c-utils.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 63 "c-utils.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 63 "c-utils.cln"
local_vars.calein_i),value_add_reference(
#line 63 "c-utils.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), 
#line 65 "c-utils.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 65 "c-utils.cln"
calein_quote),value_add_reference(
#line 65 "c-utils.cln"
local_vars.calein_string)), 
#line 66 "c-utils.cln"
local_vars.calein_string);
value_add_reference(result);
value_remove_reference(local_vars.calein_c);value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_string);value_remove_reference(local_vars.calein_literal);value_float_result(result);
return result;
}
struct value *calein_source_SPACElevel_SPACEdebugging;
struct value *global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(struct value *calein_pos, struct value *calein_out){
struct global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_pos = calein_pos;
local_vars.calein_out = calein_out;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(
#line 7 "codegen.cln"
calein_source_SPACElevel_SPACEdebugging) ? ((
#line 8 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 8 "codegen.cln"
value_make_string_from_c_string("\n#line ")),value_add_reference(
#line 8 "codegen.cln"
local_vars.calein_out)), 
#line 9 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 9 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 9 "codegen.cln"
global_SCOPEcalein_line_SPACEof_SPACEposition_ARG(value_add_reference(
#line 9 "codegen.cln"
local_vars.calein_pos))))),value_add_reference(
#line 9 "codegen.cln"
local_vars.calein_out)), 
#line 10 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 10 "codegen.cln"
value_make_string_from_c_string(" ")),value_add_reference(
#line 10 "codegen.cln"
local_vars.calein_out)), 
#line 11 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 11 "codegen.cln"
global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(
#line 11 "codegen.cln"
global_SCOPEcalein_file_SPACEof_SPACEposition_ARG(value_add_reference(
#line 11 "codegen.cln"
local_vars.calein_pos))))),value_add_reference(
#line 11 "codegen.cln"
local_vars.calein_out)), 
#line 12 "codegen.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 12 "codegen.cln"
calein_new_SPACEline),value_add_reference(
#line 12 "codegen.cln"
local_vars.calein_out)))) : (
#line 13 "codegen.cln"
calein_false)));
value_add_reference(result);
value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_pos);value_float_result(result);
return result;
}
struct value *calein_expression_SPACEcontext;
struct value *calein_statement_SPACEcontext;
struct value *calein_definition_SPACEcontext;
struct value *calein_declaration_SPACEcontext;
struct value *calein_initializer_SPACEcontext;
struct value *calein_nested_SPACEdefinition_SPACEcontext;
struct value *calein_procedure_SPACEdefinition_SPACEcontext;
struct value *calein_variable_SPACElist;
struct value *calein_function_SPACElist;
struct value *calein_function_SPACEvariable_SPACElist;
struct value *calein_module_SPACElist_SPACEby_SPACEcontext;
struct value *global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(struct value *calein_var, struct value *calein_scope){
struct global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG_local_vars local_vars;
local_vars.calein_old_SPACEscope = 0;
local_vars.calein_var = calein_var;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_old_SPACEscope = value_add_reference(
#line 53 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 53 "codegen.cln"
local_vars.calein_var),value_add_reference(
#line 53 "codegen.cln"
calein_variable_SPACElist)))), (value_boolean_is_true_remove_floating_reference(
#line 54 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 54 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 54 "codegen.cln"
local_vars.calein_old_SPACEscope),value_add_reference(
#line 54 "codegen.cln"
local_vars.calein_scope))))) ? (
#line 55 "codegen.cln"
(tmp_for_derefs = calein_variable_SPACElist, calein_variable_SPACElist = value_add_reference(
#line 55 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 55 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 55 "codegen.cln"
local_vars.calein_var),value_add_reference(
#line 55 "codegen.cln"
local_vars.calein_scope))),value_add_reference(
#line 55 "codegen.cln"
calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),calein_variable_SPACElist)) : (
#line 56 "codegen.cln"
calein_true)));
value_add_reference(result);
value_remove_reference(local_vars.calein_old_SPACEscope);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_var);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(struct value *calein_context){
struct global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation_local_vars local_vars;
local_vars.calein_context = calein_context;
struct value *tmp_for_derefs = 0;
struct value *result = 
#line 64 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 64 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 63 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 60 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 60 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 60 "codegen.cln"
calein_definition_SPACEcontext))),value_add_reference(
#line 61 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 61 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 61 "codegen.cln"
calein_initializer_SPACEcontext))),value_add_reference(
#line 62 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 62 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 62 "codegen.cln"
calein_nested_SPACEdefinition_SPACEcontext))),value_add_reference(
#line 63 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 63 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 63 "codegen.cln"
calein_procedure_SPACEdefinition_SPACEcontext))))),value_add_reference(
#line 64 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 64 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 64 "codegen.cln"
calein_declaration_SPACEcontext))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_context);value_float_result(result);
return result;
}
struct value *calein_global_SPACEscope;
struct value *global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(struct value *calein_name, struct value *calein_var_SPACEscope, struct value *calein_scope, struct value *calein_out){
struct global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_name = calein_name;
local_vars.calein_var_SPACEscope = calein_var_SPACEscope;
local_vars.calein_scope = calein_scope;
local_vars.calein_out = calein_out;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(
#line 72 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 72 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 72 "codegen.cln"
calein_global_SPACEscope))) ? (
#line 73 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 73 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 73 "codegen.cln"
local_vars.calein_out))) : (((value_boolean_is_true_remove_floating_reference(
#line 75 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 75 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 75 "codegen.cln"
local_vars.calein_scope))) ? ((
#line 76 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 76 "codegen.cln"
value_make_string_from_c_string("local_vars.")),value_add_reference(
#line 76 "codegen.cln"
local_vars.calein_out)))) : ((
#line 78 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 78 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 78 "codegen.cln"
local_vars.calein_out)), 
#line 79 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 79 "codegen.cln"
value_make_string_from_c_string("_local_vars->")),value_add_reference(
#line 79 "codegen.cln"
local_vars.calein_out))))), 
#line 81 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 81 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 81 "codegen.cln"
local_vars.calein_out))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_var_SPACEscope);value_remove_reference(local_vars.calein_name);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(struct value *calein_proc_SPACEname, struct value *calein_out){
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG_local_vars local_vars;
local_vars.calein_proc_SPACEname = calein_proc_SPACEname;
local_vars.calein_out = calein_out;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 86 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 86 "codegen.cln"
value_make_string_from_c_string("struct ")),value_add_reference(
#line 86 "codegen.cln"
local_vars.calein_out)), 
#line 87 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 87 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 87 "codegen.cln"
local_vars.calein_out)), 
#line 88 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 88 "codegen.cln"
value_make_string_from_c_string("_local_vars")),value_add_reference(
#line 88 "codegen.cln"
local_vars.calein_out)));
value_add_reference(result);
value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);value_float_result(result);
return result;
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
struct value *result = (
#line 92 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 92 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 92 "codegen.cln"
local_vars.calein_out)), 
#line 93 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 93 "codegen.cln"
value_make_string_from_c_string(" {\n")),value_add_reference(
#line 93 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 94 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 94 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 94 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 94 "codegen.cln"
calein_global_SPACEscope))))) ? ((
#line 95 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 95 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 95 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 95 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 96 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 96 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 96 "codegen.cln"
local_vars.calein_out)))) : (
#line 97 "codegen.cln"
calein_false)), (local_vars.calein_args = value_add_reference(
#line 98 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 98 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 98 "codegen.cln"
local_vars.calein_ir)))))), (local_vars.calein_ident = value_add_reference(
#line 99 "codegen.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 100 "codegen.cln"
local_vars.calein_args)) {

#line 101 "codegen.cln"
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(
#line 101 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 101 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 101 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 101 "codegen.cln"
local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);
if (value_boolean_is_true_remove_floating_reference(
#line 102 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 102 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 102 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 102 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 102 "codegen.cln"
calein_variable_SPACElist))),value_add_reference(
#line 102 "codegen.cln"
local_vars.calein_proc_SPACEname)))))) {

#line 103 "codegen.cln"
global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(value_add_reference(
#line 103 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 103 "codegen.cln"
local_vars.calein_proc_SPACEname));

#line 104 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 104 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 104 "codegen.cln"
local_vars.calein_out));

#line 105 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 105 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 105 "codegen.cln"
local_vars.calein_out));

#line 106 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 106 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 106 "codegen.cln"
local_vars.calein_out));

} else {

#line 107 "codegen.cln"
calein_false;
}
#line 108 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 108 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 108 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), 
#line 110 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 110 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 110 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 110 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 110 "codegen.cln"
calein_nested_SPACEdefinition_SPACEcontext),value_add_reference(
#line 110 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 111 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 111 "codegen.cln"
value_make_string_from_c_string("};\n")),value_add_reference(
#line 111 "codegen.cln"
local_vars.calein_out)));
value_add_reference(result);
value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);value_remove_reference(local_vars.calein_ir);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(struct value *calein_proc_SPACEname, struct value *calein_out, struct value *calein_scope){
struct global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG_local_vars local_vars;
local_vars.calein_proc_SPACEname = calein_proc_SPACEname;
local_vars.calein_out = calein_out;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 115 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEtag_SPACEfor_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 115 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 115 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 116 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 116 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 116 "codegen.cln"
local_vars.calein_scope))) ? ((
#line 117 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 117 "codegen.cln"
value_make_string_from_c_string(" local_vars")),value_add_reference(
#line 117 "codegen.cln"
local_vars.calein_out)))) : ((
#line 119 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 119 "codegen.cln"
value_make_string_from_c_string(" *")),value_add_reference(
#line 119 "codegen.cln"
local_vars.calein_out)), 
#line 120 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 120 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 120 "codegen.cln"
local_vars.calein_out)), 
#line 121 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 121 "codegen.cln"
value_make_string_from_c_string("_local_vars")),value_add_reference(
#line 121 "codegen.cln"
local_vars.calein_out))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_proc_SPACEname);value_float_result(result);
return result;
}
struct value *calein_continue;
struct value *global_SCOPEcalein_compile_SPACEerror_ARG(struct value *calein_msg){
struct global_SCOPEcalein_compile_SPACEerror_ARG_local_vars local_vars;
local_vars.calein_msg = calein_msg;
struct value *tmp_for_derefs = 0;
struct value *result = (
#line 128 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 128 "codegen.cln"
value_make_string_from_c_string("compile error: "))), 
#line 129 "codegen.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 129 "codegen.cln"
local_vars.calein_msg)), 
#line 130 "codegen.cln"
(tmp_for_derefs = calein_continue, calein_continue = value_add_reference(
#line 130 "codegen.cln"
calein_false), value_remove_reference(tmp_for_derefs),calein_continue));
value_add_reference(result);
value_remove_reference(local_vars.calein_msg);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(struct value *calein_ir, struct value *calein_out, struct value *calein_context, struct value *calein_scope){
struct global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG_local_vars local_vars;
local_vars.calein_args = 0;
local_vars.calein_var_SPACEscope = 0;
local_vars.calein_sep = 0;
local_vars.calein_name = 0;
local_vars.calein_proc_SPACEname = 0;
local_vars.calein_function_SPACEinfo = 0;
local_vars.calein_record_SPACEname = 0;
local_vars.calein_i = 0;
local_vars.calein_field_SPACEcount = 0;
local_vars.calein_adjusted_SPACEproc_SPACEname = 0;
local_vars.calein_old_SPACEfunction_SPACElist = 0;
local_vars.calein_old_SPACEvariable_SPACElist = 0;
local_vars.calein_ident = 0;
local_vars.calein_vars = 0;
local_vars.calein_items = 0;
local_vars.calein_expected_SPACEsep = 0;
local_vars.calein_old_SPACElength = 0;
local_vars.calein_import_SPACEir = 0;
local_vars.calein_module_SPACElist = 0;
local_vars.calein_ir = calein_ir;
local_vars.calein_out = calein_out;
local_vars.calein_context = calein_context;
local_vars.calein_scope = calein_scope;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_args = value_add_reference(
#line 134 "codegen.cln"
calein_false)), (local_vars.calein_var_SPACEscope = value_add_reference(
#line 135 "codegen.cln"
calein_false)), (local_vars.calein_sep = value_add_reference(
#line 136 "codegen.cln"
calein_false)), (local_vars.calein_name = value_add_reference(
#line 137 "codegen.cln"
calein_false)), (local_vars.calein_proc_SPACEname = value_add_reference(
#line 138 "codegen.cln"
calein_false)), (value_boolean_is_true_remove_floating_reference(
#line 139 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEcall(value_add_reference(
#line 139 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 140 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(
#line 140 "codegen.cln"
local_vars.calein_context))) ? ((
#line 141 "codegen.cln"
global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 141 "codegen.cln"
global_SCOPEcalein_position_SPACEof_SPACEir_SPACEcall_ARG(value_add_reference(
#line 141 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 141 "codegen.cln"
local_vars.calein_out)), 
#line 142 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 142 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEir_SPACEcall_ARG(value_add_reference(
#line 142 "codegen.cln"
local_vars.calein_ir))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), 
#line 143 "codegen.cln"
(tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(
#line 143 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEcall_ARG(value_add_reference(
#line 143 "codegen.cln"
local_vars.calein_ir))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), 
#line 144 "codegen.cln"
(tmp_for_derefs = local_vars.calein_var_SPACEscope, local_vars.calein_var_SPACEscope = value_add_reference(
#line 144 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 144 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 144 "codegen.cln"
calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),local_vars.calein_var_SPACEscope), (value_boolean_is_true_remove_floating_reference(
#line 145 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 145 "codegen.cln"
local_vars.calein_args),value_add_reference(
#line 145 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 145 "codegen.cln"
local_vars.calein_var_SPACEscope))))) ? (((local_vars.calein_function_SPACEinfo = value_add_reference(
#line 146 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 146 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 146 "codegen.cln"
calein_function_SPACElist)))), (value_boolean_is_true_remove_floating_reference(
#line 147 "codegen.cln"
local_vars.calein_function_SPACEinfo) ? (
#line 148 "codegen.cln"
(tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(
#line 148 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 148 "codegen.cln"
local_vars.calein_function_SPACEinfo))), value_remove_reference(tmp_for_derefs),local_vars.calein_name)) : (
#line 149 "codegen.cln"
(tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(
#line 149 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 149 "codegen.cln"
calein_global_SPACEscope),value_add_reference(
#line 149 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 149 "codegen.cln"
value_make_string_from_c_string("_SCOPE")),value_add_reference(
#line 149 "codegen.cln"
local_vars.calein_name))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name))), 
#line 150 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 150 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 150 "codegen.cln"
local_vars.calein_out)), 
#line 151 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 151 "codegen.cln"
value_make_string_from_c_string("(")),value_add_reference(
#line 151 "codegen.cln"
local_vars.calein_out)), 
#line 152 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 152 "codegen.cln"
value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (value_boolean_is_true_remove_floating_reference(
#line 153 "codegen.cln"
local_vars.calein_function_SPACEinfo) ? ((value_boolean_is_true_remove_floating_reference(
#line 153 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 153 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 153 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 153 "codegen.cln"
local_vars.calein_function_SPACEinfo))),value_add_reference(
#line 153 "codegen.cln"
calein_global_SPACEscope))))) ? ((
#line 154 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 154 "codegen.cln"
value_make_string_from_c_string("&local_vars")),value_add_reference(
#line 154 "codegen.cln"
local_vars.calein_out)), 
#line 155 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 155 "codegen.cln"
value_make_string_from_c_string(",")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep))) : (
#line 156 "codegen.cln"
calein_false))) : (
#line 156 "codegen.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 157 "codegen.cln"
local_vars.calein_args)) {

#line 158 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 158 "codegen.cln"
local_vars.calein_sep),value_add_reference(
#line 158 "codegen.cln"
local_vars.calein_out));

#line 159 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 159 "codegen.cln"
value_make_string_from_c_string("value_add_reference(")),value_add_reference(
#line 159 "codegen.cln"
local_vars.calein_out));

#line 160 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 160 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 160 "codegen.cln"
local_vars.calein_args))),value_add_reference(
#line 160 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 160 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 160 "codegen.cln"
local_vars.calein_scope));

#line 161 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 161 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 161 "codegen.cln"
local_vars.calein_out));

#line 162 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 162 "codegen.cln"
value_make_string_from_c_string(",")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep);

#line 163 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 163 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 163 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), 
#line 165 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 165 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 165 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 166 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 166 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 166 "codegen.cln"
calein_statement_SPACEcontext))) ? (
#line 167 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 167 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 167 "codegen.cln"
local_vars.calein_out))) : (
#line 168 "codegen.cln"
calein_false)))) : ((
#line 170 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 170 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 170 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 170 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 170 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 171 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 171 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 171 "codegen.cln"
calein_statement_SPACEcontext))) ? (
#line 172 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 172 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 172 "codegen.cln"
local_vars.calein_out))) : (
#line 173 "codegen.cln"
calein_false))))))) : (
#line 175 "codegen.cln"
calein_false)))) : ((value_boolean_is_true_remove_floating_reference(
#line 176 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACErecord(value_add_reference(
#line 176 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 177 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 177 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 177 "codegen.cln"
calein_global_SPACEscope))) ? (((value_boolean_is_true_remove_floating_reference(
#line 178 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 178 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 178 "codegen.cln"
calein_declaration_SPACEcontext))) ? (((local_vars.calein_record_SPACEname = value_add_reference(
#line 179 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 179 "codegen.cln"
global_SCOPEcalein_definition_SPACEof_SPACEir_SPACErecord_ARG(value_add_reference(
#line 179 "codegen.cln"
local_vars.calein_ir)))))), 
#line 180 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 180 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 180 "codegen.cln"
local_vars.calein_out)), 
#line 181 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 181 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 181 "codegen.cln"
local_vars.calein_out)), 
#line 182 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 182 "codegen.cln"
value_make_string_from_c_string("_SCOPE")),value_add_reference(
#line 182 "codegen.cln"
local_vars.calein_out)), 
#line 183 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 183 "codegen.cln"
local_vars.calein_record_SPACEname),value_add_reference(
#line 183 "codegen.cln"
local_vars.calein_out)), 
#line 184 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 184 "codegen.cln"
value_make_string_from_c_string("(")),value_add_reference(
#line 184 "codegen.cln"
local_vars.calein_out)), 
#line 185 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 185 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 185 "codegen.cln"
global_SCOPEcalein_definition_SPACEof_SPACEir_SPACErecord_ARG(value_add_reference(
#line 185 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), 
#line 186 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 186 "codegen.cln"
value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (local_vars.calein_i = value_add_reference(
#line 187 "codegen.cln"
value_make_number(0))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 188 "codegen.cln"
local_vars.calein_args)) {

#line 189 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 189 "codegen.cln"
local_vars.calein_sep),value_add_reference(
#line 189 "codegen.cln"
local_vars.calein_out));

#line 190 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 190 "codegen.cln"
value_make_string_from_c_string("struct value *arg")),value_add_reference(
#line 190 "codegen.cln"
local_vars.calein_out));

#line 191 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 191 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 191 "codegen.cln"
local_vars.calein_i))),value_add_reference(
#line 191 "codegen.cln"
local_vars.calein_out));

#line 192 "codegen.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 192 "codegen.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 192 "codegen.cln"
local_vars.calein_i),value_add_reference(
#line 192 "codegen.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

#line 193 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 193 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 193 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

#line 194 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 194 "codegen.cln"
value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep);

}
 0; }), (local_vars.calein_field_SPACEcount = value_add_reference(
#line 196 "codegen.cln"
local_vars.calein_i)), 
#line 197 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 197 "codegen.cln"
value_make_string_from_c_string(") {\n")),value_add_reference(
#line 197 "codegen.cln"
local_vars.calein_out)), 
#line 198 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 198 "codegen.cln"
value_make_string_from_c_string("struct value *result = value_make_record(")),value_add_reference(
#line 198 "codegen.cln"
local_vars.calein_out)), 
#line 199 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 199 "codegen.cln"
global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(
#line 199 "codegen.cln"
local_vars.calein_record_SPACEname))),value_add_reference(
#line 199 "codegen.cln"
local_vars.calein_out)), 
#line 200 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 200 "codegen.cln"
value_make_string_from_c_string(", ")),value_add_reference(
#line 200 "codegen.cln"
local_vars.calein_out)), 
#line 201 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 201 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 201 "codegen.cln"
local_vars.calein_field_SPACEcount))),value_add_reference(
#line 201 "codegen.cln"
local_vars.calein_out)), 
#line 202 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 202 "codegen.cln"
value_make_string_from_c_string(");\n")),value_add_reference(
#line 202 "codegen.cln"
local_vars.calein_out)), 
#line 203 "codegen.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 203 "codegen.cln"
value_make_number(0)), value_remove_reference(tmp_for_derefs),local_vars.calein_i), ({ while (value_boolean_is_true_remove_floating_reference(
#line 204 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 204 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 204 "codegen.cln"
local_vars.calein_i),value_add_reference(
#line 204 "codegen.cln"
local_vars.calein_field_SPACEcount)))))) {

#line 205 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 205 "codegen.cln"
value_make_string_from_c_string("result->u.record.fields[")),value_add_reference(
#line 205 "codegen.cln"
local_vars.calein_out));

#line 206 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 206 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 206 "codegen.cln"
local_vars.calein_i))),value_add_reference(
#line 206 "codegen.cln"
local_vars.calein_out));

#line 207 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 207 "codegen.cln"
value_make_string_from_c_string("] = arg")),value_add_reference(
#line 207 "codegen.cln"
local_vars.calein_out));

#line 208 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 208 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 208 "codegen.cln"
local_vars.calein_i))),value_add_reference(
#line 208 "codegen.cln"
local_vars.calein_out));

#line 209 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 209 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 209 "codegen.cln"
local_vars.calein_out));

#line 210 "codegen.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 210 "codegen.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 210 "codegen.cln"
local_vars.calein_i),value_add_reference(
#line 210 "codegen.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }), 
#line 212 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 212 "codegen.cln"
value_make_string_from_c_string("return result;\n}\n")),value_add_reference(
#line 212 "codegen.cln"
local_vars.calein_out)), 
#line 214 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 214 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 214 "codegen.cln"
global_SCOPEcalein_predicate_SPACEof_SPACEir_SPACErecord_ARG(value_add_reference(
#line 214 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname), 
#line 215 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 215 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 215 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 215 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 215 "codegen.cln"
value_make_string_from_c_string("_SCOPE")),value_add_reference(
#line 215 "codegen.cln"
local_vars.calein_proc_SPACEname))))), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname), 
#line 216 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 216 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 216 "codegen.cln"
local_vars.calein_out)), 
#line 217 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 217 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 217 "codegen.cln"
local_vars.calein_out)), 
#line 218 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 218 "codegen.cln"
value_make_string_from_c_string("(struct value *v) {\n")),value_add_reference(
#line 218 "codegen.cln"
local_vars.calein_out)), 
#line 219 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 219 "codegen.cln"
value_make_string_from_c_string("struct value *result = value_make_boolean(v->kind == value_kind_record && !strcmp(v->u.record.type, ")),value_add_reference(
#line 219 "codegen.cln"
local_vars.calein_out)), 
#line 220 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 220 "codegen.cln"
global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(
#line 220 "codegen.cln"
local_vars.calein_record_SPACEname))),value_add_reference(
#line 220 "codegen.cln"
local_vars.calein_out)), 
#line 221 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 221 "codegen.cln"
value_make_string_from_c_string("));\n")),value_add_reference(
#line 221 "codegen.cln"
local_vars.calein_out)), 
#line 222 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 222 "codegen.cln"
value_make_string_from_c_string("value_remove_reference(v);\nreturn result;\n}")),value_add_reference(
#line 222 "codegen.cln"
local_vars.calein_out)), 
#line 224 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 224 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 224 "codegen.cln"
global_SCOPEcalein_definition_SPACEof_SPACEir_SPACErecord_ARG(value_add_reference(
#line 224 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), 
#line 225 "codegen.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 225 "codegen.cln"
value_make_number(0)), value_remove_reference(tmp_for_derefs),local_vars.calein_i), ({ while (value_boolean_is_true_remove_floating_reference(
#line 226 "codegen.cln"
local_vars.calein_args)) {

#line 227 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 227 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 227 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 227 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 227 "codegen.cln"
local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname);

#line 228 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 228 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 228 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 228 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 228 "codegen.cln"
value_make_string_from_c_string("_SCOPE")),value_add_reference(
#line 228 "codegen.cln"
local_vars.calein_proc_SPACEname))))), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname);

#line 229 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 229 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 229 "codegen.cln"
local_vars.calein_out));

#line 230 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 230 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 230 "codegen.cln"
local_vars.calein_out));

#line 231 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 231 "codegen.cln"
value_make_string_from_c_string("_ARG(struct value *record) {\n")),value_add_reference(
#line 231 "codegen.cln"
local_vars.calein_out));

#line 232 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 232 "codegen.cln"
value_make_string_from_c_string("struct value *result = value_record_field(record, ")),value_add_reference(
#line 232 "codegen.cln"
local_vars.calein_out));

#line 233 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 233 "codegen.cln"
global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(
#line 233 "codegen.cln"
local_vars.calein_record_SPACEname))),value_add_reference(
#line 233 "codegen.cln"
local_vars.calein_out));

#line 234 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 234 "codegen.cln"
value_make_string_from_c_string(", ")),value_add_reference(
#line 234 "codegen.cln"
local_vars.calein_out));

#line 235 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 235 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 235 "codegen.cln"
local_vars.calein_i))),value_add_reference(
#line 235 "codegen.cln"
local_vars.calein_out));

#line 236 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 236 "codegen.cln"
value_make_string_from_c_string(");\n")),value_add_reference(
#line 236 "codegen.cln"
local_vars.calein_out));

#line 237 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 237 "codegen.cln"
value_make_string_from_c_string("value_remove_reference(record);\nreturn result;\n}")),value_add_reference(
#line 237 "codegen.cln"
local_vars.calein_out));

#line 238 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 238 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 238 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

#line 239 "codegen.cln"
(tmp_for_derefs = local_vars.calein_i, local_vars.calein_i = value_add_reference(
#line 239 "codegen.cln"
global_SCOPEcalein__SPACE_ARG_PLUS_ARG(value_add_reference(
#line 239 "codegen.cln"
local_vars.calein_i),value_add_reference(
#line 239 "codegen.cln"
value_make_number(1)))), value_remove_reference(tmp_for_derefs),local_vars.calein_i);

}
 0; }))) : (
#line 241 "codegen.cln"
calein_false)))) : (
#line 242 "codegen.cln"
global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(
#line 242 "codegen.cln"
value_make_string_from_c_string("Can only declare records at the top level."))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 243 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEprocedure(value_add_reference(
#line 243 "codegen.cln"
local_vars.calein_ir))) ? ((
#line 244 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 244 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 244 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 244 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname), (local_vars.calein_adjusted_SPACEproc_SPACEname = value_add_reference(
#line 245 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 245 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 245 "codegen.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 245 "codegen.cln"
value_make_string_from_c_string("_SCOPE")),value_add_reference(
#line 245 "codegen.cln"
local_vars.calein_proc_SPACEname)))))), 
#line 246 "codegen.cln"
(tmp_for_derefs = calein_function_SPACElist, calein_function_SPACElist = value_add_reference(
#line 246 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 246 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 246 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 246 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 246 "codegen.cln"
local_vars.calein_adjusted_SPACEproc_SPACEname),value_add_reference(
#line 246 "codegen.cln"
local_vars.calein_scope))))),value_add_reference(
#line 246 "codegen.cln"
calein_function_SPACElist))), value_remove_reference(tmp_for_derefs),calein_function_SPACElist), 
#line 247 "codegen.cln"
(tmp_for_derefs = local_vars.calein_proc_SPACEname, local_vars.calein_proc_SPACEname = value_add_reference(
#line 247 "codegen.cln"
local_vars.calein_adjusted_SPACEproc_SPACEname), value_remove_reference(tmp_for_derefs),local_vars.calein_proc_SPACEname), (local_vars.calein_old_SPACEfunction_SPACElist = value_add_reference(
#line 248 "codegen.cln"
calein_function_SPACElist)), (local_vars.calein_old_SPACEvariable_SPACElist = value_add_reference(
#line 249 "codegen.cln"
calein_variable_SPACElist)), (value_boolean_is_true_remove_floating_reference(
#line 251 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_SPACE_SPACE_ARGor_ARG(value_add_reference(
#line 250 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 250 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 250 "codegen.cln"
calein_definition_SPACEcontext))),value_add_reference(
#line 250 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 250 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 250 "codegen.cln"
calein_procedure_SPACEdefinition_SPACEcontext))),value_add_reference(
#line 251 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 251 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 251 "codegen.cln"
calein_declaration_SPACEcontext))))) ? (((value_boolean_is_true_remove_floating_reference(
#line 252 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 252 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 252 "codegen.cln"
calein_declaration_SPACEcontext))) ? ((
#line 253 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEfor_SPACEprocedure_SPACE_SPACE_ARGnamed_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 253 "codegen.cln"
local_vars.calein_ir),value_add_reference(
#line 253 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 253 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 253 "codegen.cln"
local_vars.calein_scope)), 
#line 254 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 254 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 254 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 254 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 254 "codegen.cln"
calein_declaration_SPACEcontext),value_add_reference(
#line 254 "codegen.cln"
local_vars.calein_proc_SPACEname)))) : ((
#line 256 "codegen.cln"
(tmp_for_derefs = calein_variable_SPACElist, calein_variable_SPACElist = value_add_reference(
#line 256 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 256 "codegen.cln"
local_vars.calein_adjusted_SPACEproc_SPACEname),value_add_reference(
#line 256 "codegen.cln"
calein_function_SPACEvariable_SPACElist))), value_remove_reference(tmp_for_derefs),calein_variable_SPACElist), 
#line 257 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 257 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 257 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 257 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 257 "codegen.cln"
calein_procedure_SPACEdefinition_SPACEcontext),value_add_reference(
#line 257 "codegen.cln"
local_vars.calein_proc_SPACEname))))), 
#line 259 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 259 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 259 "codegen.cln"
local_vars.calein_out)), 
#line 260 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 260 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 260 "codegen.cln"
local_vars.calein_out)), 
#line 261 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 261 "codegen.cln"
value_make_string_from_c_string("(")),value_add_reference(
#line 261 "codegen.cln"
local_vars.calein_out)), 
#line 262 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 262 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 262 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 262 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), 
#line 263 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 263 "codegen.cln"
value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), (local_vars.calein_ident = value_add_reference(
#line 264 "codegen.cln"
calein_false)), (value_boolean_is_true_remove_floating_reference(
#line 265 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 265 "codegen.cln"
local_vars.calein_args),value_add_reference(
#line 265 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 265 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 265 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 265 "codegen.cln"
calein_global_SPACEscope))))))) ? (((value_boolean_is_true_remove_floating_reference(
#line 266 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 266 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 266 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 266 "codegen.cln"
calein_global_SPACEscope))))) ? ((
#line 267 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 267 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 267 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 267 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 268 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 268 "codegen.cln"
value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep))) : (
#line 269 "codegen.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 270 "codegen.cln"
local_vars.calein_args)) {

#line 271 "codegen.cln"
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(
#line 271 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 271 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 271 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 271 "codegen.cln"
local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);

#line 272 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 272 "codegen.cln"
local_vars.calein_sep),value_add_reference(
#line 272 "codegen.cln"
local_vars.calein_out));

#line 273 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 273 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 273 "codegen.cln"
local_vars.calein_out));

#line 274 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 274 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 274 "codegen.cln"
local_vars.calein_out));

#line 275 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 275 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 275 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

#line 276 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 276 "codegen.cln"
value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_sep);

}
 0; }))) : (
#line 278 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 278 "codegen.cln"
value_make_string_from_c_string("void")),value_add_reference(
#line 278 "codegen.cln"
local_vars.calein_out)))), 
#line 279 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 279 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 279 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 280 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 280 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 280 "codegen.cln"
calein_declaration_SPACEcontext))) ? ((
#line 281 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 281 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 281 "codegen.cln"
local_vars.calein_out)))) : ((
#line 283 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 283 "codegen.cln"
value_make_string_from_c_string("{\n")),value_add_reference(
#line 283 "codegen.cln"
local_vars.calein_out)), 
#line 284 "codegen.cln"
global_SCOPEcalein_emit_SPACElocals_SPACEstruct_SPACEdeclaration_SPACEfor_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 284 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 284 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 284 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 285 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 285 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 285 "codegen.cln"
local_vars.calein_out)), 
#line 287 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 287 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 287 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 287 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 287 "codegen.cln"
calein_initializer_SPACEcontext),value_add_reference(
#line 287 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 288 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 288 "codegen.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 288 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 288 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_args), (value_boolean_is_true_remove_floating_reference(
#line 289 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 289 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 289 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 289 "codegen.cln"
calein_global_SPACEscope))))) ? ((
#line 290 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 290 "codegen.cln"
value_make_string_from_c_string("local_vars.")),value_add_reference(
#line 290 "codegen.cln"
local_vars.calein_out)), 
#line 291 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 291 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 291 "codegen.cln"
local_vars.calein_out)), 
#line 292 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 292 "codegen.cln"
value_make_string_from_c_string("_local_vars = ")),value_add_reference(
#line 292 "codegen.cln"
local_vars.calein_out)), 
#line 293 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 293 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 293 "codegen.cln"
local_vars.calein_out)), 
#line 294 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 294 "codegen.cln"
value_make_string_from_c_string("_local_vars;\n")),value_add_reference(
#line 294 "codegen.cln"
local_vars.calein_out)))) : (
#line 295 "codegen.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 296 "codegen.cln"
local_vars.calein_args)) {

#line 297 "codegen.cln"
(tmp_for_derefs = local_vars.calein_ident, local_vars.calein_ident = value_add_reference(
#line 297 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 297 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 297 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 297 "codegen.cln"
local_vars.calein_args))))))), value_remove_reference(tmp_for_derefs),local_vars.calein_ident);

#line 298 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 298 "codegen.cln"
value_make_string_from_c_string("local_vars.")),value_add_reference(
#line 298 "codegen.cln"
local_vars.calein_out));

#line 299 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 299 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 299 "codegen.cln"
local_vars.calein_out));

#line 300 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 300 "codegen.cln"
value_make_string_from_c_string(" = ")),value_add_reference(
#line 300 "codegen.cln"
local_vars.calein_out));

#line 301 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 301 "codegen.cln"
local_vars.calein_ident),value_add_reference(
#line 301 "codegen.cln"
local_vars.calein_out));

#line 302 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 302 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 302 "codegen.cln"
local_vars.calein_out));

#line 303 "codegen.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 303 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 303 "codegen.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), 
#line 306 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 306 "codegen.cln"
value_make_string_from_c_string("struct value *tmp_for_derefs = 0;\n")),value_add_reference(
#line 306 "codegen.cln"
local_vars.calein_out)), 
#line 307 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 307 "codegen.cln"
value_make_string_from_c_string("struct value *result = ")),value_add_reference(
#line 307 "codegen.cln"
local_vars.calein_out)), 
#line 308 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 308 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEprocedure_ARG(value_add_reference(
#line 308 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 308 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 308 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 308 "codegen.cln"
local_vars.calein_proc_SPACEname)), 
#line 309 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 309 "codegen.cln"
value_make_string_from_c_string(";\nvalue_add_reference(result);\n")),value_add_reference(
#line 309 "codegen.cln"
local_vars.calein_out)), (local_vars.calein_vars = value_add_reference(
#line 310 "codegen.cln"
calein_variable_SPACElist)), 
#line 311 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 311 "codegen.cln"
value_make_string_from_c_string("//"))), 
#line 312 "codegen.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 312 "codegen.cln"
local_vars.calein_proc_SPACEname)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 313 "codegen.cln"
local_vars.calein_vars)) {

#line 314 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 314 "codegen.cln"
value_make_string_from_c_string("//	")));

#line 315 "codegen.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 315 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 315 "codegen.cln"
local_vars.calein_vars))));
if (value_boolean_is_true_remove_floating_reference(
#line 316 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 316 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 316 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 316 "codegen.cln"
local_vars.calein_vars))))),value_add_reference(
#line 316 "codegen.cln"
local_vars.calein_proc_SPACEname)))) {

#line 317 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 317 "codegen.cln"
value_make_string_from_c_string("value_remove_reference(")),value_add_reference(
#line 317 "codegen.cln"
local_vars.calein_out));

#line 319 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 318 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 318 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 318 "codegen.cln"
local_vars.calein_vars))))),value_add_reference(
#line 319 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 319 "codegen.cln"
local_vars.calein_proc_SPACEname),value_add_reference(
#line 319 "codegen.cln"
local_vars.calein_out));

#line 320 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 320 "codegen.cln"
value_make_string_from_c_string(");")),value_add_reference(
#line 320 "codegen.cln"
local_vars.calein_out));

#line 321 "codegen.cln"
(tmp_for_derefs = local_vars.calein_vars, local_vars.calein_vars = value_add_reference(
#line 321 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 321 "codegen.cln"
local_vars.calein_vars))), value_remove_reference(tmp_for_derefs),local_vars.calein_vars);

} else {

#line 322 "codegen.cln"
(tmp_for_derefs = local_vars.calein_vars, local_vars.calein_vars = value_add_reference(
#line 322 "codegen.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_vars);
}
}
 0; }), 
#line 324 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 324 "codegen.cln"
value_make_string_from_c_string("value_float_result(result);\n")),value_add_reference(
#line 324 "codegen.cln"
local_vars.calein_out)), 
#line 325 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 325 "codegen.cln"
value_make_string_from_c_string("return result;\n}\n")),value_add_reference(
#line 325 "codegen.cln"
local_vars.calein_out))))), (value_boolean_is_true_remove_floating_reference(
#line 327 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 327 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 327 "codegen.cln"
calein_declaration_SPACEcontext))) ? (
#line 329 "codegen.cln"
(tmp_for_derefs = calein_function_SPACEvariable_SPACElist, calein_function_SPACEvariable_SPACElist = value_add_reference(
#line 329 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 329 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 329 "codegen.cln"
local_vars.calein_adjusted_SPACEproc_SPACEname),value_add_reference(
#line 329 "codegen.cln"
calein_variable_SPACElist))),value_add_reference(
#line 329 "codegen.cln"
calein_function_SPACEvariable_SPACElist))), value_remove_reference(tmp_for_derefs),calein_function_SPACEvariable_SPACElist)) : (
#line 330 "codegen.cln"
calein_false)))) : (
#line 331 "codegen.cln"
calein_false)), 
#line 332 "codegen.cln"
(tmp_for_derefs = calein_variable_SPACElist, calein_variable_SPACElist = value_add_reference(
#line 332 "codegen.cln"
local_vars.calein_old_SPACEvariable_SPACElist), value_remove_reference(tmp_for_derefs),calein_variable_SPACElist), 
#line 333 "codegen.cln"
(tmp_for_derefs = calein_function_SPACElist, calein_function_SPACElist = value_add_reference(
#line 333 "codegen.cln"
local_vars.calein_old_SPACEfunction_SPACElist), value_remove_reference(tmp_for_derefs),calein_function_SPACElist))) : ((value_boolean_is_true_remove_floating_reference(
#line 334 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEsequence(value_add_reference(
#line 334 "codegen.cln"
local_vars.calein_ir))) ? (((local_vars.calein_items = value_add_reference(
#line 336 "codegen.cln"
global_SCOPEcalein_items_SPACEof_SPACEir_SPACEsequence_ARG(value_add_reference(
#line 336 "codegen.cln"
local_vars.calein_ir)))), (local_vars.calein_expected_SPACEsep = value_add_reference(
#line 337 "codegen.cln"
value_make_string_from_c_string(""))), (local_vars.calein_old_SPACElength = value_add_reference(
#line 338 "codegen.cln"
calein_false)), (value_boolean_is_true_remove_floating_reference(
#line 339 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 339 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 339 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 340 "codegen.cln"
(tmp_for_derefs = local_vars.calein_expected_SPACEsep, local_vars.calein_expected_SPACEsep = value_add_reference(
#line 340 "codegen.cln"
value_make_string_from_c_string(", ")), value_remove_reference(tmp_for_derefs),local_vars.calein_expected_SPACEsep), 
#line 341 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 341 "codegen.cln"
value_make_string_from_c_string("(")),value_add_reference(
#line 341 "codegen.cln"
local_vars.calein_out)))) : (
#line 342 "codegen.cln"
calein_false)), 
#line 343 "codegen.cln"
(tmp_for_derefs = local_vars.calein_sep, local_vars.calein_sep = value_add_reference(
#line 343 "codegen.cln"
local_vars.calein_expected_SPACEsep), value_remove_reference(tmp_for_derefs),local_vars.calein_sep), 
#line 344 "codegen.cln"
(tmp_for_derefs = local_vars.calein_old_SPACElength, local_vars.calein_old_SPACElength = value_add_reference(
#line 344 "codegen.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 344 "codegen.cln"
local_vars.calein_out))), value_remove_reference(tmp_for_derefs),local_vars.calein_old_SPACElength), ({ while (value_boolean_is_true_remove_floating_reference(
#line 345 "codegen.cln"
local_vars.calein_items)) {
if (value_boolean_is_true_remove_floating_reference(
#line 346 "codegen.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 346 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 346 "codegen.cln"
local_vars.calein_old_SPACElength),value_add_reference(
#line 346 "codegen.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 346 "codegen.cln"
local_vars.calein_out)))))))) {

#line 347 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 347 "codegen.cln"
local_vars.calein_sep),value_add_reference(
#line 347 "codegen.cln"
local_vars.calein_out));

} else {

#line 348 "codegen.cln"
calein_false;
}
#line 349 "codegen.cln"
(tmp_for_derefs = local_vars.calein_old_SPACElength, local_vars.calein_old_SPACElength = value_add_reference(
#line 349 "codegen.cln"
global_SCOPEcalein_length_ARG(value_add_reference(
#line 349 "codegen.cln"
local_vars.calein_out))), value_remove_reference(tmp_for_derefs),local_vars.calein_old_SPACElength);

#line 350 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 350 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 350 "codegen.cln"
local_vars.calein_items))),value_add_reference(
#line 350 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 350 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 350 "codegen.cln"
local_vars.calein_scope));

#line 351 "codegen.cln"
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(
#line 351 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 351 "codegen.cln"
local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }), (value_boolean_is_true_remove_floating_reference(
#line 353 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 353 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 353 "codegen.cln"
calein_expression_SPACEcontext))) ? (
#line 354 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 354 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 354 "codegen.cln"
local_vars.calein_out))) : (
#line 355 "codegen.cln"
calein_false)))) : ((value_boolean_is_true_remove_floating_reference(
#line 356 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEif(value_add_reference(
#line 356 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 357 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 357 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 357 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 358 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 358 "codegen.cln"
value_make_string_from_c_string("(value_boolean_is_true_remove_floating_reference(")),value_add_reference(
#line 358 "codegen.cln"
local_vars.calein_out)), 
#line 359 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 359 "codegen.cln"
global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 359 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 359 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 359 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 359 "codegen.cln"
local_vars.calein_scope)), 
#line 360 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 360 "codegen.cln"
value_make_string_from_c_string(") ? (")),value_add_reference(
#line 360 "codegen.cln"
local_vars.calein_out)), 
#line 361 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 361 "codegen.cln"
global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 361 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 361 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 361 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 361 "codegen.cln"
local_vars.calein_scope)), 
#line 362 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 362 "codegen.cln"
value_make_string_from_c_string(") : (")),value_add_reference(
#line 362 "codegen.cln"
local_vars.calein_out)), 
#line 363 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 363 "codegen.cln"
global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 363 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 363 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 363 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 363 "codegen.cln"
local_vars.calein_scope)), 
#line 364 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 364 "codegen.cln"
value_make_string_from_c_string("))")),value_add_reference(
#line 364 "codegen.cln"
local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(
#line 365 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 365 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 365 "codegen.cln"
calein_statement_SPACEcontext))) ? ((
#line 366 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 366 "codegen.cln"
value_make_string_from_c_string("if (value_boolean_is_true_remove_floating_reference(")),value_add_reference(
#line 366 "codegen.cln"
local_vars.calein_out)), 
#line 367 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 367 "codegen.cln"
global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 367 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 367 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 367 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 367 "codegen.cln"
local_vars.calein_scope)), 
#line 368 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 368 "codegen.cln"
value_make_string_from_c_string(")) {\n")),value_add_reference(
#line 368 "codegen.cln"
local_vars.calein_out)), 
#line 369 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 369 "codegen.cln"
global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 369 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 369 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 369 "codegen.cln"
calein_statement_SPACEcontext),value_add_reference(
#line 369 "codegen.cln"
local_vars.calein_scope)), 
#line 370 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 370 "codegen.cln"
value_make_string_from_c_string(";\n} else {\n")),value_add_reference(
#line 370 "codegen.cln"
local_vars.calein_out)), 
#line 371 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 371 "codegen.cln"
global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 371 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 371 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 371 "codegen.cln"
calein_statement_SPACEcontext),value_add_reference(
#line 371 "codegen.cln"
local_vars.calein_scope)), 
#line 372 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 372 "codegen.cln"
value_make_string_from_c_string(";\n}")),value_add_reference(
#line 372 "codegen.cln"
local_vars.calein_out)))) : ((
#line 374 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 374 "codegen.cln"
global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 374 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 374 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 374 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 374 "codegen.cln"
local_vars.calein_scope)), 
#line 375 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 375 "codegen.cln"
global_SCOPEcalein_then_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 375 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 375 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 375 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 375 "codegen.cln"
local_vars.calein_scope)), 
#line 376 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 376 "codegen.cln"
global_SCOPEcalein_else_SPACEof_SPACEir_SPACEif_ARG(value_add_reference(
#line 376 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 376 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 376 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 376 "codegen.cln"
local_vars.calein_scope))))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 378 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEwhile(value_add_reference(
#line 378 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 379 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 379 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 379 "codegen.cln"
calein_statement_SPACEcontext))) ? ((
#line 380 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 380 "codegen.cln"
value_make_string_from_c_string("while (value_boolean_is_true_remove_floating_reference(")),value_add_reference(
#line 380 "codegen.cln"
local_vars.calein_out)), 
#line 381 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 381 "codegen.cln"
global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(
#line 381 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 381 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 381 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 381 "codegen.cln"
local_vars.calein_scope)), 
#line 382 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 382 "codegen.cln"
value_make_string_from_c_string(")) {\n")),value_add_reference(
#line 382 "codegen.cln"
local_vars.calein_out)), 
#line 383 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 383 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(
#line 383 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 383 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 383 "codegen.cln"
calein_statement_SPACEcontext),value_add_reference(
#line 383 "codegen.cln"
local_vars.calein_scope)), 
#line 384 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 384 "codegen.cln"
value_make_string_from_c_string("\n}\n")),value_add_reference(
#line 384 "codegen.cln"
local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(
#line 385 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 385 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 385 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 386 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 386 "codegen.cln"
value_make_string_from_c_string("({ ")),value_add_reference(
#line 386 "codegen.cln"
local_vars.calein_out)), 
#line 387 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 387 "codegen.cln"
local_vars.calein_ir),value_add_reference(
#line 387 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 387 "codegen.cln"
calein_statement_SPACEcontext),value_add_reference(
#line 387 "codegen.cln"
local_vars.calein_scope)), 
#line 388 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 388 "codegen.cln"
value_make_string_from_c_string(" 0; })")),value_add_reference(
#line 388 "codegen.cln"
local_vars.calein_out)))) : ((
#line 390 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 390 "codegen.cln"
global_SCOPEcalein_condition_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(
#line 390 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 390 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 390 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 390 "codegen.cln"
local_vars.calein_scope)), 
#line 391 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 391 "codegen.cln"
global_SCOPEcalein_body_SPACEof_SPACEir_SPACEwhile_ARG(value_add_reference(
#line 391 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 391 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 391 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 391 "codegen.cln"
local_vars.calein_scope))))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 393 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEvariable(value_add_reference(
#line 393 "codegen.cln"
local_vars.calein_ir))) ? ((
#line 395 "codegen.cln"
(tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(
#line 395 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 395 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 395 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), 
#line 396 "codegen.cln"
global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(value_add_reference(
#line 396 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 396 "codegen.cln"
local_vars.calein_scope)), (value_boolean_is_true_remove_floating_reference(
#line 397 "codegen.cln"
global_SCOPEcalein__SPACE_ARGor_ARG(value_add_reference(
#line 397 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 397 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 397 "codegen.cln"
calein_definition_SPACEcontext))),value_add_reference(
#line 397 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 397 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 397 "codegen.cln"
calein_nested_SPACEdefinition_SPACEcontext))))) ? ((
#line 398 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 398 "codegen.cln"
value_make_string_from_c_string("struct value *")),value_add_reference(
#line 398 "codegen.cln"
local_vars.calein_out)), 
#line 399 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 399 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 399 "codegen.cln"
local_vars.calein_out)), 
#line 400 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 400 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 400 "codegen.cln"
local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(
#line 401 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 401 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 401 "codegen.cln"
calein_statement_SPACEcontext))) ? ((
#line 403 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 402 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 402 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 402 "codegen.cln"
local_vars.calein_ir))))),value_add_reference(
#line 403 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 403 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 403 "codegen.cln"
local_vars.calein_out)), 
#line 404 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 404 "codegen.cln"
value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(
#line 404 "codegen.cln"
local_vars.calein_out)), 
#line 405 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 405 "codegen.cln"
global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 405 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 405 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 405 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 405 "codegen.cln"
local_vars.calein_scope)), 
#line 406 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 406 "codegen.cln"
value_make_string_from_c_string(");\n")),value_add_reference(
#line 406 "codegen.cln"
local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(
#line 407 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 407 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 407 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 408 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 408 "codegen.cln"
value_make_string_from_c_string("(")),value_add_reference(
#line 408 "codegen.cln"
local_vars.calein_out)), 
#line 410 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 409 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 409 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 409 "codegen.cln"
local_vars.calein_ir))))),value_add_reference(
#line 410 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 410 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 410 "codegen.cln"
local_vars.calein_out)), 
#line 411 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 411 "codegen.cln"
value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(
#line 411 "codegen.cln"
local_vars.calein_out)), 
#line 412 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 412 "codegen.cln"
global_SCOPEcalein_initial_SPACEvalue_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 412 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 412 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 412 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 412 "codegen.cln"
local_vars.calein_scope)), 
#line 413 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 413 "codegen.cln"
value_make_string_from_c_string("))")),value_add_reference(
#line 413 "codegen.cln"
local_vars.calein_out)))) : ((value_boolean_is_true_remove_floating_reference(
#line 414 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 414 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 414 "codegen.cln"
calein_initializer_SPACEcontext))) ? ((
#line 416 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 415 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 415 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEvariable_ARG(value_add_reference(
#line 415 "codegen.cln"
local_vars.calein_ir))))),value_add_reference(
#line 416 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 416 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 416 "codegen.cln"
local_vars.calein_out)), 
#line 417 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 417 "codegen.cln"
value_make_string_from_c_string(" = 0;\n")),value_add_reference(
#line 417 "codegen.cln"
local_vars.calein_out)))) : (
#line 418 "codegen.cln"
calein_false)))))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 419 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEassignment(value_add_reference(
#line 419 "codegen.cln"
local_vars.calein_ir))) ? ((
#line 420 "codegen.cln"
(tmp_for_derefs = local_vars.calein_name, local_vars.calein_name = value_add_reference(
#line 420 "codegen.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 420 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(
#line 420 "codegen.cln"
local_vars.calein_ir))))), value_remove_reference(tmp_for_derefs),local_vars.calein_name), 
#line 421 "codegen.cln"
(tmp_for_derefs = local_vars.calein_var_SPACEscope, local_vars.calein_var_SPACEscope = value_add_reference(
#line 421 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 421 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 421 "codegen.cln"
calein_variable_SPACElist))), value_remove_reference(tmp_for_derefs),local_vars.calein_var_SPACEscope), (value_boolean_is_true_remove_floating_reference(
#line 422 "codegen.cln"
local_vars.calein_var_SPACEscope) ? (((value_boolean_is_true_remove_floating_reference(
#line 423 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEevaluation(value_add_reference(
#line 423 "codegen.cln"
local_vars.calein_context))) ? ((
#line 424 "codegen.cln"
global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 424 "codegen.cln"
global_SCOPEcalein_position_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(
#line 424 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 424 "codegen.cln"
local_vars.calein_out)), 
#line 425 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 425 "codegen.cln"
value_make_string_from_c_string("(tmp_for_derefs = ")),value_add_reference(
#line 425 "codegen.cln"
local_vars.calein_out)), 
#line 427 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 426 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 427 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 427 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 427 "codegen.cln"
local_vars.calein_out)), 
#line 428 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 428 "codegen.cln"
value_make_string_from_c_string(", ")),value_add_reference(
#line 428 "codegen.cln"
local_vars.calein_out)), 
#line 430 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 429 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 430 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 430 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 430 "codegen.cln"
local_vars.calein_out)), 
#line 431 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 431 "codegen.cln"
value_make_string_from_c_string(" = value_add_reference(")),value_add_reference(
#line 431 "codegen.cln"
local_vars.calein_out)), 
#line 432 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 432 "codegen.cln"
global_SCOPEcalein_value_SPACEof_SPACEir_SPACEassignment_ARG(value_add_reference(
#line 432 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 432 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 432 "codegen.cln"
calein_expression_SPACEcontext),value_add_reference(
#line 432 "codegen.cln"
local_vars.calein_scope)), 
#line 433 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 433 "codegen.cln"
value_make_string_from_c_string("), value_remove_reference(tmp_for_derefs),")),value_add_reference(
#line 433 "codegen.cln"
local_vars.calein_out)), 
#line 435 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 434 "codegen.cln"
local_vars.calein_name),value_add_reference(
#line 435 "codegen.cln"
local_vars.calein_var_SPACEscope),value_add_reference(
#line 435 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 435 "codegen.cln"
local_vars.calein_out)), 
#line 436 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 436 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 436 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 437 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 437 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 437 "codegen.cln"
calein_statement_SPACEcontext))) ? (
#line 438 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 438 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 438 "codegen.cln"
local_vars.calein_out))) : (
#line 439 "codegen.cln"
calein_false)))) : (
#line 440 "codegen.cln"
calein_false)))) : ((
#line 442 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 442 "codegen.cln"
value_make_string_from_c_string("error: var "))), 
#line 443 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 443 "codegen.cln"
local_vars.calein_name)), 
#line 444 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 444 "codegen.cln"
value_make_string_from_c_string(" not in scope in "))), 
#line 445 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 445 "codegen.cln"
local_vars.calein_context)), 
#line 446 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 446 "codegen.cln"
value_make_string_from_c_string(" in "))), 
#line 447 "codegen.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 447 "codegen.cln"
local_vars.calein_scope))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 449 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEliteral(value_add_reference(
#line 449 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 450 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 450 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 450 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 451 "codegen.cln"
global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 451 "codegen.cln"
global_SCOPEcalein_position_SPACEof_SPACEir_SPACEliteral_ARG(value_add_reference(
#line 451 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 451 "codegen.cln"
local_vars.calein_out)), 
#line 452 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 452 "codegen.cln"
value_make_string_from_c_string("value_make_string_from_c_string(")),value_add_reference(
#line 452 "codegen.cln"
local_vars.calein_out)), 
#line 453 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 453 "codegen.cln"
global_SCOPEcalein_value_SPACEof_SPACEir_SPACEliteral_ARG(value_add_reference(
#line 453 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 453 "codegen.cln"
local_vars.calein_out)), 
#line 454 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 454 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 454 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 455 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 455 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 455 "codegen.cln"
calein_statement_SPACEcontext))) ? (
#line 456 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 456 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 456 "codegen.cln"
local_vars.calein_out))) : (
#line 457 "codegen.cln"
calein_false)))) : (
#line 458 "codegen.cln"
calein_false)))) : ((value_boolean_is_true_remove_floating_reference(
#line 459 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEnumber(value_add_reference(
#line 459 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 460 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 460 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 460 "codegen.cln"
calein_expression_SPACEcontext))) ? ((
#line 461 "codegen.cln"
global_SCOPEcalein_emit_SPACEposition_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 461 "codegen.cln"
global_SCOPEcalein_position_SPACEof_SPACEir_SPACEnumber_ARG(value_add_reference(
#line 461 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 461 "codegen.cln"
local_vars.calein_out)), 
#line 462 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 462 "codegen.cln"
value_make_string_from_c_string("value_make_number(")),value_add_reference(
#line 462 "codegen.cln"
local_vars.calein_out)), 
#line 463 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 463 "codegen.cln"
global_SCOPEcalein_string_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 463 "codegen.cln"
global_SCOPEcalein_value_SPACEof_SPACEir_SPACEnumber_ARG(value_add_reference(
#line 463 "codegen.cln"
local_vars.calein_ir))))),value_add_reference(
#line 463 "codegen.cln"
local_vars.calein_out)), 
#line 464 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 464 "codegen.cln"
value_make_string_from_c_string(")")),value_add_reference(
#line 464 "codegen.cln"
local_vars.calein_out)), (value_boolean_is_true_remove_floating_reference(
#line 465 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 465 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 465 "codegen.cln"
calein_statement_SPACEcontext))) ? (
#line 466 "codegen.cln"
global_SCOPEcalein_append_SPACEstring_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 466 "codegen.cln"
value_make_string_from_c_string(";\n")),value_add_reference(
#line 466 "codegen.cln"
local_vars.calein_out))) : (
#line 467 "codegen.cln"
calein_false)))) : (
#line 468 "codegen.cln"
calein_false)))) : ((value_boolean_is_true_remove_floating_reference(
#line 469 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEir_SPACEimport(value_add_reference(
#line 469 "codegen.cln"
local_vars.calein_ir))) ? (((value_boolean_is_true_remove_floating_reference(
#line 470 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 470 "codegen.cln"
local_vars.calein_scope),value_add_reference(
#line 470 "codegen.cln"
calein_global_SPACEscope))) ? (((local_vars.calein_import_SPACEir = value_add_reference(
#line 471 "codegen.cln"
global_SCOPEcalein_ir_SPACEof_SPACEir_SPACEimport_ARG(value_add_reference(
#line 471 "codegen.cln"
local_vars.calein_ir)))), (local_vars.calein_module_SPACElist = value_add_reference(
#line 473 "codegen.cln"
global_SCOPEcalein_lookup_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 473 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 473 "codegen.cln"
calein_module_SPACElist_SPACEby_SPACEcontext)))), (value_boolean_is_true_remove_floating_reference(
#line 474 "codegen.cln"
local_vars.calein_module_SPACElist) ? (((value_boolean_is_true_remove_floating_reference(
#line 475 "codegen.cln"
global_SCOPEcalein__SPACE_ARGcontains_ARG(value_add_reference(
#line 475 "codegen.cln"
local_vars.calein_module_SPACElist),value_add_reference(
#line 475 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEimport_ARG(value_add_reference(
#line 475 "codegen.cln"
local_vars.calein_ir))))) ? ((
#line 476 "codegen.cln"
(tmp_for_derefs = local_vars.calein_import_SPACEir, local_vars.calein_import_SPACEir = value_add_reference(
#line 476 "codegen.cln"
calein_false), value_remove_reference(tmp_for_derefs),local_vars.calein_import_SPACEir))) : ((
#line 480 "codegen.cln"
(tmp_for_derefs = calein_module_SPACElist_SPACEby_SPACEcontext, calein_module_SPACElist_SPACEby_SPACEcontext = value_add_reference(
#line 480 "codegen.cln"
global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 479 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 479 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 479 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEimport_ARG(value_add_reference(
#line 479 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 479 "codegen.cln"
local_vars.calein_module_SPACElist))),value_add_reference(
#line 480 "codegen.cln"
calein_module_SPACElist_SPACEby_SPACEcontext))), value_remove_reference(tmp_for_derefs),calein_module_SPACElist_SPACEby_SPACEcontext)))))) : ((
#line 485 "codegen.cln"
(tmp_for_derefs = calein_module_SPACElist_SPACEby_SPACEcontext, calein_module_SPACElist_SPACEby_SPACEcontext = value_add_reference(
#line 485 "codegen.cln"
global_SCOPEcalein_update_SPACEkey_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_ARG(value_add_reference(
#line 484 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 484 "codegen.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 484 "codegen.cln"
global_SCOPEcalein_name_SPACEof_SPACEir_SPACEimport_ARG(value_add_reference(
#line 484 "codegen.cln"
local_vars.calein_ir))),value_add_reference(
#line 484 "codegen.cln"
calein_false))),value_add_reference(
#line 485 "codegen.cln"
calein_module_SPACElist_SPACEby_SPACEcontext))), value_remove_reference(tmp_for_derefs),calein_module_SPACElist_SPACEby_SPACEcontext)))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 487 "codegen.cln"
local_vars.calein_import_SPACEir)) {

#line 488 "codegen.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 488 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 488 "codegen.cln"
local_vars.calein_import_SPACEir))),value_add_reference(
#line 488 "codegen.cln"
local_vars.calein_out),value_add_reference(
#line 488 "codegen.cln"
local_vars.calein_context),value_add_reference(
#line 488 "codegen.cln"
local_vars.calein_scope));

#line 489 "codegen.cln"
(tmp_for_derefs = local_vars.calein_import_SPACEir, local_vars.calein_import_SPACEir = value_add_reference(
#line 489 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 489 "codegen.cln"
local_vars.calein_import_SPACEir))), value_remove_reference(tmp_for_derefs),local_vars.calein_import_SPACEir);

}
 0; }))) : (
#line 491 "codegen.cln"
global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(
#line 491 "codegen.cln"
value_make_string_from_c_string("Can only import at top level."))))))) : (
#line 492 "codegen.cln"
global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(
#line 492 "codegen.cln"
value_make_string_from_c_string("unrecognized ir kind"))))))))))))))))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_module_SPACElist);value_remove_reference(local_vars.calein_import_SPACEir);value_remove_reference(local_vars.calein_old_SPACElength);value_remove_reference(local_vars.calein_expected_SPACEsep);value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_vars);value_remove_reference(local_vars.calein_ident);value_remove_reference(local_vars.calein_old_SPACEvariable_SPACElist);value_remove_reference(local_vars.calein_old_SPACEfunction_SPACElist);value_remove_reference(local_vars.calein_adjusted_SPACEproc_SPACEname);value_remove_reference(local_vars.calein_field_SPACEcount);value_remove_reference(local_vars.calein_i);value_remove_reference(local_vars.calein_record_SPACEname);value_remove_reference(local_vars.calein_function_SPACEinfo);value_remove_reference(local_vars.calein_proc_SPACEname);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_sep);value_remove_reference(local_vars.calein_var_SPACEscope);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_scope);value_remove_reference(local_vars.calein_context);value_remove_reference(local_vars.calein_out);value_remove_reference(local_vars.calein_ir);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals(void){
struct global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals_local_vars local_vars;
local_vars.calein_vars = 0;
local_vars.calein_var = 0;
local_vars.calein_s = 0;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_vars = value_add_reference(
#line 496 "codegen.cln"
calein_variable_SPACElist)), (local_vars.calein_var = value_add_reference(
#line 497 "codegen.cln"
calein_false)), (local_vars.calein_s = value_add_reference(
#line 498 "codegen.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 499 "codegen.cln"
local_vars.calein_vars)) {

#line 500 "codegen.cln"
(tmp_for_derefs = local_vars.calein_s, local_vars.calein_s = value_add_reference(
#line 500 "codegen.cln"
value_make_string_from_c_string("")), value_remove_reference(tmp_for_derefs),local_vars.calein_s);

#line 501 "codegen.cln"
(tmp_for_derefs = local_vars.calein_var, local_vars.calein_var = value_add_reference(
#line 501 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 501 "codegen.cln"
local_vars.calein_vars))), value_remove_reference(tmp_for_derefs),local_vars.calein_var);
if (value_boolean_is_true_remove_floating_reference(
#line 502 "codegen.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 502 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 502 "codegen.cln"
local_vars.calein_var))),value_add_reference(
#line 502 "codegen.cln"
calein_global_SPACEscope)))) {

#line 503 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 503 "codegen.cln"
value_make_string_from_c_string("value_remove_reference(")));

#line 505 "codegen.cln"
global_SCOPEcalein_emit_SPACEreference_SPACEto_SPACEvariable_SPACE_SPACE_ARGfrom_SPACEscope_SPACE_SPACE_ARGin_SPACEscope_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 504 "codegen.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 504 "codegen.cln"
local_vars.calein_var))),value_add_reference(
#line 505 "codegen.cln"
calein_global_SPACEscope),value_add_reference(
#line 505 "codegen.cln"
calein_global_SPACEscope),value_add_reference(
#line 505 "codegen.cln"
local_vars.calein_s));

#line 506 "codegen.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 506 "codegen.cln"
local_vars.calein_s));

#line 507 "codegen.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 507 "codegen.cln"
value_make_string_from_c_string(");")));

} else {

#line 508 "codegen.cln"
calein_false;
}
#line 509 "codegen.cln"
(tmp_for_derefs = local_vars.calein_vars, local_vars.calein_vars = value_add_reference(
#line 509 "codegen.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 509 "codegen.cln"
local_vars.calein_vars))), value_remove_reference(tmp_for_derefs),local_vars.calein_vars);

}
 0; }));
value_add_reference(result);
value_remove_reference(local_vars.calein_s);value_remove_reference(local_vars.calein_var);value_remove_reference(local_vars.calein_vars);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG(struct value *calein_file_SPACEname, struct value *calein_pos){
struct global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG_local_vars local_vars;
local_vars.calein_f = 0;
local_vars.calein_import = 0;
local_vars.calein_file_SPACEname = calein_file_SPACEname;
local_vars.calein_pos = calein_pos;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_f = value_add_reference(
#line 5 "compiler.cln"
global_SCOPEcalein_open_SPACEfile_SPACE_SPACE_ARGfor_SPACEreading(value_add_reference(
#line 5 "compiler.cln"
local_vars.calein_file_SPACEname)))), (local_vars.calein_import = value_add_reference(
#line 7 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEimport_SPACE_SPACE_ARGwith_SPACEir_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 7 "compiler.cln"
local_vars.calein_file_SPACEname),value_add_reference(
#line 7 "compiler.cln"
global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG(value_add_reference(
#line 7 "compiler.cln"
global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(value_add_reference(
#line 7 "compiler.cln"
local_vars.calein_f),value_add_reference(
#line 7 "compiler.cln"
local_vars.calein_file_SPACEname))))),value_add_reference(
#line 7 "compiler.cln"
local_vars.calein_pos)))), 
#line 8 "compiler.cln"
global_SCOPEcalein_close_SPACEfile_ARG(value_add_reference(
#line 8 "compiler.cln"
local_vars.calein_f)), 
#line 9 "compiler.cln"
local_vars.calein_import);
value_add_reference(result);
value_remove_reference(local_vars.calein_import);value_remove_reference(local_vars.calein_f);value_remove_reference(local_vars.calein_pos);value_remove_reference(local_vars.calein_file_SPACEname);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_compile_ARG(struct value *calein_tree){
struct global_SCOPEcalein_compile_ARG_local_vars local_vars;
local_vars.calein_ir_SPACEargs = 0;
local_vars.calein_args = 0;
local_vars.calein_pos = 0;
local_vars.calein_file_SPACEname = 0;
local_vars.calein_ir_SPACEitems = 0;
local_vars.calein_items = 0;
local_vars.calein_tree = calein_tree;
struct value *tmp_for_derefs = 0;
struct value *result = ((value_boolean_is_true_remove_floating_reference(
#line 13 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEan_SPACEaction(value_add_reference(
#line 13 "compiler.cln"
local_vars.calein_tree))) ? (((local_vars.calein_ir_SPACEargs = value_add_reference(
#line 14 "compiler.cln"
calein_false)), (local_vars.calein_args = value_add_reference(
#line 15 "compiler.cln"
global_SCOPEcalein_arguments_SPACEof_SPACEaction_ARG(value_add_reference(
#line 15 "compiler.cln"
local_vars.calein_tree)))), (local_vars.calein_pos = value_add_reference(
#line 16 "compiler.cln"
global_SCOPEcalein_position_SPACEof_SPACEaction_ARG(value_add_reference(
#line 16 "compiler.cln"
local_vars.calein_tree)))), (value_boolean_is_true_remove_floating_reference(
#line 17 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 17 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 17 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 17 "compiler.cln"
value_make_string_from_c_string("note")))) ? (
#line 18 "compiler.cln"
calein_false) : ((value_boolean_is_true_remove_floating_reference(
#line 19 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 19 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 19 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 19 "compiler.cln"
value_make_string_from_c_string("define record  with predicate")))) ? (
#line 22 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACErecord_SPACE_SPACE_ARGwith_SPACEpredicate_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 20 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 20 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 20 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 20 "compiler.cln"
value_make_number(0)))))),value_add_reference(
#line 21 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 21 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 21 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 21 "compiler.cln"
value_make_number(1)))))),value_add_reference(
#line 22 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 23 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 23 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 23 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 23 "compiler.cln"
value_make_string_from_c_string("define procedure  to do")))) ? (
#line 26 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEprocedure_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 24 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 24 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 24 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 24 "compiler.cln"
value_make_number(0)))))),value_add_reference(
#line 25 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 25 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 25 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 25 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 25 "compiler.cln"
value_make_number(1)))))))),value_add_reference(
#line 26 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 27 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 27 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 27 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 27 "compiler.cln"
value_make_string_from_c_string("define variable  with initial value")))) ? (
#line 30 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEvariable_SPACE_SPACE_ARGwith_SPACEinitial_SPACEvalue_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 28 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 28 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 28 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 28 "compiler.cln"
value_make_number(0)))))),value_add_reference(
#line 29 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 29 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 29 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 29 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 29 "compiler.cln"
value_make_number(1)))))))),value_add_reference(
#line 30 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 31 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 31 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 31 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 31 "compiler.cln"
value_make_string_from_c_string("set  to")))) ? (
#line 34 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEassignment_SPACE_SPACE_ARGwith_SPACEvalue_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 32 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 32 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 32 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 32 "compiler.cln"
value_make_number(0)))))),value_add_reference(
#line 33 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 33 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 33 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 33 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 33 "compiler.cln"
value_make_number(1)))))))),value_add_reference(
#line 34 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 35 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 35 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 35 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 35 "compiler.cln"
value_make_string_from_c_string("if  then  else")))) ? (
#line 39 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEif_SPACE_SPACE_ARGthen_SPACE_SPACE_ARGelse_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 36 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 36 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 36 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 36 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 36 "compiler.cln"
value_make_number(0)))))))),value_add_reference(
#line 37 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 37 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 37 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 37 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 37 "compiler.cln"
value_make_number(1)))))))),value_add_reference(
#line 38 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 38 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 38 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 38 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 38 "compiler.cln"
value_make_number(2)))))))),value_add_reference(
#line 39 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 40 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 40 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 40 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 40 "compiler.cln"
value_make_string_from_c_string("while  do")))) ? (
#line 43 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEwhile_SPACE_SPACE_ARGwith_SPACEbody_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 41 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 41 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 41 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 41 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 41 "compiler.cln"
value_make_number(0)))))))),value_add_reference(
#line 42 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 42 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 42 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 42 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 42 "compiler.cln"
value_make_number(1)))))))),value_add_reference(
#line 43 "compiler.cln"
local_vars.calein_pos))) : ((value_boolean_is_true_remove_floating_reference(
#line 44 "compiler.cln"
global_SCOPEcalein__SPACE_ARGand_ARG(value_add_reference(
#line 44 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 44 "compiler.cln"
global_SCOPEcalein_name_SPACEof_SPACEaction_ARG(value_add_reference(
#line 44 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 44 "compiler.cln"
value_make_string_from_c_string("import")))),value_add_reference(
#line 44 "compiler.cln"
local_vars.calein_args))) ? (((value_boolean_is_true_remove_floating_reference(
#line 45 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(value_add_reference(
#line 45 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 45 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 45 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 45 "compiler.cln"
value_make_number(0)))))))) ? (((local_vars.calein_file_SPACEname = value_add_reference(
#line 47 "compiler.cln"
global_SCOPEcalein_concat_SPACE_SPACE_ARGand_ARG(value_add_reference(
#line 47 "compiler.cln"
global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(value_add_reference(
#line 47 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 47 "compiler.cln"
global_SCOPEcalein__SPACE_ARGat_ARG(value_add_reference(
#line 47 "compiler.cln"
local_vars.calein_args),value_add_reference(
#line 47 "compiler.cln"
value_make_number(0)))))))),value_add_reference(
#line 47 "compiler.cln"
value_make_string_from_c_string(".cln"))))), 
#line 48 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 48 "compiler.cln"
local_vars.calein_file_SPACEname),value_add_reference(
#line 48 "compiler.cln"
local_vars.calein_pos)))) : (
#line 49 "compiler.cln"
global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(
#line 49 "compiler.cln"
value_make_string_from_c_string("import takes only literal arguments."))))))) : ((({ while (value_boolean_is_true_remove_floating_reference(
#line 51 "compiler.cln"
local_vars.calein_args)) {

#line 52 "compiler.cln"
(tmp_for_derefs = local_vars.calein_ir_SPACEargs, local_vars.calein_ir_SPACEargs = value_add_reference(
#line 52 "compiler.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 52 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 52 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 52 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 52 "compiler.cln"
local_vars.calein_args))))))),value_add_reference(
#line 52 "compiler.cln"
local_vars.calein_ir_SPACEargs))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir_SPACEargs);

#line 53 "compiler.cln"
(tmp_for_derefs = local_vars.calein_args, local_vars.calein_args = value_add_reference(
#line 53 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 53 "compiler.cln"
local_vars.calein_args))), value_remove_reference(tmp_for_derefs),local_vars.calein_args);

}
 0; }), 
#line 55 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEcall_SPACE_SPACE_ARGwith_SPACEarguments_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 55 "compiler.cln"
global_SCOPEcalein_C_SPACEident_SPACEfor_SPACEaction_ARG(value_add_reference(
#line 55 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 55 "compiler.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 55 "compiler.cln"
local_vars.calein_ir_SPACEargs))),value_add_reference(
#line 55 "compiler.cln"
local_vars.calein_pos))))))))))))))))))))) : ((value_boolean_is_true_remove_floating_reference(
#line 57 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEsequence(value_add_reference(
#line 57 "compiler.cln"
local_vars.calein_tree))) ? (((local_vars.calein_ir_SPACEitems = value_add_reference(
#line 58 "compiler.cln"
calein_false)), (local_vars.calein_items = value_add_reference(
#line 59 "compiler.cln"
global_SCOPEcalein_items_SPACEof_SPACEsequence_ARG(value_add_reference(
#line 59 "compiler.cln"
local_vars.calein_tree)))), ({ while (value_boolean_is_true_remove_floating_reference(
#line 60 "compiler.cln"
local_vars.calein_items)) {

#line 61 "compiler.cln"
(tmp_for_derefs = local_vars.calein_ir_SPACEitems, local_vars.calein_ir_SPACEitems = value_add_reference(
#line 61 "compiler.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 61 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 61 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 61 "compiler.cln"
local_vars.calein_items))))),value_add_reference(
#line 61 "compiler.cln"
local_vars.calein_ir_SPACEitems))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir_SPACEitems);
if (value_boolean_is_true_remove_floating_reference(
#line 62 "compiler.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 62 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 62 "compiler.cln"
local_vars.calein_ir_SPACEitems)))))) {

#line 63 "compiler.cln"
(tmp_for_derefs = local_vars.calein_ir_SPACEitems, local_vars.calein_ir_SPACEitems = value_add_reference(
#line 63 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 63 "compiler.cln"
local_vars.calein_ir_SPACEitems))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir_SPACEitems);

} else {

#line 64 "compiler.cln"
calein_false;
}
#line 65 "compiler.cln"
(tmp_for_derefs = local_vars.calein_items, local_vars.calein_items = value_add_reference(
#line 65 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 65 "compiler.cln"
local_vars.calein_items))), value_remove_reference(tmp_for_derefs),local_vars.calein_items);

}
 0; }), 
#line 67 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEsequence_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 67 "compiler.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 67 "compiler.cln"
local_vars.calein_ir_SPACEitems))),value_add_reference(
#line 67 "compiler.cln"
global_SCOPEcalein_position_SPACEof_SPACEsequence_ARG(value_add_reference(
#line 67 "compiler.cln"
local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(
#line 68 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEnumber(value_add_reference(
#line 68 "compiler.cln"
local_vars.calein_tree))) ? ((
#line 69 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEnumber_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 69 "compiler.cln"
global_SCOPEcalein_value_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 69 "compiler.cln"
local_vars.calein_tree))),value_add_reference(
#line 69 "compiler.cln"
global_SCOPEcalein_position_SPACEof_SPACEnumber_ARG(value_add_reference(
#line 69 "compiler.cln"
local_vars.calein_tree)))))) : ((value_boolean_is_true_remove_floating_reference(
#line 70 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEa_SPACEliteral(value_add_reference(
#line 70 "compiler.cln"
local_vars.calein_tree))) ? ((
#line 71 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEliteral_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 71 "compiler.cln"
global_SCOPEcalein_C_SPACEstring_SPACEfor_SPACEliteral_ARG(value_add_reference(
#line 71 "compiler.cln"
global_SCOPEcalein_value_SPACEof_SPACEliteral_ARG(value_add_reference(
#line 71 "compiler.cln"
local_vars.calein_tree))))),value_add_reference(
#line 71 "compiler.cln"
global_SCOPEcalein_position_SPACEof_SPACEliteral_ARG(value_add_reference(
#line 71 "compiler.cln"
local_vars.calein_tree)))))) : (
#line 72 "compiler.cln"
global_SCOPEcalein_compile_SPACEerror_ARG(value_add_reference(
#line 72 "compiler.cln"
value_make_string_from_c_string("unsupported kind of tree"))))))))))));
value_add_reference(result);
value_remove_reference(local_vars.calein_items);value_remove_reference(local_vars.calein_ir_SPACEitems);value_remove_reference(local_vars.calein_file_SPACEname);value_remove_reference(local_vars.calein_pos);value_remove_reference(local_vars.calein_args);value_remove_reference(local_vars.calein_ir_SPACEargs);value_remove_reference(local_vars.calein_tree);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG(struct value *calein_trees){
struct global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG_local_vars local_vars;
local_vars.calein_irs = 0;
local_vars.calein_trees = calein_trees;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_irs = value_add_reference(
#line 76 "compiler.cln"
calein_false)), ({ while (value_boolean_is_true_remove_floating_reference(
#line 77 "compiler.cln"
local_vars.calein_trees)) {

#line 78 "compiler.cln"
(tmp_for_derefs = local_vars.calein_irs, local_vars.calein_irs = value_add_reference(
#line 78 "compiler.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 78 "compiler.cln"
global_SCOPEcalein_compile_ARG(value_add_reference(
#line 78 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 78 "compiler.cln"
local_vars.calein_trees))))),value_add_reference(
#line 78 "compiler.cln"
local_vars.calein_irs))), value_remove_reference(tmp_for_derefs),local_vars.calein_irs);

#line 79 "compiler.cln"
(tmp_for_derefs = local_vars.calein_trees, local_vars.calein_trees = value_add_reference(
#line 79 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 79 "compiler.cln"
local_vars.calein_trees))), value_remove_reference(tmp_for_derefs),local_vars.calein_trees);

}
 0; }), 
#line 81 "compiler.cln"
global_SCOPEcalein_reverse_SPACElist_ARG(value_add_reference(
#line 81 "compiler.cln"
local_vars.calein_irs)));
value_add_reference(result);
value_remove_reference(local_vars.calein_irs);value_remove_reference(local_vars.calein_trees);value_float_result(result);
return result;
}
struct value *global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(struct value *calein_f, struct value *calein_name){
struct global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG_local_vars local_vars;
local_vars.calein_declarations = 0;
local_vars.calein_definitions = 0;
local_vars.calein_initializers = 0;
local_vars.calein_main = 0;
local_vars.calein_ir = 0;
local_vars.calein_irs = 0;
local_vars.calein_f = calein_f;
local_vars.calein_name = calein_name;
struct value *tmp_for_derefs = 0;
struct value *result = ((local_vars.calein_declarations = value_add_reference(
#line 85 "compiler.cln"
value_make_string_from_c_string(""))), (local_vars.calein_definitions = value_add_reference(
#line 86 "compiler.cln"
value_make_string_from_c_string(""))), (local_vars.calein_initializers = value_add_reference(
#line 87 "compiler.cln"
value_make_string_from_c_string(""))), (local_vars.calein_main = value_add_reference(
#line 88 "compiler.cln"
value_make_string_from_c_string(""))), (local_vars.calein_ir = value_add_reference(
#line 90 "compiler.cln"
calein_false)), (local_vars.calein_irs = value_add_reference(
#line 91 "compiler.cln"
global_SCOPEcalein_ir_SPACEof_SPACEsyntax_SPACEtrees_ARG(value_add_reference(
#line 91 "compiler.cln"
global_SCOPEcalein_parse_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(value_add_reference(
#line 91 "compiler.cln"
local_vars.calein_f),value_add_reference(
#line 91 "compiler.cln"
local_vars.calein_name)))))), 
#line 93 "compiler.cln"
(tmp_for_derefs = local_vars.calein_irs, local_vars.calein_irs = value_add_reference(
#line 93 "compiler.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 93 "compiler.cln"
global_SCOPEcalein_make_SPACEir_SPACEimport_SPACEfor_SPACE_SPACE_ARGat_ARG(value_add_reference(
#line 93 "compiler.cln"
value_make_string_from_c_string("prelude.cln")),value_add_reference(
#line 93 "compiler.cln"
global_SCOPEcalein_position_SPACEat_SPACEline_SPACE_SPACE_ARGin_SPACEfile_ARG(value_add_reference(
#line 93 "compiler.cln"
value_make_number(0)),value_add_reference(
#line 93 "compiler.cln"
local_vars.calein_name))))),value_add_reference(
#line 93 "compiler.cln"
local_vars.calein_irs))), value_remove_reference(tmp_for_derefs),local_vars.calein_irs), ({ while (value_boolean_is_true_remove_floating_reference(
#line 95 "compiler.cln"
local_vars.calein_irs)) {

#line 96 "compiler.cln"
(tmp_for_derefs = local_vars.calein_ir, local_vars.calein_ir = value_add_reference(
#line 96 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 96 "compiler.cln"
local_vars.calein_irs))), value_remove_reference(tmp_for_derefs),local_vars.calein_ir);
if (value_boolean_is_true_remove_floating_reference(
#line 97 "compiler.cln"
local_vars.calein_ir)) {

#line 98 "compiler.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 98 "compiler.cln"
local_vars.calein_ir),value_add_reference(
#line 98 "compiler.cln"
local_vars.calein_declarations),value_add_reference(
#line 98 "compiler.cln"
calein_declaration_SPACEcontext),value_add_reference(
#line 98 "compiler.cln"
calein_global_SPACEscope));

#line 99 "compiler.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 99 "compiler.cln"
local_vars.calein_ir),value_add_reference(
#line 99 "compiler.cln"
local_vars.calein_definitions),value_add_reference(
#line 99 "compiler.cln"
calein_definition_SPACEcontext),value_add_reference(
#line 99 "compiler.cln"
calein_global_SPACEscope));

#line 100 "compiler.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 100 "compiler.cln"
local_vars.calein_ir),value_add_reference(
#line 100 "compiler.cln"
local_vars.calein_initializers),value_add_reference(
#line 100 "compiler.cln"
calein_initializer_SPACEcontext),value_add_reference(
#line 100 "compiler.cln"
calein_global_SPACEscope));

#line 101 "compiler.cln"
global_SCOPEcalein_emit_SPACE_SPACE_ARGto_SPACE_SPACE_ARGin_SPACE_SPACE_ARGwith_SPACEscope_ARG(value_add_reference(
#line 101 "compiler.cln"
local_vars.calein_ir),value_add_reference(
#line 101 "compiler.cln"
local_vars.calein_main),value_add_reference(
#line 101 "compiler.cln"
calein_statement_SPACEcontext),value_add_reference(
#line 101 "compiler.cln"
calein_global_SPACEscope));

} else {

#line 102 "compiler.cln"
calein_false;
}
#line 103 "compiler.cln"
(tmp_for_derefs = local_vars.calein_irs, local_vars.calein_irs = value_add_reference(
#line 103 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 103 "compiler.cln"
local_vars.calein_irs))), value_remove_reference(tmp_for_derefs),local_vars.calein_irs);

}
 0; }), 
#line 106 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 106 "compiler.cln"
local_vars.calein_declarations)), 
#line 107 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 107 "compiler.cln"
local_vars.calein_definitions)), 
#line 108 "compiler.cln"
global_SCOPEcalein__COMMA_ARG_ARG(value_add_reference(
#line 108 "compiler.cln"
local_vars.calein_initializers),value_add_reference(
#line 108 "compiler.cln"
local_vars.calein_main)));
value_add_reference(result);
value_remove_reference(local_vars.calein_irs);value_remove_reference(local_vars.calein_ir);value_remove_reference(local_vars.calein_main);value_remove_reference(local_vars.calein_initializers);value_remove_reference(local_vars.calein_definitions);value_remove_reference(local_vars.calein_declarations);value_remove_reference(local_vars.calein_name);value_remove_reference(local_vars.calein_f);value_float_result(result);
return result;
}
struct value *calein_main_SPACEmodule;
struct value *calein_f;

void caleinmain(void) {
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
calein_left_SPACEangle = 0;
calein_right_SPACEangle = 0;
calein_backslash = 0;
calein_underscore = 0;
calein_character_SPACEn = 0;
calein_open_SPACEbrace = 0;
calein_close_SPACEbrace = 0;
calein_line_SPACEnumber = 0;
calein_column_SPACEnumber = 0;
calein_file_SPACEname = 0;
calein_file_SPACEto_SPACEread_SPACEfrom = 0;
calein_ungotten_SPACEcharacter = 0;
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = 0;
calein_source_SPACElevel_SPACEdebugging = 0;
calein_expression_SPACEcontext = 0;
calein_statement_SPACEcontext = 0;
calein_definition_SPACEcontext = 0;
calein_declaration_SPACEcontext = 0;
calein_initializer_SPACEcontext = 0;
calein_nested_SPACEdefinition_SPACEcontext = 0;
calein_procedure_SPACEdefinition_SPACEcontext = 0;
calein_variable_SPACElist = 0;
calein_function_SPACElist = 0;
calein_function_SPACEvariable_SPACElist = 0;
calein_module_SPACElist_SPACEby_SPACEcontext = 0;
calein_global_SPACEscope = 0;
calein_continue = 0;
calein_main_SPACEmodule = 0;
calein_f = 0;

calein_true = value_add_reference(
#line 1 "prelude.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 1 "prelude.cln"
value_make_number(0)),value_add_reference(
#line 1 "prelude.cln"
value_make_number(0))));
calein_false = value_add_reference(
#line 2 "prelude.cln"
global_SCOPEcalein_not_ARG(value_add_reference(
#line 2 "prelude.cln"
calein_true)));
calein_tab = value_add_reference(
#line 3 "prelude.cln"
value_make_number(9));
calein_tab_SPACEstring = value_add_reference(
#line 4 "prelude.cln"
value_make_string_from_c_string(""));

#line 5 "prelude.cln"
global_SCOPEcalein_append_SPACEcharacter_SPACE_SPACE_ARGto_ARG(value_add_reference(
#line 5 "prelude.cln"
calein_tab),value_add_reference(
#line 5 "prelude.cln"
calein_tab_SPACEstring));
calein_new_SPACEline = value_add_reference(
#line 6 "prelude.cln"
value_make_number(10));
calein_space = value_add_reference(
#line 7 "prelude.cln"
value_make_number(32));
calein_quote = value_add_reference(
#line 8 "prelude.cln"
value_make_number(34));
calein_number_SPACEsigil = value_add_reference(
#line 9 "prelude.cln"
value_make_number(35));
calein_open_SPACEparen = value_add_reference(
#line 10 "prelude.cln"
value_make_number(40));
calein_close_SPACEparen = value_add_reference(
#line 11 "prelude.cln"
value_make_number(41));
calein_star = value_add_reference(
#line 12 "prelude.cln"
value_make_number(42));
calein_plus = value_add_reference(
#line 13 "prelude.cln"
value_make_number(43));
calein_comma = value_add_reference(
#line 14 "prelude.cln"
value_make_number(44));
calein_minus = value_add_reference(
#line 15 "prelude.cln"
value_make_number(45));
calein_dot = value_add_reference(
#line 16 "prelude.cln"
value_make_number(46));
calein_slash = value_add_reference(
#line 17 "prelude.cln"
value_make_number(47));
calein_character_SPACE0 = value_add_reference(
#line 18 "prelude.cln"
value_make_number(48));
calein_left_SPACEangle = value_add_reference(
#line 19 "prelude.cln"
value_make_number(60));
calein_right_SPACEangle = value_add_reference(
#line 20 "prelude.cln"
value_make_number(62));
calein_backslash = value_add_reference(
#line 21 "prelude.cln"
value_make_number(92));
calein_underscore = value_add_reference(
#line 22 "prelude.cln"
value_make_number(95));
calein_character_SPACEn = value_add_reference(
#line 23 "prelude.cln"
value_make_number(110));
calein_open_SPACEbrace = value_add_reference(
#line 24 "prelude.cln"
value_make_number(123));
calein_close_SPACEbrace = value_add_reference(
#line 25 "prelude.cln"
value_make_number(125));
calein_line_SPACEnumber = value_add_reference(
#line 1 "parser.cln"
value_make_number(1));
calein_column_SPACEnumber = value_add_reference(
#line 2 "parser.cln"
value_make_number(1));
calein_file_SPACEname = value_add_reference(
#line 3 "parser.cln"
value_make_string_from_c_string("-"));
calein_file_SPACEto_SPACEread_SPACEfrom = value_add_reference(
#line 5 "parser.cln"
global_SCOPEcalein_standard_SPACEinput());
calein_ungotten_SPACEcharacter = value_add_reference(
#line 6 "parser.cln"
calein_false);
calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers = value_add_reference(
#line 4 "c-utils.cln"
calein_false);

#line 9 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 9 "c-utils.cln"
value_make_string_from_c_string("_SPACE")),value_add_reference(
#line 9 "c-utils.cln"
calein_space));

#line 10 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 10 "c-utils.cln"
value_make_string_from_c_string("_UNDERSCORE")),value_add_reference(
#line 10 "c-utils.cln"
calein_underscore));

#line 11 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 11 "c-utils.cln"
value_make_string_from_c_string("_STAR")),value_add_reference(
#line 11 "c-utils.cln"
calein_star));

#line 12 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 12 "c-utils.cln"
value_make_string_from_c_string("_PLUS")),value_add_reference(
#line 12 "c-utils.cln"
calein_plus));

#line 13 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 13 "c-utils.cln"
value_make_string_from_c_string("_DASH")),value_add_reference(
#line 13 "c-utils.cln"
calein_minus));

#line 14 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 14 "c-utils.cln"
value_make_string_from_c_string("_SLASH")),value_add_reference(
#line 14 "c-utils.cln"
calein_slash));

#line 15 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 15 "c-utils.cln"
value_make_string_from_c_string("_COMMA")),value_add_reference(
#line 15 "c-utils.cln"
calein_comma));

#line 16 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 16 "c-utils.cln"
value_make_string_from_c_string("_LESSER")),value_add_reference(
#line 16 "c-utils.cln"
calein_left_SPACEangle));

#line 17 "c-utils.cln"
global_SCOPEcalein_substitute_SPACE_SPACE_ARGfor_ARG(value_add_reference(
#line 17 "c-utils.cln"
value_make_string_from_c_string("_GREATER")),value_add_reference(
#line 17 "c-utils.cln"
calein_right_SPACEangle));
calein_source_SPACElevel_SPACEdebugging = value_add_reference(
#line 4 "codegen.cln"
calein_true);
calein_expression_SPACEcontext = value_add_reference(
#line 39 "codegen.cln"
value_make_string_from_c_string("expression context"));
calein_statement_SPACEcontext = value_add_reference(
#line 40 "codegen.cln"
value_make_string_from_c_string("statement context"));
calein_definition_SPACEcontext = value_add_reference(
#line 41 "codegen.cln"
value_make_string_from_c_string("definition context"));
calein_declaration_SPACEcontext = value_add_reference(
#line 42 "codegen.cln"
value_make_string_from_c_string("declaration context"));
calein_initializer_SPACEcontext = value_add_reference(
#line 43 "codegen.cln"
value_make_string_from_c_string("initializer context"));
calein_nested_SPACEdefinition_SPACEcontext = value_add_reference(
#line 44 "codegen.cln"
value_make_string_from_c_string("nested definition context"));
calein_procedure_SPACEdefinition_SPACEcontext = value_add_reference(
#line 45 "codegen.cln"
value_make_string_from_c_string("procedure definition context"));
calein_variable_SPACElist = value_add_reference(
#line 47 "codegen.cln"
calein_false);
calein_function_SPACElist = value_add_reference(
#line 48 "codegen.cln"
calein_false);
calein_function_SPACEvariable_SPACElist = value_add_reference(
#line 49 "codegen.cln"
calein_false);
calein_module_SPACElist_SPACEby_SPACEcontext = value_add_reference(
#line 50 "codegen.cln"
calein_false);
calein_global_SPACEscope = value_add_reference(
#line 66 "codegen.cln"
value_make_string_from_c_string("global"));

#line 69 "codegen.cln"
global_SCOPEcalein_register_SPACEvariable_SPACE_SPACE_ARGin_SPACEscope_ARG(value_add_reference(
#line 68 "codegen.cln"
value_make_string_from_c_string("calein_program_SPACEarguments")),value_add_reference(
#line 69 "codegen.cln"
calein_global_SPACEscope));
calein_continue = value_add_reference(
#line 125 "codegen.cln"
calein_true);

#line 111 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 111 "compiler.cln"
value_make_string_from_c_string("#include \"caleinrtl.inc.c\"")));
if (value_boolean_is_true_remove_floating_reference(
#line 113 "compiler.cln"
calein_program_SPACEarguments)) {
if (value_boolean_is_true_remove_floating_reference(
#line 114 "compiler.cln"
global_SCOPEcalein__SPACE_ARGis_SPACEequal_SPACEto_ARG(value_add_reference(
#line 114 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 114 "compiler.cln"
calein_program_SPACEarguments))),value_add_reference(
#line 114 "compiler.cln"
value_make_string_from_c_string("-g"))))) {

#line 115 "compiler.cln"
(tmp_for_derefs = calein_program_SPACEarguments, calein_program_SPACEarguments = value_add_reference(
#line 115 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 115 "compiler.cln"
calein_program_SPACEarguments))), value_remove_reference(tmp_for_derefs),calein_program_SPACEarguments);

#line 116 "compiler.cln"
(tmp_for_derefs = calein_source_SPACElevel_SPACEdebugging, calein_source_SPACElevel_SPACEdebugging = value_add_reference(
#line 116 "compiler.cln"
calein_false), value_remove_reference(tmp_for_derefs),calein_source_SPACElevel_SPACEdebugging);

} else {

#line 117 "compiler.cln"
calein_false;
}
} else {

#line 118 "compiler.cln"
calein_false;
}calein_main_SPACEmodule = value_add_reference(
#line 120 "compiler.cln"
calein_false);
calein_f = value_add_reference(
#line 121 "compiler.cln"
calein_false);
if (value_boolean_is_true_remove_floating_reference(
#line 122 "compiler.cln"
calein_program_SPACEarguments)) {

#line 123 "compiler.cln"
(tmp_for_derefs = calein_f, calein_f = value_add_reference(
#line 123 "compiler.cln"
global_SCOPEcalein_open_SPACEfile_SPACE_SPACE_ARGfor_SPACEreading(value_add_reference(
#line 123 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 123 "compiler.cln"
calein_program_SPACEarguments))))), value_remove_reference(tmp_for_derefs),calein_f);

#line 124 "compiler.cln"
(tmp_for_derefs = calein_main_SPACEmodule, calein_main_SPACEmodule = value_add_reference(
#line 124 "compiler.cln"
global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(value_add_reference(
#line 124 "compiler.cln"
calein_f),value_add_reference(
#line 124 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 124 "compiler.cln"
calein_program_SPACEarguments))))), value_remove_reference(tmp_for_derefs),calein_main_SPACEmodule);

#line 125 "compiler.cln"
global_SCOPEcalein_close_SPACEfile_ARG(value_add_reference(
#line 125 "compiler.cln"
calein_f));

} else {

#line 127 "compiler.cln"
(tmp_for_derefs = calein_main_SPACEmodule, calein_main_SPACEmodule = value_add_reference(
#line 127 "compiler.cln"
global_SCOPEcalein_compile_SPACEfile_SPACE_SPACE_ARGwith_SPACEname_ARG(value_add_reference(
#line 127 "compiler.cln"
global_SCOPEcalein_standard_SPACEinput()),value_add_reference(
#line 127 "compiler.cln"
value_make_string_from_c_string("<stdin>")))), value_remove_reference(tmp_for_derefs),calein_main_SPACEmodule);
}
#line 130 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 130 "compiler.cln"
value_make_string_from_c_string("void caleinmain(void) {")));

#line 131 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 131 "compiler.cln"
value_make_string_from_c_string("struct value *tmp_for_derefs = 0;\n")));

#line 132 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 132 "compiler.cln"
global_SCOPEcalein_first_ARG(value_add_reference(
#line 132 "compiler.cln"
calein_main_SPACEmodule))));

#line 133 "compiler.cln"
global_SCOPEcalein_write_ARG(value_add_reference(
#line 133 "compiler.cln"
global_SCOPEcalein_second_ARG(value_add_reference(
#line 133 "compiler.cln"
calein_main_SPACEmodule))));

#line 134 "compiler.cln"
global_SCOPEcalein_write_SPACEderefs_SPACEfor_SPACEglobals();

#line 135 "compiler.cln"
global_SCOPEcalein_write_SPACEline_ARG(value_add_reference(
#line 135 "compiler.cln"
value_make_string_from_c_string("}")));
value_remove_reference(calein_f);
value_remove_reference(calein_main_SPACEmodule);
value_remove_reference(calein_continue);
value_remove_reference(calein_global_SPACEscope);
value_remove_reference(calein_module_SPACElist_SPACEby_SPACEcontext);
value_remove_reference(calein_function_SPACEvariable_SPACElist);
value_remove_reference(calein_function_SPACElist);
value_remove_reference(calein_variable_SPACElist);
value_remove_reference(calein_procedure_SPACEdefinition_SPACEcontext);
value_remove_reference(calein_nested_SPACEdefinition_SPACEcontext);
value_remove_reference(calein_initializer_SPACEcontext);
value_remove_reference(calein_declaration_SPACEcontext);
value_remove_reference(calein_definition_SPACEcontext);
value_remove_reference(calein_statement_SPACEcontext);
value_remove_reference(calein_expression_SPACEcontext);
value_remove_reference(calein_source_SPACElevel_SPACEdebugging);
value_remove_reference(calein_substitutions_SPACEfor_SPACEC_SPACEidentifiers);
value_remove_reference(calein_ungotten_SPACEcharacter);
value_remove_reference(calein_file_SPACEto_SPACEread_SPACEfrom);
value_remove_reference(calein_file_SPACEname);
value_remove_reference(calein_column_SPACEnumber);
value_remove_reference(calein_line_SPACEnumber);
value_remove_reference(calein_close_SPACEbrace);
value_remove_reference(calein_open_SPACEbrace);
value_remove_reference(calein_character_SPACEn);
value_remove_reference(calein_underscore);
value_remove_reference(calein_backslash);
value_remove_reference(calein_right_SPACEangle);
value_remove_reference(calein_left_SPACEangle);
value_remove_reference(calein_character_SPACE0);
value_remove_reference(calein_slash);
value_remove_reference(calein_dot);
value_remove_reference(calein_minus);
value_remove_reference(calein_comma);
value_remove_reference(calein_plus);
value_remove_reference(calein_star);
value_remove_reference(calein_close_SPACEparen);
value_remove_reference(calein_open_SPACEparen);
value_remove_reference(calein_number_SPACEsigil);
value_remove_reference(calein_quote);
value_remove_reference(calein_space);
value_remove_reference(calein_new_SPACEline);
value_remove_reference(calein_tab_SPACEstring);
value_remove_reference(calein_tab);
value_remove_reference(calein_false);
value_remove_reference(calein_true);
value_remove_reference(calein_program_SPACEarguments);
}
