#ifndef POLYNOM_H
#define POLYNOM_H
// #include <ctype.h>
#include <stdint.h>
#define YYSTYPE uint64_t
#include <stdio.h>
#include <malloc.h>
typedef struct polynomMember
{
    char base;
    int factor;
    int degree;
    struct polynomMember* nextMember;   
} polynomMember;



polynomMember* createPolynom(int initFactor, int initDegree, char initBase);
void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void multiplePolynomByFactor(polynomMember* firstPolynom, int factor);
void powPolynom(polynomMember* polynom, int deg);
void printPolynom(polynomMember* polynom);
void checkPolynomBases(polynomMember* firstPolynom, polynomMember* secondPolynom);
void sortPolynom(polynomMember* poly);
void printPolynomDebug(polynomMember* poly);
void changePolynomBase(polynomMember* poly, char newBase);

#endif
