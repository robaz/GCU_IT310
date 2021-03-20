#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Preprocessor includes


int main(void) {

	int i, missed, win;
	int result, missedCount;
	char guess;
	char theWord[] = "animal"; // hangman word
	int length;
	length = strlen(theWord);
	missedCount = 0;
	char final[40];
	strcpy_s(final, 40, theWord);
	
	// loop that copies underscores into a varible
	for (i = 0; i < length; ++i) {
		final[i] = '_';
	}

	printf("Word has %d letters\n", length);

	// Main loop that counts guesses and determines if player wins or losses
	while (missedCount < 6) {
		printf("Enter your guess: "); // Player input
		scanf_s(" %c", &guess, 1);
		system("cls");
		printf("Your guess is: %c\n", guess);
		missed = 0;

		// Loop to check for a match
		for (i = 0; i < length; ++i) {
			
			if (guess == theWord[i]) {
				final[i] = theWord[i];
				missed = 1;
			}
			
		}
		if (missed == 0) {
			missedCount = missedCount + 1; // counts each miss
		}
		//feedback to the player
		printf("Hangman progress (%d letters): %s\n", length, final);
		printf("You have missed %d times!\n", missedCount);
		win = strcmp(theWord, final);
		
		// Loop to determine if player wins
		if (win == 0) {
			printf("You Win!!!");
			exit(0);
		}
	}
	//If player excedes 6 misses the player losses
	printf("Out of guesses you lose!");
		
	


	return 0;
}
