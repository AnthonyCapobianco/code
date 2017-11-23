//
//  main.cpp
//  med.cpp
//
//  Created by Anthony Capobianco on 11/11/2017.
//  Copyright © 2017 Anthony Capobianco. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
//  Set time string value
string theTime(){
    string result;
    time_t  timeResult  =   time(nullptr);
    string  theTime     =   ctime(&timeResult);
    //  Using pop_back(); to remove the annoying '\n' in ctime();
    theTime.pop_back();

    return "[" + theTime + "] ";
}

//  Redefinition of int vector
typedef vector<int> intvect;
//  Set default size for the vector
size_t size = 4;


//  Class definition
class drug{

    intvect  doses;
    char     drugID;
    string   drugName;


public:

    int getDoses(){
        int result = 0
        ,e;
        cout << "Please select a dose:" << endl;
        for(int x = 0; x < doses.size(); x++){
            int i = x+1;
            cout << "["<< i <<"] " << doses[x] << endl;
        }

        cin >> e;

        //  If doses[e] isn't past the size of the vector return e else 0
        result = e < doses.size() ? e : result;
        return result;
    }
    void isOther(){
        int dose = 0;
        cout << "Please type the drug name:" << endl;
        cin.ignore();
        getline(cin, drugName);
        cout << "Please type the dose taken:" << endl;
        cin >> dose;
        doses.push_back(dose);
    }

    //  prints the drug…
    void print() {
        cout << "[" << drugID << "] " << drugName << endl;
    }
    void out(int x = 0){
        ofstream myass;
        myass.open("doseLog", ios::app);
        myass << theTime() << drugName << " " << doses[x-1] << "mg" << endl;
        myass.close();
    }
    //  Constructor
    drug(string nameString, intvect doseVector){
        static char ID = 'a';
        drugName = nameString;
        for (auto dose: doseVector) {
            doses.push_back(dose);
        }
        drugID = ID <= 'z' ? ID : ID - 49 ;
        ID++;
    }
};
//  Ask for choice function
char ask(){
    char e = '\0';
    cout << "Please insert the letter of the drug you took:" << endl;
    cin >> e;
    return e;

};

int main(int argc, const char * argv[]) {


    //  Set variables
    char    choice = '\0';    /*  User input:         Choice of the drug from the list.                                   */
    int     dose        =   0;
    bool    idiot       =   1 /*  Error handling:     Is set to false if choice is correct                                */
    ,canCount   =   0;
    //  Set the objects
    drug ritalin("Ritalin", {5,10,15,20});
    drug effexor("Effexor",{225});
    drug concerta("Concerta",{72});
    drug other("other",{});

    //  Switch as long as idiot is true. If the input is correct idiot is set to false.
    do{
        //  Pretty self explanatory.
        switch (choice) {
            default:
                //  Print the drugs
                ritalin.print();
                effexor.print();
                concerta.print();
                other.print();
                //  ask for choice (yes, really)
                choice = ask();
                continue;
            case 'c' :
                //  Concerta
                concerta.out();
                idiot = 0;
                break;
            case 'b' :
                //  Effexor
                effexor.out();
                idiot = 0;
                break;
            case 'a' :
                //  Ritalin
                do{
                    dose = ritalin.getDoses();
                    //  canCount is true if getDoses returns anything but 0
                    canCount = dose;
                    /*
                     * The reason this works is that the function size(); for vectors returns the size of the vector + 1
                     * A bool is always true unless it's false. So the only way canCount is true
                     * is if the user inputs a value which is in the vector.
                     *
                     */
                }while (canCount == 0);
                ritalin.out(dose);
                idiot = 0;
                break;
            case 'd' :
                other.isOther();
                other.out();
                idiot = 0;
                break;
        }
    }while (idiot == 1);

    return 0;
}
