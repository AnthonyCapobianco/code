#include "includes/web.hpp"

int main() {
  using namespace vt::web;
  html("Hello, World!");
  p("center") << "Hello, World!";
}