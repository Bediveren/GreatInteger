#include <stdio.h>
#include <stdlib.h>
#include "greatInt.h"


int main()
{
    greatInt a= greatIntInitialise("1123581321");  // 10^9

    greatInt b= greatIntInitialise("123456789");

    fprintf(stdout, "a:");
    greatIntPrint(stdout, a);

    fprintf(stdout, "\nb: ");
    greatIntPrint(stdout, b);

    greatInt sum = greatIntAdd(a, b);
    greatInt mul = greatIntMul(a, b);
    greatInt div = greatIntDiv(a, b);
    greatInt mod = greatIntMod(a, b);
    fprintf(stdout, "\nSum: \n");
    greatIntPrint(stdout, sum);
    fprintf(stdout, "\nMultiplication: \n");
    greatIntPrint(stdout, mul);
    fprintf(stdout, "\nDivision: \n");
    greatIntPrint(stdout, div);
    fprintf(stdout, "\nModulus: \n");
    greatIntPrint(stdout, mod);
    fprintf(stdout, "\n");

    greatIntFree(a);
    greatIntFree(b);
    greatIntFree(sum);
    greatIntFree(div);
    greatIntFree(mod);
    return 0;
}
