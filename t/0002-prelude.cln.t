import "test".
import "prelude".

plan #51 tests.

assert (true) with label "constant true is true".
deny (false) with label "constant false is false".

assert ((true) or (true)) with label "T | T = T".
assert ((true) or (false)) with label "T | F = T".
assert ((false) or (true)) with label "F | T = T".
deny ((false) or (false)) with label "F | F = F".

assert ((true) and (true)) with label "T & T = T".
deny ((true) and (false)) with label "T & F = F".
deny ((false) and (true)) with label "F & T = F".
deny ((false) and (false)) with label "F & F = F".

define variable (l) with initial value (false).
set (l) to (#2, (l)).
set (l) to (#1, (l)).
set (l) to (#0, (l)).

assert ((l) at #0) is equal to #0 with label "at 0".
assert ((l) at #1) is equal to #1 with label "at 1".
assert ((l) at #2) is equal to #2 with label "at 2".

set (l) to (reverse list (l)).
assert ((l) at #2) is equal to #0 with label "at 0 of reversed list".
assert ((l) at #1) is equal to #1 with label "at 1 of reversed list".
assert ((l) at #0) is equal to #2 with label "at 2 of reversed list".

assert (#5 is between #3 and #6) with label "5 is between 3 and 6".
assert (#3 is between #3 and #6) with label "3 is between 3 and 6".
deny (#6 is between #3 and #6) with label "6 is not between 3 and 6".

assert (reverse string "") is equal to "" with label "reverse(\"\") is \"\"".
assert (reverse string "abc") is equal to "cba" with label "reverse(\"abc\") is \"cba\")".

assert (string of number #123) is equal to "123" with label "string of number(123)".
assert (string of number #0) is equal to "0" with label "string of number(0)".
assert (string of number #-123) is equal to "-123" with label "string of number(-123)".

define procedure (assert (digit string) is a digit) to do {
	assert ((character at #0 of (digit string)) is digit)
		with label (concat (digit string) and " is a digit").
}.
define procedure (assert (digit string) is not a digit) to do {
	deny ((character at #0 of (digit string)) is digit)
		with label (concat (digit string) and " is not a digit").
}.

assert "0" is a digit.
assert "1" is a digit.
assert "2" is a digit.
assert "3" is a digit.
assert "4" is a digit.
assert "5" is a digit.
assert "6" is a digit.
assert "7" is a digit.
assert "8" is a digit.
assert "9" is a digit.
assert "/" is not a digit.
assert ":" is not a digit.

assert (last character of "0") is equal to (character 0) with label "last character of single-character string".
assert (last character of "abcdef0") is equal to (character 0) with label "last character of seven,character string".

define variable (s) with initial value "foo".
append string "bar" to (s).
assert (s) is equal to "foobar" with label "append string _ to _".

set (s) to "foo".
assert (concat (s) and (s)) is equal to "foofoo" with label "concat _ and _".
assert (s) is equal to "foo" with label "'concat _ and _' doesn't change either arugment".

assert ((l) contains #2) with label "[2,1,0] contains 2".
assert ((l) contains #1) with label "[2,1,0] contains 1".
assert ((l) contains #0) with label "[2,1,0] contains 0".
deny ((l) contains #4) with label "[2,1,0] does not contain 4".
set (l) to ((false), (l)).
assert ((l) contains (false)) with label "[false,2,1,0] contains false".

define variable (assoc list) with initial value (false).
set (assoc list) to (("1", "a"), (assoc list)).
set (assoc list) to (("2", "b"), (assoc list)).
set (assoc list) to (("1", "c"), (assoc list)).
set (assoc list) to (("3", (false)), (assoc list)).

assert (lookup "1" in (assoc list)) is equal to "c" with label "lookup gets the first value for a key".
assert (lookup "2" in (assoc list)) is equal to "b" with label "lookup works with only a single value, too".
assert (lookup "3" in (assoc list)) is equal to (false) with label "lookup returns false if the value for the key is false".

set (assoc list) to (update key "1" to "d" in (assoc list)).
assert (lookup "1" in (assoc list)) is equal to "d" with label "updating existing keys works in assoc lists".
set (assoc list) to (update key "4" to "e" in (assoc list)).
assert (lookup "4" in (assoc list)) is equal to "e" with label "adding new keys to assoc list with update".
