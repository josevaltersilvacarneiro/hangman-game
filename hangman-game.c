#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int
main(void)
{
	char secret_word[20], spoken_word[20];
	bool hit = false, hung = 0;

	sprintf(secret_word, "Melancia");

	do {
		printf("Type the spoken word: ");
		scanf("%s", spoken_word);

		if (strcmp(spoken_word, secret_word) == 0) {
			hit = true;
		}


	} while (!hit && !hung);

	printf("%s\n", secret_word);

	return 0;
}
