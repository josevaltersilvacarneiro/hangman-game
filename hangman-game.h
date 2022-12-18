#define MAX_NUMBER_OF_TRIES 5

void get_secret_word(char *secret_word);
void push_secret_word(void);
int failed(void);
char get_letter(char *secret_letters_found);
bool take_guess(const char *secret_word, char *secret_letters_found, unsigned int word_length);
void update(char *secret_letters_found);
