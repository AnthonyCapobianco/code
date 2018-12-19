/*
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <iostream>
#include <string>

int main() {
    std::string decimal_number; 
    std::getline(std::cin, decimal_number);
    long ternary_number = std::stol(decimal_number, nullptr, 3);
    
    std::cout << ternary_number << std::endl;

}
