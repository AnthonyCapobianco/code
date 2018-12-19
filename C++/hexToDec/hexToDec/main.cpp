//  Honestly I don't want my name on this. You can have it. 

#include <iostream>
#include <string>

using namespace std;

class hexadicimal{
    string  hexInput;
    long    decOutput;

public:
    void askForHexValue(){
        cout    << "Please type hexadecimal values then press enter. Type Q to quit" << endl;
        getline(cin, hexInput);
        if (hexInput == "Q") {
            cout<< "Goodbye." << endl;
            return;
        }else{
            decOutput = stol(hexInput,nullptr, 16);
            cout    << "Hexadecimal: '" << hexInput << "' \t"
                    << "Decimal: " << decOutput << endl;
            askForHexValue();
        }
    }
};

int main(int argc, const char * argv[]) {
    hexadicimal hex;
    hex.askForHexValue();

    return 1;
}
