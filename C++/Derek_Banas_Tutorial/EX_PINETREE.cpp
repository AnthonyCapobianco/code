#include <iostream>

int 
main() 
{
        bool first = true;
        int user_input = 0; 
        
        do 
        {
               if (!first) std::cout << "Please enter a value between 3 and 10" << '\n';
                
                std::cout << "How many rows should the tree have? "; 
                
                std::cin >> user_input; 
                
        } while ((first = false) and (user_input < 3 or user_input > 20));
        
        
        for (int row = 1; row <= user_input; row++)
        {
                int spaces_to_print = (2 * user_input) - row;
                
                while (spaces_to_print > 0)
                {
                        if (spaces_to_print > 1) std::cout << ' ';
                        else
                        {
                                int pines_to_print = (row > 1) ? (row + row - 1) : row;
                                while (pines_to_print > 0) 
                                {
                                        std::cout << '#';
                                        pines_to_print--;
                                }
                                
                                std::cout << std::endl;
                        }
                        spaces_to_print--;
                }
                
                if (row == user_input)
                {
                        for (spaces_to_print = (2 * user_input) - 1; spaces_to_print > 1; spaces_to_print--) 
                        {
                                std::cout << ' ';
                        }
                
                        std::cout << '#' << std::endl;
                }
        }
}