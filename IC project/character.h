#ifndef CHARACTER_H
#define CHARACTER_H
// Structure to represent a character variable
typedef struct {
    char name[50];
    char value;
    int scope;
} character;

void init_char_storage();
void increase_char_capacity();
void free_char_memory();

character* add_char_variable(char *name, char value, int scope);
void update_char_variable(character *var, char new_value);
void print_char_variable_ptr(character *var);

character* get_char_variable(char* name, int scope);

void delete_char_variable(character *var);
void print_char_variable(character *char_loc, int size, char *name);
void display_char_variables();

// Relational operators
int char_equals(char a, char b);
int char_not_equals(char a, char b);
int char_greater_than(char a, char b);
int char_less_than(char a, char b);
int char_greater_equals(char a, char b);
int char_less_equals(char a, char b);

// Character utility functions
char to_uppercase(char c);
char to_lowercase(char c);
int is_digit(char c);
int is_letter(char c);
int is_whitespace(char c);
int is_vowel(char c);
int is_consonant(char c);
int is_punctuation(char c);
char toggle_case(char c);
int char_to_int(char c);
char int_to_char(int n);
int get_ascii_value(char c);

#endif // CHARACTER_H
