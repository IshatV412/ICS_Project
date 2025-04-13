#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "boolean.h"
#include <string.h> // Include for string functions

#define MAX_LENGTH 50 // Maximum length for variable names

int bool_capacity = 1; // Initial storage capacity
int bool_size = 0; // Number of currently stored variables
struct boolean *bool_loc = NULL; // Pointer to dynamically allocated array

// Structure to represent a boolean variable
typedef struct boolean {
    char name[MAX_LENGTH]; // Name of the variable
    int value; // Boolean value (0 or 1)
    int scope; // Scope of the variable
}boolean;

// int capacity = 1;  // Initial storage capacity
// int size = 0;  // Number of currently stored variables
// struct boolean *bool_loc = NULL; // Pointer to dynamically allocated array

// Function to initialize storage
void bool_init_storage() {
    bool_loc = (struct boolean*)malloc(bool_capacity * sizeof(struct boolean));
    if (bool_loc == NULL) {
        printf("Memory allocation failed\n");
    }
}

// Function to double the storage capacity
void bool_increase_capacity() {
    bool_capacity *= 2;
    struct boolean* temp = (struct boolean*)realloc(bool_loc, bool_capacity * sizeof(struct boolean));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    bool_loc = temp;
}

// Function to add a new boolean variable
void bool_add_variable(char *name, int value, int scope) {
    // Ensure value is either 0 or 1
    if (value != 0 && value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        return;
    }

    // Check if a variable with the same name and scope exists
    for (int i = 0; i < bool_size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0 && bool_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }

    // Increase capacity if needed
    if (bool_size == bool_capacity) {
        bool_increase_capacity(bool_capacity);
    }

    // Add new variable
    strcpy(bool_loc[bool_size].name, name);
    bool_loc[bool_size].value = value;
    bool_loc[bool_size].scope = scope;
    bool_size++;
}

// Function to get a variable by name
struct boolean* bool_get_variable(char *name) {
    for (int i = 0; i < bool_size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0) {
            return &bool_loc[i];
        }
    }
    return NULL;
}

// Logical operations for boolean values
bool bool_or(bool a, bool b) { return (a || b); }
bool bool_and(bool a, bool b) { return (a && b); }
bool bool_not(bool a) { return (!a); }
bool bool_nor(bool a, bool b) { return (!(a || b)); }
bool bool_nand(bool a, bool b) { return !(a && b); }
bool bool_xor(bool a, bool b) { return (((!a) && b) || ((!b) && a)); }
bool bool_xnor(bool a, bool b) { return !xor(a, b); }

// Function to read a boolean value from the user
void bool_read_variable(boolean *bool_loc) {
    int value;
    printf("Enter boolean value (0 or 1) for %s: ", bool_loc->name);
    scanf("%d", &value);

    // Validate input
    if (value != 0 && value != 1) {
        printf("Invalid input. Only 0 or 1 are allowed.\n");
        return;
    }

    bool_add_variable(bool_loc->name, value, scope);
}

// Function to update the value of an existing variable
void bool_update_variable(boolean *bool_loc, int new_value) {
    if (new_value != 0 && new_value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        return;
    }
    bool_loc->value = new_value;
}

// Function to delete a specific variable by name
void bool_delete_variable(boolean *bool_loc) {
    free(bool_loc);
}

// Function to free memory allocated for variables of a specific scope
void bool_free_variables(int scope, int size, struct boolean *bool_loc) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (bool_loc[i].scope != scope) {
            bool_loc[new_size] = bool_loc[i];
            new_size++;
        }
    }
    size = new_size;
    printf("Variables with scope %d have been removed.\n", scope);
}

// Function to free all allocated memory
void bool_free_all_memory(struct boolean *bool_loc, int size, int capacity) {
    free(bool_loc);
    bool_loc = NULL;
    size = 0;
    capacity = 1;
    printf("All memory has been freed.\n");
}

// Function to display all stored variables
void bool_display_variables(int size, struct boolean *bool_loc) {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", bool_loc[i].name, bool_loc[i].value, bool_loc[i].scope);
    }
}
