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

static inline void
do_fatal_error(const char *func_name, int line)
{
        fprintf(stderr, "ERROR: %s returned NULL in %s:%i", func_name, __FILE__, line);
        exit(EXIT_FAILURE);
}
#define fatal_error(x) do_fatal_error(x, __LINE__)

static inline char*
safer_gets(char *string, int max_str_len)
{
        static char *fgot_ptr;
        
        if ((fgot_ptr = fgets(string, max_str_len, stdin)) == NULL) fatal_error("fgets");
        
        return fgot_ptr;
}

static inline int
get_dimension(char *the_dimension, char the_name)
{
        int temp = 0;
        
        while (true)
        {
                char string[STRING_LIMIT] = "";
                
                printf("Veuillez introduire la %s de la matrice %c (Max %i): ", the_dimension, the_name, MAX_MATRIX_DIMENSION);
                safer_gets(string, STRING_LIMIT);
                
                if (string[0] >= '0' && string[0] <= '9')
                {
                        if (sscanf(string, "%d", &temp) != 1 || temp > MAX_MATRIX_DIMENSION || temp < 0)
                        {
                                temp = 0;
                                fprintf(stderr, "ERROR: OUT OF RANGE\n");
                                printf("Important: Veuillez introduire un nombre entier positif entre 1 et %i\n", MAX_MATRIX_DIMENSION);
                                continue;
                        }
                        else break;
                }
                else
                {
                        *string = 0;
                        puts("Veillez réessayer.");
                        continue;
                }
        }
        
        return temp;
}

static inline Matrix_d*
new_matrix(char mat_name)
{
        Matrix_d *matrix;
        
        if ((matrix = malloc(sizeof *matrix)) == NULL) fatal_error("malloc");
        
        matrix->name = mat_name;
        matrix->width = get_dimension("longueur", mat_name);
        matrix->height = get_dimension("hauteur", mat_name);
        
        return matrix;
}

static inline Matrix_d*
new_anonymous_matrix(char mat_name, int width, int height)
{
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
        for (int i = 0; mat_list[i] != NULL; i++) free(*(mat_list + i));
        free(mat_list);
        
        exit(EXIT_SUCCESS);
}

static inline void
set_values(Matrix_d *mat)
{
        char string[STRING_LIMIT] = "";
        
        puts("A tout moment, tapez \"ret\" (sans guillemets) pour retourner une étape en arrière.");
        puts("Veillez introduire la valeur pour:");
        
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
        
        printf("\nMatrice \'%c\' \n", this.name);
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
init_matrix(void)
{
        static Matrix_d **mat_array;
        
        if ((mat_array = malloc(sizeof mat_array * (MATRICES_TO_CREATE + 1))) == NULL) fatal_error("malloc");
        
        static char mat_ID = 'A';
        
        for (int i = 0; i < MATRICES_TO_CREATE; i++, mat_ID++) mat_array[i] = new_matrix(mat_ID);
        
        mat_array[MATRICES_TO_CREATE] = NULL;
        
        return mat_array;
}

static inline int
show_matrices(Matrix_d *mat_array[])
{
        static int i = 0;
        static char string[3] = "";
        
        while (true)
        {
                puts("Veuillez choisir une des matrices suivantes:");
                
                for (i = 0; mat_array[i] != NULL; i++) printf("%d) %c\n", i + 1, mat_array[i]->name);
                
                printf("\n> ");
                
                *string = 000; safer_gets(string, 3);
                
                if (string[0] >= '0' && string[0] <= ('0' + i)) break;
                else
                {
                        SET_COLOR(FG_RED);
                        
                        printf("Choix incorrecte, veuillez réessayer.");
                        
                        SET_COLOR(CL_RESET); ENDL();
                        continue;
                }
        }
        
        return (int) (string[0] - '1');
}

static inline Matrix_d**
add_matrix_to_array(Matrix_d **mat_array[])
{
        Matrix_d **this = *mat_array;
        static char name = 'A';
        
        static int nbr_of_matrices = 0;
        while (this[nbr_of_matrices] != NULL)
        {
                if (this[nbr_of_matrices] == NULL) break;
                
                name = this[nbr_of_matrices]->name;
                nbr_of_matrices++;
        }
        
        if ((this = realloc(this, (sizeof *mat_array) * (nbr_of_matrices + 2))) == NULL) fatal_error("realloc");
        
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
        
        printf("Par quel entier désirez-vous multiplier la matrice %c? ", this->name);
        
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
        
        printf("Le résultat à été enregistré dans la matrice %c\n", new_mat->name);
}

static inline void
are_matrices_equal(Matrix_d **map[])
{
        Matrix_d **this = *map;
        
        bool is_equal = true;
        
        if (this[0] == NULL || this[1] == NULL)
        {
                SET_COLOR(FG_RED);
                puts("Aucune matrice à comparer.\n");
                SET_COLOR(CL_RESET);
                
                return;
        }
        else
        {
                puts("Quelle matrice désirez vous comparer ?");
                Matrix_d *m_A = this[show_matrices(*map)];
                
                printf("Avec quelle matrice souhaitez vous comparer \'%c\' ?\n", m_A->name);
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
                
                if (is_equal) printf("La matrice \'%c\' est égale à la matrice \'%c\'\n", m_A->name, m_B->name);
                else puts("Les matrices sont différente");
                
        }
}

extern void
matrix_menu()
{
        Matrix_d **mat_array = init_matrix();
        
        while (true)
        {
                printf( "Veuillez choisir une des options suivante:\n\n\t"
                       "1) Introduire les données d\'une matrice.\n\t"
                       "2) Afficher une des matrices déjà entrées.\n\t"
                       "3) Multiplier une des matrices déjà entrée par un entier.\n\t"
                       "4) Tester l\'égalité de deux matrices déjà entrées.\n\t"
                       "5) Effectuer la somme de deux matrices déjà entrée.\n\t"
                       "6) Multiplier deux matrices déjà entrées.\n\t"
                       "Tapez \"Q\" pour quitter le programme.\n\n"
                       "> "
                       );
                
                char string[STRING_LIMIT] = ""; safer_gets(string, STRING_LIMIT);
                
                switch (string[0])
                {
                        case '1': set_values(mat_array[show_matrices(mat_array)]);
                                break;
                        case '2': print_matrix(mat_array[show_matrices(mat_array)]);
                                break;
                        case '3': multiply_matrix_by_integer(&mat_array);
                                break;
                        case '4': are_matrices_equal(&mat_array);
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

int
main(void)
{
        matrix_menu();
}
