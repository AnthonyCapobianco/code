/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MITNFA 
 * <https://fedoraproject.org/wiki/Licensing/MITNFA>
 */

#ifndef _MATRIX_CALC_H_
#define _MATRIX_CALC_H_

/* 'F' pour Français */
/* 'E' for English   */
#define PROGRAM_LOCALE 'F'

#define STRING_LIMIT 100
#define MAX_MATRIX_DIMENSION 10

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

extern void matrix_menu(const size_t);

#endif
