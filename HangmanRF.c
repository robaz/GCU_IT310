/*
* Hangman Game
* Author Rob H
* Project for ITT 310
* This verison allows for custom words using word.txt
*/

// Preprocessor items
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define  LINESIZE 25

//Used to debug
const int DEBUGGING = 1; // set to 1 to show debugging

void playAgain(void)
{
	char playAgain;
	printf("Would you like to play again? y/n\n");
	scanf_s(" %c", &playAgain, 1);

	if (DEBUGGING == 1)
	{
		printf("**%c**", playAgain);
	}

	if (playAgain == 'y')
	{
		main();
	}
}

//Function to check if player wins
void testWin(int check)
{
	if (check == 0)
	{
		printf("You Win!!!\n\n");
		playAgain();
		exit(0);
	}
}

//Random number generator used to select a random word
int random(int num)
{
	int pick;
	srand(time(0));
	pick = rand() % num + 1;
	//printf("Random Word being selected.......\n\n");
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

	system("cls");
	FILE* wordFile;
	errno_t err;

	err = fopen_s(&wordFile, "word.txt", "r"); //word.txt is external list of hangman words
	char line[LINESIZE];
	int isFile = 1; //Flag will be set to 0 if word.txt is not present and then the hard coded list of word will be used

	if (wordFile == NULL)
		printf("*** word.txt not found! Using built-in words\n");
	else {
		printf("*** Loading words from word.txt\n");
		int count = 0;
		int x = 1;
		isFile = 0;
		//This while loop counts the words in the word.txt file
		while (x != 0)
		{
			fgets(line, LINESIZE, wordFile);
			count++;
			if (feof(wordFile))
			{
				//printf(" Word Count %d\n", count);
				x = 0;
			}

		}
		
		fclose(wordFile);

		//Reopens word.txt file to read in a random word
		err = fopen_s(&wordFile, "word.txt", "r");

		if (wordFile == NULL)
		{
			printf("*** Error selecting word! Defaulting to built-in words.\n");
			isFile = 1; // If there is an error opening the word.txt file a 2nd time the build in list of words will be used
		}
		else
		{
			printf("*** Selecting a random word\n");

			int select2;
			int p;
			select2 = random(count); // random number is picked (1 upto count)

			// for loop to set line = random word 
			for (p = 0; p < select2; p++)
			{
				fgets(line, LINESIZE, wordFile);
				//printf("Select2 is %d P= %d Word is %s\n", select2, p, line);


			}
		}
		fclose(wordFile);
	}
	char theWord[40]; // hangman word string array
	int i, missed, win;
	int result, missedCount;
	char guess;

	if (isFile == 1 || strlen(line) > 25)
	{
		//Built-in words, these are used if word.txt is not present
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

		//picks one of the words in wordSet1 based on the value of the "select" variable, copies to theWord
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
	}
	else {
		//else is used for word.txt word
		//trims \n from end of word
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}
		strcpy_s(theWord, 40, line); // copies word that was picked from word.txt to theWord
	}
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

	//Debugging, prints the hangman word
	if (DEBUGGING == 1)
	{
		printf("%s\n", theWord);
	}

	printf("Word has %d letters\n", length.size);

	printf("+---+\n");
	printf("|   |\n");
	printf("|    \n");
	printf("|    \n");
	printf("|    \n");
	printf("|    \n");
	printf("======\n");

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

		//Debugging, prints the hangman word
		if (DEBUGGING == 1)
		{
			printf("%s\n", theWord);
		}

		//feedback to the player
		printf("Hangman progress (%d letters): %s\n", length.size, final);
		printf("You have missed %d times!\n", missedCount);
		
		switch (missedCount)
		{
		case 0 :
			printf("+---+\n");
			printf("|   |\n");
			printf("|    \n");
			printf("|    \n");
			printf("|    \n");
			printf("|    \n");
			printf("======\n");
			break;
		case 1 :
			printf("+---+\n");
			printf("|   |\n");
			printf("|   O\n");
			printf("|    \n");
			printf("|    \n");
			printf("|    \n");
			printf("======\n");
			break;
		case 2:
			printf("+---+\n");
			printf("|   |\n");
			printf("|   O\n");
			printf("|   |\n");
			printf("|    \n");
			printf("|    \n");
			printf("======\n");
			break;
		case 3:
			printf("+---+\n");
			printf("|   |\n");
			printf("|   O\n");
			printf("|  /|\n");
			printf("|    \n");
			printf("|    \n");
			printf("======\n");
			break;
		case 4:
			printf("+---+\n");
			printf("|   |\n");
			printf("|   O\n");
			printf("|  /|\\ \n");
			printf("|    \n");
			printf("|    \n");
			printf("======\n");
			break;
		case 5:
			printf("+---+\n");
			printf("|   |\n");
			printf("|   O\n");
			printf("|  /|\\ \n");
			printf("|  /  \n");
			printf("|    \n");
			printf("======\n");
			break;
		}
		
		
		win = strcmp(theWord, final);

		testWin(win); //check to see if player wins

	}
	//If player excedes 6 misses the player losses
	system("cls");
	printf("Hangman progress (%d letters): %s\n", length.size, final);
	printf("You have missed %d times!\n", missedCount);

	printf("+---+\n");
	printf("|   |\n");
	printf("|   O\n");
	printf("|  /|\\ \n");
	printf("|  / \\ \n");
	printf("|    \n");
	printf("======\n");

	printf("Out of guesses you lose!\n\n");

	playAgain();

	return 0;
}
