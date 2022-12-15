#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char
get_letter(void)
{
	char spoken_letter;
		
	printf("Type the spoken letter: ");
	scanf(" %c", &spoken_letter);

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
	bool hit = false, hung = false;

	sprintf(secret_word, "Melancia");

	for (register int i = 0; i < strlen(secret_word); i++)
		secret_letters_found[i] = '_';
	secret_letters_found[strlen(secret_word)] = '\0';

	do {
		char letter;

		update(secret_letters_found);

		letter = get_letter();

		for (register int i = 0; i < strlen(secret_word); i++)
			if (secret_word[i] == letter)
				secret_letters_found[i] = letter;

		if (strcmp(secret_letters_found, secret_word) == 0)
			hit = true;

	} while (!hit && !hung);

	update(secret_letters_found);

	return 0;
}
