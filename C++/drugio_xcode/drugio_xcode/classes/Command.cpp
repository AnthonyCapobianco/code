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

#include <string>
#include <iostream>

#include "includes/Command.hpp"
#include "includes/Time.hpp"
#include "includes/DBConfig.hpp"

namespace Command
{
        bool
        DoesUserAgree(const std::string &query)
        {
                std::string ua = "";
                
                std::cout << query << std::endl;
                std::cin >> ua;
                
                return (std::toupper(ua[0]) == 'Y');
        }
        
        void
        PrintLine()
        {
                std::cout << "════════════════════════════════════════════════════════════"
                          << std::endl;
        }
        
        void
        Info(const std::string &name)
        {
                std::cout << "Please type the letter conresponding to the " + name + " taken\n"
                          << "then press the return key. Type \"help\" for help.\n"
                          << std::endl;
        }
        
        void
        InfoLogs()
        {
                std::cout << "Please type the letter conresponding to the drug\n"
                          << "you want to see the logs for then press the return key."
                          << "\n> ";
                std::cout.flush();
        }
        
        void
        PrintHelp()
        {
                using std::cout;
                using std::endl;
                
                PrintLine();
                
                cout << "Help menu:\n" << endl;
                
                cout << "\tType \"exit\" or \"quit\" to exit the program\n"
                     << "\tType \"back\" to go back to the previous menu\n"
                     << "\tType \"last\" to show logs for a specific medication\n"
                     << "\tType \"rmlast\" to remove the last log entry\n"
                     << "\tType \"clear\" or \"cls\" to clear the screen\n"
                     << "\tType \"help\" to show this menu\n"
                     << endl;
                
                PrintLine();
                
                cout << "Press the return key to go back to the main menu." << std::endl;
                
                std::cin.ignore();
                std::cin.get();
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
        PrintLogsFromToday()
        {
                sqlite::database db(DBConfig::DBName);
                
                bool need_line = true;
                
                const std::string STATEMENT = "SELECT theTime, name, dose FROM logs WHERE theDate IS ? ;";
                
                for (auto &&row: db << STATEMENT << Time::DateNow())
                {
                        if (need_line)
                        {
                                PrintLine();
                                need_line = false;
                        }
                        
                        std::string theTime;
                        std::string name;
                        double dose;
                        
                        row >> theTime >> name >> dose;
                        std::string tabs = (dose > 10) ? "\t" : "\t\t";
                        
                        std::cout << "[" + theTime + "] " + name + tabs
                        << dose << " mg" << std::endl;
                }
                
                if (!need_line) PrintLine();
        }
        
        void
        PrintMoreLogs(const std::string &name_of_drug)
        {
                sqlite::database db(DBConfig::DBName);
                
                bool need_line = true;
                
                const std::string STATEMENT = "SELECT theDate, theTime, name, dose FROM logs "
                                              "WHERE name IS ? ORDER BY ID ASC LIMIT 10;";
                
                for (auto &&row: db << STATEMENT << name_of_drug)
                {
                        if (need_line)
                        {
                                PrintLine();
                                need_line = false;
                        }
                        
                        std::string theDate;
                        std::string theTime;
                        std::string name;
                        
                        double dose;
                        
                        row >> theDate >> theTime >> name >> dose;
                        std::string tabs = (dose > 10) ? "\t" : "\t\t";
                        
                        std::cout << "[" + theDate + " - " + theTime + "] " + name + tabs
                        << dose << " mg" << std::endl;
                        
                        std::cout.flush();
                        
                }
                if (!need_line) PrintLine();
        }
        
        const std::string
        GetLastNameInDatabase()
        {
                sqlite::database db(DBConfig::DBName);
                std::string name;
                
                db << "SELECT name FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);"
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
                                     +  name + " from the database? (Y/N)";
                
                DoesUserAgree(querry);
                
                db << "DELETE FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);";
                
                std::cout << "The last dose of " << name << " has been removed from the database." << std::endl;
        }
        
        
        int
        Menu(std::string &command)
        {
                if (command == "help")
                {
                        ClearScreen();
                        PrintHelp();
                }
                
                if (command == "quit" or command == "exit")
                {
                        exit(EXIT_SUCCESS);
                }
                
                if (command == "cls" or command == "clear")
                {
                        ClearScreen();
                }
                
                if (command == "back")
                {
                        ClearScreen();
                        PrintLogsFromToday();
                }
                
                if (command == "last")
                {
                        ClearScreen();
                        InfoLogs();
                        return -2;
                }
                
                if (command.find("logs") != std::string::npos)
                {
                        PrintLogsFromToday();
                }
                
                if (command == "rmlast")
                {
                        RemoveLastLogEntry();
                        ClearScreen();
                }
                
                return -1;
        }
        
        int
        GetKey()
        {
                std::string it = "";
                
                try
                {
                        std::cin >> it;
                        
                        if (it.length() > 1) return Command::Menu(it);
                        
                        return (int) (it[0] - 'a');
                }
                catch (const std::exception& e)
                {
                        std::cerr << "ERROR: " << e.what() << std::endl;
                        return -1;
                }
        }
}
