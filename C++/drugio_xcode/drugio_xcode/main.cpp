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

#include <iostream>
#include <vector>
#include <initializer_list>

#include "resources/sqlite_modern_cpp.h"

/*
 * sqlite modern cpp can be obtained here: https://github.com/SqliteModernCpp/sqlite_modern_cpp
 * I love it and I'm sure if you ever need an sqlite wrapper you'll love it too!
 *
 */

#include "classes/includes/Command.hpp"
#include "classes/includes/Time.hpp"
#include "classes/includes/DBConfig.hpp"
#include "classes/Drugio.cpp"
  
int 
main() 
{
        using namespace Drugio;
        
        DrugList medications = 
        DrugList({ Drug("Ritalin", {5, 10, 15, 20})
                 , Drug("Concerta", {36, 72})
                 , Drug("Effexor", {225})
                 , Drug("Xanax", {0.125, 0.25, 0.5, 1, 1.5, 2})
                 , Drug("Akton", {1, 2, 3, 4})
                 , Drug("Zolpidem", {5, 10, 15})
                 , Drug("Pantomed", {20, 40})
                 , Drug("Dafalgan", {500, 1000})
                 , Drug("DXM", {50, 100, 150, 200, 250})
                 , Drug("chlorphenamine", {3.4})
                 , Drug("Ibuprofen", {200, 300, 400, 600})
                 , Drug("Weed", {125, 250, 500})
                 });
        
        do medications.Menu(); while (Command::DoesUserAgree("Do you want to run this again? (Y/N): "));
}
