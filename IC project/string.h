#ifndef STRING_H
#define STRING_H

#define MAX_STRING_LENGTH 50  // Maximum allowed string length

// Structure to represent a string variable
typedef struct {
    char name[MAX_STRING_LENGTH];
    char value[MAX_STRING_LENGTH];  // Character array for storing the string
    int scope;                      // Scope of the string
} string;

#define MAX_STRING_LENGTH 50  // Maximum allowed string length

// Initialize string storage
void init_string_storage();

// Resize string storage
void increase_string_capacity();

// Add new string variable
void add_string_variable(const char *name, const char *value, int scope);

// Find string variable by name and highest available scope
string* get_string_variable(const char *name, int current_scope);

// Update string value using pointer
void update_string_variable_ptr(string *var, const char *new_value);

// Print string value using pointer
void print_string_variable_ptr(string *var);

// Delete a variable using pointer
void delete_string_variable_ptr(string *var);

// Display all variables
void display_string_variables();

// Free all variables of a specific scope
void free_string_variables_by_scope(int scope);

// Free all memory
void free_all_string_memory();

#endif // STRING_H
