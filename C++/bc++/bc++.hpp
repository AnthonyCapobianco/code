#pragma once

#include <iostream>
#include <vector>
#include <string>


namespace bc {
class Calc {
private:
  std::vector<std::string> m_args;

public:
  Calc(const int array_length, const char** array_of_strings) noexcept(false) {
    if (array_length > 1) {
      for (int i = 1; i < array_length; ++i) {
        m_args.push_back(array_of_strings[i]);
      }
    } else {
      std::cout << "Welcome to "
    }
  }

//private:
  void eval() const noexcept(false) {
    for (std::string arg: m_args) {
      switch (arg) {
      	
          
      }
    }
  }
};

} // namespace bc