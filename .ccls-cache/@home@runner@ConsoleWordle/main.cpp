//last edited 2/3/22
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

struct Guess
{
  char chars[100];
  int colors[100]; //2 = green, 1 = yellow, 0 = white
};

bool charIsCorrect(char c, int index, char* wordle);
int charCount(char* array, char c);
int coloredCharCount(Guess* guess, char c);
void printGuess(Guess* guess);
void setWordLength(int &wordlen);
void numbers(int wordlen);
vector<const char*> createDictonary(const char* fileName);

int main() 
{
  //setting up the dictonarys
  vector<const char*>commonWords = createDictonary("popular.txt");
  vector<const char*>allWords = createDictonary("words.txt");


  char wordle[100];
  char input[100];
  vector<Guess*>guesses;
  bool playing = true;
  int wordlen;
  while(playing == true)
  {
    setWordLength(wordlen);
    cout << "finding word..." << endl;
    int i = 1;
    while(strlen(commonWords[i]) != wordlen) //keep randomly going through dictonary until word with desired length is found
    {
      srand(time(NULL));
      i = rand()%(commonWords.size() - 1);
    }
    strcpy(wordle, commonWords[i]); 
    //debugging:
    //cout << "wordle is: " << wordle << endl;
    //cout << "Enter the wordle: ";
    //cin.getline(wordle, 100);
    while(strcmp(input, wordle) != 0)
    {
      bool validGuess = false;
      while(validGuess == false) //keep prompting user for guess until it is correct length
      {
        cout << "-------";
        numbers(wordlen); //prints numbers 1 - length of wordle, serves as a guide to show user how long the word that they are inputing is and how long it needs to be
        cout << "Guess: ";
        cin.getline(input, 100);
        if(strlen(input) > strlen(wordle))
        {
          cout << "Too long!" << endl;
        }
        else if(strlen(input) < strlen(wordle))
        {
          cout << "Too short!" << endl;
        }
        else
        {
          validGuess = true;
        }
      }
      cout << "-----------------" << endl;
      Guess* newGuess = new Guess();
      strcpy(newGuess->chars, input);
      guesses.push_back(newGuess); 
      //set all the greens
      for(int i = 0; i < strlen(input); i++)
      {
        if(charIsCorrect(input[i], i, wordle) == true)
        {
          newGuess->colors[i] = 2;
        }
        else
        {
          newGuess->colors[i] = 0;
        }
      }
      //set any yellows
      for(int i = 0; i < strlen(input); i++)
      {
        //for debugging:
        /*cout << "number of " << guess[i] << " that are green or yellow: " << usedCharCount(newGuess, guess[i]) << endl; 
        cout << "number of " << guess[i] <<  " in wordle: " << charCount(wordle, guess[i]) << endl;*/
        if(newGuess->colors[i] != 2 && coloredCharCount(newGuess, input[i]) < charCount(wordle, input[i])) //if char is not green and the amount of yellow/green ones of this char currently in guess is less than the amount of this char in wordle
        {
          newGuess->colors[i] = 1;
        }
      }
      //for debugging:
      /*for(int i = 0; i < strlen(wordle); i++)
      {
        cout << " " << (char)toupper(wordle[i]);
      }
      cout << endl;*/
      for(int i = 0; i < guesses.size(); i++)
      {
        printGuess(guesses[i]);
      }
    }
    cout << "-----------------" << endl;
    cout << "You win!" << endl;
    cout << "Total guesses: " << guesses.size() << endl;
    guesses.clear();
    cout << "Play again? (y/n)" << endl;
    cout << "> ";
    cin.getline(input, 100);
    if(strcmp(input, "n") == 0)
    {
      playing = false;
    }   
  }
}

vector<const char*> createDictonary(const char* fileName)
{
  vector<const char*>dictonary;
  ifstream file(fileName);
  string line;
  if(!file.is_open())
  {
    cout << "Could not open file" << endl;
  }
  while (getline(file, line))
  {
    char* c = new char[100];
    //cout << line << endl;
    strcpy(c, line.c_str());
    dictonary.push_back(c);
  }
  return dictonary;
}

void setWordLength(int &wordlen)
{
  char input[100];
  while(true == true)
  {
    cout << "Enter word length: ";
    cin.getline(input, 100);
    if(atoi(input) > 9 || atoi(input) < 3)
    {
      cout << "Not a valid length" << endl;
    }
    else
    {
      wordlen = atoi(input);
      return;
    }
  }
}

void numbers(int wordlen)
{
  for(int i = 1; i <= wordlen; i++)
  {
    cout << i;
  }
  cout << "--" << endl;
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
int coloredCharCount(Guess* guess, char c)
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