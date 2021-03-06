/*
 *  This program is designed to provide an easy way for
 *  users to log doses of the medication(s) they use.
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
#include "drugio.h"

int main(void)
{    
    
    drugList( newDrug("Ritalin", mg(5, 10, 15, 20))
            , newDrug("Concerta", mg(36, 72))
            , newDrug("Effexor", mg(225))
            , newDrug("Xanax", ng(250, 500, 1000, 1500, 2000))
            , newDrug("Akton", mg(1, 2, 3, 4))
            , newDrug("Zolpidem", mg(5, 10, 15))
            );

    drugioSetPath("/Users/Muddy/Desktop/log.txt"); 
    printd(drugList);

    return(0);
}
