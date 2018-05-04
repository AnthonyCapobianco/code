/* 05/03/2018 */
#include <stdio.h>  /* Standard header */
#include <stdlib.h>
#include <string.h>
//#include "header.h" /* Project header */

typedef int CustomType;

int /* Type (and storage) of a function */
main(int argc, char *argv[]) /* function declaration */ 
{       /* Braces on a new line */
        
        /* 8 spaces. No tabs. */
        
/* 
!* IMPORTANT COMMENTS        
!*
!* DESCRIPTION: This is an important comment.
!*
!*/
        
        /* Descriptive comment */
        
        /* Dont' use local typedefs */
        //typedef unsigned char Bool//
        
        /* Local function declarations. 1 line */
        void foo(int);
        /* Or */
        void foo(int bar);
        
        /* Local variables */
        int i
          , j
          , k
          ; 
        
        int userNumber;
        
        int x = 0
          , y = 10
          ;
        
        char userInputBuffer[40];
        char *endPtr;
        
        char *copyOfUserInputBuffer; 
        
        unsigned long xPosition = 0
                    , yPosition = 5
                    ;
        
        /* 
         * malloc isn't cast.
         * Here i'm using a function on a variable then I define it's value. 
         * In this case try and keep it on a single line. 
         */
        copyOfUserInputBuffer = malloc(strlen(userInputBuffer) + 1); strcpy(copyOfUserInputBuffer, userInputBuffer);
        
        /* Function like macros are declare before using them is they are only used in the scope */
        /* Constant values and defines are in ALL CAPS */
        #define PRINT_SINGLE_INT(int) printf("%i", int)
        
        PRINT_SINGLE_INT(y);
        
/* GO TO header. <WHERE>_<WHAT IT POINTS TO>_<WHAT IT DOES> */        
MAIN_IF_X_EQUAL_Y_GOTO:
        
        /* If if statement and expression fit on one line use that */
        if (x == y) goto MAIN_IF_X_EQUAL_Y_GOTO;
        else
        {
                /* Use brakets */
        }
        
        /* When checking for an error. Check it isn't an error instead */
        if (!fgets(userInputBuffer, 40, stdin))
        {
                fprintf(stderr, "ERROR: THIS IS AN ERROR MESSAGE (END OF FILE)");
                exit(EXIT_FAILURE);
        }
        else 
        {
                while (0) if (x == y) goto MAIN_IF_X_EQUAL_Y_GOTO;
                while (1)
                {
                        /* Do stuff */
                        break;
                }
                
                for (i = 0; i < y; i++) printf("printed %i times\n", (i + 1));
                
                switch (i) 
                {
                        case 9:
                        {
                                i++;
                                break; 
                        }
                        default: break;	
                }
                
                do printf("%i", i); while (0);
                do
                {
                        /* More stuff */
                        break;
                } while (0);
        }
        
        /* No parenthesis when returning a literal */
        return 0;
}