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
        
<<<<<<< Updated upstream
        /* Local variables */
        int i
          , j
          , k
          ; 
        
        int userNumber;
        
=======
        /* Functions with longer names: */
        unsigned int** foo_bar_baz_spam(unsigned long, char*, int*);
        
        /* Local variables */
        /* Itterrators. Either all initialise or none. */
        int i = 0
          , j = 0
          , k = 0
          ; 
        
        /* Different purpose for this int. So it's sepparated from the others. */
        int userNumber;
        
        /* Same rule. */
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
        copyOfUserInputBuffer = malloc(strlen(userInputBuffer) + 1); strcpy(copyOfUserInputBuffer, userInputBuffer);
        
        /* Function like macros are declare before using them is they are only used in the scope */
=======
        copyOfUserInputBuffer = malloc(strlen(userInputBuffer) + 1); 
        
        /* Check for malloc before doing anything */
        if (copyOfUserInputBuffer == NULL)
        {
                /* 
                 * THIS is extremely helpful when debugging. 
                 * If you have an itterator you can add it to the fprintf 
                 * to know exactly when the error occured. 
                 */
                fprintf(stderr, "ERROR: malloc returned NULL in file '%s' at line: %i !", __FILE__, __LINE__);
                exit(EXIT_FAILURE);
        }
        
        strcpy(copyOfUserInputBuffer, userInputBuffer);
        
        /* Function like macros are declare before using them if they are only used in the scope */
>>>>>>> Stashed changes
        /* Constant values and defines are in ALL CAPS */
        #define PRINT_SINGLE_INT(int) printf("%i", int)
        
        PRINT_SINGLE_INT(y);
        
<<<<<<< Updated upstream
/* GO TO header. <WHERE>_<WHAT IT POINTS TO>_<WHAT IT DOES> */        
MAIN_IF_X_EQUAL_Y_GOTO:
        
        /* If if statement and expression fit on one line use that */
        if (x == y) goto MAIN_IF_X_EQUAL_Y_GOTO;
=======
        #undef PRINT_SINGLE_INT
        
/* goto label. <WHERE>_<WHAT IT POINTS TO>_<WHAT IT DOES> */        
MAIN_IF_X_EQUAL_Y:
        
        /* If if statement and expression fit on one line use that */
        if (x == y) goto MAIN_IF_X_EQUAL_Y;
>>>>>>> Stashed changes
        else
        {
                /* Use brakets */
        }
        
<<<<<<< Updated upstream
        /* When checking for an error. Check it isn't an error instead */
        if (!fgets(userInputBuffer, 40, stdin))
=======
        /* When checking for an error. Check for the error. Not for it not accuring. */
        if (fgets(userInputBuffer, 40, stdin) == NULL)
>>>>>>> Stashed changes
        {
                fprintf(stderr, "ERROR: THIS IS AN ERROR MESSAGE (END OF FILE)");
                exit(EXIT_FAILURE);
        }
        else 
        {
<<<<<<< Updated upstream
                while (0) if (x == y) goto MAIN_IF_X_EQUAL_Y_GOTO;
=======
                while (0) if (x == y) goto MAIN_IF_X_EQUAL_Y;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
                
>>>>>>> Stashed changes
                do
                {
                        /* More stuff */
                        break;
                } while (0);
        }
        
        /* No parenthesis when returning a literal */
        return 0;
<<<<<<< Updated upstream
}
=======
}

/* This function does foo bar baz spam */
unsigned int** 
foo_bar_baz_spam(unsigned long bear, char* string, int* array)
{
        /* do stuff */
        return 0;
}
/* Trailing newline character. */
>>>>>>> Stashed changes
