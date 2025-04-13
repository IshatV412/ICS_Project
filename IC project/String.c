#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#define MAX_STRING_LENGTH 50  // Maximum allowed string length

int string_capacity = 1;
int string_size = 0;
string *string_loc = NULL;

// Initialize string storage
void init_string_storage() {
    string_loc = (string*) malloc(string_capacity * sizeof(string));
    if (string_loc == NULL) {
        //printf("Memory allocation failed\n");
        exit(1);
    }
}

// Resize string storage
void increase_string_capacity() {
    string_capacity *= 2;
    string *temp = (string*) realloc(string_loc, string_capacity * sizeof(string));
    if (temp == NULL) {
        //printf("Memory reallocation failed\n");
        exit(1);
    }
    string_loc = temp;
}

// Add new string variable
void add_string_variable(const char *name, const char *value, int scope) {
    for (int i = 0; i < string_size; i++) {
        if (strcmp(string_loc[i].name, name) == 0 && string_loc[i].scope == scope) {
            //printf("Error: Variable '%s' already exists in scope %d\n", name, scope);
            exit(1);
        }
    }

    if (string_size == string_capacity) {
        increase_string_capacity();
    }

    strncpy(string_loc[string_size].name, name, sizeof(string_loc[string_size].name) - 1);
    string_loc[string_size].name[sizeof(string_loc[string_size].name) - 1] = '\0';

    strncpy(string_loc[string_size].value, value, MAX_STRING_LENGTH - 1);
    string_loc[string_size].value[MAX_STRING_LENGTH - 1] = '$';  // Custom terminator

    string_loc[string_size].scope = scope;
    string_size++;
}

// Find string variable by name and highest available scope
string* get_string_variable(const char *name, int current_scope) {
    string *result = NULL;
    int highest_scope = -1;

    for (int i = 0; i < string_size; i++) {
        if (strcmp(string_loc[i].name, name) == 0 && string_loc[i].scope <= current_scope) {
            if (string_loc[i].scope > highest_scope) {
                highest_scope = string_loc[i].scope;
                result = &string_loc[i];
            }
        }
    }

    return result;
}

// Update string value using pointer
void update_string_variable_ptr(string *var, const char *new_value) {
    if (var != NULL) {
        strncpy(var->value, new_value, MAX_STRING_LENGTH - 1);
        var->value[MAX_STRING_LENGTH - 1] = '$';  // Ensure custom terminator
    } else {
        //printf("Error: String variable not found for update\n");
        exit(1);
    }
}

// Print string value using pointer
void print_string_variable_ptr(string *var) {
    if (var != NULL) {
        printf("Variable %s = %s\n", var->name, var->value);
    } else {
        printf("Error: String variable not found for print\n");
        exit(1);
    }
}

// Delete a variable using pointer
void delete_string_variable_ptr(string *var) {
    if (var == NULL) {
        //printf("Error: Null pointer for delete\n");
        exit(1);
    }

    int found = 0;
    for (int i = 0; i < string_size; i++) {
        if (&string_loc[i] == var) {
            found = 1;
        }
        if (found && i < string_size - 1) {
            string_loc[i] = string_loc[i + 1];
        }
    }

    if (found) {
        string_size--;
    } else {
        //printf("Error: Variable not found in storage for deletion\n");
        exit(1);
    }
}

// Display all variables
void display_string_variables() {
    if (string_size == 0) {
        printf("No string variables found.\n");
        return;
    }

    for (int i = 0; i < string_size; i++) {
        printf("Name: %s, Value: %s, Scope: %d\n", string_loc[i].name, string_loc[i].value, string_loc[i].scope);
    }
}

// Free all variables of a specific scope
void free_string_variables_by_scope(int scope) {
    int new_size = 0;

    for (int i = 0; i < string_size; i++) {
        if (string_loc[i].scope != scope) {
            string_loc[new_size++] = string_loc[i];
        }
    }

    string_size = new_size;
}

// Free all memory
void free_all_string_memory() {
    free(string_loc);
    string_loc = NULL;
    string_capacity = 1;
    string_size = 0;
}
