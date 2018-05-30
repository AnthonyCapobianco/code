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
 
using System;
using System.Collections.Generic;
using System.Linq;

namespace Drugio
{
        class Drug
        {
                string _name;
                List<double> _doses;
                
                char
                PrintDoses()
                {
                        char c = 'a';

			foreach (var it in _doses)
			{
				Console.WriteLine($"[{c++}] {it}");
			}

			Console.Write("\n> ");
                        
                        return c;
                }
                
                public Drug(string n, List<double> d) 
                {
			_name = n;
                        _doses = d;
                }
                
                public List<double> GetDoses() =>_doses;
                
                public string GetName() =>_name;
                
                public ReturnStructures.MaybeDouble
                GetSelection()
                {
                        ReturnStructures.InputReturn it;

			if (_doses.Count == 0) return new ReturnStructures.MaybeDouble(0, false);
			
                        if (_doses.Count() != 1)
			{
				Command.Info("dose");

				PrintDoses();
				it = Command.GetKey();

				if (it.is_action || it.is_error) return new ReturnStructures.MaybeDouble(0, false);

				return new ReturnStructures.MaybeDouble(_doses[it.key], true);
			}
			return new ReturnStructures.MaybeDouble(_doses[0], true);
                }
        } /* class Drug */;

        class DrugList
        {
                List<Drug> _list;
                
                int
                PrintNames()
                {
                        char c = 'a';

			foreach (var d in _list)
			{
				Console.WriteLine($"[{c++}] {d.GetName()}");
			}
                        
                        Console.Write("\n> ");
                        
                        return (c - 'a') - 1;
                }

		Drug GetSelection(int user_input) => _list[user_input];
                
                ReturnStructures.UserSelection
                GetUsedDose(int user_input)
                {
                        try
                        {
                                Drug d = GetSelection(user_input);
                                ReturnStructures.MaybeDouble dose_used = d.GetSelection();
                                
                                if (dose_used.is_double) 
                                {
					return new ReturnStructures.UserSelection(d.GetName(), dose_used.dosage, true); 
                                }
                        }
                        catch (Exception oor)
                        {
				Console.Write($"ERROR: Out of range ({oor.what()}");
                        }
                        
                        return new ReturnStructures.UserSelection("", 0.0, false );
                }

                void
                ShowLast()
                {
                        ReturnStructures.InputReturn it = Command.GetKey();
                        Command.ClearScreen();

			int list_size = _list.Count();

                        if (!it.is_action && !it.is_error
                            && it.key >= 0 && it.key < list_size)
                        {
                                Drug d = GetSelection(it.key);
                                Command.PrintLogsForDrugByName(d.GetName());
                        }
                }
                
                public DrugList(List<Drug> d)
                {
			_list = d;
                }
                
                void
                Menu()
                {
                        while (true)
                        {
                                ReturnStructures.InputReturn it;

                                while (true)
                                {
                                        Command.Info("drug");
                                        Command.PrintLogsFromToday();

                                        PrintNames();

                                        it = Command.GetKey();

                                        if (it.is_action and it.key == Actions.SHOW_LAST) ShowLast();
                                        else
                                        {
                                                if (it.is_error || (it.is_action && it.key == Actions.Actions.RUN_AGAIN)) continue;

                                                int list_size = this._list.Count();
                                                if (it.key >= 0 and it.key < list_size) break;
                                        }
                                        continue;
                                } /* while (true)  */

                                ReturnStructures.UserSelection us = GetUsedDose(it.key);

                                if (!us.has_dosage) continue;

                                sqlite.database db(DBConfig.DBName);

                                db << "INSERT INTO logs (theDate, theTime, name, dose) VALUES (?, ?, ?, ?);"
                                   << Time.DateNow() << Time.TimeNow() << us.name << us.dose;

                        } /* while (true) */
                } /* Menu() */
        }/* class DrugList */;
} /* namespace Drugio */
