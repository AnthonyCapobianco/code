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

namespace ReturnStructures
{
        class InputReturn
        {       
                public readonly int key;
                public readonly bool is_action;
                public readonly bool is_error;
                
                public InputReturn(int key, bool is_action, bool is_error)
                { 
                        this.key = key;
			this.is_action = is_action;
			this.is_error = is_error;
                }
        };

        class UserSelection
        {       
                public readonly string name;
                public readonly double dose;
                public readonly bool has_dosage;
                
                public UserSelection(string name, double dose, bool has_dosage)
                {
			this.name = name;
			this.dose = dose;
			this.has_dosage = has_dosage;
                }
        };

        class MaybeDouble
        {       
                public readonly double dosage;
                public readonly bool is_double;
                
                public MaybeDouble(double dosage, bool is_double)
                {
			this.dosage = dosage;
			this.is_double = is_double;
                }
        };
} ;
