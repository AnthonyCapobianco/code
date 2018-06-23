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

#include <ctime>
#include "includes/Time.hpp"

namespace Time
{
        std::string DateNow()
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%d-%m-%Y", std::localtime(&t));
                
                return now;
        }
        
        std::string TimeNow()
        {
                std::time_t t = std::time(nullptr);
                char now[100] = "";
                
                std::strftime(now, sizeof(now), "%H:%M", std::localtime(&t));
                
                return now;
        }
}
