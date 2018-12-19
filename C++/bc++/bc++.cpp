/*
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include "bc++.hpp"

int main(const int argc, const char** argv) {
	bc::Calc calc(argc, argv);
  calc.eval();
}
