/* 11/03/2018 
 *
 * Fun with binary? 
 */
#include <stdio.h>
#include <stdlib.h>

int 
main(void) 
{
        int num = 10;
        
        int bin;
        
        enum _mask
        { a = 0x0007
        , b = 0x0070
        , c = 0x0700
        , d = 0x7000
        } mask;
        
        bin = 0;
        for (int i = 0; i < 4; i++)
                bin += num & (mask + i);
                
        printf("%i", bin);
        
}