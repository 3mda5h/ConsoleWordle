#include <iostream>
#include <cstring>
#include <map>

using namespace std;

int letterSearch(char c, int index, char* wordle);
int numOfLetters(char c, char* wordle);
map<char, int> createMap(char* wordle)

int main() 
{
  char wordle[100];
  char guess[100];
  cout << "enter the wordle" << endl;
  cin.getline(wordle, 100);
  map<char, int> letterCounts = createMap(wordle);
  while(strcmp(guess, wordle) != 0)
  {
    cout << "enter guess" << endl;
    cin.getline(guess, 100);
    for(int i = 0; i < strlen(guess); i++)
    {
      if(letterSearch(guess[i], i, wordle) == 1)
      {
        cout << "\e[0;33m" << guess[i]; //yellow
      }
      else if(letterSearch(guess[i], i, wordle) == 2)
      {
        cout << "\e[0;32m" << guess[i]; //green
      }
      else
      {
        cout << "\e[0;37m" << guess[i]; //white
      }
      letterCounts.find(wordle[i]) = letterCounts.find(wordle[i]) - 1;
    }
    cout << "\e[0;37m" << endl;
  }
  cout << "you win!" << endl;
}

int letterSearch(char c, int index, char* wordle, map<int, char> letterCounts)
{
  if(wordle[index] == c)
  {
    return 2; //correct letter in correct place
  }
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(wordle[i] == c && (letterCounts.find(wordle[i]) > 0))
    {
      letterCounts
      return 1; //contains letter but not in right place
    }
  }
  return 0; //does not contain letter
}

int numOfLetters(char c, char* wordle)
{
  int total;
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(wordle[i] == c)
    {
      total++;
    }
  }
  return total;
}

map<char, int> createMap(char* wordle)
{
  map<char, int>* letterCounts = new map<char,int>;
  for(int i = 0; i < strlen(wordle); i++)
  {
    if(!letterCounts->count(wordle[i])) //if map does not contain this key/letter already
    {
      letterCounts->emplace(wordle[i], numOfLetters(wordle[i], wordle));
    }
  }
}