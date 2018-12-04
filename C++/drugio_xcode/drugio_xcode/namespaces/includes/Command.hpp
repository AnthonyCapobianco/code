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

#include "../../resources/sqlite_modern_cpp.h"
#include "../Command.cpp"
#include "../ReturnStructures.cpp"

namespace Command {
ReturnStructures::InputReturn get_key();

bool user_agrees(const std::string &) noexcept(true);

void print_horizontal_separator() noexcept(true);

void print_info(const std::string &) noexcept(true);

void print_log() noexcept(true);

void print_help() noexcept(true);

void clear_screen() noexcept(true);

void print_todays_log() noexcept(false);

void print_log_by_drug_name(const std::string &, const std::string, bool) noexcept(false);

void print_more_logs() noexcept(false);

void print_more_logs_from_last() noexcept(false);

std::string get_last_drug_name_in_db() noexcept(false);

void remove_last_log_entry() noexcept(false);

ReturnStructures::InputReturn menu(std::string &) noexcept(false);
}  // namespace Command
