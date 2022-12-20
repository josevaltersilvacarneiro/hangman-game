#define MAX_NUMBER_OF_TRIES 5

void get_secret_word(char *secret_word);
void push_secret_word(void);
bool failed(void);
char get_letter(char *typed_letters);
bool take_guess(const char *secret_word, char *secret_letters_found, unsigned int word_length);
void update(char *secret_letters_found);
void print_win(const char *secret_word);
void print_loss(const char *secret_word);
