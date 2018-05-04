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
#include <ctime>
#include <string>
#include <vector>
#include <initializer_list>

#include "resources/sqlite_modern_cpp.h"

namespace DBConfig 
{
        const std::string DBName = "/Users/tony/Desktop/yogurd/logs/debug.db";
}

namespace Time 
{
        std::string 
        DateNow()
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%d-%m-%Y", std::localtime(&t));

                return (std::string) now;
        }
        
        std::string 
        TimeNow()
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%H:%M", std::localtime(&t));

                return (std::string) now;
        }
}

namespace Command
{       
        bool
        DoesUserAgree(const std::string query)
        {
                std::string ua = "";
                
                std::cout << query << std::endl;
                std::cin >> ua;
                
                return (std::toupper(ua[0]) == 'Y');
        }
        
        void
        PrintLine()
        {
                std::cout << "════════════════════════════════════════════════════════════" << std::endl;
        }
        
        void
        Info(const std::string &name)
        {
                std::cout << "Please type the letter conresponding to the " << name << " taken" << '\n'
                          << "then press the return key. Type \".help\" for help.\n" << std::endl;
        }
        
        void
        InfoLogs()
        {
                std::cout << "Please type the letter conresponding to the drug you want to see the logs for" << '\n'
                          << "then press the return key. Type \".help\" for help.\n" << std::endl;
        }
        
        void
        PrintHelp()
        {
                using std::cout; 
                using std::endl;
                
                PrintLine();
                
                cout << "Help menu:\n" << endl;
                
                cout << "\tType \".exit\" or \"quit\" to exit the program\n"
                     << "\tType \".back\" to go back to the previous menu\n"
                     << "\tType \".last\" to show logs for a specific medication\n"
                     << "\tType \".rmlast\" to remove the last log entry\n"
                     << "\tType \".clear\" or \".cls\" to clear the screen\n"
                     << "\tType \".help\" to show this menu\n" << endl;
                
                PrintLine();
        }

                
        void 
        ClearScreen()
        {
                #if defined (_WIN32) || defined (_WIN64)
                        std::system("cls");
                #else
                        std::cout << "\x1B[2J" << std::endl;
                #endif                
        }
        
        void
        PrintLast()
        {
                sqlite::database db(DBConfig::DBName);
                PrintLine();
                
                const std::string STATEMENT = "SELECT theTime, name, dose FROM logs WHERE theDate == ? ;";
                
                for (auto &&row : db << STATEMENT << Time::DateNow()) 
                {
                        std::string theTime; std::string name; double dose;
                        
                        row >> theTime >> name >> dose;
                        std::string tabs = (dose > 10) ? "\t" : "\t\t";
                        
                        std::cout << "[" << theTime << "]" << ' ' << name << tabs << dose << " mg" << std::endl;
                }
                
                PrintLine();
        }
        
        void
        PrintMoreLogs(std::string name_of_drug)
        {
                sqlite::database db(DBConfig::DBName);
                PrintLine();
                
                const std::string STATEMENT = "SELECT theDate, theTime, name, dose FROM logs WHERE name is ? ORDER BY ID ASC LIMIT 10;";
                
                for (auto &&row : db <<  STATEMENT << name_of_drug)
                {
                        std::string theDate; std::string theTime; std::string name; 
                        double dose; 
                        
                        row >> theDate >> theTime >> name >> dose;
                        std::string tabs = (dose > 10) ? "\t" : "\t\t";
                        
                        std::cout << "[" << theDate << " - " << theTime << "] " << name << tabs << dose << " mg" << std::endl; 
                }
                PrintLine();
                
        }
        
        const std::string
        GetLastNameInDatabase()
        {
                sqlite::database db(DBConfig::DBName);
                
                uint64_t ID = 0;
                std::string name;
                
                db << "SELECT MAX(ID) AS last_id FROM logs AS l;" >> ID;
                
                db << "SELECT name FROM logs where ID == ?;" << ID
                   >> name;
                
                
                return name; 
        }
        
        void
        RemoveLastLogEntry()
        {
                sqlite::database db(DBConfig::DBName);
                PrintLine();
                
                const std::string name = GetLastNameInDatabase();
                
                std::string querry = "Are you sure you want to delete the last dose of "
                                +  name
                                + " from the database? (Y/N)";
                
                
                DoesUserAgree(querry);
                
                db << "DELETE FROM logs WHERE ID = (SELECT MAX(ID) FROM logs);";
                
                std::cout << "The last dose of " << name << " has been removed from the database." << std::endl;
        }
        
        
        int
        Menu(std::string command)
        {
                if (command.compare(".help") == 0) PrintHelp();
                
                if (command.compare(".quit") == 0 or command.compare(".exit") == 0) exit(EXIT_SUCCESS);
                
                if (command.compare(".cls") == 0 or command.compare(".clear") == 0) ClearScreen();
                
                if (command.compare(".back") == 0)
                {
                        ClearScreen();
                        PrintLast();
                }
                
                if (command.compare(".last") == 0)
                {
                        ClearScreen();
                        InfoLogs();
                
                        return 2;
                }
                
                if (command.compare(".logs") == 0)
                {
/******************************************************
 *  Make command to show logs with user given limit   * 
 ******************************************************/

                        Command::PrintLast();
                        return 2;
                }
                
                if (command.compare(".rmlast") == 0)
                {
                        RemoveLastLogEntry();
                        ClearScreen();
                }
                
                return 1;
        }
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
                                std::cout << "[" << c++ << "] " << it << std::endl;
                        
                        std::cout << "\n" << "> ";
                        
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
                GetSelection(Drug d)
                {
                        std::string user_input = "";
                        
                        do 
                        {       
                                Command::Info("dose");
                                
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
                                Command::PrintLast();
                                
                                char last = PrintNames();
                                
                                std::string key_or_string = "";
                                std::cin >> key_or_string; 
                                
                                if (key_or_string[0] == '.')
                                {
                                        int menu_returned = Command::Menu(key_or_string);
                                        
                                        if (menu_returned == 1) continue;
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
main(void) 
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
