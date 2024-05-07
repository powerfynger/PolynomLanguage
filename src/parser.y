%{
    #include <stdio.h>
    #include <math.h>
    #include "polynom.h"
    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }
    

%}

%token NUM
%token LETTER
%token VAR
%define parse.error detailed
%left '+' '-' '*'


%%

OUTPUT:
    POLYNOM
    {
      printf("\n-------------END-------------\n");
      printPolynom($$);
    }



EQUATION:       VAR '=' INITIAL_POLYNOM 
                {
                  addVariable($1, $3);
                  printPolynom($3);
                  printf("=Adding new var\n");
                }
                | EQUATION VAR '=' INITIAL_POLYNOM 
                {
                  addVariable($2, $4);
                  printPolynom($4);
                  printf("=Adding new var\n");
                }

POLYNOM:        FACTOR
                {
                  $$ = $1;
                  // printPolynom($$);
                  printf("From factor to poly\n");
                }

                | EQUATION '(' POLYNOM ')'
                {
                  printf("From EQUATION ( poly to poly\n");
                  // summPolynom((polynomMember*)$3, getVariable($1));
                  printPolynom((polynomMember*)$3);
                  printf("\n\n\n");
                  $$ = $3;
                }
                | POLYNOM '+' FACTOR 
                {
                  printf("From poly + factor to poly\n");
                  summPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                }
                | POLYNOM '-' FACTOR 
                {
                  printf("From poly - factor to poly\n");
                  substractPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                }
                | POLYNOM '*' POLYNOM
                {
                  printf("From POLYNOM * POLYNOM to POLYNOM\n");
                  
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }
                | POLYNOM '+' POLYNOM
                {
                  printf("From POLYNOM + POLYNOM to POLYNOM\n");
                  printPolynom((polynomMember*)$1);
                  printf("\n\n");
                  printPolynom((polynomMember*)$3);
                                    printf("\n\n");

                  summPolynom((polynomMember*)$1, (polynomMember*)$3);
                  printPolynom((polynomMember*)$1);
                  $$ = $1;
                }
                | POLYNOM '-' POLYNOM
                {
                  printf("From POLYNOM - POLYNOM to POLYNOM\n");
                  printPolynom((polynomMember*)$1);
                  printf("\n\n");
                  printPolynom((polynomMember*)$3);
                  substractPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                  printf("\n\n");
                  printPolynom((polynomMember*)$1);

                }


;

                
FACTOR:         INITIAL_POLYNOM
                {
                  printf("From INITIAL_POLYNOM to factor\n");
                  $$ = $1;
                }


POWER:          ATOM
                {
                  printf("From atom: %d to power\n", $1);
                  $$ = $1;
                }
                | ATOM '^' POWER 
                {
                  printf("From atom:%d ^ power:%d to power: %d\n", $1,  $3, $$);
                  $$ = (int)pow($1, $3);
                }

;

INITIAL_POLYNOM:        
                 INITIAL_POLYNOM '^' POWER 
                {
                  printf("From INITIAL_POLYNOM ^ power:%d to INITIAL_POLYNOM\n", $3);
                  powPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                }
                | POWER
                {
                  printf("From power %d to INITIAL_POLYNOM\n", $1);
                  $$ = createPolynom((polynomMember*)$1, 0, 0);
                  
                }
                | LETTER
                {
                  char a = $1;
                  $$ = createPolynom(1, 1, a);
                  printf("Init base: %c\n", a);
                }
                | POWER INITIAL_POLYNOM
                {
                  multiplePolynomByFactor((polynomMember*)$2, (int)$1);
                  $$ = $2;
                }
                | '(' POLYNOM ')'
                {
                  printf("From polynom to INITIAL_POLYNOM\n");
                  $$ = $2;
                  // printPolynom($$);
                }
                |  INITIAL_POLYNOM '*' INITIAL_POLYNOM
                {
                  printf("From INITIAL_POLYNOM * INITIAL_POLYNOM to INITIAL_POLYNOM\n");
                  // printPolynom((polynomMember*)$1);
                  // printPolynom((polynomMember*)$3);
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }
                | VAR
                {
                  printPolynom(getVariable($1));
                  printf("=====From var to INITIAL_POLYNOM=====\n");
                  polynomMember* tmp = createPolynom(0, 0, 0);
                  summPolynom(tmp, getVariable($1));
                  $$ = tmp;
                }

ATOM:           NUM 
                {
                  printf("Init num: %d\n", $$);
                  $$ = $1;
                }
                | ATOM NUM 
                {
                  printf("Init new num: %d\n", $$);
                  $$ = $1*10 + $2;
                }
;

%%