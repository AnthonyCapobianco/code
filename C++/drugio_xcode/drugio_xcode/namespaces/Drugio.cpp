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

#pragma once

#include "includes/Actions.hpp"
#include "includes/Command.hpp"
#include "includes/DBConfig.hpp"
#include "includes/DrugioExceptions.hpp"
#include "includes/Time.hpp"

#include "ReturnStructures.cpp"

namespace Drugio {

class Drug {
  const std::string _name;
  const std::vector<double> _doses;

  char PrintDoses() const {
    // Show last 3 doses with full date
    Command::PrintLogsForDrugByName(this->_name, "3", false, false);
    std::cout << std::endl;

    char c = 'a';

    for (auto it : this->GetDoses()) {
      std::cout << "[" << c++ << "] " << it << std::endl;
    }

    std::cout << "\n> " << std::flush;

    return c;
  }

 public:
  Drug(const std::string &drug_name,
       const std::initializer_list<double> &dose_array)
      : _name{drug_name}, _doses{dose_array.begin(), dose_array.end()} {}

  const std::vector<double> &GetDoses() const { return this->_doses; }

  const std::string &GetName() const { return this->_name; }

  double GetSelection() const {
    ReturnStructures::InputReturn it;

    if (this->_doses.empty()) {
      throw DrugioException::NotDouble();
    }

    else if (this->_doses.size() != 1) {
      Command::Info("dose");

      this->PrintDoses();
      it = Command::GetKey();

      if (it.is_action or it.is_error) {
        throw DrugioException::IsAction();
      }

      return this->_doses.at(static_cast<size_t>(it.key));
    }

    return this->_doses.at(0);
  }
} /* class Drug */;

class DrugList {
 private:
  const std::vector<Drug> _list;

  int PrintNames() const {
    char c = 'a';

    for (auto d : this->_list) {
      std::cout << "[" << c++ << "] " << d.GetName() << std::endl;
    }

    std::cout << "\n> ";
    std::cout.flush();

    return (c - 'a') - 1;
  }

  Drug GetSelection(int &user_input) const {
    return this->_list.at(static_cast<size_t>(user_input));
  }

  ReturnStructures::UserSelection GetUsedDose(int &user_input) const {
    try {
      Drug d = this->GetSelection(user_input);
      double dose_used;

      try {
        dose_used = d.GetSelection();
      } catch (DrugioException::NotDouble &nd) {
        std::cerr << "ERROR: " << nd.what() << std::endl;
      } catch (DrugioException::IsAction) {
        // Just leave and return nothing (make it optional)
        return {"", 0.0, false};
      }

      return {d.GetName(), dose_used, true};
    } catch (std::out_of_range &oor) {
      std::cerr << "ERROR: Out of range (" << oor.what() << ")." << std::endl;
    }

    return {"", 0.0, false};
  }

  void ShowLast() const {
    ReturnStructures::InputReturn it = Command::GetKey();
    Command::ClearScreen();

    int list_size = static_cast<int>(this->_list.size());

    if (not it.is_action and not it.is_error and it.key >= 0 and
        it.key < list_size) {
      Drug d = this->GetSelection(it.key);
      Command::PrintLogsForDrugByName(d.GetName());
    }
  }

 public:
  DrugList(const std::initializer_list<Drug> &d) : _list{d} {}

  inline void Menu() {
    while (true) {
      ReturnStructures::InputReturn it;

      while (true) {
        Command::Info("drug");
        Command::PrintLogsFromToday();

        PrintNames();

        it = Command::GetKey();

        if (it.is_action and it.key == Actions::SHOW_LAST)
          ShowLast();
        else {
          if (it.is_error or (it.is_action and it.key == Actions::RUN_AGAIN))
            continue;

          int list_size = static_cast<int>(this->_list.size());

          if (it.key >= 0 and it.key < list_size) break;
        }
      } /* while (true) Input loop */

      ReturnStructures::UserSelection us = this->GetUsedDose(it.key);

      if (not us.has_dosage) continue;

      sqlite::database db(DBConfig::DBName);

      db << "INSERT INTO logs (theDate, theTime, name, dose) VALUES (?, ?, ?, "
            "?);"
         << Time::DateNow() << Time::TimeNow() << us.name << us.dose;

    } /* while (true) Program loop */
  }   /* Menu() */
} /* class DrugList */;
} /* namespace Drugio */
