#include <stdlib.h>
#include <stdio.h>
#include "greatInt.h"


int validNumberFormat(char[]);
int checkIfZero(greatInt);

int greatIntMulSign(greatInt numberHead1, greatInt numberHead2)
{
    if(numberHead1->sign == greatIntNegative)
    {
        if(numberHead2->sign == greatIntNegative)
        {
            return 0;
        }
        else
        {
            return greatIntNegative;
        }
    }
    else
    {
        if(numberHead2->sign == greatIntNegative)
        {
            return greatIntNegative;
        }
        else
        {
            return 0;
        }
    }

}

greatInt greatIntStore(char numberString[], greatInt numberHead)
{
    int i = 0;
    number* singleDigit = NULL;
    number* tempDigit = NULL;
    if(numberString[0] == '-')
    {
        numberHead->sign = greatIntNegative;
        i++;
    }
    else
    {
        numberHead->sign = 0;
    }
    singleDigit = (number*) malloc(sizeof(number));
    singleDigit->next = NULL;
    singleDigit->prev = NULL;
    singleDigit->digit =numberString[i] - '0';
    numberHead->first = singleDigit;
    i++;
    while(numberString[i])
    {
        tempDigit = (number*) malloc(sizeof(number));
        singleDigit->next = tempDigit;
        tempDigit->prev = singleDigit;
        tempDigit->next = NULL;
        tempDigit->digit = numberString[i] - '0';
        singleDigit = tempDigit;
        i++;
    }
    numberHead->last = singleDigit;

    return numberHead;
}

greatInt greatIntInitialise(char numberString[])
{
    if(validNumberFormat(numberString))
    {
        greatInt numberHead = (greatInt) malloc(sizeof(bigInt));
        if(numberHead == NULL)
        {
            return NULL;
        }
        numberHead->first = NULL;
        numberHead->last = NULL;
        numberHead = greatIntStore(numberString, numberHead);
        return numberHead;
    }
    else return NULL;
}



int validNumberFormat(char numberString[])
{
    int i = 0;
    if (numberString[i])
    {
        if(numberString[i] == '0' && numberString[i+1] != '\0')
        {
            return 0;
        }
        else if (numberString[i] == '-')
        {
            if(numberString[i+1] == '\0')
            {
                return 0;
            }
            i++;

        }

        for(; numberString[i];i++)
        {
            if(numberString[i] > '9' || numberString[i] < '0')
            {
                return 0;
            }
        }

        return 1;
    }
    else return 0;

}

void greatIntFree(greatInt* tempHead)
{
    greatInt numberHead = &tempHead;
    if(numberHead != NULL)
    {
        number* tempNumber;
        tempNumber = numberHead->first;
        while(tempNumber->next != NULL)
        {
            tempNumber = tempNumber->next;
            free(tempNumber->prev);
        }
        free(tempNumber);
        free(numberHead);
    }

}

void greatIntPrint(FILE *fp, greatInt numberHead)
{
    if(numberHead != NULL)
    {
        number* tempNumber;
        tempNumber = numberHead->first;
        if(numberHead->sign == greatIntNegative)
        {
            fprintf(fp, "%c", '-');
        }
        do
        {
            fprintf(fp, "%d", tempNumber->digit);
            tempNumber = tempNumber->next;
        }while(tempNumber != NULL);
    }

}

