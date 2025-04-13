#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 50  // Maximum allowed string length

typedef struct {
    char chars[MAX_STRING_LENGTH];  // Character array for storing the string
    int scope;
} string;

// Initialize storage
string* init_string_storage(int *capacity, int *size) {
    *capacity = 1;
    *size = 0;

    string *str_loc = (string*) malloc((*capacity) * sizeof(string));
    if (str_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return str_loc;
}

// Resize storage
string* increase_string_capacity(string *str_loc, int *capacity) {
    *capacity *= 2;
    string *temp = (string*) realloc(str_loc, (*capacity) * sizeof(string));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    return temp;
}

// Add a new string variable
void add_string(string **str_loc, int *size, int *capacity, const char *value, int scope) {
    if (*size == *capacity) {
        *str_loc = increase_string_capacity(*str_loc, capacity);
    }

    strncpy((*str_loc)[*size].chars, value, MAX_STRING_LENGTH - 1);
    (*str_loc)[*size].chars[MAX_STRING_LENGTH - 1] = '$';  // Custom null character
    (*str_loc)[*size].scope = scope;
    (*size)++;
}

// Display all strings
void display_strings(string *str_loc, int size) {
    for (int i = 0; i < size; i++) {
        printf("String: %s, Scope: %d\n", str_loc[i].chars, str_loc[i].scope);
    }
}

// Free string variables of a specific scope
void free_string_variables(string *str_loc, int *size, int scope) {
    int new_size = 0;

    for (int i = 0; i < *size; i++) {
        if (str_loc[i].scope != scope) {
            str_loc[new_size++] = str_loc[i];
        }
    }

    *size = new_size;  // Update size after removal
}

int main() {
    int string_capacity, string_size;
    string *str_loc = init_string_storage(&string_capacity, &string_size);

    add_string(&str_loc, &string_size, &string_capacity, "Hello$", 1);
    add_string(&str_loc, &string_size, &string_capacity, "World$", 2);
    add_string(&str_loc, &string_size, &string_capacity, "Compiler$", 1);

    display_strings(str_loc, string_size);

    free_string_variables(str_loc, &string_size, 1);
    printf("\nAfter freeing scope 1:\n");
    display_strings(str_loc, string_size);

    free(str_loc);  // Free allocated memory
    return 0;
}
