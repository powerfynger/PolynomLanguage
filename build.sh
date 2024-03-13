#!/bin/bash

cd src

LEXER_FILE="lexer.lex"
PARSER_FILE="parser.y"

if [ -z "$1" ]; then
  echo "No argument provided. Usage: $0 (win|linux)"
  exit 1
fi

if [[ "$1" == "win" ]]; then
  echo "Cleaning up..."
  rm -f lex.yy.c parser.tab.c
  echo "Building..."
  flex.exe $LEXER_FILE
  bison.exe -d $PARSER_FILE
  gcc -w -o ../build/myCalc main.c polynom.c lex.yy.c parser.tab.c -lm || exit 1
  echo "Build completed."
else
  if [[ "$1" == "linux" ]]; then
    echo "Cleaning up..."
    rm -f lex.yy.c parser.tab.c
    echo "Building..."
    lex $LEXER_FILE
    bison -d $PARSER_FILE
    cc -o ../build/myCalc main.c polynom.c lex.yy.c parser.tab.c -lm || exit 1
    echo "Build completed."
  fi
fi