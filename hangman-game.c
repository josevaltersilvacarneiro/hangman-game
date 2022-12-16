#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 5;

int
hung(const char *secret_word)
{
	static int hung = MAX + strlen(secret_word);

	return --hung;
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
	bool hit = false;

	sprintf(secret_word, "Melancia");

	for (register int i = 0; i < strlen(secret_word); i++)
		secret_letters_found[i] = '_';
	secret_letters_found[strlen(secret_word)] = '\0';

	do {
		char letter;

		update(secret_letters_found);

		letter = get_letter(secret_letters_found);

		for (register int i = 0; i < strlen(secret_word); i++)
			if (secret_word[i] == letter)
				secret_letters_found[i] = letter;

		if (strcmp(secret_letters_found, secret_word) == 0)
			hit = true;

	} while (!hit && hung(secret_word));

	update(secret_letters_found);

	return 0;
}
