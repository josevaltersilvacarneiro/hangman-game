#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "hangman-game.h"

void
get_secret_word(char *secret_word)
{
	/*
	 * This procedure gets a new secret word
	 * from the file `words.txt`.
	 */

	FILE *fil;
	int seconds = time(0);
	unsigned int number_of_words;
	unsigned int line;

	srandom(seconds);

	fil = fopen("words.txt", "r"); // It tries to open the file `words.txt` in read only mode //
	if (fil == 0) {
		printf("There was an error\n");
		exit(1);
	}

	fscanf(
			fil,
			"%d",
			&number_of_words
		);                     // It gets the num of secret words in the file `words.txt` //

	line = random() % number_of_words + 1;    /* It draws a secret word */

	for (register int i = 0; i < line; i++) { /* It gets the secret word drawn */
		fscanf(fil, "%s", secret_word);
	}

	fclose(fil);                   // It closes the file                                      //
}

void
push_secret_word(void)
{
	/* 
	 * This procedure stores a new secret word
	 * in the file `words.txt`.
	 */

	FILE *file;
	unsigned int number_of_words;
	char new_secret_word[20];

	/* It waits for the user to type a new word and stores in new_secret_word */

	printf("Type new secret word: ");
	scanf("%s", new_secret_word);

	/* It tries to open the file `words.txt` in read and write mode */

	file = fopen("words.txt", "r+");
	if (file == 0) {
		printf("There was an error\n");
		exit(1);
	}
	
	fscanf(
			file,
			"%d",
			&number_of_words
		);                      // It reads the number of words in the file `words.txt`         //
	number_of_words++;              // It increments plus                                           //
	fseek(file, 0, SEEK_SET);       // It puts the pointer at the beginning                         //
	fprintf(
			file,
			"%d",
			number_of_words
		);                      // It saves the new num of secret words in the file `words.txt` //
	fseek(file, 0, SEEK_END);       // It puts the pointer at the end                               //
	fprintf(
			file,
			"%s",
			new_secret_word
		);                      // It saves one more secret word in the file `words.txt`        //
	fclose(file);                   // It closes the file                                           //
}

bool
failed(void)
{
	/*
	 * This function should be called every time the
	 * user types a letter that doens't belong
	 * to the secret word.
	 *
	 * This function returns `true` if the number
	 * of tries reached zero; else returns
	 * `false`.
	 *
	 * Initially the `hung` variable is set
	 * equal to `MAX_NUMBER_OF_TRIES`.
	 * Every time the function is called
	 * the variable `hung` is decremented
	 * by one. As every positive num is
	 * treated as true, it's enougth to
	 * deny it to know if it has reached
	 * zero and returns it.
	 */

	static int hung = MAX_NUMBER_OF_TRIES;
	
	return !(--hung);
}

bool
won(const char *secret_word, const char *typed_letters)
{
	unsigned int number_of_corrected_letters = 0;

	for (register int i = 0; i < strlen(secret_word); i++)
	{
		bool found = false;

		for (register int j = 0; j < strlen(typed_letters) && !found; j++)
			if (*(secret_word + i) == *(typed_letters + j))
			{
				found = true;
				number_of_corrected_letters++;
			}
	}

	return number_of_corrected_letters == strlen(secret_word);
}

char
get_letter(const char *typed_letters)
{
	/*
	 * This function receives as parameter a pointer
	 * that points to the letters typed by the user.
	 * It waits until the user enters a letter that
	 * isn't in this set of letters entered by the
	 * user. At the end, returns the letter.
	 */

	char typed_letter;
	bool in;

	do
	{
		in = false;

		printf("Type the spoken letter: ");
		scanf(" %c", &typed_letter);

		while (*typed_letters && !in)
		{
			if (*typed_letters == typed_letter)
				in = true;

			typed_letters++;
		}
	} while (in);

	return typed_letter;
}

bool
take_guess(const char *secret_word, char *typed_letters)
{
	unsigned length;
	bool found = false;
	char letter;

	length = strlen(typed_letters);

	letter = get_letter(typed_letters);

	typed_letters[length] = letter;
	typed_letters[length + 1] = '\0';

	while (*secret_word && !found)
	{
		if (*secret_word == letter)
			found = true;
		
		secret_word++;
	}
	
	return found;
}

void
update(const char *secret_word, const char *typed_letters)
{
	system("clear");

	printf("************************************\n");
	printf("*          Hangman Game            *\n");
	printf("************************************\n");

	while (*secret_word)
	{
		bool found = false;

		for (register int i = 0; i < strlen(typed_letters) && !found; i++)
			if (*secret_word == *(typed_letters + i))
				found = true;

		found ? printf("%c", *secret_word) : printf("_");

		secret_word++;
	}
	printf("\n");
}

void
print_win(const char *secret_word)
{
	char new;

	system("clear");

	printf("You win! The secret word is %s\n", secret_word);

	printf("Do you want to type a new secret word: ");
	scanf(" %c", &new);

	if (new == 'y')
		push_secret_word();
}

void
print_loss(const char *secret_word)
{
	system("clear");

	printf("What a pity! You lost\n");
}

int
main(void)
{
	char secret_word[20], typed_letters[25];
	bool hit = false, hung = false;

	get_secret_word(secret_word);
	
	do {
		bool found;

		update(secret_word, typed_letters);

		found = take_guess(secret_word, typed_letters);

		if (!found && failed())
			hung = true;

		if (won(secret_word, typed_letters))
			hit = true;

	} while (!hit && !hung);

	if (hit)
		print_win(secret_word);
	else
		print_loss(secret_word);

	return 0;
}
