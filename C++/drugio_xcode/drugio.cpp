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
#include <string>
#include <vector>
#include <initializer_list>

#include "drugio_xcode/resources/sqlite_modern_cpp.h"


#include "classes/includes/Command.hpp"
#include "classes/includes/Time.hpp"
#include "classes/includes/DBConfig.hpp"

namespace DBConfig 
{
        const std::string DBName = "/Users/tony/Desktop/yogurd/logs/debug.db";
}

namespace Drugio 
{

        class Drug
        {
         private:
                const std::string _name;
                const std::vector<double> _doses;
                      
                char
                PrintDoses(Drug d)
                {
                        char c = 'a';
                        
                        for (auto it: d.GetDoses())
                        {
                                std::cout << "[" << c++ << "] " << it << std::endl;
                        }
                        
                        std::cout << "\n" << "> " << std::flush;
                        
                        return c;
                }
                
         public:
                Drug(const std::string& drug_name, const std::initializer_list<double> &dose_array)
                : _name{drug_name}, _doses{ dose_array.begin(), dose_array.end()}
                {
                }
                
                ~Drug(){}
                
                const std::vector<double>
                GetDoses() { return this->_doses; }

                const std::string
                GetName() { return this->_name; }
                
                const double
                GetSelection(Drug &d)
                {
                        std::string user_input = "";
                        
                        do 
                        {       
                                Command::Info("dose");
                                
                                if (d._doses.size() == 1) break;
                                
                                PrintDoses(d);
                                std::cin >> user_input; 
                                
                                if (user_input[0] == '.' and Command::Menu(user_input) == 1) return -1.0;
                                
                                user_input[0] -= 'a';
                        
                        } while (user_input[0] >= this->_doses.size());
                        
                        return this->_doses.at(user_input[0]);
                }
        };

        class DrugList
        {
         private:
                const std::vector<Drug> _list;
                
                struct UserSelection
                {       
                        const std::string name;
                        const double dose;
                        const bool is_escape;
                };
                
                char
                PrintNames()
                {
                        char c = 'a';
                        
                        for (auto d: this->_list) std::cout << "[" << c++ << "] " << d.GetName() << std::endl;
                        
                        std::cout << "\n" << "> ";
                        
                        return c;
                }
                
                Drug
                GetSelection(char user_input, char &last) { return this->_list.at(user_input); }
                
                UserSelection
                GetUsedDose(char &user_input, char &last)
                {
                        Drug d = this->GetSelection(user_input, last);
                        
                        
                        const double dose_used = d.GetSelection(d);
                        
                        if (dose_used == -1.0) return { "", 0.0, true };
                        
                        return { d.GetName(), dose_used, false };
                }
                
         public:
                DrugList(const std::initializer_list<Drug> &d) : _list{d}
                {
                }
                
                ~DrugList(){}
                
                void
                Menu()
                {
                        while (true)
                        {
                        
                                Command::Info("drug");
                                Command::PrintLogsFromToday();
                                
                                char last = PrintNames();
                                
                                std::string key_or_string = "";
                                std::cin >> key_or_string; 
                                
                                if (key_or_string[0] == '.')
                                {
                                        int menu_returned = Command::Menu(key_or_string);
                                        
                                        if (menu_returned == 1) break;
                                        if (menu_returned == 2)
                                        {
                                                last = PrintNames();
                                                std::cin >> key_or_string;
                                                
                                                if (key_or_string[0] != '.' and (key_or_string[0] -= 'a') >= this->_list.size())
                                                {
                                                        std::cerr << "ERROR: Out of range." << std::endl;
                                                        std::cout << "Try again." << std::endl;
                                                        
                                                        continue;
                                                } 
                                                else 
                                                {
                                                        Drug d = this->GetSelection(key_or_string[0], last);
                                                        Command::PrintMoreLogs(d.GetName());
                                                }
                                                
                                        }
                                } 
                                else 
                                {
                                        if (key_or_string[0] != '.' and (key_or_string[0] -= 'a') >= this->_list.size()) 
                                        {
                                                std::cerr << "ERROR: Out of range." << std::endl;
                                                std::cout << "Try again." << std::endl;
                                                
                                                continue;
                                        }
                                        
                                        UserSelection us = this->GetUsedDose(key_or_string[0], last);
                                        
                                        if (us.is_escape) continue;
                                        
                                        const std::string name = us.name;
                                        const double dose = us.dose;
                                        
                                        
                                        sqlite::database db(DBConfig::DBName);
                                        
                                        db << "INSERT INTO logs (theDate, theTime, name, dose) VALUES (?, ?, ?, ?);"
                                           << Time::DateNow() << Time::TimeNow() << name << dose;
                                        
                                        break;
                                }
                        }
                }       
        };
}
  
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
