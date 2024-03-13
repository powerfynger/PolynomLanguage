#include "polynom.h"


polynomMember* createPolynom(int initFactor, int initDegree)
{
    polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
    tmp->factor = initFactor;
    tmp->degree = initDegree;
    tmp->nextMember = NULL;
    return tmp;
}

void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    polynomMember* counter;
    counter = firstPolynom;
    while (counter->nextMember != NULL)
    {
        counter = counter->nextMember;
    }


    polynomMember* nextMemberFirst = firstPolynom->nextMember;
    
    for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
    {
        int added = 0;
        for ( polynomMember* counterTmp =  firstPolynom; counterTmp != NULL; counterTmp = counterTmp->nextMember)
        {
            if(counterTmp->degree == secondMember->degree)
            {
                counterTmp->factor += secondMember->factor;
                added = 1;
                break;
            }
        } 
        if (added) continue;

        polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
        tmp->degree = secondMember->degree;
        tmp->factor = secondMember->factor;
        tmp->nextMember = NULL;
        
        counter->nextMember = tmp;
        counter = counter->nextMember;
    }
    // printPolynom(firstPolynom);
}

void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    polynomMember* counter;
    counter = firstPolynom;
    while (counter->nextMember != NULL)
    {
        counter = counter->nextMember;
    }


    polynomMember* nextMemberFirst = firstPolynom->nextMember;
    
    for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
    {
        int added = 0;
        for ( polynomMember* counterTmp =  firstPolynom; counterTmp != NULL; counterTmp = counterTmp->nextMember)
        {
            if(counterTmp->degree == secondMember->degree)
            {
                counterTmp->factor -= secondMember->factor;
                added = 1;
                break;
            }
        } 
        if (added) continue;

        polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
        tmp->degree = secondMember->degree;
        tmp->factor = -secondMember->factor;
        tmp->nextMember = NULL;
        
        
        counter->nextMember = tmp;
        counter = counter->nextMember;
    }
    // printPolynom(firstPolynom);
}

polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{

    polynomMember* tmp = createPolynom(0, 1);

    for(polynomMember* firstMember = firstPolynom; firstMember != NULL; firstMember = firstMember->nextMember)
    {
        for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
        {
            summPolynom(tmp, createPolynom(firstMember->factor * secondMember->factor, firstMember->degree + secondMember->degree));
        }
    }
    return tmp;
}

void multiplePolynomByFactor(polynomMember* firstPolynom, int factor)
{
    firstPolynom->factor *= factor; 
    printPolynom(firstPolynom);
}

void powPolynom(polynomMember* polynom, int deg)
{
    polynom->degree *= deg;
    printf("Pow poly: ");
    printPolynom(polynom);
}

void printPolynom(polynomMember* polynom)
{
    for(polynomMember* member = polynom; member != NULL; member = member->nextMember)
    {
        if(member->factor == 0) continue;
        if (member->degree == 0)
        {
            if(member->factor >= 0) printf("+%d", member->factor);
            else printf("%d", member->factor);
        }
        else if (member->degree == 1)
        {
            if(member->factor >= 0) printf("+%dx", member->factor);
            else printf("%dx", member->factor);
        }
        else 
        {
            if(member->factor >= 0) printf("+%dx^%d", member->factor, member->degree);
            else printf("%dx^%d", member->factor, member->degree);
        }
    }
    printf("\n");
}
