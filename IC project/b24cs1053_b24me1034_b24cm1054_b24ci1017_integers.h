#ifndef B24CS1053_B24ME1034_B24CM1054_B24CI1017_INTEGERS_H
#define B24CS1053_B24ME1034_B24CM1054_B24CI1017_INTEGERS_H

typedef struct {
    char int_name[50];
    int int_value;
    int int_scope;
} int_var;


void int_init_storage();
void int_increase_capacity();
int_var* get_int_var(char *name, int scope);
void int_update_variable(int_var *var, int new_value);
void int_print_variable(int_var *var);
void int_delete_variable(int_var *var);
void int_free_scope(int scope);
void int_free_all();
void int_display_variables();
void int_add_variable(char *name, int scope, int value);
int int_add(int a, int b);
int int_subtract(int a, int b);
int int_multiply(int a, int b);
int int_divide(int a, int b);
int int_modulus(int a, int b);
int int_power(int a, int b);
int int_absolute(int a);

int int_and(int a, int b);
int int_or(int a, int b);
int int_not(int a);

int int_equals(int a, int b);
int int_not_equals(int a, int b);
int int_greater(int a, int b);
int int_less(int a, int b);
int int_greater_eq(int a, int b);
int int_less_eq(int a, int b);

int int_factorial(int n);
int int_gcd(int a, int b);
int int_lcm(int a, int b);
int int_is_prime(int n);
int int_is_square(int n);
int int_reverse(int n);
int int_digit_count(int n);
int int_digit_sum(int n);

#endif // INTEGERS_H
