#include "temperature_converter.hpp"
#include <iostream>

int main(const int argc, const char* argv[]) {
  if (argc == 3) {
    auto temperature_converter = TemperatureConverter(argv[1], argv[2]);
    std::cout << temperature_converter.get_celsius();
  } else if (argc == 2) {
    auto temperature_converter = TemperatureConverter(argv[1]);
  } else {
    std::cout << "usage: temperature_convert temperature [unit]";
  }
}
