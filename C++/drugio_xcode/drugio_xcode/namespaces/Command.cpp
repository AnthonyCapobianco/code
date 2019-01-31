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

#include <fstream>
#include <iostream>
#include <string>

#include "includes/Actions.hpp"
#include "includes/Command.hpp"
#include "includes/DBConfig.hpp"
#include "includes/Time.hpp"

#include "ReturnStructures.cpp"

namespace Command {
static inline void pause()
noexcept(true) {
  std::cout << "Press the return key to go back to the main menu." << std::endl;

  std::cin.get();
  std::cin.ignore();
}

static void clear_screen() 
noexcept(true) {
#if defined(_WIN32) || defined(_WIN64)
  std::system("cls");
#else
  std::cout << "\x1B[3J";
#endif
}

static void print_horizontal_separator() 
noexcept(true) {
  std::cout << "════════════════════════════════════════════════════════════\n";
}

bool user_agrees(const std::string& query) 
noexcept(true) {
  std::string ua;

  std::cout << query << std::endl;
  std::cin >> ua;

  if (std::toupper(ua[0]) == 'Y' and (ua == "YES" or ua == "yes")) {
    return true;
  } else {
    std::cout << "Canceled.";
    return false;
  }
}

void print_info(const std::string& name) 
noexcept(true) {
  std::cout << "Please type the letter conresponding to the " + name + " taken\n"
            << "then press the return key. Type \"help\" for help.\n\n";
}

static void print_log()
noexcept(true) {
  std::cout << "Please type the letter conresponding to the drug\n"
            << "you want to see the logs for then press the return key."
            << "\n> ";

  std::cout.flush();
}

static void print_help()
noexcept(true) {
  print_horizontal_separator();

  std::cout << "Help menu:\n\n"
            << "\tType \"exit\" or \"quit\" to exit the program\n"
            << "\tType \"back\" to go back to the previous menu\n"
            << "\tType \"last\" to show logs for a specific medication\n"
            << "\tType \"rmlast\" to remove the last log entry\n"
            << "\tType \"csv\" to export your logs to a csv file\n"
            << "\tType \"clear\" or \"cls\" to clear the screen\n"
            << "\tType \"help\" to show this menu\n\n";

  print_horizontal_separator();

  pause();
}

void print_more_logs(const std::string& sql_statement
  , const std::string& variable
  , bool is_short_format = false
  , bool is_single_screen = true)
noexcept(false) {
  
  sqlite::database db(DBConfig::DBName);

  bool has_line = false;

  for (auto&& row : db << sql_statement << variable) {
    if (not has_line) {
      print_horizontal_separator();
      has_line = true;
    }

    std::string theDate;
    std::string theTime;
    std::string name;

    double dose;

    row >> theDate >> theTime >> name >> dose;

    std::string header =
        (!is_short_format) ? theDate + " - " + theTime : theTime;

    std::cout << "[" + header + "] " + name + " \t" << dose << " mg\n";
  }
  if (has_line) print_horizontal_separator();

  if (not is_short_format and is_single_screen) pause();
}

void print_todays_log() {
  print_more_logs(DBConfig::select_statement + "WHERE theDate IS ? ;"
  , Time::DateNow()
  , true // short format
  , false // single screen
  );
}

std::string get_last_drug_id_in_db()
noexcept(false) {
  sqlite::database db(DBConfig::DBName);
  std::string id;

  db << "SELECT ID FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);" >> id;

  return id;
}

void print_more_logs_from_last(unsigned int& limit)
noexcept(false) {
  std::string limit_string = (limit <= 30) ? std::to_string(limit) : "10";

  print_more_logs(DBConfig::select_statement
  + "WHERE ID >= ((SELECT MAX(ID) FROM logs) + 1 - " + limit_string + ") ORDER BY ID ASC LIMIT ?;"
  , limit_string
  , false // short format
  , true // single screen
  );
}

void print_logs_for_drug_by_name(const std::string& name_of_drug
  , const std::string limit = "10"
  , bool is_short = false
  , bool is_excerpt = false)
noexcept(false) {

  print_more_logs(DBConfig::select_statement
    + "WHERE name IS ? ORDER BY ID DESC LIMIT " + limit + ";"
  , name_of_drug
  , is_short
  , is_excerpt
  );
}

std::string get_last_drug_name_in_db()
noexcept(false) {
  sqlite::database db(DBConfig::DBName);
  std::string name;

  db << "SELECT name FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);" >> name;

  return name;
}


void remove_last_log_entry()
noexcept(false) {
  sqlite::database db(DBConfig::DBName);
  print_horizontal_separator();

  const std::string name = get_last_drug_name_in_db();

  std::string querry = "Are you sure you want to delete the last dose of "
    + name + " from the database? (Y/N)";

  if (user_agrees(querry)) {
    db << "DELETE FROM logs WHERE ID IS (SELECT MAX(ID) FROM logs);";

    std::cout << "The last dose of " + name + " has been removed from the database."
              << std::endl;
  }
}

bool export_log_to_csv_file()
noexcept(false) {
  sqlite::database db(DBConfig::DBName);

  std::string csv_file_path = DBConfig::DBFolder + "backup.csv";
  std::string sql_statement = DBConfig::select_statement + " WHERE 1";

  std::ofstream csv_file;
  csv_file.open(csv_file_path, std::ios::trunc);

  if (csv_file.is_open()) {
    for (auto&& row : db << sql_statement) {
      std::string date;
      std::string time;
      std::string name;
      double dose;
      row >> date >> time >> name >> dose;

      csv_file << date + ", " + time + ", " + "\"" + name + "\"" + ", " << dose << "\n";
    }

    csv_file.close();

    return true;
  }
  return false;
}


/*
 *  struct InputReturn {
 *    int key;
 *    bool is_action;
 *    bool is_error;
 *  };
 */
ReturnStructures::InputReturn menu(std::string& command)
noexcept(false) {
  /* This is the only command which returns something different so I check for
   * it first. */
  if (command == "last") {
    print_log();
    return { Actions::SHOW_LAST, true, false };

  } else if (command == "quit" or command == "exit") {
    export_log_to_csv_file();
    clear_screen();
    std::exit(EXIT_SUCCESS);

  } else if (command.find("logs") != std::string::npos) {
    unsigned int num;
    std::cin >> num;

    if (std::cin.eof() or std::cin.bad()) {
      num = 10;
    } else if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    print_more_logs_from_last(num);

  } else if (command == "cls" or command == "clear" or command == "back") {
    clear_screen();

  } else if (command == "help") {
    clear_screen();
    print_help();

  } else if (command == "rmlast") {
    remove_last_log_entry();
    clear_screen();

  } else if (command == "csv") {
    if (export_log_to_csv_file()) {
      std::cout << "Success." << std::endl;

    } else {
      std::cerr << "ERROR: Couldn't open the CSV log file" << std::endl;
    }
  }

  return { Actions::RUN_AGAIN, true, false };
}

ReturnStructures::InputReturn get_key()
noexcept(false) {
  std::string it;

  try {
    std::cin >> it;

    if (it.length() > 1) return Command::menu(it);

    return {static_cast<int>(it[0] - 'a'), false, false};

  } catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;

    return {Actions::ERROR, false, true};
  }
}
}  // namespace Command
