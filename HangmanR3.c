/*
* Hangman Game
* Author Rob H
* Project for ITT 310
* This verison doe not allow for custom words
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Preprocessor includes


//Function to check if player wins
void testWin(int check)
{
	if (check == 0)
	{
		printf("You Win!!!");
		exit(0);
	}
}

//Random number generator used to select a random word
int random(int num)
{
	int pick;
	srand(time(0));
	pick = rand() % num + 1;
	printf("Random Word being selected.......\n\n");
	return pick;
}
//Structure to store different word sets
struct wordSets {
	char word1[40];
	char word2[40];
	char word3[40];
	char word4[40];
	char word5[40];
	char word6[40];
};


int main(void) {
	
	int select;
	//Call to the "random function" to get a random number	
	select = random(6); // six is the number of words in wordSetOne

	//Word set number 1
	struct wordSets wordSetOne;
	strcpy_s(wordSetOne.word1, 40, "house");
	strcpy_s(wordSetOne.word2, 40, "fountain");
	strcpy_s(wordSetOne.word3, 40, "church");
	strcpy_s(wordSetOne.word4, 40, "nature");
	strcpy_s(wordSetOne.word5, 40, "animal");
	strcpy_s(wordSetOne.word6, 40, "southwest");

	int i, missed, win;
	int result, missedCount;
	char guess;
	char theWord[40]; // hangman word string array
	
	//picks one of the words in wordSet1 based on the value of the "select" variable
	if (select == 1)
		strcpy_s(theWord, 40, wordSetOne.word1);
	else if (select == 2)
		strcpy_s(theWord, 40, wordSetOne.word2);
	else if (select == 3)
		strcpy_s(theWord, 40, wordSetOne.word3);
	else if (select == 4)
		strcpy_s(theWord, 40, wordSetOne.word4);
	else if (select == 5)
		strcpy_s(theWord, 40, wordSetOne.word5);
	else
		strcpy_s(theWord, 40, wordSetOne.word6);
	
	union data {
		int size;
	};
	union data length; //Union to store string length of the selected hangman word
	
	length.size = strlen(theWord);
	missedCount = 0;
	char final[40]; //array to compare the hangman word to. This is used to determine a win
	strcpy_s(final, 40, theWord);

	// loop that copies underscores into a varible
	for (i = 0; i < length.size; ++i) {
		final[i] = '_';
	}

	printf("Word has %d letters\n", length.size);

	// Main loop that counts guesses and determines if player wins or losses
	while (missedCount < 6) {
		printf("Enter your guess: "); // Player input
		scanf_s(" %c", &guess, 1);
		system("cls");
		printf("Your guess is: %c\n", guess);
		missed = 0;

		// Loop to check for a match
		for (i = 0; i < length.size; ++i) {

			if (guess == theWord[i]) {
				final[i] = theWord[i];
				missed = 1;
			}

		}
		if (missed == 0) {
			missedCount = missedCount + 1; // counts each miss
		}
		//feedback to the player
		printf("Hangman progress (%d letters): %s\n", length.size, final);
		printf("You have missed %d times!\n", missedCount);
		win = strcmp(theWord, final);

		testWin(win); //check to see if player wins

	}
	//If player excedes 6 misses the player losses
	printf("Out of guesses you lose!");




	return 0;
}
