using System;
using System.Collections.Generic;

namespace DBConfig
{
        
        
}

namespace dlog2
{
        public class Drugs
        {
        
                static int
                GetKey(char last)
                {
                        char key;
                        while ((key = Console.ReadKey().KeyChar) >= last && key < 'a') Console.Write("\b");
                        
                        char UserInput = '\0';

                        if (char.TryParse(key.ToString(), out UserInput))
                        {
                                return (UserInput - 'a');
                        }
                        
                        return -1;
                }
                
                class DrugNameAndDoses
                {
                        public string name;
                        public List<double> doses;
                        
                        public 
                        DrugNameAndDoses(string DrugName, List<double> DrugDoses)
                        {
                                name = DrugName;
                                doses = DrugDoses;
                        }
                        
                        char
                        PrintDoses()
                        {
                                char ident = 'a';
                                
                                foreach (var d in doses)
                                {
                                        Console.WriteLine($"[{ident}] {d} mg");
                                        ident++;
                                }

                                return ident;
                        }
                        
                        public double
                        GetDose()
                        {
                                if (doses.Count == 1) return doses[0];
                                
                                else
                                {
                                        var DoseIndex = GetKey(PrintDoses());

                                        if (DoseIndex < doses.Count)
                                        {
                                                Console.WriteLine();
                                                return doses[DoseIndex];
                                        }
                                        return -1;
                                }
                        } 
                }

                static readonly List<DrugNameAndDoses> ListOfDrugs = new List<DrugNameAndDoses>();

                public void
                Add(string DrugName, List<double> Doses)
                {
                        ListOfDrugs.Add(new DrugNameAndDoses(DrugName, Doses));
                }
        
                public void
                PrintNames()
                {
                        char ident = 'a';

                        foreach (var d in ListOfDrugs)
                        {
                                Console.WriteLine($"[{ident}] {d.name}");
                                ident++;
                        }
                        
                        var IndexFromInput = GetKey(ident);
                        
                        if (IndexFromInput < ListOfDrugs.Count && IndexFromInput > -1)
                        {
                                Console.WriteLine();
                                DrugNameAndDoses ChosenOne = ListOfDrugs[IndexFromInput];

                                var DoseUsed = ChosenOne.GetDose();
                                
                                if (DoseUsed > -1)
                                {
                                        /******************************************************************
                                         *       TO DO -> write function to add the dose to the db.       * 
                                         ******************************************************************/
                                        DateTime TimeNow = DateTime.Now;
                                        const string LOCALE = "dd/MM/yyyy - HH:mm";
                                        
                                        Console.WriteLine($"[{TimeNow.ToString(LOCALE)}] {ChosenOne.name}\t{DoseUsed} mg");
                                }
                        }
                }
        }

        public class Yogurd
        {
                static void
                Main()
                {
                        var DrugList = new Drugs();
                        
                        DrugList.Add("Ritalin", new List<double> { 5, 10, 15, 20 });
                        DrugList.Add("Concerta", new List<double> { 36, 72 });
                        DrugList.Add("Effexor", new List<double> { 225 });
                        DrugList.Add("Xanax", new List<double> { 0.25, 0.5, 0.7, 1, 1.5, 2, 2.5, 3 });

                        DrugList.PrintNames();
                }
        }
}
