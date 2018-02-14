#include <stdio.h>
#include <ctype.h>

enum { inputSize = 2 };
int checkForValues(char);
int main() 
{
    char input[inputSize];
    int result[inputSize];
    int i;

    printf("Please insert %i hexadecimal values \n", inputSize);
    for (i = 0; i < inputSize; ++i) 
    {
        scanf("%c", &input[i]);
        result[i] = checkForValues(input[i]);
        printf("Hexadecimal: %c \t Decimal: %i \n", input[i], result[i]);
    }

    return 0;
}
int checkForValues(char e)
{
    char hexValues[17] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','\0'};
    int result = 'G';
    for (int x = 0; x < 16; ++x) 
    {
        result = toupper(e) == hexValues[x] ? x : result;
    }
    if(result == 'G') printf("Value not in table");
    return result;
}
