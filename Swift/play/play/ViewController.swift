//
//  ViewController.swift
//  play
//
//  Created by aj on 09/04/2018.
//  Copyright © 2018 aj. All rights reserved.
//

import Cocoa
import WebKit

class ViewController: NSViewController {

        override func viewDidLoad() {
                super.viewDidLoad()
        }

        override var representedObject: Any?
        {
                didSet
                {
                        // Update the view, if already loaded.
                        let url = NSURL(string: "https://play.google.com/music/listen#/home");
                        let request = Foundation.NSURLRequest(url: url! as URL);
                        WebView.loadRequest(request);
                }
        }


}

