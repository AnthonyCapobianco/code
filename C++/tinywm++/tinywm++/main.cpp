/*
 * copyleft ViralTaco_ 2018
 * This is based based on TinyWM, just a port in C++
 *
 */

/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>
#include <cstdlib>

inline int max(int a, int b) noexcept(true) {
  return (a > b) ? a : b;
}

namespace tinywm {
  enum mouse_button {
    left = 1
  , right = 3
  };

  struct key {
    static constexpr KeySym F1 = static_cast<KeySym>(0xffbe);
  };
}

int main() {
  using tinywm::mouse_button;
  using tinywm::key;

  Display *display_ptr = XOpenDisplay(0x0);
  if (display_ptr == nullptr) {
    std::exit(EXIT_FAILURE);
  }

  XWindowAttributes window_attributes;
  XButtonEvent button_event;
  XEvent event;

  XGrabKey(display_ptr, XKeysymToKeycode(display_ptr, key::F1)
    , Mod1Mask, DefaultRootWindow(display_ptr)
    , True, GrabModeAsync, GrabModeAsync
  );

  static constexpr auto click_or_motion_mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

  XGrabButton(display_ptr, mouse_button::left
    , Mod1Mask, DefaultRootWindow(display_ptr), True
    , click_or_motion_mask
    , GrabModeAsync, GrabModeAsync, None, None
  );

  XGrabButton(display_ptr, mouse_button::right
    , Mod1Mask, DefaultRootWindow(display_ptr), True
    , click_or_motion_mask
    , GrabModeAsync, GrabModeAsync, None, None
  );

  button_event.subwindow = None;
  int xdiff = 0;
  int ydiff = 0;

  while (true) {
    XNextEvent(display_ptr, &event);

    if (event.type == KeyPress and event.xkey.subwindow != None) {
      XRaiseWindow(display_ptr, event.xkey.subwindow);

    } else if (event.type == ButtonPress and event.xbutton.subwindow != None) {
      XGetWindowAttributes(display_ptr, event.xbutton.subwindow, &window_attributes);
      button_event = event.xbutton;

    } else if (event.type == MotionNotify and button_event.subwindow != None) {
      xdiff = event.xbutton.x_root - button_event.x_root;
      ydiff = event.xbutton.y_root - button_event.y_root;

      if (button_event.button == mouse_button::left) {
        XResizeWindow(display_ptr, button_event.subwindow
          , window_attributes.x + xdiff
          , window_attributes.y + ydiff
        );

      } else if (button_event.button == mouse_button::right) {
        XMoveWindow(display_ptr, button_event.subwindow
          , max(window_attributes.width + xdiff, 1)
          , max(window_attributes.height + ydiff, 1)
        );
      }

    } else if (event.type == ButtonRelease) {
      button_event.subwindow = None;
    }
  } // while true
}
