if exists("b:current_syntax")
	finish
endif

syn match caleinNumber '#-\?\d\+'
syn region caleinString start='"' end='"' skip='\\["\\]'
syn match caleinSequenceDelimiter '[{}]'
syn match caleinSubActionDelimiter '[()]'
syn match caleinStatementTerminator '\.'

let b:current_syntax = "calein"

hi def link caleinString String
hi def link caleinNumber Number
hi def link caleinSequenceDelimiter Delimiter
hi def link caleinSubActionDelimiter Delimiter
hi def link caleinStatementTerminator Special
