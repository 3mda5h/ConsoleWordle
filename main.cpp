#include <iostream>
#include <cstring>

using namespace std;

int letterSearch(char c, int index, char* wordle);
int letterTally(char c, char* wordle);

int main() 
{
  char wordle[100];
  char guess[100];
  cout << "enter the wordle" << endl;
  cin.getline(wordle, 100);
  while(strcmp(guess, wordle) != 0)
  {
    cout << "enter guess" << endl;
    cin.getline(guess, 100);
    char usedSoFar[100];
    for(int i = 0; i < strlen(guess); i++)
    {
      usedSoFar[i] = guess[i];
      if(letterSearch(guess[i], i, wordle) == 2)
      {
        cout << "\e[0;32m" << guess[i]; //green
      }
      else if(letterSearch(guess[i], i, wordle) == 1 && letterTally(guess[i], usedSoFar) <= letterTally(guess[i], wordle))  
      {
        cout << "\e[0;33m" << guess[i]; //yellow
      }
      else
      {
        cout << "\e[0;37m" << guess[i]; //white
      }
    }
    cout << "\e[0;37m" << endl;
  }
  cout << "you win!" << endl;
}

int letterSearch(char c, int index, char* wordle)
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
}

int letterTally(char c, char* array)
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

