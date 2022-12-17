#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 5;

int
failed(void)
{
	static int hung = MAX;
	
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

int
main(void)
{
	char secret_word[20], secret_letters_found[20];
	unsigned int word_length;
	bool hit = false, hung = true;

	sprintf(secret_word, "Melancia");
	word_length = strlen(secret_word);

	for (register int i = 0; i < word_length; i++)
		secret_letters_found[i] = '_';
	secret_letters_found[word_length] = '\0';

	do {
		bool found;

		update(secret_letters_found);

		found = take_guess(secret_word, secret_letters_found, word_length);

		if (!found && failed())
			hung = false;

		if (strcmp(secret_letters_found, secret_word) == 0)
			hit = true;

	} while (!hit && hung);

	update(secret_letters_found);

	return 0;
}
