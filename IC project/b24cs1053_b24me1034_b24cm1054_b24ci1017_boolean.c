#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_boolean.h"
#define MAX_LENGTH 50 // Max length for variable names

// Global variables
int bool_capacity = 1;
int bool_size = 0;
boolean *bool_loc = NULL;

// Initialize boolean variable storage
void bool_init_storage() {
    bool_loc = (boolean*)malloc(bool_capacity * sizeof(boolean));
    if (bool_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Increase storage capacity
void bool_increase_capacity() {
    bool_capacity *= 2;
    boolean *temp = (boolean*)realloc(bool_loc, bool_capacity * sizeof(boolean));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    bool_loc = temp;
}

// Add a new boolean variable (ensures unique name in scope)
void bool_add_variable(char *name, int value, int scope) {
    if (value != 0 && value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        exit(1);
    }

    // Check for existing variable in same scope
    for (int i = 0; i < bool_size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0 && bool_loc[i].scope == scope) {
            printf("Error: Variable %s already exists in scope %d!\n", name, scope);
            return;
        }
    }

    if (bool_size == bool_capacity) {
        bool_increase_capacity();
    }

    strcpy(bool_loc[bool_size].name, name);
    bool_loc[bool_size].value = value;
    bool_loc[bool_size].scope = scope;
    bool_size++;
}

// Get variable by name and scope
boolean* bool_get_variable(char *name, int scope) {
    for (int i = 0; i < bool_size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0 && bool_loc[i].scope == scope) {
            return &bool_loc[i];
        }
    }
    return NULL;
}

// Logical operations
bool bool_or(bool a, bool b)   { return a || b; }
bool bool_and(bool a, bool b)  { return a && b; }
bool bool_not(bool a)          { return !a; }
bool bool_nor(bool a, bool b)  { return !(a || b); }
bool bool_nand(bool a, bool b) { return !(a && b); }
bool bool_xor(bool a, bool b)  { return (a && !b) || (!a && b); }
bool bool_xnor(bool a, bool b) { return !(a ^ b); }

// Update existing variable's value
void bool_update_variable(char *name, int scope, int new_value) {
    if (new_value != 0 && new_value != 1) {
        printf("Error: Boolean values must be 0 or 1.\n");
        return;
    }

    boolean *var = bool_get_variable(name, scope);
    if (var != NULL) {
        var->value = new_value;
    } else {
        printf("Error: Variable %s not found in scope %d.\n", name, scope);
    }
}

// Delete a boolean variable by name and scope
void bool_delete_variable(char *name, int scope) {
    for (int i = 0; i < bool_size; i++) {
        if (strcmp(bool_loc[i].name, name) == 0 && bool_loc[i].scope == scope) {
            // Shift remaining elements
            for (int j = i; j < bool_size - 1; j++) {
                bool_loc[j] = bool_loc[j + 1];
            }
            bool_size--;
            printf("Variable %s in scope %d deleted.\n", name, scope);
            return;
        }
    }
    printf("Variable %s not found in scope %d.\n", name, scope);
}

// Free all variables with a specific scope
void bool_free_scope_variables(int scope) {
    int new_size = 0;
    for (int i = 0; i < bool_size; i++) {
        if (bool_loc[i].scope != scope) {
            bool_loc[new_size++] = bool_loc[i];
        }
    }
    int removed = bool_size - new_size;
    bool_size = new_size;
    printf("%d variable(s) removed from scope %d.\n", removed, scope);
}

// Free all allocated memory
void bool_free_all_memory() {
    free(bool_loc);
    bool_loc = NULL;
    bool_size = 0;
    bool_capacity = 1;
    printf("All boolean memory freed.\n");
}

// Display all boolean variables
void bool_display_variables() {
    if (bool_size == 0) {
        printf("No variables stored.\n");
        return;
    }

    for (int i = 0; i < bool_size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n",
               bool_loc[i].name, bool_loc[i].value, bool_loc[i].scope);
    }
}
void bool_test_all() {
    printf("---- Initializing Boolean System ----\n");
    bool_init_storage();

    printf("\n---- Adding Boolean Variables ----\n");
    bool_add_variable("flag", 1, 0);
    bool_add_variable("done", 0, 0);
    bool_add_variable("ready", 1, 1);
    bool_display_variables();

    printf("\n---- Testing Duplicate Entry (Should Fail) ----\n");
    bool_add_variable("flag", 0, 0); // Duplicate in same scope

    printf("\n---- Updating Variable Value ----\n");
    bool_update_variable("done", 0, 1);
    bool_update_variable("missing", 0, 1); // Should show error
    bool_display_variables();

    printf("\n---- Logical Operations ----\n");
    printf("true OR false = %d\n", bool_or(1, 0));
    printf("true AND false = %d\n", bool_and(1, 0));
    printf("NOT true = %d\n", bool_not(1));
    printf("true NOR false = %d\n", bool_nor(1, 0));
    printf("true NAND true = %d\n", bool_nand(1, 1));
    printf("true XOR false = %d\n", bool_xor(1, 0));
    printf("true XNOR false = %d\n", bool_xnor(1, 0));

    printf("\n---- Delaeting a Variable ----\n");
    bool_delete_variable("flag", 0);
    bool_display_variables();

    printf("\n---- Freeing Variables in Scope 1 ----\n");
    bool_free_scope_variables(1);
    bool_display_variables();

    printf("\n---- Final Cleanup ----\n");
    bool_free_all_memory();
}
