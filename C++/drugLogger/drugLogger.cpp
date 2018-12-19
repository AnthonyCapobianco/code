#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <ctime>

using namespace std;

//  Set time string value
string theTime()
{
    string result;
    time_t timeResult = time(nullptr);
    string theTime = ctime(&timeResult);
    //  Using pop_back(); to remove the annoying '\n' in ctime();
    theTime.pop_back();

    return "[" + theTime + "] ";
}
size_t size = 4;
class drug
{
    private:
        
        string name;
        vector<int> doses;
        char *ID;
        
    public:
        
        drug(string nameString, int* doseArray)
        {
            static char dID = 'a';
            name = nameString;
            for (auto dose: doseArray) doses.push_back(dose);
            ID = &dID;
        }
};

int main(int argc, char *argv[]) 
{
    drug ritalin("Ritalin", {5, 10, 15, 20});
    drug effexor("Effexor", {225});
    drug concerta("Concerta", {36, 72});
}