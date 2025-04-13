#ifndef STRING_H
#define STRING_H

#define MAX_STRING_LENGTH 50  // Maximum allowed string length

// Structure to represent a string variable
typedef struct {
    char chars[MAX_STRING_LENGTH];  // Character array for storing the string
    int scope;                      // Scope of the string
} string;

// Initialization and Memory Management
string* init_string_storage(int *capacity, int *size);
string* increase_string_capacity(string *str_loc, int *capacity);

// Add string
void add_string(string **str_loc, int *size, int *capacity, const char *value, int scope);

// Display stored strings
void display_strings(string *str_loc, int size);

// Free strings by scope
void free_string_variables(string *str_loc, int *size, int scope);

#endif // STRING_H
