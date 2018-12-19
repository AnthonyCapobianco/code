//
//  main.cpp
//  nocurses
//
//  Created by aj on 08/12/2018.
//  Copyright © 2018 aj. All rights reserved.
//

#include <iostream>
#include "includes/nocurses.h"

int main(int argc, const char * argv[]) {

//  noc::Window win("test");
//  win << "hello"; refresh();
//  win.wait();
  initscr();
  std::cout << "hello" << std::endl;
  getch();
  std::cout << "hello" << std::endl;
  getch();
  endwin();
}
