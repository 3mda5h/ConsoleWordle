#include <iostream>
#include <cstring>

using namespace std;

//int letterSearch(char c, int index, char* wordle);
bool charIsCorrect(char c, int index, char* wordle);
int yellowCount(char c, int index, char* wordle);
int charCount(char c, char* array);
int greenCount(char c, int index, char* array, char* wordle);

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
    for(int i = 0; i < strlen(guess); i++)
    {
      if(charIsCorrect(guess[i], i, wordle) == true)
      {
        cout << "\e[0;32m" << guess[i]; //green
      }
      else if((correctTally(guess[i], i, guess, wordle) || incorrectTally(guess[i], i, wordle)) < totalTally(guess[i], wordle))  
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

bool charIsCorrect(char c, int index, char* wordle)
{
  if(wordle[index] == c)
  {
    return true; //correct letter in correct place
  }
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

int totalTally(char c, char* array)
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