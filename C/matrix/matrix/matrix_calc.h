/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT
 * <http://www.opensource.org/licenses/MIT>
 */

#ifndef _MATRIX_CALC_H_
#define _MATRIX_CALC_H_

#define STRING_LIMIT 100
#define MAX_MATRIX_DIMENSION 10
#define MATRICES_TO_CREATE 2

#define FG_YELLOW "33"
#define FG_RED "91"
#define CL_RESET "0"

#define SET_COLOR(x) printf("\x1b["x"m")
#define ENDL() puts("")

typedef struct Matrix_data
{
        char name;
        
        int width;
        int height;
        
        int m[MAX_MATRIX_DIMENSION][MAX_MATRIX_DIMENSION];
        
} Matrix_d;

extern void matrix_menu(void);

#endif
