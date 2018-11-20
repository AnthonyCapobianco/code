/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT
 * <http://www.opensource.org/licenses/MIT>
 */

#include <iostream>
#include <random>
#include <vector>

class Coin {
  enum sides { head, tail };

  std::vector<bool> _results;

  void Result() {
    unsigned int number_of_heads = 0;
    unsigned int number_of_tails = 0;

    for (auto&& s : this->_results) {
      if (s == head) {
        number_of_heads++;
        std::cout << "h ";
      } else {
        number_of_tails++;
        std::cout << "t ";
      }
    }

    std::cout << "\n\nHeads flipped: " 
              << number_of_heads
              << "\nTails flipped: " 
              << number_of_tails 
              << std::endl;
  }

 public:
  Coin(const int& number_of_flips = 1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    for (int i = 0; i < number_of_flips; i++) {
      this->_results.push_back((dis(gen) & 1));
    }

    this->Result();
  }
};

int main(int argc, const char** argv) {
  /*********************************************************\
  |*                                                        |
  |* Coin Flip Simulation:                                  |
  |* Write some code that simulates flipping a single coin  |
  |* however many times the user decides.                   |
  |* The code should record the outcomes and                |
  |* count the number of tails and heads.	                  |
  |*                                                        |
  \*********************************************************/

  int arg = 0;

  if (argc > 1) arg = std::atoi(argv[1]);

  auto coin = (arg <= 0) ? Coin() : Coin(arg);
}
