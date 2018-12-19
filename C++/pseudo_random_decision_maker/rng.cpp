/*
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <iostream>
#include <random>

int main() {
	std::random_device rand_device;
  std::mt19937 mt(rand_device());
  std::uniform_int_distribution<int> dist(0, 1);
  
  std::string result = (dist(mt) != 0) ? "Yes" : "No";
  
  std::cout << result << std::endl;
}
