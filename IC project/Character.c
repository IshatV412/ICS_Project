#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "character.h"

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
void update_char_variable_ptr(character *var, char new_value) {
    if (var != NULL) {
        var->value = new_value;
    }
}

// Function to print variable via pointer
void print_char_variable_ptr(character *var) {
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
void delete_char_variable_ptr(character *var) {
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

// Function to read from user and return pointer
character* read_char_variable(char *name, int scope) {
    char value;
    scanf(" %c", &value);
    return add_char_variable(name, value, scope);
}
void test_operations() {
    init_char_storage();

    // Add some variables
    character *a = add_char_variable("a", 'x', 1);
    character *b = add_char_variable("b", 'y', 2);
    character *c = add_char_variable("c", 'z', 3);

    printf("After adding variables:\n");
    display_char_variables();
    printf("\n");

    // Print individual variables
    printf("Printing individual variables:\n");
    print_char_variable_ptr(a);
    print_char_variable_ptr(b);
    print_char_variable_ptr(c);
    printf("\n");

    // Update variable 'a'
    update_char_variable_ptr(a, 'A');
    update_char_variable_ptr(b, 'B');
    printf("After updating variables 'a' and 'b':\n");
    display_char_variables();
    printf("\n");

    // Use character functions
    printf("Character functions on variable 'c' (%c):\n", c->value);
    printf("Uppercase: %c\n", to_uppercase(c->value));
    printf("Is vowel? %s\n", is_vowel(c->value) ? "Yes" : "No");
    printf("ASCII value: %d\n", get_ascii_value(c->value));
    printf("\n");

    // Delete variable 'b'
    delete_char_variable_ptr(b);
    printf("After deleting variable 'b':\n");
    display_char_variables();
    printf("\n");

    // Read a variable from user
    printf("Enter a character for new variable 'd': ");
    character *d = read_char_variable("d", 4);
    printf("After reading variable 'd':\n");
    print_char_variable_ptr(d);
    printf("\n");

    // Final state
    printf("Final stored variables:\n");
    display_char_variables();

    // Clean up
    free_char_memory();
    return;
}
