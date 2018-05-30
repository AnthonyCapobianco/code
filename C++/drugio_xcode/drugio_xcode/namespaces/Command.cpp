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
#include "includes/Actions.hpp"

#include "ReturnStructures.cpp"

namespace Command
{
        void
        Pause()
        {
                std::cout << "Press the return key to go back to the main menu." << std::endl;

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
        PrintLine()
        {
                std::cout << "════════════════════════════════════════════════════════════"
                          << std::endl;
        }

        bool
        DoesUserAgree(const std::string &query)
        {
                std::string ua = "";
                
                std::cout << query << std::endl;
                std::cin >> ua;
                
                if (std::toupper(ua[0]) == 'Y' && (ua == "YES" || ua == "yes")) return true;
                else
                {
                        std::cout << "Canceled." << std::endl;
                        return false;
                }
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
                PrintLine();
                
                std::cout << "Help menu:\n" << std::endl;
                
                std::cout << "\tType \"exit\" or \"quit\" to exit the program\n"
                          << "\tType \"back\" to go back to the previous menu\n"
                          << "\tType \"last\" to show logs for a specific medication\n"
                          << "\tType \"rmlast\" to remove the last log entry\n"
                          << "\tType \"clear\" or \"cls\" to clear the screen\n"
                          << "\tType \"help\" to show this menu\n"
                          << std::endl;
                
                PrintLine();
                
                Pause();
        }

        void
        PrintMoreLogs(const std::string &sql_statement, const std::string &variable, bool is_short_format = false)
        {
                sqlite::database db(DBConfig::DBName);

                bool has_line = false;

                for (auto &&row: db << sql_statement << variable)
                {
                        if (!has_line)
                        {
                                PrintLine();
                                has_line = true;
                        }

                        std::string theDate;
                        std::string theTime;
                        std::string name;

                        double dose;

                        row >> theDate >> theTime >> name >> dose;

                        std::string tabs = (name.length() < 6) ? "\t\t" : "\t";
                        std::string header = (!is_short_format) ? theDate + " - " + theTime : theTime;

                        std::cout << "[" + header + "] " + name + tabs
                                  << dose << " mg"
                                  << std::endl;
                }
                if (has_line) PrintLine();

                if (!is_short_format) Pause();
        }

        void
        PrintLogsFromToday()
        {
                PrintMoreLogs("SELECT theDate, theTime, name, dose FROM logs WHERE theDate IS ? ;", Time::DateNow(), true);
        }

        void
        PrintMoreLogsFromLast(std::string &limit)
        {
                PrintMoreLogs("SELECT theDate, theTime, name, dose FROM logs ORDER BY ID DESC LIMIT ?;", limit);
        }

        void
        PrintLogsForDrugByName(const std::string &name_of_drug)
        {
                PrintMoreLogs("SELECT theDate, theTime, name, dose FROM logs WHERE name IS ? ORDER BY ID DESC LIMIT 10;", name_of_drug);
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
                
                std::string querry = "Are you sure you want to delete the last dose of " + name + " from the database? (Y/N)";
                
                if (DoesUserAgree(querry))
                {
                        db << "DELETE FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);";

                        std::cout << "The last dose of " + name + " has been removed from the database."
                                  << std::endl;
                }
        }
        
        
        ReturnStructures::InputReturn
        Menu(std::string &command)
        {
                /* This is the only command which returns something different so I check for it first. */
                if (command == "last")
                {
                        InfoLogs();
                        return { Actions::SHOW_LAST, true, false };
                }

                else if (command == "quit" || command == "exit")
                {
                        exit(EXIT_SUCCESS);
                }

                else if (command.find("logs") != std::string::npos)
                {
                        std::string num;
                        std::cin >> num;
                        PrintMoreLogsFromLast(num);
                }

                else if (command == "cls" || command == "clear" || command == "back")
                {
                        ClearScreen();
                }

                else if (command == "help")
                {
                        ClearScreen();
                        PrintHelp();
                }

                else if (command == "rmlast")
                {
                        RemoveLastLogEntry();
                        ClearScreen();
                }

                return { Actions::RUN_AGAIN, true, false };
        }
        
        ReturnStructures::InputReturn
        GetKey()
        {
                std::string it = "";
                
                try
                {
                        std::cin >> it;
                        
                        if (it.length() > 1) return Command::Menu(it);
                        
                        return { static_cast<int>(it[0] - 'a'), false, false };
                }
                catch (const std::exception& e)
                {
                        std::cerr << "ERROR: " << e.what() << std::endl;

                        return { Actions::ERROR, false, true };
                }
        }
}
