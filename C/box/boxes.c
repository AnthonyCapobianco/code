#include "boxes.h"

static unsigned char
didDrawLine(unsigned int *boxLength)
{
    for (unsigned int i = 0; i < *boxLength; i++) printf(P_BOX_HORIZONTAL_LINE);
    return(1);
}

static void
drawLine(unsigned int *boxLength, POSITION isBottom)
{
    if (isBottom) printf(P_BOX_BOTTOM_LEFT);
    else printf(P_BOX_TOP_LEFT); 
    
    if (didDrawLine(boxLength) && isBottom) puts(P_BOX_BOTTOM_RIGHT); 
    else puts(P_BOX_TOP_RIGHT);
}

static void
printLine(char *stringPtr)
{
    printf(P_BOX_VERTICAL_LINE "%*c%s%*c", 5, ' ', stringPtr, 5, ' '); puts(P_BOX_VERTICAL_LINE);
}

extern void
_closedBox(const int variableArgumentsCount, ...)
{
    va_list variableArgumentPointer; 
    
    int i = 0;
    
    static char **stringPointer; 
    static unsigned int boxLength;
    
    va_start(variableArgumentPointer, variableArgumentsCount);
         
    while (variableArgumentsCount >= i++)
    {
        stringPointer = va_arg(variableArgumentPointer, char**);
        
        boxLength = strlen(*(stringPointer));
        
        drawLine(&boxLength, P_TOP); 
    
        printLine(*stringPointer);
    
        drawLine(&boxLength, P_BOTTOM);
    }
    
    va_end(variableArgumentPointer);
}
int main(void)
{
        _closedBox(1, (char*[]) {"string", "arg2"});
}