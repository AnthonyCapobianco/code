//
//  main.cpp
//  randomizer
//
//  Created by Anthony Capobianco on 01/12/2017.
//  Copyright © 2017 Anthony Capobianco. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
typedef vector<char> char_Arr;

class Alphabet
{
private:
    char     alpha[27] = "abcdefghijklmnopqrstuvwxyz";
public:

    void printAlphabet()
    {   cout        << '"';
        for (auto letter: alpha)
        {
            cout    << (char) letter + 27
                    << endl;
        }// for
        cout        << '"'
                    << endl;
    }
}A;
int main()
{
    A.printAlphabet();

    return 0;
}
