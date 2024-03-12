#!/bin/bash

cd src

LEXER_FILE="lexer.lex"
PARSER_FILE="parser.y"



lex $LEXER_FILE
bison -d $PARSER_FILE


cc -o ../build/myCalc main.c polynom.c lex.yy.c parser.tab.c  -lm


echo "Сборка завершена."
