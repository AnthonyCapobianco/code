/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

int main(int argc, char *argv[]) 
{
        if (argc == 1)
        {
                fputs("ERROR: No file to decamelize", stderr);
                exit(EXIT_FAILURE);
        }
        
        FILE *file_ptr;
        
        if ((file_ptr = fopen(argv[1], "r")) == NULL)
        {
                fputs("ERROR: Couldn't read the file", stderr);
                exit(EXIT_FAILURE);
        }

        bool is_ok = true;
        int c = 0;
        int temp = 0;
        do 
        {
                c = fgetc(file_ptr);
                if (c == '\"') is_ok = (is_ok) ? false : true;
                
                if (islower(temp) && isupper(c) && is_ok)
                {
                        fputc('_', stdout);
                        fputc(tolower(c), stdout);
                }
                else fputc(c, stdout);
                
                temp = c;
        } while (c != EOF);
        
        fclose(file_ptr);
}
