/*
 * version: 0.0.2~idgaff
 */

/*
 * C++ port of failsafewm
 * Copyright (c) 2018 ViralTaco_
 * SPDX-License-Identifier: GPL-2.0-only
 * <https://opensource.org/licenses/GPL-2.0>
 */

/***************************************************************************
              failsafewm.h  -  description
              ---------------------
  begin                : Sun Dec 25 18:12:15 CEST 2001
  copyright            : (C) 2000-2001 by Robert Sperling
  email                : sperling@small-window-manager.de
  version              : v0.0.2
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#pragma once

#ifndef CONFDIR
#define CONFDIR "$HOME"
#endif

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>
#include <cstdlib>

namespace vt {
class WindowManager {
private:
  static constexpr auto kChildMask = SubstructureRedirectMask | SubstructureNotifyMask;
  static constexpr auto kButtonMask = ButtonPressMask | ButtonReleaseMask;
  static constexpr auto kMouseMask = kButtonMask | PointerMotionMask;
  static constexpr auto kDragMask = PointerMotionMask | ButtonPressMask;

  /* X11 needed things */
  static constexpr const char *m_display_option = "";
  Display *m_display;
  int m_screen;
  Window m_root_window;

  Window m_focused_window;
  int m_dummy;
  unsigned int m_size_x;
  unsigned int m_size_y;

  Atom xa_wm_state;
  Atom xa_wm_change_state;
  Atom xa_wm_protos;
  Atom xa_wm_delete;
  Atom xa_mwm_wm_hints;
  int m_motion_x = -1;
  int m_motion_y = -1;
  bool m_want_exit = false;

  enum pointer_modes {
    point
  , move
  , resize  
  };

  int m_pointer_mode = pointer_modes::point;
  
public:
  WindowManager() noexcept(true)
    : m_display(XOpenDisplay(m_display_option))
    , m_screen(DefaultScreen(m_display))
    , m_root_window(RootWindow(m_display, m_screen))
    , xa_wm_protos(XInternAtom(m_display, "WM_PROTOCOLS", False))
    , xa_wm_delete(XInternAtom(m_display, "WM_DELETE_WINDOW", False))
  {
    if (m_display == nullptr) {
      fprintf(stderr, "vtwm: cannot open display, giving up\n:(\n");
      std::exit(EXIT_FAILURE);
    }

    GrabKeys();
    EventLoop();
  }
  
