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
private:
  const std::string m_name;
  const std::vector<double> m_doses;

  char print_doses() const noexcept(true) {
    // Show last 3 doses with full date
    Command::print_logs_for_drug_by_name(m_name, "3", false, false);
    std::cout << std::endl;

    char c = 'a';

    for (auto it : this->get_doses()) {
      std::cout << "[" << c++ << "] " << it << std::endl;
    }

    std::cout << "\n> " << std::flush;

    return c;
  }

public:
  Drug(const std::string &drug_name, const std::initializer_list<double> &dose_array) noexcept(true)
  : m_name{drug_name}
  , m_doses{dose_array.begin(), dose_array.end()} {
  }

  const std::vector<double>& get_doses() const noexcept(true) {
    return m_doses;
  }

  const std::string& get_name() const noexcept(true) {
    return m_name;
  }

  double get_selection() const  noexcept(false) {
    ReturnStructures::InputReturn it;

    if (m_doses.empty()) {
      throw DrugioException::NotDouble();
    }

    else if (m_doses.size() != 1) {
      Command::print_info("dose");

      this->print_doses();
      it = Command::get_key();

      if (it.is_action or it.is_error) {
        throw DrugioException::IsAction();
      }

      return m_doses.at(static_cast<size_t>(it.key));
    }

    return m_doses.at(0);
  }
} /* class Drug */;

class DrugList {
 private:
  const std::vector<Drug> m_drug_list;

  int print_drugs() const {
    char c = 'a';

    for (auto d : m_drug_list) {
      std::cout << "[" << c++ << "] " << d.get_name() << std::endl;
    }

    std::cout << "\n> ";
    std::cout.flush();

    return (c - 'a') - 1;
  }

  Drug get_selection(int& user_input) const noexcept(false) {
    return m_drug_list.at(static_cast<size_t>(user_input));
  }

  ReturnStructures::UserSelection get_dose_used(int &user_input) const noexcept(false) {
    try {
      Drug d = this->get_selection(user_input);
      double dose_used;

      try {
        dose_used = d.get_selection();
      } catch (DrugioException::NotDouble &nd) {
        std::cerr << "ERROR: " << nd.what();
      } catch (DrugioException::IsAction) {
        // Just leave and return nothing (make it optional)
        return {"", 0.0, false};
      }

      return {d.get_name(), dose_used, true};
    } catch (std::out_of_range &oor) {
      std::cerr << "ERROR: Out of range (" << oor.what() << ").";
    }

    return {"", 0.0, false};
  }

  void show_last() const noexcept(false) {
    ReturnStructures::InputReturn it = Command::get_key();
    Command::clear_screen();

    int list_size = static_cast<int>(m_drug_list.size());

    if (not it.is_action and not it.is_error and it.key >= 0 and
        it.key < list_size) {
      Drug d = this->get_selection(it.key);
      Command::print_logs_for_drug_by_name(d.get_name());
    }
  }

 public:
  DrugList(const std::initializer_list<Drug> &d) : m_drug_list{d} {}

   void menu() const noexcept(false) {
    while (true) {
      ReturnStructures::InputReturn it;

      while (true) {
        Command::print_info("drug");
        Command::print_todays_log();

        print_drugs();

        it = Command::get_key();

        if (it.is_action and it.key == Actions::SHOW_LAST) {
          show_last();
          Command::pause();
        } else {
          if (it.is_error or (it.is_action and it.key == Actions::RUN_AGAIN))
            continue;

          int list_size = static_cast<int>(m_drug_list.size());

          if (it.key >= 0 and it.key < list_size) break;
        }
      } /* while (true) Input loop */

      ReturnStructures::UserSelection us = this->get_dose_used(it.key);

      if (not us.has_dosage) continue;

      sqlite::database db(DBConfig::DBName);

      db << "INSERT INTO logs (theDate, theTime, name, dose) VALUES (?, ?, ?, "
            "?);"
         << Time::DateNow() << Time::TimeNow() << us.name << us.dose;

    } /* while (true) Program loop */
  } /* Menu() */
} /* class DrugList */;
} /* namespace Drugio */
