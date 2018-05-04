/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char* string;

int main(int argc, char *argv[]) 
{
        if (argc == 1)
        {
                fputs("ERROR: No file selected", stderr);
                exit(EXIT_FAILURE);
        }
        
        FILE *file_ptr;
        
        if ((file_ptr = fopen(argv[1], "r")) == NULL)
        {
                fputs("ERROR: Couldn't read the file", stderr);
                exit(EXIT_FAILURE);
        }

        bool is_string = false;
        bool is_end = false;
        int c = 0;
        int i = 0;
        do 
        {
                c = fgetc(file_ptr);
                if (c == '\"' && (c - 1) != '\\')
                {
                        is_end = is_string;
                        is_string = (is_string) ? false : true;
                        
                        if (!is_end)
                        {
                                printf("#define STRING_%i \"", i);
                                c++;
                        }
                        else
                        {
                                puts("\"");
                                i++;
                        }
                }
                
                if (is_string) fputc(c, stdout);
        } while (c != EOF);
        
        fclose(file_ptr);
}
