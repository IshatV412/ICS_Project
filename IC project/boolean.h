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
// Initialize boolean variable storage
void bool_init_storage();
// Increase storage capacity
void bool_increase_capacity();
// Add a new boolean variable (ensures unique name in scope)
void bool_add_variable(char *name, int value, int scope);
boolean* bool_get_variable(char *name, int scope);
// Logical operations
bool bool_or(bool a, bool b);  
bool bool_and(bool a, bool b);  
bool bool_not(bool a);     
bool bool_nor(bool a, bool b);  
bool bool_nand(bool a, bool b); 
bool bool_xor(bool a, bool b);  
bool bool_xnor(bool a, bool b); 

// Update existing variable's value
void bool_update_variable(char *name, int scope, int new_value);
// Delete a boolean variable by name and scope
void bool_delete_variable(char *name, int scope);
// Free all variables with a specific scope
void bool_free_scope_variables(int scope);
// Free all allocated memory
void bool_free_all_memory();
// Display all boolean variables
void bool_display_variables();
void bool_test_all();
#endif // BOOLEAN_H
