#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    string  longitude
           ,latitude
           ;
    string  defibrillator;
    int     n // Number of defibrillators.
           ,i // Itterator
           ;

    cin >> longitude;   cin.ignore();
    cin >> latitude;    cin.ignore();
    cin >> n;           cin.ignore();

    for (i = 0; i < n; ++i)
    {
        getline(cin, defibrillator);
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << "answer" << endl;
}
