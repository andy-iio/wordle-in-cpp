#include <stdio.h>
#include <iostream> //for cout
#include <vector> //for vector
#include <cctype> //for toupper()
#include <cstdlib> //for rand
#include <ctime> // for time()
#include <fstream> //for ifstream class
#define MAX_WORD_SIZE 6 //five letters plus null character at end 
#define NUM_OF_TURNS 6
#define GREY 0
#define YELLOW 1
#define GREEN 2

//TO DO:
//union for the colours 

using namespace std;

string chooseRandomWord(const vector<string>& words) {
	srand(time(NULL));
	int randIndex = rand() % words.size();
	return words[randIndex];
}

int main() {
	//open the words list file
	ifstream file("wordList.txt");
	if (!file) {
		cerr << "cant open file\n";
		return 1;
	}

	//vector to store words
	vector<string> words;

	//read from file and store in string
	string w; //w is one word from the file, going line by line
	while (file >> w) {
		words.push_back(w); //push_back adds a new element at the end of the vector
	}

	//close file
	file.close();

	string word = chooseRandomWord(words);
//	char word[MAX_WORD_SIZE] = "TRUCK";
	int colourOfLetters[MAX_WORD_SIZE] = { 0,0,0,0,0 }; //0 is grey, 1 is yellow, 2 is green
	char guess[MAX_WORD_SIZE];
	

	cout << "<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> \n";
	cout << "    Welcome to C++ Wordle! You have 6 chances to guess the 5 letter word.\n";
	cout << "   If the letter turns green, it is the correct letter in the correct spot.\n";
	cout << "If the letter turns yellow, it is a letter in the word, but in the wrong spot.\n";
	cout << "<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> \n";
	
	int turnsTaken = 1; 

	do {
		int winCount = 0;
		cout << "\nGuess " << turnsTaken << ": ";
		cin >> guess;
		cout << "\t "; //for formatting
		for (int i = 0; i < MAX_WORD_SIZE - 1; i++) {
			if (toupper(guess[i]) == word[i]) {
				colourOfLetters[i] = GREEN;
				winCount++;
			}
			else {
				for (int j = 0; j < MAX_WORD_SIZE - 1; j++) {
					if (toupper(guess[i]) == word[j]) {
						colourOfLetters[i] = YELLOW;
						break;
					}
					else {
						colourOfLetters[i] = GREY;
					}
				}
			}
			//cout << colourOfLetters[i] << "\n";
			switch (colourOfLetters[i]) {
			case GREEN:
				cout << "\033[32m" << guess[i] << "\033[0m";
				break;
			case YELLOW:
				cout << "\033[33m" << guess[i] << "\033[0m";
				break;
			case GREY:
				cout << guess[i];
			}

		}
		if (winCount == 5) {
			cout << "\nYou Won in " << turnsTaken << " turns! Congrats!\n";
			break;
		}
		turnsTaken++;
	} while (turnsTaken <= NUM_OF_TURNS);

	return 0;
}