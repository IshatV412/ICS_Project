#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_string.h"
#define MAX_STRING_LENGTH 50  
int string_capacity = 1;
int string_size = 0;
string *string_loc = NULL;

// Initialize string storage
/*void init_string_storage() {
    string_loc = (string*) malloc(string_capacity * sizeof(string));
    if (string_loc == NULL) {
        //printf("Memory allocation failed\n");
        exit(1);
    }
}
*/
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
// Add new string variable (initializes storage if needed)
void add_string_variable(char *name, char *value, int scope) {
    // Initialize storage if not already done
    if (string_loc == NULL) {
        string_loc = (string*) malloc(string_capacity * sizeof(string));
        if (string_loc == NULL) {
            exit(1);
        }
    }

    // Check for duplicate in the same scope
    for (int i = 0; i < string_size; i++) {
        if (strcmp(string_loc[i].name, name) == 0 && string_loc[i].scope == scope) {
            exit(1);
        }
    }

    // Resize if necessary
    if (string_size == string_capacity) {
        increase_string_capacity();
    }

    // Add new variable
    strncpy(string_loc[string_size].name, name, sizeof(string_loc[string_size].name) - 1);
    string_loc[string_size].name[sizeof(string_loc[string_size].name) - 1] = '\0';

    strncpy(string_loc[string_size].value, value, MAX_STRING_LENGTH - 1);
    string_loc[string_size].value[MAX_STRING_LENGTH - 1] = '$';  // Custom terminator

    string_loc[string_size].scope = scope;
    string_size++;
}

// Find string variable by name and highest available scope
string* get_string_variable(char *name, int current_scope) {
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
void update_string_variable_ptr(string *var, char *new_value) {
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
/*int main() {
    // Adding variables (initialization is now automatic)
    add_string_variable("greeting", "Hello", 0);
    add_string_variable("name", "Alice", 0);
    add_string_variable("farewell", "Goodbye", 1);

    printf("All string variables after addition:\n");
    display_string_variables();

    // Access and print a variable
    string *var = get_string_variable("name", 0);
    print_string_variable_ptr(var);

    // Update variable
    update_string_variable_ptr(var, "Bob");
    printf("\nAfter updating 'name':\n");
    print_string_variable_ptr(var);

    // Delete variable
    delete_string_variable_ptr(get_string_variable("greeting", 0));
    printf("\nAfter deleting 'greeting':\n");
    display_string_variables();

    // Free variables in scope 1
    free_string_variables_by_scope(1);
    printf("\nAfter freeing scope 1:\n");
    display_string_variables();

    // Free all memory
    free_all_string_memory();
    return 0;
}*/
