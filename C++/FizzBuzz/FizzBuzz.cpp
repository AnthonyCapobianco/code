/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <iostream>

int main()
{
	/* Fizz Buzz  
         * Write a program that prints the numbers from 1 to 100. 
         * But for multiples of three print “Fizz” instead of the number and 
         * for the multiples of five print “Buzz”. 
         * For numbers which are multiples of both three and five print “FizzBuzz”.
         */
        
        for (int i = 1; i <= 100; ++i)
        {
                if (i % 3 != 0) // if not multiple of 3
                {
                        if (i % 5 == 0) // is it mult of 5
                        {
                                std::cout << "Buzz\n";
                        }
                        else
                        {
                                std::cout << i << '\n';
                        }
                }
                else // if it is mult of 3
                {
                        if (i % 5 == 0) // is it mult of 5
                        {
                                std::cout << "FizzBuzz\n";
                        }
                        else
                        {
                                std::cout << "Fizz\n"; 
                        }
                }
        }
        
        std::cout.flush();
}