/*
 * nocurses is a modern C++ wrapper for ncurses
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT
 * <http://www.opensource.org/licenses/MIT>
 *
 * I do not own the ncurses library, they have their own license.
 */

#pragma once

#include <ncurses.h>
#include <string>

namespace noc {
class Window {
private:
  std::string m_title;
  int m_height;
  int m_width;
  int m_start_x;
  int m_start_y;
  WINDOW *m_window;

public:
  Window(const std::string title = "", const int height = 10, const int width = 80)
    : m_title(title)
    , m_height(height)
    , m_width(width)
    , m_start_x((COLS - width) / 2)
    , m_start_y((LINES - height) / 2)
  {
    initscr();
    cbreak();
    
    m_window = newwin(m_height, m_width, m_start_y, m_start_x);
    if (m_window == nullptr) {
      m_window = stdscr;
    }
    this->refresh();
  }

  ~Window() {
    this->refresh();
    delwin(m_window);
    endwin();
  }

  void refresh() const noexcept(true) {
    wrefresh(m_window);
  }
  
  void wait() const noexcept(true) {
    getch();
  }

  void print(const std::string line, const int start_y, const int start_x) const noexcept(false) {
    mvwprintw(m_window, start_y, start_x, "%s", line.c_str());
    this->refresh();
  }
  
  void print(const std::string line) const noexcept(false) {
    mvwprintw(m_window, m_start_y, m_start_x, "%s", line.c_str());
    this->refresh();
  }

public:
  void operator<<(const std::string line) {
    this->print(line);
  }

};


}
