void get_secret_word(char *secret_word);
int failed(void);
char get_letter(char *secret_letters_found);
bool take_guess(const char *secret_word, char *secret_letters_found, unsigned int word_length);
void update(char *secret_letters_found);
