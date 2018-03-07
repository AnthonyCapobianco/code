//
// ascii_to_hex.h
// Created by Anthony Capobianco on 07/03/2018.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ASCII_TO_HEX_H_INCLUDED_
#define _ASCII_TO_HEX_H_INCLUDED_

extern unsigned char printHelp(void);
extern void printBinaryFromInt(int);

#define showBinary(x) printBinaryFromInt(x)

#endif