import "test".

plan #12 tests.

assert #0 with label "Numbers, even #0, are true.".

assert (#0 is equal to #0) with label "Numbers are equal to themselves.".
deny (#0 is equal to #1) with label "Numbers are unequal to other numbers.".

assert ((#5 + #6) is equal to #11) with label "5 + 6 = 11".
assert ((#5 - #6) is equal to #-1) with label "5 - 6 = -1".
assert ((#5 * #6) is equal to #30) with label "5 * 6 = 30".
assert ((#12 / #6) is equal to #2) with label "12 / 6 = 2".
assert ((#13 mod #6) is equal to #1) with label "13 = 1 mod 6".

assert (#5 < #6) with label "5 < 6".
assert (#6 > #5) with label "6 > 5".
deny (#5 < #5) with label "5 !< 5".
deny (#5 > #5) with label "5 !> 5".
