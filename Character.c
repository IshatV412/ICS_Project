#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char value;
    int scope;
} character;

// Function to initialize storage
character* init_char_storage(int *capacity, int *size) {
    *capacity = 1;
    *size = 0;
    character *char_loc = (character*)malloc(*capacity * sizeof(character));
    if (char_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return char_loc;
}

// Function to resize storage when needed
character* increase_char_capacity(character *char_loc, int *capacity) {
    *capacity *= 2;
    character *temp = (character*)realloc(char_loc, (*capacity) * sizeof(character));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    return temp;
}

// Function to add a new character variable
void add_char_variable(character **char_loc, int *size, int *capacity, char *name, char value, int scope) {
    if (*size == *capacity) {
        *char_loc = increase_char_capacity(*char_loc, capacity);
    }
    strcpy((*char_loc)[*size].name, name);
    (*char_loc)[*size].value = value;
    (*char_loc)[*size].scope = scope;
    (*size)++;
}

// Function to get a character variable by name
character* get_char_variable(character *char_loc, int size, char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            return &char_loc[i];
        }
    }
    return NULL;
}

// Function to update a character variable
void update_char_variable(character *char_loc, int size, char *name, char new_value) {
    for (int i = 0; i < size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            char_loc[i].value = new_value;
            printf("Updated %s to %c\n", name, new_value);
            return;
        }
    }
    printf("Character variable %s not found.\n", name);
}

// Function to print a character variable
void print_char_variable(character *char_loc, int size, char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(char_loc[i].name, name) == 0) {
            printf("Variable %s = %c\n", name, char_loc[i].value);
            return;
        }
    }
    printf("Character variable %s not found.\n", name);
}

// Relational Operators for Characters
int char_equals(char a, char b) { return a == b; }
int char_not_equals(char a, char b) { return a != b; }
int char_greater_than(char a, char b) { return a > b; }
int char_less_than(char a, char b) { return a < b; }
int char_greater_equals(char a, char b) { return a >= b; }
int char_less_equals(char a, char b) { return a <= b; }

// Additional Character Functions
char to_uppercase(char c) { return toupper(c); }
char to_lowercase(char c) { return tolower(c); }
int is_digit(char c) { return isdigit(c); }
int is_letter(char c) { return isalpha(c); }
int is_whitespace(char c) { return isspace(c); }

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
int is_consonant(char c) {
    return is_letter(c) && !is_vowel(c);
}
int is_punctuation(char c) {
    return ispunct(c);
}
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
int get_ascii_value(char c) {
    return (int)c;
}

// Delete a variable by name
void delete_char_variable(character *char_loc, int *size, char *name) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp(char_loc[i].name, name) != 0) {
            char_loc[new_size++] = char_loc[i];
        }
    }
    if (new_size == *size) {
        printf("Character variable %s not found.\n", name);
    } else {
        *size = new_size;
        printf("Deleted character variable %s.\n", name);
    }
}

// Delete variables by scope
void free_variable_by_scope(character *char_loc, int *size, int scope) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if (char_loc[i].scope != scope) {
            char_loc[new_size++] = char_loc[i];
        }
    }
    *size = new_size;
    printf("Freed variables with scope %d.\n", scope);
}

// Display all variables
void display_char_variables(character *char_loc, int size) {
    if (size == 0) {
        printf("No character variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %c, Scope: %d\n", char_loc[i].name, char_loc[i].value, char_loc[i].scope);
    }
}

// Read character from user
void read_char_variable(character **char_loc, int *size, int *capacity, char *name, int scope) {
    char value;
    printf("Enter value for %s: ", name);
    scanf(" %c", &value);
    add_char_variable(char_loc, size, capacity, name, value, scope);
}

// Free memory
void free_char_memory(character *char_loc) {
    free(char_loc);
    printf("All character memory has been freed.\n");
}

// Main function to test
int main() {
    int char_capacity, char_size;
    character *char_loc = init_char_storage(&char_capacity, &char_size);

    add_char_variable(&char_loc, &char_size, &char_capacity, "ch1", 'A', 1);
    add_char_variable(&char_loc, &char_size, &char_capacity, "ch2", 'b', 2);
    add_char_variable(&char_loc, &char_size, &char_capacity, "ch3", '9', 1);

    display_char_variables(char_loc, char_size);

    printf("ch1 == ch2: %d\n", char_equals(get_char_variable(char_loc, char_size, "ch1")->value, get_char_variable(char_loc, char_size, "ch2")->value));
    printf("ch1 > ch2: %d\n", char_greater_than(get_char_variable(char_loc, char_size, "ch1")->value, get_char_variable(char_loc, char_size, "ch2")->value));

    printf("Uppercase of ch2: %c\n", to_uppercase(get_char_variable(char_loc, char_size, "ch2")->value));
    printf("Lowercase of ch1: %c\n", to_lowercase(get_char_variable(char_loc, char_size, "ch1")->value));
    printf("Is ch3 a digit? %d\n", is_digit(get_char_variable(char_loc, char_size, "ch3")->value));

    printf("\nDeleting 'ch2'...\n");
    delete_char_variable(char_loc, &char_size, "ch2");
    display_char_variables(char_loc, char_size);

    printf("\nFreeing variables with scope 1...\n");
    free_variable_by_scope(char_loc, &char_size, 1);
    display_char_variables(char_loc, char_size);

    printf("\nFreeing all memory...\n");
    free_char_memory(char_loc);

    return 0;
}
