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

#include "includes/Command.hpp"
#include "includes/Time.hpp"
#include "includes/DBConfig.hpp"

#ifndef Drugio_cpp
#define Drugio_cpp

namespace Drugio
{
        struct MaybeDouble
        {       const double dosage;
                bool is_double;
        };
        
        class Drug
        {
        private:
                const std::string _name;
                const std::vector<double> _doses;
                
                char
                PrintDoses()
                {
                        char c = 'a';
                        
                        for (auto it: this->GetDoses())
                        {
                                std::cout << "[" << c++ << "] " << it << std::endl;
                        }
                        
                        std::cout << "\n> " << std::flush;
                        
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
                
                MaybeDouble
                GetSelection()
                {
                        int it = 0;
                        
                        if (this->_doses.size() != 1)
                        {
                                Command::Info("dose");
                                
                                this->PrintDoses();
                                it = Command::GetKey();
                                
                                if (it == -1) return { 0, false};
                        }
                        
                        return {this->_doses.at(it), true};
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
                
                int
                PrintNames()
                {
                        char c = 'a';
                        
                        for (auto d: this->_list) std::cout << "[" << c++ << "] " << d.GetName() << std::endl;
                        
                        std::cout << "\n" << "> ";
                        
                        return (c - 'a') - 1;
                }
                
                Drug
                GetSelection(int user_input) { return this->_list.at(user_input); }
                
                UserSelection
                GetUsedDose(int &user_input, int &last)
                {
                        try
                        {
                                Drug d = this->GetSelection(user_input);
                                MaybeDouble dose_used = d.GetSelection();
                                
                                if (dose_used.is_double) return { d.GetName(), dose_used.dosage, false };
                        }
                        catch (std::out_of_range &oor)
                        {
                                std::cerr << "ERROR: Out of range (" << oor.what() << ")." << std::endl;
                        }
                        
                        return { "", 0.0, true };
                }
                
        public:
                DrugList(const std::initializer_list<Drug> &d) : _list{d}
                {
                }
                
                ~DrugList(){}
                
                void
                Menu()
                {
                        int last = -1;
                        int it = -1;
                        
                        while (true)
                        {
                                Command::Info("drug");
                                Command::PrintLogsFromToday();
                                
                                last = PrintNames();
                                
                                it = Command::GetKey();
                                
                                if (it >= 0 and it < this->_list.size()) break;
                                else if (it == -2)
                                {
                                        it = Command::GetKey();
                                        
                                        if (it >= 0 and it < this->_list.size())
                                        {
                                                Drug d = this->GetSelection(it);
                                                Command::PrintMoreLogs(d.GetName());
                                        }
                                }
                                continue;
                        }
                        
                        UserSelection us = this->GetUsedDose(it, last);
                        
                        if (us.is_escape) return;
                        
                        const std::string name = us.name;
                        const double dose = us.dose;
                        
                        
                        sqlite::database db(DBConfig::DBName);
                        
                        db << "INSERT INTO logs (theDate, theTime, name, dose) VALUES (?, ?, ?, ?);"
                        << Time::DateNow() << Time::TimeNow() << name << dose;
                }
        };
}

#endif
