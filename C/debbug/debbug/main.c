/* 06/03/2018
 *
 * Ecrire une fonction qui à partir d'un nombre hexadécimel reçu en paramètre
 * calcule et affiche sa valeur en base 10
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char HEX_LOOKUP_TABLE[17] = "0123456789abcdef";

unsigned int printUintFromHexadecimal(const char*);

int
main(void)
{
    printf("%d", printUintFromHexadecimal("ff"));

    return 0;
}

unsigned int
printUintFromHexadecimal(const char *HEX_STRING)
{
    unsigned int stringLength = strlen(HEX_STRING) + 1;

    int i
      , j
      ;

    static unsigned int decimalSum;

    static char *hexStringReverseCopy; hexStringReverseCopy = malloc(stringLength);

    /* Reverse the string. */
    hexStringReverseCopy[stringLength] = 0;
/*
    for (i = 0, j = (stringLength - 1); i < stringLength; i++, j--)
    {
        if (HEX_STRING[j] == 'x' || HEX_STRING[j] == 'X') break;
        else hexStringReverseCopy[i] = tolower(HEX_STRING[j]);
    }
*/
    /* Now we check the values and add them to the decimalSum */
    for (unsigned int mult = 1, i = 0; i < stringLength; i++, mult *= 16)
    {
        if (hexStringReverseCopy[i] == HEX_LOOKUP_TABLE[i]) decimalSum += (i * mult);
    }

    free(hexStringReverseCopy);

    return decimalSum;
}

