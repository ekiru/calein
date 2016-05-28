#include "parser.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "err.h"
#include "str.h"
#include "syntax.h"


static size_t line = 0;
static struct syntax_tree *try_parse_following_action(struct syntax_tree *tree, void *data, int (*getc)(void *), void (*ungetc)(int, void *));

static struct syntax_tree *parse_generic(bool start_of_expression, void *data, int (*getc)(void *), void (*ungetc)(int, void *)) {
	int c;
	for (;;) {
		c = getc(data);
		if (c == EOF) {
			return 0;
		}
		if (c == '\n') {
			line++;
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
				if (c == '\n') {
					line++;
				}
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
					if (start_of_expression) {
						return try_parse_following_action(tree, data, getc, ungetc);
					} else {
						return tree;
					}
				} else {
					if (!string_add_character(&tree->u.literal, c)) {
						goto literal_err;
					}
				}
			}
		literal_err:
			syntax_tree_free(tree);
			return 0;
		} else if (c == '#') {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_number); 
			bool negative = false, start = true;
			if (!tree) {
				return 0;
			}
			for (;;) {
				c = getc(data);
				if (c == '\n') {
					line++;
				}
				if (start && c == '-') {
					negative = true;
					c = getc(data);
					if (c == '\n') {
						line++;
					}
				}
				if (start && c == EOF) {
					log_error("Unexpected EOF at beginning of numeric literal.");
					syntax_tree_free(tree);
					return 0;
				}
				if (!isdigit(c)) {
					if (c != EOF) {
						if (c == '\n') {
							line--;
						}
						ungetc(c, data);
					}
					if (negative) {
						tree->u.number *= -1;
					}
					if (start_of_expression) {
						return try_parse_following_action(tree, data, getc, ungetc);
					} else {
						return tree;
					}
				}
				tree->u.number *= 10;
				tree->u.number += c - '0';
				start = false;
			}
		} else if (c == '{') {
			struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_sequence);
			size_t next = 0;
			for (;;) {
				c = getc(data);
				if (c == '\n') {
					line++;
				}
				if (c == EOF) {
					log_error("Unexpected EOF in sequence.");
					syntax_tree_free(tree);
					return 0;
				}
				if (c == '}') {
					return tree;
				}
				ungetc(c, data);
				if (c == '\n') {
					line--;
				}
				if (next == syntax_tree_max_sequence) {
					log_error("Sequence larger than maximum length %d at line %lu", syntax_tree_max_sequence, line);
					return tree;
				}
				tree->u.sequence[next] = parse_generic(true, data, getc, ungetc);
				next++;
			}
		} else if (isspace(c)) {
			continue;
		} else if (c == '}') {
			ungetc(c, data);
			return 0;
		} else {
			ungetc(c, data);
			if (c == '\n') {
				line--;
			}
			return try_parse_following_action(0, data, getc, ungetc);
		}
	}
}

static struct syntax_tree *try_parse_following_action(struct syntax_tree *firstChild, void *data, int (*getc)(void *), void (*ungetc)(int, void *)) {
	struct syntax_tree *tree = syntax_tree_new(syntax_tree_kind_action);
	string_init_empty(&tree->u.action.selector);
	if (firstChild) {
		tree->u.action.arg_indexes[tree->u.action.arg_count] = 0;
		tree->u.action.args[tree->u.action.arg_count] = firstChild;
		tree->u.action.arg_count++;
	}
	for (;;) {
		int c = getc(data);
		if (c == EOF || c == '.' || c == ')' || c == '}') {
			if (tree->u.action.arg_count == 0 || tree->u.action.arg_indexes[tree->u.action.arg_count-1] < tree->u.action.selector.length) {
				string_trim_right(&tree->u.action.selector);
			}
			if (c == ')' || c == '}') {
				ungetc(c, data);
			}
			return tree;
		} else if (c == '"' || c == '#' || c == '(' || c == '{') {
			bool paren = c == '(';
			if (tree->u.action.arg_count == syntax_tree_max_args) {
				log_error("Parse error: exceed max arg count %d",
					syntax_tree_max_args);
				goto action_err;
			}
			if (c == '"' || c == '#' || c == '{') {
				ungetc(c, data);
			}
			struct syntax_tree *child = parse_generic(c == '(', data, getc, ungetc);
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
				log_error("Subexpression had no close paren at line %lu.", line);
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

static int parse_file_getc(void *fp) {
	FILE *f = fp;
	return getc(f);
}

static void parse_file_ungetc(int c, void *fp) {
	FILE *f = fp;
	ungetc(c, f);
}

struct syntax_tree *parse(void) {
	return parse_from_file(stdin);
}

struct syntax_tree *parse_from_file(FILE *f) {
	return parse_generic(true, f, parse_file_getc, parse_file_ungetc);
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
	return parse_generic(true, &data, parse_string_getc, parse_string_ungetc);
}
