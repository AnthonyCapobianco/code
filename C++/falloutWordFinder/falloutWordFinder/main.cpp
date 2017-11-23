//  For better readability: Font = Hack; Tab = 4 spaces;
//  This program helps finding the word to hack a terminals in Fallout 4.

#include <iostream>
#include <vector>

using namespace std;

typedef vector<string> stringArray;
typedef vector<int> intArray;
typedef unsigned long Ulong;

class Word{
private:
          Ulong     lengthOfTheWord;
       intArray     matches;
    stringArray     word;
           char     predictedWord[14];
public:
    void setWord(){

        string      theWord;
           int      theNumber;

        cout << "Please enter the word: " << flush;
        cin  >> theWord;

        lengthOfTheWord = theWord.length();

        cout << "Please enter the number of matches: " << flush;
        cin  >> theNumber;

        if (theNumber > 0)
        {
	    word.push_back(theWord);
            matches.push_back(theNumber);
	}

    }// setWord();

    void searchWordsForMatches()
    {
        static int x = 0;

        for(int i = 0; i <= word[x].length(); ++i)
        {
	    predictedWord[i]  =  (word[x][i] == word[x+1][i]) ? word[x][i] : '.';
	}

        ++x;

        cout << predictedWord << endl;
    }// searchWordForMatches();

}Word;

int main(int argc, const char * argv[]) {
    int    it = 4;

    while (it --> 0)
    {
	Word.setWord();
        Word.searchWordsForMatches();
    }

    return 0;
}// main();
