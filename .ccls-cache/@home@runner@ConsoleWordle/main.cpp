#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Guess
{
  char chars[100];
  int colors[100]; //2 = green, 1 = yellow, 0 = white
};

bool charIsCorrect(char c, int index, char* wordle);
int charCount(char* array, char c);
int usedCharCount(Guess* guess, char c);
void printGuess(Guess* guess);

int main() 
{
  char wordle[100];
  char guess[100];
  vector<Guess*>guesses;
  bool playing = true;
  while(playing == true)
  {
    cout << "Enter the wordle: ";
    cin.getline(wordle, 100);
    while(strcmp(guess, wordle) != 0)
    {
      cout << "----------------" << endl;
      bool validGuess = false;
      while(validGuess == false)
      {
        cout << "Guess: ";
        cin.getline(guess, 100);
        if(strlen(guess) > strlen(wordle))
        {
          cout << "Too long!" << endl;
        }
        else if(strlen(guess) < strlen(wordle))
        {
          cout << "Too short!" << endl;
        }
        else
        {
          validGuess = true;
        }
      }
      cout << "----------------" << endl;
      Guess* newGuess = new Guess();
      strcpy(newGuess->chars, guess);
      guesses.push_back(newGuess); 
      //set all the greens
      for(int i = 0; i < strlen(guess); i++)
      {
        if(charIsCorrect(guess[i], i, wordle) == true)
        {
          newGuess->colors[i] = 2;
        }
        else
        {
          newGuess->colors[i] = 0;
        }
      }
      //set any yellows
      for(int i = 0; i < strlen(guess); i++)
      {
        //for debugging:
        //cout << "number of " << guess[i] << " that are green or yellow: " << usedCharCount(newGuess, guess[i]) << endl; 
        //cout << "number of " << guess[i] <<  " in wordle: " << charCount(wordle, guess[i]) << endl;
        if(newGuess->colors[i] != 2 && usedCharCount(newGuess, guess[i]) < charCount(wordle, guess[i]))
        {
          newGuess->colors[i] = 1;
        }
      }
      //for debugging:
      for(int i = 0; i < strlen(wordle); i++)
      {
        cout << " " << (char)toupper(wordle[i]);
      }
      cout << endl;
      for(int i = 0; i < guesses.size(); i++)
      {
        printGuess(guesses[i]);
      }
    }
    cout << "----------------" << endl;
    cout << "You win!" << endl;
    cout << "Total guesses: " << guesses.size() << endl;
    cout << "Play again? (y/n)" << endl;
    cout << "> ";
    cin.getline(guess, 100);
    if(strcmp(guess, "n") == 0)
    {
      playing = false;
    }   
  }
}

//wordle matches given char at same index 
bool charIsCorrect(char c, int index, char* wordle)
{
  if(wordle[index] == c)
  {
    return true; 
  }
  return false;
}

void printGuess(Guess* guess)
{
  for(int i = 0; i < strlen(guess->chars); i++)
  {
    if(guess->colors[i] == 2)
    {
      cout << "\e[0;32m" << " " << (char)toupper(guess->chars[i]); //green
    }
    else if(guess->colors[i] == 1)
    {
      cout << "\e[0;33m" << " " << (char)toupper(guess->chars[i]); //yellow
    }
    else
    {      
      cout << "\e[0;37m" << " " << (char)toupper(guess->chars[i]); //white
    }
  }
  cout << "\e[0;37m" << endl;
}

//returns amount of a certain character in the guess that is either green or yellow
int usedCharCount(Guess* guess, char c)
{
  int total = 0;
  for(int i = 0; i < strlen(guess->chars); i++)
  {
    if(guess->chars[i] == c && guess->colors[i] != 0) 
    {
      total++;
    }
  }
  return total;
}

//returns total amount of a certain char in a given array
int charCount(char* array, char c)
{
  int total = 0;
  for(int i = 0; i < strlen(array); i++)
  {
    if(array[i] == c) 
    {
      total++;
    }
  }
  return total;
}