/* 07/03/2018 
 *
 * 
 */
#include "./src/ascii_to_hex.h"
#include "./src/intio.h"

int 
main(int argc, char *argv[]) 
{
    static char *argOneString;
    static char *argTwoString;
    
    static int argOneLen;
    static int argTwoLen;
    
    switch (argc) 
    {
        case 1: printHelp(); break;
        /* 
         * You'll probably need gcc for the next case statement. 
         * Just deroll it or get a good preprocessor. 
         */
        case 2 ... 10:
        {
            if (argv[1][0] == '-')
            {
                argOneLen = strlen(argv[1]) + 1;
                argTwoLen = strlen(argv[2]) + 1;
                
                argOneString = malloc(argOneLen); strcpy(argOneString, argv[1]);
                argTwoString = malloc(argTwoLen); strcpy(argTwoString, argv[2]);
                
                for (int i = 1; i < argOneLen; i++)
                {
                    switch (argOneString[i]) 
                    {
                	    case 'b': 
                        {
                            showBinary(getIntFromString(&argTwoString));
                            break;
                        }
                    }
                }
                free(argOneString); free(argTwoString);
            } /* if (argv[1][0] == '-')*/
        }		
    }
    return 0;
}