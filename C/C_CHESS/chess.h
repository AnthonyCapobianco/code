/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#ifndef _CHESS_H_
#define _CHESS_H_

#include <stdbool.h>
/*
 * A board contains 2 sets of pieces, one whith the other black. 
 *
 * Objects to define are therefore:
 * 
 * 3) A Board.
 * 2) A set.
 * 1) A piece.
 * 
 */

typedef struct _Piece_d
{       const char name_ID[3];
        
        const unsigned int min_x_distance;
        const unsigned int max_x_distance;
        
        const unsigned int min_y_distance;
        const unsigned int max_y_distance;
         
} Piece_d;

typedef struct _Piece
{       Piece_d *self;
        bool is_white;
        int position;
} Piece;

typedef struct _Set
{       Piece pieces[16];
} Set;

enum _Position 
{        a8, b8, c8, d8, e8, f8, g8, h8 = 7
,        a7, b7, c7, d7, e7, f7, g7, h7 = 15
,        a6, b6, c6, d6, e6, f6, g6, h6 = 23
,        a5, b5, c5, d5, e5, f5, g5, h5 = 31
,        a4, b4, c4, d4, e4, f4, g4, h4 = 39
,        a3, b3, c3, d3, e3, f3, g3, h3 = 47
,        a2, b2, c2, d2, e2, f2, g2, h2 = 55
,        a1, b1, c1, d1, e1, f1, g1, h1 = 63
} Position;

struct Board
{
        Set white;
        Set black;
        
        Piece self[8][8];
};

#endif
