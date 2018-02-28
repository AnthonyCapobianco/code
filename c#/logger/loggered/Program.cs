using System;

namespace loggered
{
    public class Drug
    {
        private string name;
        private decimal[] doses;
        private static int e = 0;

        //public string Name { get => name; set => name = value; }

        public void set(string Name, decimal[] Doses)
        {
            if (!string.IsNullOrEmpty(Name)) this.name = Name;
            else Console.WriteLine("The name used for item n° {0} is empty", e);

            this.doses = Doses;
            e++;
        }
        public void print()
        {
            for (int i = 0; i < e; i++)
            {
                Console.WriteLine("Name of the drug is: {0}", name);
                Console.WriteLine("The doses are: ");
                foreach (decimal d in doses) Console.Write("{0}, ", d);
            }
        }

    }

    class MainClass
    {
        
        public static void Main(string[] args)
        {
            Drug d = new Drug();
            decimal[] arrayOfDecimals = { 1, 2, 3 };
            d.set("name", arrayOfDecimals);

            d.print();
        }
    }
}
