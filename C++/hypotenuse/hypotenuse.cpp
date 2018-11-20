/*
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <cmath>
#include <iostream>
#include <stdexcept>

class Triangle {
private: 
  float m_side_a;
  float m_side_b;
  double m_hypotenuse;
  
public:
  Triangle(const float side_a, const float side_b) noexcept(false) {
    m_side_a = side_a;
    m_side_b = side_b;
    m_hypotenuse = sqrt((side_a * side_a) + (side_b * side_b));
  }
  
  double get_hypotenuse() const noexcept(true) {
    return m_hypotenuse;
  }
};

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Please provide two positive integers as argument.";
    std::exit(EXIT_SUCCESS);
  }

  try {
    Triangle triangle(std::stof(argv[1]), std::stof(argv[2]));
    
    std::cout << triangle.get_hypotenuse();
  } catch (const std::invalid_argument& exept) {
    std::cerr << "Invalid number: " << exept.what() << '\n';
    std::exit(EXIT_FAILURE);
  }
}
