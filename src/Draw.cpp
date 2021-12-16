#include <iostream>
#include <string>
using namespace std;
string playGame (string word)
{
    int points = 0;
    cout << "Welcome to Draw++" << endl;
    cout << " " << endl;
         
    int letterCorrect = 0;
    double score = (letterCorrect / word.length()) * 100; 
    string loser_message = "The word was " + word + ". ";
    string winner_message = "Correct, the word was " + word + ". ";
    
    string mystery = word;
    for(int i = 0 ; i < mystery.length() ; i ++)
        mystery[i] = '*';
      

    while(letterCorrect < word.length())
    {
        cout << "Number of Points: " << points << endl;
        cout << "Enter a letter" << " " << mystery << ": ";
        char guess;
        cin>> guess;
       
        bool correctGuess = false;
        bool duplicateLetter = false;
        for(int i=0; i < word.length(); i++)
        {
            if(guess == word[i])
            {
                if (mystery[i] == word[i])
                {
                    cout << guess << " is already in the word" << endl;
                    cout << " "<< endl;
                    duplicateLetter = true;
                    correctGuess = true;
                    break;
                }
                else
                {
                    points++;
                    mystery[i] = word[i];
                    letterCorrect++;
                    correctGuess = true;
                    cout << " "<< endl;
                }
                if(duplicateLetter)
                    continue ;
             }
        }
        if (!correctGuess)
        {
            points--;
            cout << " "<< endl;
            cout << "Number of Points: " << points << endl;
            cout << guess << " is not in the word." << endl;
            return loser_message;
        }
    }
    return winner_message;
}
int main()
{
    string result = playGame ("programming");
    cout << result << endl;
    cout << "Wait for the next round." << endl; 
}