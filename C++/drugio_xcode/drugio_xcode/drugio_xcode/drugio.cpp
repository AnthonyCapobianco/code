#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <initializer_list>

#include "resources/sqlite_modern_cpp.h"

const std::string BOLD_LINE = "════════════════════════════════════════════════════════════";

namespace DBConfig 
{
        const std::string DBName = "/Users/tony/Desktop/yogurd/logs/debug.db";
}

namespace Time 
{
        std::string 
        DateNow(void)
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%d-%m-%Y", std::localtime(&t));

                return (std::string) now;
        }
        
        std::string 
        TimeNow(void)
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%H:%M", std::localtime(&t));

                return (std::string) now;
        }
}

namespace Command
{        
        void
        Info(std::string name)
        {
                std::cout << "Please type the letter conresponding to the " << name << " taken" << std::endl
                          << "then press the return key. Type \".help\" for help.\n" << std::endl;
        }
        
        void
        PrintHelp(void)
        {
                using std::cout, std::endl;
                
                cout << BOLD_LINE << endl
                     << "Help menu:\n" << endl;
                
                cout << "\tType \".exit\" or \"quit\" to exit the program" << endl
                     << "\tType \".back\" to go back to the previous menu" << endl
                     << "\tType \".logs <N>\" to show N log entries before today" << endl
                     << "\tType \".rmlast\" to remove the last log entry" << endl
                     << "\tType \".clear\" or \".cls\" to clear the screen" << endl
                     << "\tType \".help\" to show this menu\n" << endl;
                
                cout << BOLD_LINE << endl;
        }

                
        void 
        ClearScreen(void)
        {
                #if defined (_WIN32) || defined (_WIN64)
                        #define ESC_CLS "Just install a decent operating system."
                #else
                        #define ESC_CLS "\x1B[2J"
                #endif
                
                std::cout << ESC_CLS << std::endl;
        }
        
        void
        PrintLogs(void)
        {
                sqlite::database db(DBConfig::DBName);
                
                for (auto &&row : db << "SELECT theTime, name, dose FROM logs WHERE theDate IS ? ;" << Time::DateNow()) 
                {
                        std::string theTime; std::string name; double dose;
                        
                        row >> theTime >> name >> dose;
                        std::cout << "[" << theTime << "]" << ' ' << name << ' ' << dose << std::endl;
                }
        }
        
        void
        PrintMoreLogs(void)
        {
                sqlite::database db(DBConfig::DBName);
                
                for (auto &&row : db << "SELECT theDate, theTime, name, dose FROM logs WHERE theDate != ? ORDER BY ID DESC LIMIT 10;" << Time::DateNow())
                {
                        std::string theDate; std::string theTime; std::string name; 
                        double dose; 
                        
                        row >> theDate >> theTime >> name >> dose;
                        
                        std::cout << "[" << theDate << " - " << theTime << "] " << name << "\t" << dose << " mg" << std::endl; 
                }
                
        }
        
        int
        Menu(std::string command)
        {
                if (command.compare(".help") == 0) PrintHelp();
                
                if (command.compare(".quit") == 0 || command.compare(".exit") == 0) exit(EXIT_SUCCESS);
                
                if (command.compare(".back") == 0)
                {
                        ClearScreen();
                        PrintLogs();
                }
                
                if (command.compare(".cls") == 0 || command.compare(".clear") == 0)
                {
                        ClearScreen();
                }
                
                if (command.compare(".logs"))
                {
                        ClearScreen();
                        PrintMoreLogs();
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
                
                const std::vector<double>
                GetDoses(void){ return this->_doses; }

                const std::string
                GetName(void){ return this->_name; }
                
                const double
                GetSelection(Drug d)
                {
                        std::string user_input = "";
                        
                        do 
                        {       
                                Command::Info("dose");
                                
                                PrintDoses(d);
                                std::cin >> user_input; 
                                
                                if (user_input[0] == '.' && Command::Menu(user_input) == 1) return -1.0;
                                
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
                PrintNames(void)
                {
                        char c = 'a';
                        
                        Command::Info("drug");
                        
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
                
                void
                Menu(void)
                {
                        while (true)
                        {
                                std::cout << BOLD_LINE << std::endl;
                                
                                Command::PrintLogs();
                                
                                std::cout << BOLD_LINE << std::endl;
                                
                                char last = PrintNames();
                                
                                std::string key_or_string = "";
                                std::cin >> key_or_string; 
                                
                                if (key_or_string[0] == '.' && Command::Menu(key_or_string) == 1) continue;
                                else
                                {
                                        if (key_or_string[0] != '.' && (key_or_string[0] -= 'a') >= this->_list.size()) 
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
        
        while (true) medications.Menu();
}
