//
//  AppDelegate.swift
//  toAppOrNotToApp
//
//  Created by Anthony Capobianco on 16/02/2018.
//  Copyright © 2018 Anthony Capobianco. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {



    func applicationDidFinishLaunching(_ aNotification: Notification) {
        // Insert code here to initialize your application
        main();
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }

    func main() -> Int {
        //var i: Int = 0;
        for i in 1...10{
            print(i);
        }

        return 0;
    }

}

