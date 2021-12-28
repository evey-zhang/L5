// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

/* Delete the array below and replace by reading in words from a file 
   in main() */
/*
const char* wordBank[] = {
   "computer", "president", "trojan", "program", "coffee",
   "library", "football", "popcorn", "science", "engineer"};

const int numWords = 10;
*/
int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;
  
  
  ifstream in_file;
  in_file.open(argv[1]); // open file name from command line
  
  if (in_file.fail()) // if fails to open the file
  {
    cout <<"The file could not be opened, exit." <<endl;
    return 0;
  }

  /* Add code to declare the wordBank array, read in each word
     and store it */
  int numWords;
  in_file >> numWords; 
  
  if (in_file.fail())//step 5: if fails to read integer from file 
  {
    cout <<"The integer could not be read, exit.";
    return 0;
  }

  char** wordBank = new char* [numWords]; // dynammic allocation of an array of pointers to char arrays (c strings)
  
  
  for (int i = 0; i <numWords; i++)
  {
     char buffer[41]; 
     in_file >> buffer;
     
     //wordbank[i][j] = buffer[j]; // store each word in index i of the array
    wordBank[i] = new char[strlen(buffer)+1]; // allocate each "row" of cstrings ->pointer of wordbank points to char array
    
    //wordBank[i] = buffer; //pointer to first element of buffer array
    for (int j = 0; j<strlen(buffer); j++)
       wordBank[i][j] = buffer[j]; // DO I COPY IN EACH LETTER? no just pass in the pointer 
    
    wordBank[i][strlen(buffer)]= '\0';
  }
  
  //close file
  in_file.close();
    
  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    /* Complete the next line of code */
    if (strcmp (guess, wordBank[target]) == 0)
        wordGuessed = true;
    else
        wordGuessed = false;
   // ADD code to check if the guess is equal to the chosen word.
   // wordGuessed should be true if they are equal, and false otherwise
        
    numTurns--;   // Every guess counts as a turn
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  /* Free up any necessary memory */
  for (int k = 0; k < numWords; k++)
    delete [] wordBank[k];
  delete [] wordBank;
  delete [] word;
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

