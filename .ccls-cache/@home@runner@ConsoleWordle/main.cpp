#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Guess
{
  char chars[100];
  int colors[100]; //2 = green, 1 = yellow, 0 = white
};

//int letterSearch(char c, int index, char* wordle);
bool charIsCorrect(char c, int index, char* wordle);
int yellowCount(char c, int index, char* wordle);
int charCount(char* array, char c);
int usedCharCount(Guess* guess, char c)
int greenCount(char c, int index, char* array, char* wordle);
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
      cout << "Guess: ";
      cin.getline(guess, 100);
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
      //set any remaining letters to yellow
      for(int i = 0; i < strlen(guess); i++)
      {
        if(newGuess->colors[i] != 2 && usedCharCount(newGuess, guess[i]) < charCount(wordle, guess[i]))
        {
          newGuess->colors[i] = 1;
        }
      }
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

bool charIsCorrect(char c, int index, char* wordle)
{
  if(wordle[index] == c)
  {
    return true; //correct letter in correct place
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

/*int letterSearch(char c, int index, char* wordle)
{
  if(wordle[index] == c)
  {
    return 2; //correct letter in correct place
  }
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(wordle[i] == c)
    {
      return 1; //contains letter but not in right place
    }
  }
  return 0; //does not contain letter
}*/

//returns the amount of a given char from GUESS that EXIST in the worlde but do not share the INDEX   
int yellowCount(char c, int index, char* wordle)
{
  int total = 0;
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(wordle[i] == c && i != index)
    {
      total++;
    }
  }
  return total;
}

//returns the amount of chars that are in the right place and 
int greenCount(char c, int index, char* array, char* wordle)
{
  int total = 0;
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(charIsCorrect(c, i, wordle) == true)
    {
      total++;
    }
  }
  return total;
}

//returns amount of a certain character in the guess that is either green or yellow
int usedCharCount(Guess* guess, char c)
{
  int total = 0;
  for(int i = 0; i < strlen(guess->chars); i++)
  {
    if(guess->colors[i] != 0) 
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




//yellow allowed if: amount of greens 