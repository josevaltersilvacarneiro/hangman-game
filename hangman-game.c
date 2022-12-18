#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "hangman-game.h"

void
get_secret_word(char *secret_word)
{
	FILE *fil;

	int seconds = time(0);

	unsigned int number_of_words;
	unsigned int line;

	srandom(seconds);

	fil = fopen("words.txt", "r");

	if (fil == 0) {
		printf("There was an error\n");
		exit(1);
	}

	fscanf(fil, "%d", &number_of_words);

	line = random() % number_of_words + 1;

	for (register int i = 0; i < line; i++) {
		fscanf(fil, "%s", secret_word);
	}

	fclose(fil);
}

void
push_secret_word(void)
{
	/* 
	 * This procedure stores a new secret word
	 * in the file `words.txt`.
	 *
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

int
failed(void)
{
	static int hung = MAX_NUMBER_OF_TRIES;
	
	return !(--hung);
}

char
get_letter(char *secret_letters_found)
{
	char spoken_letter;
	bool in;

	do {
		in = false;

		printf("Type the spoken letter: ");
		scanf(" %c", &spoken_letter);

		while (*secret_letters_found) {
			if (*secret_letters_found == spoken_letter) {
				in = true;

				break;
			}
			secret_letters_found++;
		}
	} while (in);

	return spoken_letter;
}

bool
take_guess(const char *secret_word, char *secret_letters_found, unsigned int word_length)
{
	char letter;
	bool found = false;

	letter = get_letter(secret_letters_found);

	for (register int i = 0; i < word_length; i++)
		if (secret_word[i] == letter) {
			secret_letters_found[i] = letter;
			found = true;
		}
	
	return found;
}

void
update(char *secret_letters_found)
{
	system("clear");

	printf("************************************\n");
	printf("*          Hangman Game            *\n");
	printf("************************************\n");

	printf("%s\n", secret_letters_found);
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
	char secret_word[20], secret_letters_found[20];
	unsigned int word_length;
	bool hit = false, hung = false;

	get_secret_word(secret_word);

	word_length = strlen(secret_word);

	for (register int i = 0; i < word_length; i++)
		secret_letters_found[i] = '_';
	secret_letters_found[word_length] = '\0';

	do {
		bool found;

		update(secret_letters_found);

		found = take_guess(secret_word, secret_letters_found, word_length);

		if (!found && failed())
			hung = true;

		if (strcmp(secret_letters_found, secret_word) == 0)
			hit = true;

	} while (!hit && !hung);

	if (hit)
		print_win(secret_word);
	else
		print_loss(secret_word);

	return 0;
}
