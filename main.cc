/*
 * main.cc
 *
 *  Created on: 21 mar 2014
 *      Author: Patrik Wilhelmsson
 */
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;


void fillWords(vector<string>& w) {
	ifstream is("words.txt");
	string temp;
	while(is >> temp)
		w.push_back(temp);
}

bool letterAlreadyUsed(const char& c, vector<char>& usedLetters) {
	for (unsigned int i=0; i < usedLetters.size(); ++i) {
			if (usedLetters.at(i) == c)
				return true;
		}
	usedLetters.push_back(c);
	return false;
}

void printWord(const int& whichWord, vector<string>& words, string& playersWord) {
	cout << "There are " <<
	words.at(whichWord).size() <<
	" letters in the word." << endl <<
	"Your progress: " <<
	playersWord << endl;
}


int main()
{
	vector<string> words;
	vector<char> usedLetters;
	int nrTries = 7;
	int whichWord = 0;
	char c;
	bool foundLetter = false;

	fillWords(words); //Fetch the words.
	srand(time(NULL));
	whichWord = rand() % words.size(); //A random number between 0 and size().
	cout << whichWord << endl;

	//The word to fill with letters the player guessed right.
	string playersWord(words.at(whichWord).size(), '_');

	while(nrTries > 0)
		{
			//Print word length.
			printWord(whichWord, words, playersWord);

			cout << "Which letter would you like to try?\n";
			cin >> c;

			//Loop here until player gives a char that is OK.
			while ( letterAlreadyUsed(c, usedLetters) ) {
				cout << "You've already used this letter.\n";
				cin >> c;
			}

			//Check if the letter is in the word.
			for(unsigned int i = 0; i < words.at(whichWord).size(); ++i) {
				if( words.at(whichWord).at(i) == c) {
					foundLetter = true;
					playersWord.at(i) = c;
				}
			}
			if (!foundLetter) {
				--nrTries;
				if (nrTries == 0) {
					cout << "Sorry, game over :(\n";
					return 0;
				}
				else
				cout << "Sorry, the letter was not in the word. You have " <<
						nrTries << " chances left.\n";
			}
			else if (playersWord == words.at(whichWord)) {
				cout << "Wow! You've won! Well done sir.\n" <<
						"The word looks like this: " << playersWord << endl;
				return 1;
			}
			else {
				cout << "Nice! the letter was in the word.\n" <<
						"You have " << nrTries << " chances left.\n";
				foundLetter = false;
			}
		}
}
