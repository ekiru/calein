#include "parser.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "err.h"
#include "str.h"
#include "syntax.h"

static struct syntax_tree *parse_generic(void *data, int (*getc)(void *), void (*ungetc)(int, void *)) {
	int c;
	for (;;) {
		c = getc(data);
		if (c == EOF) {
			return 0;
		}
		if (c == '"') {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_literal); 
			if (!tree) {
				return 0;
			}
			string_init_empty(&tree->u.literal);
			
			bool in_escape = false;
			for (;;) {
				c = getc(data);
				if (c == EOF) {
					log_error("Parse error: unterminated string literal.");
					goto literal_err;
				}
				if (in_escape) {
					if (c == '\\' || c == '"') {
						if (!string_add_character(&tree->u.literal, c)) {
							goto literal_err;
						}
					} else if (c == 'n') {
						if (!string_add_character(&tree->u.literal, '\n')) {
							goto literal_err;
						}
					} else {
						log_error("Parse error: undefine escape sequence \\%c",
							c);
						goto literal_err;
					}
					in_escape = false;
				} else if (c == '\\') {
					in_escape = true;
				} else if (c == '"') {
					return tree;
				} else {
					if (!string_add_character(&tree->u.literal, c)) {
						goto literal_err;
					}
				}
			}
		literal_err:
			syntax_tree_free(tree);
			return 0;
		} else if (c == '{') {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_sequence);
			size_t next = 0;
			for (;;) {
				c = getc(data);
				if (c == EOF) {
					log_error("Unexpected EOF in sequence.");
					syntax_tree_free(tree);
					return 0;
				}
				if (c == '}') {
					return tree;
				}
				ungetc(c, data);
				if (next == syntax_tree_max_sequence) {
					log_error("Sequence larger than maximum length %d", syntax_tree_max_sequence);
					return tree;
				}
				tree->u.sequence[next] = parse_generic(data, getc, ungetc);
				next++;
			}
		} else if (isspace(c)) {
			continue;
		} else if (c == '}') {
			ungetc(c, data);
			return 0;
		} else {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_action);
			string_init_empty(&tree->u.action.selector);
			ungetc(c, data);
			for (;;) {
				c = getc(data);
				if (c == EOF || c == '.' || c == ')' || c == '}') {
					if (tree->u.action.arg_count == 0 || tree->u.action.arg_indexes[tree->u.action.arg_count-1] < tree->u.action.selector.length) {
						string_trim_right(&tree->u.action.selector);
					}
					if (c == ')' || c == '}') {
						ungetc(c, data);
					}
					return tree;
				} else if (c == '"' || c == '(' || c == '{') {
					bool paren = c == '(';
					if (tree->u.action.arg_count == syntax_tree_max_args) {
						log_error("Parse error: exceed max arg count %d",
							syntax_tree_max_args);
						goto action_err;
					}
					if (c == '"' || c == '{') {
						ungetc(c, data);
					}
					struct syntax_tree *child = parse_generic(data, getc, ungetc);
					if (!child) {
						log_error("Parse error: expected argument");
						goto action_err;
					}
					//printf("Adding arg %lu at %lu\n", tree->u.action.arg_count, tree->u.action.selector.length);
					tree->u.action.arg_indexes[tree->u.action.arg_count] =
						tree->u.action.selector.length;
					tree->u.action.args[tree->u.action.arg_count] = child;
					tree->u.action.arg_count++;
					if (paren && getc(data) != ')') {
						log_error("Subexpression had no close paren.");
						goto action_err;
					}
				} else if (isspace(c)) {
					if (tree->u.action.selector.length == 0 || tree->u.action.selector.data[tree->u.action.selector.length-1] != ' '
					    || (tree->u.action.arg_count != 0 && tree->u.action.selector.length == tree->u.action.arg_indexes[tree->u.action.arg_count-1])) {
						if (!string_add_character(&tree->u.action.selector, ' ')) {
							goto action_err;
						}
					}
				} else {
					if (!string_add_character(&tree->u.action.selector, c)) {
						goto action_err;
					}
				}
			}
		action_err:
			syntax_tree_free(tree);
			return 0;
		}
	}
}

static int parse_file_getc(void *fp) {
	FILE *f = fp;
	return getc(f);
}

static void parse_file_ungetc(int c, void *fp) {
	FILE *f = fp;
	ungetc(c, f);
}

struct syntax_tree *parse(void) {
	FILE *f = stdin;
	return parse_generic(f, parse_file_getc, parse_file_ungetc);
}

struct parse_string_data {
	const char *buf;
	size_t offset;
	size_t len;
};

static int parse_string_getc(void *datap) {
	struct parse_string_data *data = datap;
	if (data->offset == data->len) {
		return EOF;
	} else {
		return data->buf[data->offset++];
	}
}

static void parse_string_ungetc(int c, void *datap) {
	struct parse_string_data *data = datap;
	if (data->offset != 0) {
		data->offset--;
		if (data->buf[data->offset] != c) {
			log_error("Ungetc of the wrong character: 0x%x vs. 0x%x",
			          data->buf[data->offset], c);
		}
	}
}

struct syntax_tree *parse_string(const char *s) {
	struct parse_string_data data;
	data.buf = s;
	data.offset = 0;
	data.len = strlen(s);
	return parse_generic(&data, parse_string_getc, parse_string_ungetc);
}