private:
  
  inline void DoGrabKey(const char *key_string) const noexcept(true) {
    XGrabKey(m_display, XKeysymToKeycode(m_display, XStringToKeysym(key_string))
      , Mod1Mask, m_root_window, True, GrabModeAsync, GrabModeAsync
    );
  }
  
  void GrabKeys() const noexcept(true) {
    DoGrabKey("Tab");
    DoGrabKey("F2");
    DoGrabKey("F3");
    DoGrabKey("F4");
    DoGrabKey("F5");
  }

  void KeyEventHandler(XKeyEvent *event) noexcept(true) {
    int dummy_num;
    unsigned int dummy_unsigned;
    Window dummy_window;

    XQueryPointer(m_display, m_root_window, &dummy_window, &m_focused_window
      , &dummy_num, &dummy_num, &dummy_num, &dummy_num, &dummy_unsigned
    );
    
    if (event->keycode == XKeysymToKeycode(m_display, XStringToKeysym("Tab"))
    and event->state == Mod1Mask) {
      XCirculateSubwindowsUp(m_display, m_root_window);
    }

    if (event->keycode == XKeysymToKeycode(m_display, XStringToKeysym("F2"))
    and event->state == Mod1Mask) {
      m_pointer_mode = pointer_modes::move;
      XGrabPointer(m_display, m_focused_window, False
        , kDragMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime
      );
    }
    
    if (event->keycode == XKeysymToKeycode(m_display, XStringToKeysym("F3")) 
    and event->state == Mod1Mask) {
      m_pointer_mode = pointer_modes::resize;
      
      XGrabPointer(m_display, m_focused_window, False
        , kDragMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime
      );

      XGetGeometry(m_display, m_focused_window, &m_root_window
        , &dummy_num, &dummy_num, &m_size_x, &m_size_y, &dummy_unsigned, &dummy_unsigned
      );
    }
    
    if (event->keycode == XKeysymToKeycode(m_display, XStringToKeysym("F4"))
    and event->state == Mod1Mask) {
      SendExitClient(m_focused_window);
    }
    
    if (event->keycode == XKeysymToKeycode(m_display, XStringToKeysym("F5"))
    and event->state == Mod1Mask) {
      XRaiseWindow(m_display, m_focused_window);
    }
  }

  void ButtonPressedEventHandler(XButtonEvent *event) noexcept(true) {
    while (XCheckTypedEvent(m_display, ButtonPress, (XEvent *) event)) {
      // Do nothing
    }

    if (event->window == m_root_window) {
      switch (event->button) {
        case Button1:
          system(CONFDIR
                 "/.failsafewm/button1"
                 "&");
          break;
        case Button2:
          system(CONFDIR
                 "/.failsafewm/button2"
                 "&");
          break;
        case Button3:
          system(CONFDIR
                 "/.failsafewm/button3"
                 "&");
          break;
      }
    } else {
      XUngrabPointer(m_display, CurrentTime);
      switch (event->button) {
        case Button1:
          m_pointer_mode = pointer_modes::point;
        case Button2: case Button3:
          break;
      }
    }
  }

  void MouseMotionEventHandler(XMotionEvent *event) noexcept(true) {
    if (m_motion_x < 0) m_motion_x = event->x = event->x_root;
    if (m_motion_y < 0) m_motion_y = event->y = event->y_root;

    while (XCheckTypedEvent(m_display, MotionNotify, (XEvent *) event)) {
      // Do nothing.
    }

    if (m_pointer_mode == pointer_modes::move) {
      XMoveWindow(m_display, m_focused_window, event->x_root, event->y_root);
    }
    if (m_pointer_mode == pointer_modes::resize) {
      XResizeWindow(m_display, m_focused_window
        , m_size_x + event->x_root - m_motion_x
        , m_size_y + event->y_root - m_motion_y
      );
    }
  }
  
  int SendXMessage(Window given_window, Atom xatom, long value) noexcept(true) {
    XEvent event;
    event.type = ClientMessage;
    event.xclient.window = given_window;
    event.xclient.message_type = xatom;
    event.xclient.format = 32;
    event.xclient.data.l[0] = value;
    event.xclient.data.l[1] = CurrentTime;

    return XSendEvent(m_display, given_window, False, NoEventMask, &event);
  } 

  void SendExitClient(Window client_window) noexcept(true) {
    int maxcount;
    int found = 0;
    Atom *protocols;

    if (XGetWMProtocols(m_display, client_window, &protocols, &maxcount)) {
      for (int count = 0; count < maxcount; ++count) {
        if (protocols[count] == xa_wm_delete) ++found;
      }
      
      if (protocols != nullptr) { 
        XFree(protocols);
      }
      
    } if (found != 0) {
      SendXMessage(client_window, xa_wm_protos, xa_wm_delete);
      
    } else {
      XKillClient(m_display, client_window);
    }
  }

  void EventLoop() noexcept(true) {
    XEvent event;

    while (not m_want_exit) {
      XNextEvent(m_display, &event);
      switch (event.type) {
        case ButtonPress:
          ButtonPressedEventHandler(&event.xbutton);
          break;
        case MotionNotify:
          MouseMotionEventHandler(&event.xmotion);
          break;
        case KeyPress:
          KeyEventHandler(&event.xkey);
          break;
      }
    }
  }
    
};
}  // namespace vt

