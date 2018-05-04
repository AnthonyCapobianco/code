/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MITNFA
 * <https://fedoraproject.org/wiki/Licensing/MITNFA>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matrix_calc.h"

#if !defined(MATRIX_LOCALE_INCLUDED)
  #if PROGRAM_LOCALE == 'F'
    #include "locale/matrix_locale_fr.h"
  #else
    #include "locale/matrix_locale_en.h"
  #endif
#endif

static inline void
do_fatal_error(const char *func_name, int line)
{
        /*
         * If a function returns NULL use this to print the 
         * line and the file where it happened to stderr.
         */
        
        fprintf(stderr, "ERROR: %s returned NULL in %s:%i", func_name, __FILE__, line);
        exit(EXIT_FAILURE);
}
#define fatal_error(x) do_fatal_error(x, __LINE__)

static inline char*
safer_gets(char *string, int max_str_len)
{
        /* Get the user input from stdin and exit if fgets returns NULL */
        
        static char *fgot_ptr;
        
        if ((fgot_ptr = fgets(string, max_str_len, stdin)) == NULL) fatal_error("fgets");
        
        return fgot_ptr;
}

static inline int
get_dimension(char *the_dimension, char the_name)
{
        /* Get the maximum dimentions of the two initial matrices from stdin. */
        
        int temp = 0;
        
        while (true)
        {
                char string[STRING_LIMIT] = "";
                
                printf(STRING_ASK_DIMENSION, the_dimension, the_name, MAX_MATRIX_DIMENSION);
                safer_gets(string, STRING_LIMIT);
                
                if (string[0] >= '0' && string[0] <= '9')
                {
                        if (sscanf(string, "%d", &temp) != 1 || temp > MAX_MATRIX_DIMENSION || temp < 0)
                        {
                                /* Keep on looping until input is in range. */
                                
                                temp = 0;
                                fprintf(stderr, "ERROR: OUT OF RANGE\n");
                                printf(STRING_REMIND_RANGE, MAX_MATRIX_DIMENSION);
                                continue;
                        }
                        else break;
                }
                else
                {
                        /* Keep on looping if the user entered a character that isn't a number. */
                        
                        *string = 0;
                        puts(STRING_TRY_AGAIN);
                        continue;
                }
        }
        
        return temp;
}

static inline Matrix_d*
new_matrix(char mat_name)
{
        /*
         * Allocate memory for a matrix.
         * The width and height variables come from
         * a call to the get_dimentions() function. 
         *
         * Return a pointer to it.
         */
        
        Matrix_d *matrix;
        
        if ((matrix = malloc(sizeof *matrix)) == NULL) fatal_error("malloc");
        
        matrix->name = mat_name;
        matrix->width = get_dimension(STRING_WORD_LENGTH, mat_name);
        matrix->height = get_dimension(STRING_WORD_HEIGHT, mat_name);
        
        return matrix;
}

static inline Matrix_d*
new_anonymous_matrix(char mat_name, int width, int height)
{
        /*
         * Allocate memory for a matrix.
         * The width and height variables are parameters.
         *
         * Return a pointer to it.
         */
        
        Matrix_d *matrix;
        
        if ((matrix = malloc(sizeof *matrix)) == NULL) fatal_error("malloc");
        
        matrix->name = mat_name;
        matrix->width = width;
        matrix->height = height;
        
        return matrix;
}

static void
delete_matrices(Matrix_d *mat_list[])
{
        /* Simple deallocation using the array of pointer to matrices. */
        
        for (int i = 0; mat_list[i] != NULL; i++) free(*(mat_list + i));
        free(mat_list);
        
        exit(EXIT_SUCCESS);
}

static inline void
set_values(Matrix_d *mat)
{
        /* Set the values for the member `m` of a Matrix_d object. */
        
        char string[STRING_LIMIT] = "";
        
        puts(STRING_USE_RET);
        puts(STRING_ENTER_VALUE);
        
        for (int x = 0, y = 0; x < mat->height; x++, y = 0)
        {
                while (y < mat->width)
                {
                        int temp = 0;
                        
                        printf("%c(%d,%d) : ", mat->name, x + 1, y + 1);
                        
                        safer_gets(string, STRING_LIMIT);
                        
                        if (y > 0 && !strncmp(string, "ret", 3)) y--;
                        
                        else if (sscanf(string, "%d", &temp) == 1)
                        {
                                mat->m[x][y] = temp;
                                y++;
                        }
                }
        }
}

static inline void
print_matrix(Matrix_d *self)
{
        Matrix_d this = *self;
        
        printf("\n"STRING_WORD_MATRIX" \'%c\' \n", this.name);
        printf("==========================================================");
        
        SET_COLOR(FG_YELLOW); ENDL();
        
        for (int y = 0; y < this.height; ++y, ENDL())
                for (int x = 0; x < this.width; ++x)
                {
                        if (this.m[y][x]) printf("\t%d", this.m[y][x]);
                }
        
        SET_COLOR(CL_RESET);
}

static inline Matrix_d**
init_matrix(const size_t MAX_MAT_TO_CREATE)
{
        /*
         * Allocate memory for the (constant) number of matrices to create.
         * Return an array of pointers to Matrix_d objects.
         */
        
        static Matrix_d **mat_array;
        
        if ((mat_array = malloc(sizeof (*mat_array) * (MAX_MAT_TO_CREATE + 1))) == NULL) fatal_error("malloc");
        
        static char mat_ID = 'A';
        
        for (unsigned int i = 0; i < MAX_MAT_TO_CREATE; i++, mat_ID++) mat_array[i] = new_matrix(mat_ID);
        
        mat_array[MAX_MAT_TO_CREATE] = NULL;
        
        return mat_array;
}

