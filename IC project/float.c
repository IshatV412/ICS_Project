#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "float.h"
/*typedef struct {
    char name[50];
    float value;
    int scope;
} decimal;*/

int float_capacity = 1;
int float_size = 0;
decimal *dec_loc = NULL;

// Initialize float storage
void init_float_storage() {
    dec_loc = (decimal*)malloc(float_capacity * sizeof(decimal));
    if (dec_loc == NULL) exit(1);
}

// Increase capacity when needed
void increase_float_capacity() {
    float_capacity *= 2;
    decimal* temp = (decimal*)realloc(dec_loc, float_capacity * sizeof(decimal));
    if (temp == NULL) exit(1);
    dec_loc = temp;
}

// Add a new float variable
void add_float_variable(char *name, float value, int scope) {
    for (int i = 0; i < float_size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0 && dec_loc[i].scope == scope) {
            exit(1); // same name and scope not allowed
        }
    }
    if (float_size == float_capacity) {
        increase_float_capacity();
    }
    strcpy(dec_loc[float_size].name, name);
    dec_loc[float_size].value = value;
    dec_loc[float_size].scope = scope;
    float_size++;
}

// Get variable by name and highest available scope
decimal* get_float_variable(char* name, int scope) {
    decimal* result = NULL;
    int highest_scope = -1;
    for (int i = 0; i < float_size; i++) {
        if (strcmp(dec_loc[i].name, name) == 0 && dec_loc[i].scope <= scope) {
            if (dec_loc[i].scope > highest_scope) {
                highest_scope = dec_loc[i].scope;
                result = &dec_loc[i];
            }
        }
    }
    return result;
}

// Update using pointer
void update_float_variable(decimal *var, float new_value) {
    if (var != NULL) {
        var->value = new_value;
    } else {
        exit(1);
    }
}

// Print using pointer
void print_float_variable(decimal *var) {
    if (var != NULL) {
        printf("Variable %s = %f\n", var->name, var->value);
    } else {
        exit(1);
    }
}

// Delete using pointer
void delete_float_variable(decimal *var) {
    if (var == NULL) exit(1);

    int found = 0;
    for (int i = 0; i < float_size; i++) {
        if (&dec_loc[i] == var) {
            found = 1;
        }
        if (found && i < float_size - 1) {
            dec_loc[i] = dec_loc[i + 1];
        }
    }

    if (found) {
        float_size--;
    } else {
        exit(1);
    }
}

// Display all variables
void display_variables() {
    if (float_size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < float_size; i++) {
        printf("Name: %s, Value: %f, Scope: %d\n", dec_loc[i].name, dec_loc[i].value, dec_loc[i].scope);
    }
}

// Free variables by scope
void free_variables(int scope) {
    int new_size = 0;
    for (int i = 0; i < float_size; i++) {
        if (dec_loc[i].scope != scope) {
            dec_loc[new_size++] = dec_loc[i];
        }
    }
    float_size = new_size;
}

// Free all memory
void free_all_memory() {
    free(dec_loc);
    dec_loc = NULL;
    float_size = 0;
    float_capacity = 1;
}

// Arithmetic operations
float float_add(float a, float b) { return a + b; }
float float_subtract(float a, float b) { return a - b; }
float float_multiply(float a, float b) { return a * b; }
float float_divide(float a, float b) {
    if (b == 0) exit(1);
    return a / b;
}
float float_power(float a, float b) {
    return powf(a, b);
}
float float_absolute(float a) { return fabsf(a); }

// Relational operations
float float_equals(float a, float b) { return a == b; }
float float_not_equals(float a, float b) { return a != b; }
float float_greater_than(float a, float b) { return a > b; }
float float_less_than(float a, float b) { return a < b; }
float float_greater_equals(float a, float b) { return a >= b; }
float float_less_equals(float a, float b) { return a <= b; }
