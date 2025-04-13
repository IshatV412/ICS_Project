#ifndef STRING_H
#define STRING_H

#define MAX_STRING_LENGTH 50  // Maximum allowed string length

typedef struct {
    char name[MAX_STRING_LENGTH];
    char value[MAX_STRING_LENGTH];  // Character array for storing the string
    int scope;                      // Scope of the string
} string;

void init_string_storage();
void increase_string_capacity();
void add_string_variable(char *name, char *value, int scope);
string* get_string_variable(char *name, int current_scope);
void update_string_variable_ptr(string *var, char *new_value);
void print_string_variable_ptr(string *var);
void delete_string_variable_ptr(string *var);
void display_string_variables();
void free_string_variables_by_scope(int scope);
void free_all_string_memory();

#endif // STRING_H
