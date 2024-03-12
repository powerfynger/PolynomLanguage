%{
    #include <stdio.h>
    #include <math.h>
    #include "polynom.h"
    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }
    
//     typedef struct polynomMember
// {
//     int factor;
//     int degree;
//     struct polynomMember* nextMember;   
// } polynomMember;

  polynomMember* polynomsGlobal[128];
  int polynomsGlobalCount = 0;
%}

%token NUM

%%

EXPRESSION:     POLYNOM 
                { 
                  printPolynom($$); 
                }

POLYNOM:        FACTOR
                {
                  $$ = $1;
                  printf("From factor to poly\n");
                }
                | POLYNOM '+' FACTOR 
                {
                  printf("From poly + factor to poly\n");
                  summPolynom($1, $3);
                  $$ = $1;
                }
                | POLYNOM '-' FACTOR 
                {
                  printf("From poly + factor to poly\n");
                  substractPolynom($1, $3);
                  $$ = $1;
                }
                | POLYNOM '*' POLYNOM
                {
                  printf("From POLYNOM * POLYNOM to POLYNOM\n");
                  
                  $$ = multiplePolynomByPolynom($1, $3);
                }
                
;

FACTOR:         POWER_X
                {
                  printf("From power_x to factor\n");
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

POWER_X:        
                 POWER_X '^' POWER 
                {
                  printf("From power_x ^ power:%d to power_x\n", $3);
                  powPolynom($1, $3);
                  $$ = $1;
                }
                | POWER
                {
                  printf("From power to power_x\n");
                  $$ = createPolynom($1, 0);
                  
                }
                | 'x'
                {
                  printf("Init x\n");
                  $$ = createPolynom(1, 1);
                }
                | POWER POWER_X
                {
                  multiplePolynomByFactor($2, $1);
                  $$ = $2;
                }
                | '(' POLYNOM ')'
                {
                  printf("From polynom to power_x\n");
                  $$ = $2;
                }
                |  POWER_X '*' POWER_X
                {
                  printf("From power_x * power_x to power_x\n");
                  
                  $$ = multiplePolynomByPolynom($1, $3);
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