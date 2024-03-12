#ifndef POLYNOM_H
#define POLYNOM_H
#include <ctype.h>
#define YYSTYPE __uint64_t
#include <stdio.h>
#include <malloc.h>
typedef struct polynomMember
{
    int factor;
    int degree;
    struct polynomMember* nextMember;   
} polynomMember;



polynomMember* createPolynom(int initFactor, int initDegree);
void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void multiplePolynomByFactor(polynomMember* firstPolynom, int factor);
void powPolynom(polynomMember* polynom, int deg);
void printPolynom(polynomMember* polynom);

#endif
