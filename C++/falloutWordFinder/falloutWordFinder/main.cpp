//  For better readability: Font = Hack; Tab = 4 spaces;
//  This program helps finding the word to hack a terminals in Fallout 4.

#include <iostream>
#include <vector>

using namespace std;

typedef vector<string>  stringArray;
typedef vector<int>     intArray;
typedef unsigned long   Ulong;

class Word{
private:
          Ulong     lengthOfTheWord;
       intArray     matches
                   ,userWordsPicked;
    stringArray     word;
public:
    bool setWord(){

        string      theWord;
          bool      isDone = 0;
           int      i = 1;

        cout        << "Type \":DONE\" once you're done."
                    << endl;

        while (!isDone)
        {
            cout    << "Please enter the word: "
                    << flush;

            cin     >> theWord;

            isDone = ((theWord == ":DONE") || (theWord == ":done")) ? 1 : 0;

            word.push_back(theWord);
            matches.push_back(0);

        }

        word.pop_back();

        while (isDone)
        {

            for (auto words : word)
            {
                cout    << "[" << i <<"] "
                        << words
                        << endl;
                ++i;
            }

            break;
        }

        return isDone;

    }// setWord();

    void setMatchesForWord()
    {
        int     userPick
               ,theNumber;
        for (int i = 0; i <= 2; i++)
        {
            cout    << "Please insert the number corresponding to one of the words:"
                    << flush;
            cin     >> userPick;
            userWordsPicked.push_back(userPick-1);

            cout    << "Please insert the number of matches of \""
                    << word[userPick-1]
                    << "\": "
                    << flush;
            cin     >> theNumber;
            matches[userPick-1] = theNumber;
        }

    }

    void searchWordsForMatches()
    {

        for(auto x : userWordsPicked)
        {
            for(auto w : word)
            {
                if(checkForNumberOfMatches(w, word[x]) == matches[x])
                {
                    cout    << w;
                }
            }

        }

    }// searchWordForMatches();

    int checkForNumberOfMatches(string w,string wordx)
    {
        int     foundMatches = 0;
        for(int i = 0; i <= w.length() ; i++ )
        {
            foundMatches += (wordx[i] == w[i]) ? 1 : 0;
        }
        return foundMatches;
    }// checkForNumberOfMatches();

}Word;

int main() {
    while ( !Word.setWord() )
    {
        Word.setWord();
    }

    Word.setMatchesForWord();
    Word.searchWordsForMatches();
    return 0;
}// main();