int greatIntCompare(greatInt numberHead1, greatInt numberHead2)
{
    if(numberHead1 != NULL && numberHead2 != NULL)
    {
        if(numberHead1->sign == numberHead2->sign)
        {
            int firstBiggerDigitValue = 0;
            number* tempNumber1 = numberHead1->first;
            number* tempNumber2 = numberHead2->first;
            while(tempNumber1 != NULL && tempNumber2 != NULL)
            {
                if(firstBiggerDigitValue == 0)
                {
                    if(tempNumber1->digit > tempNumber2->digit)
                    {
                        firstBiggerDigitValue = 1;
                    }
                    else if (tempNumber1->digit < tempNumber2->digit)
                    {
                        firstBiggerDigitValue = 2;
                    }
                }
                tempNumber1 = tempNumber1->next;
                tempNumber2 = tempNumber2->next;
            }
            if(tempNumber1 == NULL)
            {
                if(tempNumber2 == NULL)
                {
                    if(firstBiggerDigitValue == 1)
                    {
                        return 1;
                    }
                    else if(firstBiggerDigitValue == 2)
                    {
                        return -1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else if (tempNumber2 == NULL)
            {
                return 1;
            }
        }
        else
        {
            if(numberHead1->sign == 1)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

    }
    return -2;
}

void greatIntInvert(greatInt numberHead)
{
    if(numberHead != NULL)
    {
        if(numberHead->last->digit == 0)
        {
            if(numberHead->last->prev == NULL)
            {
                return;
            }
        }
        if(numberHead->sign == greatIntNegative)
        {
            numberHead->sign = 0;
        }
        else
        {
            numberHead->sign = greatIntNegative;
        }
    }
}

void greatIntToPowerOfTen(greatInt numberHead, int power)
{
    if(numberHead != NULL)
    {
        while(power > 0)
        {
            power--;
            number* tempDigit = (number*) malloc(sizeof(number));
            tempDigit->prev = numberHead->last;
            numberHead->last->next = tempDigit;
            tempDigit->next = NULL;
            tempDigit->digit = 0;
            numberHead->last = tempDigit;
        }
    }

}

greatInt adjustGreatIntHead(greatInt numberHead, number* tempNumber)
{
    if(numberHead->first == NULL && numberHead->last == NULL)
    {
        numberHead->last = tempNumber;
    }
    numberHead->first = tempNumber;

    return numberHead;
}

greatInt greatIntMul(greatInt numberHead1, greatInt numberHead2)
{
    if(numberHead1 != NULL && numberHead2 != NULL)
    {
        if(checkIfZero(numberHead1) || checkIfZero(numberHead2))
        {
            return greatIntInitialise("0");
        }
    greatInt result = greatIntInitialise("0");
    result->sign = 0;

    //Numbers
    number* firstMulNumber = numberHead1->last;
    number* secondMulNumber = numberHead2->last;
    long long int position = 0;

    while(secondMulNumber != NULL)
    {
        int overflow = 0;
        // Temporary greatInt
        greatInt tempGreatInt = (greatInt) malloc(sizeof(bigInt));
        tempGreatInt->first = NULL;
        tempGreatInt->last = NULL;
        tempGreatInt->sign = 0;

        // First greatInt number place
        number* firstNumberPlace = NULL;


        while(firstMulNumber!= NULL)
        {
            int numberMulMod = (firstMulNumber->digit * secondMulNumber->digit + overflow) % 10;
            //printf("%d <-- numberMulMod", numberMulMod);
            overflow = (firstMulNumber->digit * secondMulNumber->digit + overflow) / 10;
            //printf("%d <-- overflow", overflow);
            number* tempNumber = (number*) malloc(sizeof(number));
            tempNumber->prev = NULL;
            tempNumber->next = firstNumberPlace;
            tempNumber->digit = numberMulMod;

            tempGreatInt = adjustGreatIntHead(tempGreatInt, tempNumber);

            if(firstNumberPlace != NULL)
            {
                firstNumberPlace->prev = tempNumber;
            }
            firstNumberPlace = tempNumber;
            firstMulNumber = firstMulNumber->prev;
        }
        if(overflow > 0)
        {
            number* overflowNumber = (number*) malloc(sizeof(number));
            overflowNumber->prev = NULL;
            overflowNumber->next = firstNumberPlace;
            overflowNumber->digit = overflow;
            firstNumberPlace->prev = overflowNumber;
            tempGreatInt = adjustGreatIntHead(tempGreatInt, overflowNumber);
        }
        greatIntToPowerOfTen(tempGreatInt, position);
        greatInt oldGreatInt = result;
        result = greatIntAdd(result, tempGreatInt);
        greatIntFree(oldGreatInt);
        greatIntFree(tempGreatInt);


        firstMulNumber = numberHead1->last;
        secondMulNumber = secondMulNumber->prev;
        position++;
    }
        result->sign = greatIntMulSign( numberHead1, numberHead2);
        return result;
    }
    else
    {
        return NULL;
    }
}

int checkIfZero(greatInt a)                             /*Check if Value == 0 */
{
    if( (a->last->prev == NULL) && (a->last->digit == 0) )
    {
        return 1;
    }
    return 0;
}

int greatIntCompareUnsigned(greatInt a, greatInt b)     /*Comparing unsigned greatInts*/
{
    short aSign = 0;                                    // setting sign storage, and making both unsigned
    short bSign = 0;
    if(a->sign)
    {
        aSign = greatIntNegative;
        a->sign = 0;
    }
    if(b->sign)
    {
        bSign = greatIntNegative;
        b->sign = 0;
    }
    int direction = greatIntCompare(a,b);               //calling the compare and returning old sign values
    a->sign = aSign;
    b->sign = bSign;
    return direction;
}

greatInt greatIntAdd(greatInt a, greatInt b)            /*Addition*/
{
    if(a == NULL || b == NULL)                          //checking if a or b are not NULL
    {
        return NULL;
    }
    greatInt c;
    if (a->sign != b->sign)                             //checking sign if not equal using subtraction
    {
        if(a->sign == greatIntNegative)
        {
            a->sign = 0;
            c = greatIntSub (b,a);
            a->sign = greatIntNegative;
        }
        else
        {
            b->sign = 0;
            c = greatIntSub (a,b);
            b->sign = greatIntNegative;
        }
        int direction = greatIntCompareUnsigned(a,b);   //checking for which sign should be returned
        if (direction == 0)
        {
            return c;
        }
        else if(direction == greatIntNegative)
        {
            c->sign = a->sign;

        }
        else
        {
            c->sign = b->sign;
        }
        return c;
    }
    else                                                //addition if sings match
    {
        short d = 0;
        c = (greatInt) malloc(sizeof(bigInt));
        number* cCurrent = (number*) malloc(sizeof(number));
        c->sign = a->sign;
        c->last = cCurrent;
        cCurrent->next = NULL;
        number* aTemp = a->last;
        number* bTemp = b->last;
        while ( (aTemp != NULL) && (bTemp != NULL) )    //while a and b digit place is not empty adding up and carrying over d
        {
            cCurrent->digit = (aTemp->digit + bTemp->digit + d) % 10;
            d = (aTemp->digit + bTemp->digit + d) / 10;
            aTemp = aTemp->prev;
            bTemp = bTemp->prev;
            if ( (aTemp != NULL) || (bTemp != NULL) )
            {
                cCurrent->prev = (number*) malloc(sizeof(number));
                cCurrent->prev->next = cCurrent;
                cCurrent = cCurrent->prev;
            }
        }
        while ( (aTemp != NULL) || (bTemp != NULL) )    //while a or b digit place is not empty copying and carrying over d
        {
            if (aTemp != NULL)
            {
                cCurrent->digit = (aTemp->digit + d) % 10;
                d = (aTemp->digit + d) / 10;
                if ( ((aTemp = aTemp->prev) != NULL) )
                {
                    cCurrent->prev = (number*) malloc(sizeof(number));
                    cCurrent->prev->next = cCurrent;
                    cCurrent = cCurrent->prev;
                }
            }
            else if(bTemp != NULL)
            {
                cCurrent->digit = (bTemp->digit + d) % 10;
                d = (bTemp->digit + d) / 10;
                if ( ((bTemp = bTemp->prev) != NULL) )
                {
                    cCurrent->prev = (number*) malloc(sizeof(number));
                    cCurrent->prev->next = cCurrent;
                    cCurrent = cCurrent->prev;
                }
            }
        }
        if (d != 0)                                     //if carrying over d after both a and b ended
        {
            cCurrent->prev = (number*) malloc(sizeof(number));
            cCurrent->prev->next = cCurrent;
            cCurrent = cCurrent->prev;
            cCurrent->digit = 1;
        }
        cCurrent->prev = NULL;
        c->first = cCurrent;
        return c;
    }
}

greatInt greatIntSub(greatInt a, greatInt b)            /*Subtraction*/
{
    if(a == NULL || b == NULL)                          //checking to see if a or b are not NULL
    {
        return NULL;
    }
    greatInt c;
    int direction = greatIntCompareUnsigned(a,b);
    if (direction == 0)                                 //if a and b equal unsigned
    {
        if (a->sign == b->sign)                         //if sign equal then answer 0 -a-(-b) or a-b
        {
            c = greatIntInitialise("0");
            return c;
        }
        else if(a->sign && !b->sign)                    //if a signed and b unsigned add them up -a-b
        {
            b->sign = greatIntNegative;
            c = greatIntAdd (a,b);
            b->sign = 0;
            return c;
        }
        else                                            //else b is signed and a unsigned add them up a-(-b)
        {
            b->sign = 0;
            c = greatIntAdd (a,b);
            b->sign = greatIntNegative;
            return c;
        }
    }
    else if (a->sign != b->sign)                        //if a sign not equal b add them up a-(-b) or -a-b
    {
        if(a->sign)                                     //if a is signed then b unsigned add them up -a-b
        {
            b->sign = greatIntNegative;
            c = greatIntAdd (a,b);
            b->sign = 0;
            return c;
        }
        else                                           //else a is unsigned then b signed add them up a-(-b)
        {
            b->sign = 0;
            c = greatIntAdd (a,b);
            b->sign = greatIntNegative;
            return c;
        }
    }
    else                                                //else sings equal so a-b or -a-(-b)
    {
        c = greatIntInitialise("0");
        number* cCurrent = c->last;
        short d = 0;
        number* aTemp;
        number* bTemp;
        if(direction == 1)                              // if unsigned a>b then c = a-b with a sign
        {
            aTemp = a->last;
            bTemp = b->last;
            c->sign = a->sign;
        }
        else                                            // else unsigned b>a then c = b-a with b sign (inverting a=b and b=a)
        {
            aTemp = b->last;
            bTemp = a->last;
            if (b->sign)
            {
                c->sign = 0;
            }
            else
            {
                c->sign = greatIntNegative;
            }

        }
        while ( (aTemp != NULL) && (bTemp != NULL) )    // while a and b digit places not empty subtracting and borrowing with d
        {
            cCurrent->digit = (aTemp->digit - bTemp->digit - d) % 10;
            if (cCurrent->digit < 0)
            {
                d = 1;
                cCurrent->digit += 10;
            }
            else
            {
                d = 0;
            }
            aTemp = aTemp->prev;
            bTemp = bTemp->prev;
            if ( (aTemp != NULL) || (bTemp != NULL) )   //if a or b digit place not NULL we take new c digit place
            {
                cCurrent->prev = (number*) malloc(sizeof(number));
                cCurrent->prev->next = cCurrent;
                cCurrent = cCurrent->prev;
            }
        }
        while ( (aTemp != NULL) )                       //because a>b all the time while a digit place not NULL we borrow
        {
            cCurrent->digit = (aTemp->digit - d) % 10;
            if (cCurrent->digit < 0)
            {
                d = 1;
                cCurrent->digit += 10;
            }
            else
            {
                d = 0;
            }
            if ( ((aTemp = aTemp->prev) != NULL) )      // if there is sill digit places left initiate new c digit places
            {
                cCurrent->prev = (number*) malloc(sizeof(number));
                cCurrent->prev->next = cCurrent;
                cCurrent = cCurrent->prev;
            }
        }
        while ( (cCurrent->digit == 0) && (cCurrent->next != NULL ) )   // if we get highest value digit 0 by subtraction we remove it and check next one
        {
            cCurrent = cCurrent->next;
            free(cCurrent->prev);
            cCurrent->prev = NULL;
        }
        cCurrent->prev = NULL;
        c->first = cCurrent;
        return c;
    }
}

greatInt greatIntDivision(greatInt a, greatInt b, int mod) /*Division returning divident or modulus */
{
    greatInt c;
    int direction;
    c = greatIntInitialise("0");                    //initialise answer with 0;
        number* cCurrent = c->first;
        if (a->sign == b->sign)                         //setting answer sign;
        {
            c->sign = 0;
        }
        else
        {
            c->sign = greatIntNegative;
        }
        greatInt aTemp = (greatInt) malloc(sizeof(bigInt)); //initialising required temporary a and digit place pointers for a and b
        number* aTempCurrent = (number*) malloc(sizeof(number));
        number* aCurrent = a->first;
        number* bCurrent = b->first;
        greatInt modTemp;                               //to keep modulus after each subtraction
        aTemp->first = aTempCurrent;
        aTemp->sign = 0;
        aTempCurrent->prev = NULL;
        short bSign = 0;
        if (b->sign)
        {
            b->sign = 0;
            bSign = greatIntNegative;
        }
        while(bCurrent != NULL)                         //while b digit place is not NULL we get temporary a to match digit places with b
        {
            aTempCurrent->digit = aCurrent->digit;
            aCurrent = aCurrent->next;
            bCurrent = bCurrent->next;
            if(bCurrent != NULL)                        //if not b end initialise new aTemp digit place
            {
                aTempCurrent->next = (number*) malloc(sizeof(number));
                aTempCurrent->next->prev = aTempCurrent;
                aTempCurrent = aTempCurrent->next;
            }
        }
        aTempCurrent->next = NULL;                      //closing out aTemp
        aTemp->last = aTempCurrent;
        direction = greatIntCompareUnsigned(aTemp,b);   // checking if aTemp >b
        if (direction == -1)                            //if aTemp < b we add another digit to a
            {
                aTempCurrent->next = (number*) malloc(sizeof(number));
                aTempCurrent->next->prev = aTempCurrent;
                aTempCurrent = aTempCurrent->next;
                aTempCurrent->digit = aCurrent->digit;
                aTempCurrent->next = NULL;
                aTemp->last = aTempCurrent;
                aCurrent = aCurrent->next;
            }
        direction = greatIntCompareUnsigned(aTemp,b);
        do
        {
            while(direction >= 0)                       //while aTemp >= b we subtract aTemp - b and increase c and get new aTemp after subtraction;
            {
                modTemp = greatIntSub(aTemp,b);
                greatIntFree(aTemp);
                aTemp = modTemp;
                cCurrent->digit += 1;
                direction = greatIntCompareUnsigned(aTemp,b);
            }
            if ((checkIfZero(aTemp) == 1) && (aCurrent != NULL)) // if aTemp is 0 and aCurrent is not NULL then change the current digit with aCurrent digit
            {
                aTempCurrent = aTemp->last;
                aTempCurrent->digit = aCurrent->digit;
                aTempCurrent->next = NULL;
                aCurrent = aCurrent->next;
                cCurrent->next = (number*) malloc(sizeof(number));
                cCurrent->next->prev = cCurrent;
                cCurrent = cCurrent->next;
                cCurrent->digit =0;
            }
            else if (direction == -1 && (aCurrent != NULL) ) //if aTemp is less than b and a digit place is not NULL add new aTemp digit place and new c digit place
            {
                while (direction == -1 && (aCurrent != NULL))
                {
                    aTempCurrent = aTemp->last;
                    aTempCurrent->next = (number*) malloc(sizeof(number));
                    aTempCurrent->next->prev = aTempCurrent;
                    aTempCurrent = aTempCurrent->next;
                    aTempCurrent->digit = aCurrent->digit;
                    aTempCurrent->next = NULL;
                    aTemp->last = aTempCurrent;
                    aCurrent = aCurrent->next;
                    cCurrent->next = (number*) malloc(sizeof(number));
                    cCurrent->next->prev = cCurrent;
                    cCurrent = cCurrent->next;
                    cCurrent->digit =0;
                    direction = greatIntCompareUnsigned(aTemp,b);
                }
            }
        direction = greatIntCompareUnsigned(aTemp,b);
        } while ( ( direction  >= 0) || (aCurrent != NULL));
        b->sign = bSign;
        cCurrent->next = NULL;
        c->last = cCurrent;
        if (mod)                                        //checking if need to return modulus
        {
            greatIntFree(c);
            return aTemp;
        }
        else
        {
            greatIntFree(aTemp);
            return c;
        }
}

greatInt greatIntDiv(greatInt a,greatInt b)             /* Division */
{
    if(a == NULL || b == NULL)        //checking if a or b are not NULL
    {
        return NULL;
    }
    if(checkIfZero(b))
    {
        return NULL;
    }
    int direction = greatIntCompareUnsigned(a,b);
    greatInt c;
    if (direction == -1)                                //if unsigned b>a answer 0
    {
        c = greatIntInitialise("0");
        return c;
    }
    else if (direction == 0)                            //if a == b answer and signs same answer 1 if sings differ answer -1
    {
        c = greatIntInitialise("1");
        if (a->sign == b->sign)
        {
            c->sign = 0;
        }
        else
        {
            c->sign = greatIntNegative;
        }
        return c;
    }
    else                                                //else a > b so we divide
    {
        c = greatIntDivision(a,b,0);
        return c;
    }
}

greatInt greatIntMod(greatInt a,greatInt b)             /* Modulus */
{
    if(a == NULL || b == NULL)        //checking if a or b are not NULL
    {
        return NULL;
    }
    if(checkIfZero(b))
    {
        return NULL;
    }
    int direction = greatIntCompareUnsigned(a,b);
    greatInt c;
    greatInt toFree;
    if (direction == -1)                                //if unsigned b>a answer is a
    {
        c = greatIntInitialise("0");
        toFree= c;
        c = greatIntAdd(a,c);
        c->sign =0;
        greatIntFree(toFree);
        return c;
    }
    else if (direction == 0)                            //if a == b answer 0
    {
        c = greatIntInitialise("0");
        c->sign =0;
        return c;
    }
    else                                                //else a > b so we divide and ask to return modulus
    {
        c = greatIntDivision(a,b,1);
        c->sign =0;
        return c;
    }
}
