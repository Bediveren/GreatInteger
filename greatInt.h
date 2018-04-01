#ifndef FILE_greatInt_SEEN
#define FILE_greatInt_SEEN
#include <stdio.h>
#define greatIntError NULL
#define greatIntNegative 1

typedef struct numberHead{
    struct number* first;
    struct number* last;
    short sign;
}bigInt;

typedef bigInt* greatInt;

typedef struct number{
    struct number* next;
    struct number* prev;
    short digit;
}number;


// Prints the greatInt variable to given destination
// e.g greatIntPrintf(stdout, greatIntVariable);
void greatIntPrint(FILE*, greatInt );


//Frees dynamically allocated memory for greatInt;
// e.g greatIntFree(greatIntVariable);
void greatIntFree(greatInt*);


// Inverts the value of a greatInt by changing variable sign value;
// e.g. greatIntInvert(greatIntVariable);
void greatIntInvert(greatInt);


// Compares two greatInt variables. Returns -1,0,1 if first variable is accordingly lower,equal,higher than the second variable.
// e.g. if(greatIntComapre(greatIntVariable1, greatIntVariable2) == 0) printf("The values are equal");
// in case of an error, -2 is returned.
int greatIntCompare(greatInt, greatInt);


// Returns initialised greatInt variable.
// e.g. greatInt a = greatIntInitialise("123456");
greatInt greatIntInitialise(char[]);


// Sums two varuables of type greatInt, returns a new dynamically allocated greatInt value.
// NOTE! If used to overwrite the old value of a greatInt, the old value must be free'd first.
// e.g.
/*
...
greatInt c = b;                 //Saving the value we want to overwrite
b = greatIntAdd(a,b);
greatIntFree(c);
*/
greatInt greatIntAdd(greatInt,greatInt);


// Subtracts two varuables of type greatInt, returns a new dynamically allocated greatInt value.
// NOTE! If used to overwrite the old value of a greatInt, the old value must be free'd first.
// e.g.
/*
...
greatInt c = b;                 //Saving the value we want to overwrite
b = greatIntSub(a,b);
greatIntFree(c);
*/
greatInt greatIntSub(greatInt,greatInt);


// Multiplies two varuables of type greatInt, returns a new dynamically allocated greatInt value.
// NOTE! If used to overwrite the old value of a greatInt, the old value must be free'd first.
// e.g.
/*
...
greatInt c = b;                 //Saving the value we want to overwrite
b = greatIntMul(a,b);
greatIntFree(c);
*/
greatInt greatIntMul(greatInt, greatInt);


// Divides two varuables of type greatInt, returns a new dynamically allocated greatInt value.
// NOTE! If used to overwrite the old value of a greatInt, the old value must be free'd first.
// e.g.
/*
...
greatInt c = b;                 //Saving the value we want to overwrite
b = greatIntDiv(a,b);
greatIntFree(c);
*/
greatInt greatIntDiv(greatInt, greatInt);

// Divides two varuables of type greatInt, returns modulus (always positive) in a new dynamically allocated greatInt value.
// NOTE! If used to overwrite the old value of a greatInt, the old value must be free'd first.
// e.g.
/*
...
greatInt c = b;                 //Saving the value we want to overwrite
b = greatIntMod(a,b);
greatIntFree(c);
*/
greatInt greatIntMod(greatInt, greatInt);

#endif
