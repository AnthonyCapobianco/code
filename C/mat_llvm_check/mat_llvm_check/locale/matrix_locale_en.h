/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MITNFA 
 * <https://fedoraproject.org/wiki/Licensing/MITNFA>
 */

#ifndef MATRIX_LOCALE_INCLUDED
#define MATRIX_LOCALE_INCLUDED

#define STRING_ASK_DIMENSION "Please enter the %s of matrix %c (Max %i): "
#define STRING_REMIND_RANGE "Please enter a positive whole number from 1 to %i\n"

#define STRING_TRY_AGAIN "Please try again."
#define STRING_WRONG_CHOICE "Wrong choice."

#define STRING_WORD_MATRIX "Matrix"	
#define STRING_WORD_LENGTH "length"
#define STRING_WORD_HEIGHT "height"

#define STRING_USE_RET "At any time, type \"ret\" (without quotes) to return to the previous point."
#define STRING_ENTER_VALUE "Please enter the value for:"

#define STRING_CHOOSE_MATRIX "Please choose one of the following matrices:"	
#define STRING_INT_MULT "What integer do you wish to multiply matrix \'%c\' by? "
#define STRING_RES_SAVED_IN "The result has been saved in matrix \'%c\'\n"

#define STRING_FUCK_ALL "Nothing to compare."
#define STRING_WHICH "Which matrix do you want to compare ?"
#define STRING_WITH_WHICH "With which matrix do you want to compare \'%c\' ?\n"

#define STRING_YAY "Matrix \'%c\' is equal to matrix \'%c\'\n"
#define STRING_NOPE "The matrices are different"

#define STRING_MAT_MENU						\
	"Please choose one of the following:\n\n\t"		\
	"1) Set values of a matrix.\n\t"			\
	"2) Print an existing matrix.\n\t"			\
	"3) Multiply an existing matrix by an integer.\n\t"	\
	"4) Check existing matrices for equality.\n\t"		\
	"5) Get the sum of two existing matrices.\n\t"		\
	"6) Multiply a matrix by another.\n\t"			\
	"Type \"Q\" to quit the program.\n\n"			\


#endif
