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


void bool_init_storage(); 
void bool_increase_capacity();
void bool_add_variable(char *name, int value, int scope);
struct boolean* bool_get_variable(char *name, struct boolean *bool_loc);

bool bool_or(bool a, bool b) { return (a || b); }
bool bool_and(bool a, bool b) { return (a && b); }
bool bool_not(bool a) { return (!a); }
bool bool_nor(bool a, bool b) { return (!(a || b)); }
bool bool_nand(bool a, bool b) { return !(a && b); }
bool bool_xor(bool a, bool b) { return (((!a) && b) || ((!b) && a)); }
bool bool_xnor(bool a, bool b) { return !xor(a, b); }

void bool_read_variable(char *name, int scope, struct boolean *bool_loc);
void bool_print_variable(char *name, struct boolean *bool_loc);
void bool_update_variable(char *name, int new_value, struct boolean *bool_loc);
void bool_delete_variable(char *name, struct boolean *bool_loc);
void bool_free_variables(int scope, struct boolean *bool_loc);
void bool_free_all_memory(struct boolean *bool_loc);
void bool_display_variables(struct boolean *bool_loc);

#endif // BOOLEAN_H
