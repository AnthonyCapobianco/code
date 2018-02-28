#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef _BOXES_H_INCLUDED_
#define _BOXES_H_INCLUDED_

#define P_BOX_TOP_LEFT "╔"
#define P_BOX_BOTTOM_LEFT "╚"
#define P_BOX_TOP_RIGHT "╗"
#define P_BOX_BOTTOM_RIGHT "╝"

#define P_BOX_VERTICAL_LINE "║"
#define P_BOX_HORIZONTAL_LINE "═"

#define POSITION unsigned char
#define P_TOP 0
#define P_BOTTOM 1

/* Functions prototypes */
extern void _closedBox(const int variableArgumentsCount, ...);

#define NUMBER_OF_ARGS(...)  (sizeof((char*) {0, ##__VA_ARGS__}) / sizeof((char*) - 1))
#define closedBox(x, ...) _closedBox(x, (char*[]) {__VA_ARGS__})

#endif