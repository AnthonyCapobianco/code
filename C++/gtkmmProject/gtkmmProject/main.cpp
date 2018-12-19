//
//  main.cpp
//  gtkmmProject
//
//  Created by aj on 28/06/2018.
//  Copyright © 2018 aj. All rights reserved.
//

//#include <iostream>
#include <gtkmm.h>

int main()
{
        //Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

        auto app = Gtk::Application::create("org.aj.com");
        Gtk::Window win;

        win.set_default_size(500, 500);
        win.set_title("gtkmmProject");

        Gtk::Button button_quit;
        button_quit.set_label("QUIT");
        button_quit.clicked();

        Gtk::Box box;
        box.pack_start(button_quit);

        win.set_attached_to(box);



        return app->run(win);
}
