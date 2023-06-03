MM_HEADERS:=clock_mini.h
MM_TESTS:=test

test.c:=test.c
test-:=-Wl,--wrap=malloc,--wrap=free,--wrap=main
test-I:=../test-mini/ ./
test-L:=../test-mini/
test-l:=test-mini

include makefile_mini.mk
