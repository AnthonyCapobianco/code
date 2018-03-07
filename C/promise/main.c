/* 
 * This project falls under the JustDontUseItForDeviousPurposes License.
 * Any use of the promise.h header with the intent to annoy and/or
 * cause physical and/or psychological harm to anyone, including but not limited to,
 * yourself and/or other forms of life is STRICTLY prohibited.
 * Otherwise do whatever you want with it, just don't blame me afterwards.
 *
 * Note that this license only applies this project and doesn't extend to other software/library used.
 */
#include <stdlib.h>
#include <string.h>
#include "promise.h"

int 
main() 
{
        Promise_Int getIntFromStdin(void);
        Promise_Long getLongFromStdin(void);
        
        Promise_Int number = getIntFromStdin();
        
        if (number.promise) printf("%d", number.obj);
        else
        {
                puts("Something went wrong…");
                Promise_Long longNumber = getLongFromStdin();
                if (longNumber.promise) printf("%ld", longNumber.obj);
                else return EXIT_FAILURE;
                /* Here I just return EXIT_FAILURE but you could go on… */
        }
        
        return 0;
}

/* 
 * Example use case 
 * Here we want to get an integer from stdin. 
 * Imagine that another function relies on this one to get an int. 
 * How can you tell that function "hey, I failed"? Well with a int return type you can't. 
 * You have to either return an int or exit with an error. 
 * This aims to fix that problem so you can manage the error however you want.
 *
 */

Promise_Int
getIntFromStdin()
{
        Promise_Int example; 
        
        char buffer[33]
           , *endPtr
           ;
        
        long temp;
        
        if (!fgets(buffer, 33, stdin))
        {
                fprintf(stderr, "ERROR: END OF FILE");
                exit(EXIT_FAILURE);
        }
        else 
        {
                buffer[strlen(buffer) - 1] = 0;
                temp = strtol(buffer, &endPtr, 10);
                #define INT_MAX +2147483647
                #define INT_MIN -2147483647
                
                if (temp > INT_MAX || temp < INT_MIN) example.promise = FALSE;
                else
                {
                        example.obj = (int) temp;
                        example.promise = TRUE;
                }
        }
        
        return example;
}

Promise_Long
getLongFromStdin()
{
        Promise_Long example; 
        
        char buffer[33]
           , *endPtr
           ;
        
        long temp;
        
        if (!fgets(buffer, 33, stdin))
        {
                fprintf(stderr, "ERROR: END OF FILE");
                exit(EXIT_FAILURE);
        }
        else 
        {
                buffer[strlen(buffer) - 1] = 0;
                temp = strtol(buffer, &endPtr, 10);
                if (temp < 0) example.promise = FALSE;
                else
                {
                        example.obj = temp;
                        example.promise = TRUE;
                }
        }
        
        return example;
}