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

#include "../Command.cpp"
#include "../ReturnStructures.cpp"
#include "../../resources/sqlite_modern_cpp.h"

namespace Command
{
        ReturnStructures::InputReturn GetKey();

        bool DoesUserAgree(const std::string &);
        
        void PrintLine();
        
        void Info(const std::string &);
        
        void InfoLogs();
        
        void PrintHelp();
        
        void ClearScreen();
        
        void PrintLogsFromToday();
        
        void PrintMoreLogs(const std::string &);
        
        const std::string GetLastNameInDatabase();
        
        void RemoveLastLogEntry();
  
        ReturnStructures::InputReturn Menu(std::string &);
}
