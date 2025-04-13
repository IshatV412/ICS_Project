#ifndef CHAR_STORAGE_H
#define CHAR_STORAGE_H

// Structure to represent a character variable
typedef struct {
    char name[50];
    char value;
    int scope;
} character;

// Initialization and memory management
void init_char_storage(character **char_loc, int *capacity, int *size);
void increase_char_capacity(character **char_loc, int *capacity);
void free_char_memory(character **char_loc, int *size, int *capacity);
void free_variable_by_scope(character *char_loc, int *size, int scope);

// Character variable operations
void add_char_variable(character **char_loc, int *size, int *capacity, char *name, char value, int scope);
character* get_char_variable(character *char_loc, int size, char *name);
void update_char_variable(character *char_loc, int size, char *name, char new_value);
void delete_char_variable(character *char_loc, int *size, char *name);
void print_char_variable(character *char_loc, int size, char *name);
void display_char_variables(character *char_loc, int size);
void read_char_variable(character **char_loc, int *size, int *capacity, char *name, int scope);

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

#endif // CHAR_STORAGE_H
