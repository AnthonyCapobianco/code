//
// intio.h
// Created by Anthony Capobianco on 28/02/2018.
#include <stdio.h>
#include <stdlib.h>   /* for exit()               */
#include <string.h>   /* for strlen()             */

#ifndef _INTIO_H_INCLUDED
#define _INTIO_H_INCLUDED

#ifndef INT_MAX
#define INT_MAX +2147483647
#endif

#ifndef INT_MIN
#define INT_MIN -2147483647
#endif

#ifndef UINT_MIN
#define UINT_MIN 0
#endif

#ifndef UINT_MAX
#define UINT_MAX +4294967295
#endif

extern int getIntFromString(char**);
extern int getIntFromStdin(void);
extern unsigned int getUintFromStdin(void);

extern int printInt(int number);
extern int sumOfInts(int n1, int n2);
extern int areaOfRectangle(int length, int height);
extern int getAndPrintRectangleArea(void);
extern int smallestOfTwoNumber(int n1, int n2);
extern int smallestOfFourNumberFromStdin(void);
extern int smallestOfNNumberFromStdin(int numberOfNumbersToCompare);

#endif