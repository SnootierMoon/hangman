#include <iostream>
#include <string>
using namespace std;
string playGame (string word)
{
    //Creates points and letterCorrect and assigns to 0. 
    //loser message is displayed if the player guesses an incorrect letter
    //winner message is displayed if the player guesses the entire word correctly
    int points = 0;     
    int letterCorrect = 0;
    string loser_message = "The word was " + word + ". ";
    string winner_message = "Correct, the word was " + word + ". ";
    
    //"Covers" the letters of the word and displays it to the user
    string mystery = word;
    for(int i = 0 ; i < mystery.length() ; i ++)
    {    
        mystery[i] = '*';
    } 

    //loop runs till all the letters in the word are guessed correctly
    while(letterCorrect < word.length())
    {
        //Asks the player to enter a letter and displays the number points the player has each turn
        cout << "Number of Points: " << points << endl;
        cout << "Enter a letter" << " " << mystery << ": ";
        char guess;
        cin>> guess;
        bool correctGuess = false;
        
        //Iterates through the word to see if the letter is present in the word
        for(int i=0; i < word.length(); i++)
        {
            if(guess == word[i])
            {
                //if the letter is present but is a duplicate, notify the player
                if (mystery[i] == word[i])
                {
                    cout << guess << " is already in the word" << endl;
                    cout << " "<< endl;
                    correctGuess = true;
                    break;
                }
                
                /*if the letter is present and it is not a duplicate, add 1 point 
                and uncover the correctly identified letter */
                else
                {
                    points++;
                    mystery[i] = word[i];
                    letterCorrect++;
                    correctGuess = true;
                    cout << " "<< endl;
                }
             }
        }
        
        //if the letter is not present, the player loses 1 point and returns the loser message 
        if (!correctGuess)
        {
            //No negative points
            if(points > 0)
            {
               points--;
            }
            cout << " "<< endl;
            cout << "Number of Points: " << points << endl;
            cout << guess << " is not in the word." << endl;
            return loser_message;
        }
    }
    
    //If all letters are uncovered the winner message is return
    cout << "Number of Points: " << points << endl;
    return winner_message;
}

int main()
{
    //Opening message
    cout << "Welcome to Draw++" << endl;
    cout << " " << endl;
    
    //Calls the playGame function
    string result = playGame ("programming");
    cout << result << endl;
    cout << "Wait for the next round." << endl; 
}
