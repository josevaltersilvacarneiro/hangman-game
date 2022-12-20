#define MAX_NUMBER_OF_TRIES 5

void get_secret_word(char *secret_word);
void push_secret_word(void);
bool failed(void);
bool won(const char *secret_word, const char *typed_letters);
char get_letter(const char *typed_letters);
bool take_guess(const char *secret_word, char *typed_letters);
void update(const char *secret_word, const char *typed_letters);
void print_win(const char *secret_word);
void print_loss(const char *secret_word);
