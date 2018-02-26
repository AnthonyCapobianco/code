/*
 *  This program is designed to provide an easy way for
 *  users to graphically represent a point on a graph
 *
 *  Copyright (C) 2018 Anthony Capobianco
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#ifndef PRINTG_INCLUDED
#define PRINTG_INCLUDED

#define G_UP "   ^"
#define G_BOTTOM_T "───┼───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬──>"
#define G_BOTTOM_B " 0 │   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15"
#define G_LEFT "\n%s%i┤", (i < 10) ? "  " : " ", i
#define G_LEFT_P "\n   │"
#define G_LEFT_B "   │"

extern void printg(unsigned int x, unsigned int y);
#endif