static inline int
show_matrices(Matrix_d *mat_array[])
{
        /*
         * Show a list of matrices from the array of pointers.
         * Return an int corresponding to the position of the matrix in the array.
         */
        
        static int i = 0;
        static char string[3] = "";
        
        while (true)
        {
                puts(STRING_CHOOSE_MATRIX);
                
                for (i = 0; mat_array[i] != NULL; i++) printf("%d) %c\n", i + 1, mat_array[i]->name);
                
                printf("\n> ");
                
                *string = 000; safer_gets(string, 3);
                
                if (string[0] >= '0' && string[0] <= ('0' + i)) break;
                else
                {
                        SET_COLOR(FG_RED);
                        
                        printf(STRING_WRONG_CHOICE " " STRING_TRY_AGAIN);
                        
                        SET_COLOR(CL_RESET); ENDL();
                        continue;
                }
        }
        
        return (int) (string[0] - '1');
}

static inline Matrix_d**
add_matrix_to_array(Matrix_d **mat_array[])
{
        /*
         * Using a pointer to the array of pointer to Matrix_d objects
         * create a new matrix then add it to that array.
         *
         * Return the new array.
         */
        
        Matrix_d **this = *mat_array;
        static char name = 'A';
        
        static int nbr_of_matrices = 0;
        while (this[nbr_of_matrices] != NULL)
        {
                if (this[nbr_of_matrices] == NULL) break;
                
                name = this[nbr_of_matrices]->name;
                nbr_of_matrices++;
        }
        
        if ((this = realloc(this, (sizeof *this) * (nbr_of_matrices + 2))) == NULL) fatal_error("realloc");
        
        static int width; width = this[nbr_of_matrices - 2]->width;
        static int height; height = this[nbr_of_matrices - 2]->height;
        
        this[nbr_of_matrices] = new_anonymous_matrix((name + 1), width, height);
        this[nbr_of_matrices + 1] = NULL;
        
        return &(this[nbr_of_matrices]);
}

static inline void
multiply_matrix_by_integer(Matrix_d **mat_array[])
{
        Matrix_d *this = *mat_array[show_matrices(*mat_array)];
        Matrix_d *new_mat = *add_matrix_to_array(mat_array);
        int the_number = 0;
        char string[STRING_LIMIT] = "";
        
        printf(STRING_INT_MULT, this->name);
        
        safer_gets(string, STRING_LIMIT);
        
        if (sscanf(string, "%d", &the_number) != 1) fatal_error("sscanf");
        else
        {
                for (int y = 0; y < this->width; y++)
                        for (int x = 0; x < this->height; x++)
                        {
                                new_mat->m[x][y] = (this->m[x][y] * the_number);
                        }
        }
        
        printf(STRING_RES_SAVED_IN, new_mat->name);
}

static inline void
are_matrices_equal(Matrix_d **map[])
{
        /*
         * Check the equality between two EXISTING matrices.
         * Print to stdout whether they are equal or not. 
         */
        
        Matrix_d **this = *map;
        
        bool is_equal = true;
        
        if (this[0] == NULL || this[1] == NULL)
        {
                SET_COLOR(FG_RED);
                puts(STRING_FUCK_ALL);
                SET_COLOR(CL_RESET);
                
                return;
        }
        else
        {
                puts(STRING_WHICH);
                Matrix_d *m_A = this[show_matrices(*map)];
                
                printf(STRING_WITH_WHICH, m_A->name);
                Matrix_d *m_B = this[show_matrices(*map)];
                
                if (m_A->width != m_B->width || m_A->height != m_B->height) is_equal = false;
                else if (m_A == m_B) is_equal = true;
                else
                {
                        for (int y = 0; y < m_A->height; y++)
                                for (int x = 0; x < m_B->width; x++)
                                {
                                        if (m_A->m[x][y] ^ m_B->m[x][y])
                                        {
                                                is_equal = false;
                                                break;
                                        }
                                }
                }
                
                if (is_equal) printf(STRING_YAY, m_A->name, m_B->name);
                else 
                {
                        puts(STRING_NOPE);
                }
        }
}

extern void
matrix_menu(const size_t MAX_MAT_TO_CREATE)
{
        static Matrix_d **mat_array; mat_array = init_matrix(MAX_MAT_TO_CREATE);
        
        while (true)
        {
                printf( STRING_MAT_MENU "> ");
                
                char string[STRING_LIMIT] = ""; safer_gets(string, STRING_LIMIT);
                
                switch (string[0])
                {
                        case '1': 
                                set_values(mat_array[show_matrices(mat_array)]);
                                break;
                                
                        case '2':
                                print_matrix(mat_array[show_matrices(mat_array)]);
                                break;
                                
                        case '3':
                                multiply_matrix_by_integer(&mat_array);
                                break;
                                
                        case '4': 
                                are_matrices_equal(&mat_array);
                                break;
                                
                        case '5':
                        case '6':
                                
                        case 'q': 
                        case 'Q': delete_matrices(mat_array);
                                
                        default: continue;
                }
        }
}

#undef fatal_error
