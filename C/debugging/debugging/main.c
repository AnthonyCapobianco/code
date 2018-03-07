/* Fonction qui à partir d’un nombre entier positif reçu en paramètre calcul et affiche sa valeur binaire. */
#include <stdio.h>

void printBinaryFromUint(unsigned int numberToConvertToBinary);

int
main(void)
{
    printBinaryFromUint(10);
    return(0);
}

void printBinaryFromUint(unsigned int numberToConvertToBinary)
{
    static unsigned char i
                       , j
                       ;

    static unsigned char valueOfIWhenLastTrueBit = 0;

    static unsigned int localCopyOfTheNumberToConvert; localCopyOfTheNumberToConvert = numberToConvertToBinary;

    static char binaryRepresentationOfTheNumber[33];

    while (i++ < 33)
    {
        if (localCopyOfTheNumberToConvert & 1) valueOfIWhenLastTrueBit = 32 - i;

        binaryRepresentationOfTheNumber[(32 - (int) i)] = (localCopyOfTheNumberToConvert & 1) + '0';

        localCopyOfTheNumberToConvert >>= 1;
    }

    /* Remove leading zeros */
    while (j++ < 33)
    {
        if ((valueOfIWhenLastTrueBit + j) < 33)
            binaryRepresentationOfTheNumber[j] = binaryRepresentationOfTheNumber[valueOfIWhenLastTrueBit + j];

        else
        {
            binaryRepresentationOfTheNumber[j] = 0;
            break;
        }
    }

    printf("%s", binaryRepresentationOfTheNumber);

}
