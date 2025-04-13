#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integers.h"


// Function to initialize storage
void int_init_storage(integer **int_loc, int *capacity, int *size) {
    *capacity = 1;
    *size = 0;
    *int_loc = (integer *)malloc(sizeof(integer) * (*capacity));
    if (*int_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to increase capacity
void int_increase_capacity(integer **int_loc, int *capacity) {
    *capacity *= 2;
    integer *temp = (integer *)realloc(*int_loc, sizeof(integer) * (*capacity));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    *int_loc = temp;
}

// Add variable
void int_add_variable(integer **int_loc, int *size, int *capacity, char *name, int value, int scope) {
    if (*size == *capacity) {
        int_increase_capacity(int_loc, capacity);
    }
    strcpy((*int_loc)[*size].name, name);
    (*int_loc)[*size].value = value;
    (*int_loc)[*size].scope = scope;
    (*size)++;
}

// Get variable
integer* int_get_variable(integer **int_loc, int* size, char *name, int scope) {
    if(size == NULL || name == NULL) {
        printf("Invalid name.\n");
        return NULL;
    }
    integer* latest = NULL;
    for (int i = 0; i < *size; i++) {
        if ((strcmp((*int_loc)[i].name,name) == 0) && (*int_loc)[i].scope <= scope) {
            if (latest == NULL || (*int_loc)[i].scope > latest->scope) {
                latest = int_loc[i];
            }
        }
    }
    if (latest == NULL) {
        printf("Integer with name \"%s\" not found.\n", name);
    }
    return latest;
}

// Arithmetic operations
int int_add(int a, int b) { return a + b; }
int int_subtract(int a, int b) { return a - b; }
int int_multiply(int a, int b) { return a * b; }
int int_divide(int a, int b) { return (b != 0) ? (a / b) : (printf("Division by zero!\n"), 0); }
int int_modulus(int a, int b) { return a % b; }
int int_power(int a, int b) { int result = 1; for (int i = 0; i < b; i++) result *= a; return result; }
int int_absolute(int a) { return abs(a); }

// Logical
int int_logical_and(int a, int b) { return a && b; }
int int_logical_or(int a, int b) { return a || b; }
int int_logical_not(int a) { return !a; }

// Relational
int int_equals(int a, int b) { return a == b; }
int int_not_equals(int a, int b) { return a != b; }
int int_greater_than(int a, int b) { return a > b; }
int int_less_than(int a, int b) { return a < b; }
int int_greater_equals(int a, int b) { return a >= b; }
int int_less_equals(int a, int b) { return a <= b; }

// More integer functions
int int_factorial(int n) { if (n < 0) return -1; int f = 1; for (int i = 1; i <= n; i++) f *= i; return f; }
int int_gcd(int a, int b) { while (b != 0) { int t = b; b = a % b; a = t; } return a; }
int int_lcm(int a, int b) { return (a * b) /int_gcd(a, b); }
int int_is_prime(int n) { if (n < 2) return 0; for (int i = 2; i*i <= n; i++) if (n % i == 0) return 0; return 1; }
int int_is_perfect_square(int n) { for (int i = 0; i*i <= n; i++) if (i*i == n) return 1; return 0; }
int int_reverse_integer(int n) { int r = 0; while (n != 0) { r = r*10 + n%10; n /= 10; } return r; }
int int_count_digits(int n) { if (n == 0) return 1; int c = 0; while (n != 0) { c++; n /= 10; } return c; }
int int_sum_of_digits(int n) { int s = 0; while (n != 0) { s += n % 10; n /= 10; } return s; }

// I/O and management

void int_print_variable(integer *int_loc, int size, char *name,int scope) {
    integer *var = int_get_variable(&int_loc, &size, name,scope);
    if (var) {
        printf("%s = %d\n", var->name, var->value);
    } else {
        printf("Variable %s not found.\n", name);
    }
}

void int_update_variable(integer *int_loc, int size, char *name, int new_value,int scope) {
    integer *var = int_get_variable(&int_loc, &size, name,scope);
    if (var) {
        var->value = new_value;
        printf("%s updated to %d\n", name, new_value);
    } else {
        printf("Variable %s not found.\n", name);
    }
}

void int_delete_variable(integer *int_loc, int *size, char *name) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp(int_loc[i].name, name) != 0) {
            int_loc[new_size++] = int_loc[i];
        }
    }
    if (new_size == *size) {
        printf("Variable %s not found.\n", name);
    } else {
        printf("Variable %s deleted.\n", name);
    }
    *size = new_size;
}

void int_free_scope_variables(integer *int_loc, int *size, int scope) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if (int_loc[i].scope != scope) {
            int_loc[new_size++] = int_loc[i];
        }
    }
    *size = new_size;
    printf("Variables with scope %d removed.\n", scope);
}

void int_display_variables(integer *int_loc, int size) {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", int_loc[i].name, int_loc[i].value, int_loc[i].scope);
    }
}

void int_free_all(integer **int_loc, int *capacity, int *size) {
    free(*int_loc);
    *int_loc = NULL;
    *capacity = 0;
    *size = 0;
    printf("All memory freed.\n");
}

// Main to test
void int_test() {
    integer *int_loc = NULL;
    int capacity = 0, size = 0;

    int_init_storage(&int_loc, &capacity, &size);

    int_add_variable(&int_loc, &size, &capacity, "a", 5, 1);
    int_add_variable(&int_loc, &size, &capacity, "b", 10, 1);
    int_display_variables(int_loc, size);

    printf("\nReading a new variable:\n");

    int_update_variable(int_loc, size, "a", 15,0);
    int_print_variable(int_loc, size, "a",0);

    printf("\nDeleting variable 'b'\n");
    int_delete_variable(int_loc, &size, "b");
    int_display_variables(int_loc, size);

    printf("\nMath test on 'a' and 'c':\n");
    integer *a = int_get_variable(&int_loc, &size, "a",1);
    integer *c = int_get_variable(&int_loc, &size, "c",2);
    if (a && c) {
        printf("Sum = %d\n", int_add(a->value, c->value));
        printf("Product = %d\n", int_multiply(a->value, c->value));
        printf("Power = %d\n", int_power(a->value, 2));
        printf("GCD = %d\n", int_gcd(a->value, c->value));
    }

    printf("\nFreeing scope 1 variables:\n");
    int_free_scope_variables(int_loc, &size, 1);
    int_display_variables(int_loc, size);

    printf("\nFreeing all memory.\n");
    int_free_all(&int_loc, &capacity, &size);

    return;
}

