#ifndef INTEGERS_H
#define INTEGERS_H

typedef struct {
    char name[50];
    int value;
    int scope;
} integer;

// Storage management
integer* int_init_storage(integer *int_loc, int capacity);
integer* int_increase_capacity(integer *int_loc, int capacity);
void int_free_variables(int scope, integer *int_loc, int size);
void int_free_all_memory(integer *int_loc, int size, int capacity);

// Variable operations
integer* int_add_variable(char *name, int value, int scope, integer *int_loc, int size, int capacity);
integer* int_get_variable(char *name, integer *int_loc, int size);
integer* int_read_variable(char *name, int scope, integer *int_loc, int size, int capacity);
void int_print_variable(char *name, integer *int_loc, int size);
integer* int_update_variable(char *name, int new_value, integer *int_loc, int size);
integer* int_delete_variable(char *name, integer *int_loc, int size);
integer* int_display_variables(integer *int_loc, int size);

// Arithmetic functions
int int_add(int a, int b);
int int_subtract(int a, int b);
int int_multiply(int a, int b);
int int_divide(int a, int b);
int int_modulus(int a, int b);
int int_power(int a, int b);
int int_absolute(int a);

// Logical operations
int int_logical_and(int a, int b);
int int_logical_or(int a, int b);
int int_logical_not(int a);

// Relational operators
int int_equals(int a, int b);
int int_not_equals(int a, int b);
int int_greater_than(int a, int b);
int int_less_than(int a, int b);
int int_greater_equals(int a, int b);
int int_less_equals(int a, int b);

// Utility functions
int int_factorial(int n);
int int_gcd(int a, int b);
int int_lcm(int a, int b);
int int_is_prime(int n);
int int_is_perfect_square(int n);
int int_reverse_integer(int n);
int int_count_digits(int n);
int int_sum_of_digits(int n);

#endif // INTEGERS_H
