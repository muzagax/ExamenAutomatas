all: run

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexer.flex
	flex lexer.flex

run: lex.yy.c parser.tab.c
	g++ -o run parser.tab.c lex.yy.c -std=c++11

clear:
	rm run parser.tab.c lex.yy.c parser.tab.h
