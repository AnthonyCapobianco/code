using System;
using Plugin.BluetoothLE;
using static System.Console;

namespace SendKeys
{
        class Program
        {

                static void 
                Main(string[] args)
                {
                        WriteLine("Hello World!");
                        
                        // discover some devices
                        CrossBleAdapter.Current.Scan().Subscribe(scanResult => {});

                        
                }
        }
}
