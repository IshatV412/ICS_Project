#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <stdbool.h>

#define MAX_LENGTH 50

// Structure to represent a boolean variable
struct boolean {
    char name[MAX_LENGTH];
    int value;
    int scope;
};

#define MAX_LENGTH 50 // Maximum length for variable names

void bool_init_storage(); 

// Function to double the storage capacity
void bool_increase_capacity();

// Function to add a new boolean variable
void bool_add_variable(char *name, int value, int scope);

// Function to get a variable by name
struct boolean* bool_get_variable(char *name, struct boolean *bool_loc);

// Logical operations for boolean values
bool bool_or(bool a, bool b) { return (a || b); }
bool bool_and(bool a, bool b) { return (a && b); }
bool bool_not(bool a) { return (!a); }
bool bool_nor(bool a, bool b) { return (!(a || b)); }
bool bool_nand(bool a, bool b) { return !(a && b); }
bool bool_xor(bool a, bool b) { return (((!a) && b) || ((!b) && a)); }
bool bool_xnor(bool a, bool b) { return !xor(a, b); }

// Function to read a boolean value from the user
void bool_read_variable(char *name, int scope, struct boolean *bool_loc);

// Function to print the value of a specific variable
void bool_print_variable(char *name, struct boolean *bool_loc);

// Function to update the value of an existing variable
void bool_update_variable(char *name, int new_value, struct boolean *bool_loc);

// Function to delete a specific variable by name
void bool_delete_variable(char *name, struct boolean *bool_loc);

// Function to free memory allocated for variables of a specific scope
void bool_free_variables(int scope, struct boolean *bool_loc);

// Function to free all allocated memory
void bool_free_all_memory(struct boolean *bool_loc);

// Function to display all stored variables
void bool_display_variables(struct boolean *bool_loc);

#endif // BOOLEAN_H
