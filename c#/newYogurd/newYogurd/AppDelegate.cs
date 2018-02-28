using AppKit;
using Foundation;
using System;

namespace newYogurd
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

            int i = 0;
            foreach (decimal d in Doses)
            {
                this.doses[i] = d;
                ++i;
            }
            e++;
        }
    }

    [Register("AppDelegate")]
    public partial class AppDelegate : NSApplicationDelegate
    {
        public AppDelegate()
        {
            
        }

        public override void DidFinishLaunching(NSNotification notification)
        {
            
        }

        public override void WillTerminate(NSNotification notification)
        {
            // Insert code here to tear down your application
        }
    }
}
