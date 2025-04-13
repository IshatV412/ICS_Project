#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int char_capacity = 1;
int char_size = 0;
character *char_loc = NULL;

// Function to initialize storage
void init_char_storage() {
    char_loc = (character*)malloc(char_capacity * sizeof(character));
    if (char_loc == NULL) exit(1);
}

// Function to resize storage when needed
void increase_char_capacity() {
    char_capacity *= 2;
    character* temp = (character*)realloc(char_loc, char_capacity * sizeof(character));
    if (temp == NULL) exit(1);
    char_loc = temp;
}

character* get_char_variable(char *name, int scope) {
    character* latest = NULL;
    for (int i = 0; i < char_size; i++) {
        if (strcmp(char_loc[i].name, name) == 0 && char_loc[i].scope <= scope) {
            if (latest == NULL || char_loc[i].scope > latest->scope) {
                latest = &char_loc[i];
            }
        }
    }
    return latest;
}
// Function to add a new character variable and return its pointer
character* add_char_variable(char *name, char value, int scope) {
    if (char_size == char_capacity) {
        increase_char_capacity();
    }
    strcpy(char_loc[char_size].name, name);
    char_loc[char_size].value = value;
    char_loc[char_size].scope = scope;
    return &char_loc[char_size++];
}

// Function to update value via pointer
void update_char_variable(character *var, char new_value) {
    if (var != NULL) {
        var->value = new_value;
    }
}

// Function to print variable via pointer
void print_char_variable(character *var) {
    if (var != NULL) {
        printf("Variable %s = %c\n", var->name, var->value);
    }
}

// Relational Operators
int char_equals(char a, char b) { return a == b; }
int char_not_equals(char a, char b) { return a != b; }
int char_greater_than(char a, char b) { return a > b; }
int char_less_than(char a, char b) { return a < b; }
int char_greater_equals(char a, char b) { return a >= b; }
int char_less_equals(char a, char b) { return a <= b; }

// Additional Character Functions
char to_uppercase(char c) { return toupper(c); }
char to_lowercase(char c) { return tolower(c); }
int is_digit(char c) { return isdigit(c) != 0; }
int is_letter(char c) { return isalpha(c) != 0; }
int is_whitespace(char c) { return isspace(c) != 0; }
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
int is_consonant(char c) {
    return is_letter(c) && !is_vowel(c);
}
int is_punctuation(char c) { return ispunct(c); }
char toggle_case(char c) {
    if (isupper(c)) return tolower(c);
    if (islower(c)) return toupper(c);
    return c;
}
int char_to_int(char c) {
    return is_digit(c) ? c - '0' : -1;
}
char int_to_char(int n) {
    return (n >= 0 && n <= 9) ? '0' + n : '\0';
}
int get_ascii_value(char c) { return (int)c; }

// Function to delete a variable via pointer
void delete_char_variable(character *var) {
    int index = -1;
    for (int i = 0; i < char_size; i++) {
        if (&char_loc[i] == var) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int j = index; j < char_size - 1; j++) {
            char_loc[j] = char_loc[j + 1];
        }
        char_size--;
    }
}

// Function to display all stored variables
void display_char_variables() {
    if (char_size == 0) {
        printf("No character variables stored.\n");
        return;
    }
    for (int i = 0; i < char_size; i++) {
        printf("Name: %s, Value: %c, Scope: %d\n", char_loc[i].name, char_loc[i].value, char_loc[i].scope);
    }
}

// Free all memory
void free_char_memory() {
    free(char_loc);
    char_loc = NULL;
    char_size = 0;
    char_capacity = 1;
}
