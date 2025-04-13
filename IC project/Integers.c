#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int value;
    int scope;
} integer;

// Function to initialize storage
void init_integer_array(integer **int_loc, int *capacity, int *size) {
    *capacity = 1;
    *size = 0;
    *int_loc = (integer *)malloc(sizeof(integer) * (*capacity));
    if (*int_loc == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to increase capacity
void increase_capacity(integer **int_loc, int *capacity) {
    *capacity *= 2;
    integer *temp = (integer *)realloc(*int_loc, sizeof(integer) * (*capacity));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    *int_loc = temp;
}

// Add variable
void add_variable(integer **int_loc, int *size, int *capacity, const char *name, int value, int scope) {
    if (*size == *capacity) {
        increase_capacity(int_loc, capacity);
    }
    strcpy((*int_loc)[*size].name, name);
    (*int_loc)[*size].value = value;
    (*int_loc)[*size].scope = scope;
    (*size)++;
}

// Get variable
integer* get_variable(integer *int_loc, int size, const char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(int_loc[i].name, name) == 0) {
            return &int_loc[i];
        }
    }
    return NULL;
}

// Arithmetic operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return (b != 0) ? (a / b) : (printf("Division by zero!\n"), 0); }
int modulus(int a, int b) { return a % b; }
int power(int a, int b) { int result = 1; for (int i = 0; i < b; i++) result *= a; return result; }
int absolute(int a) { return abs(a); }

// Logical
int logical_and(int a, int b) { return a && b; }
int logical_or(int a, int b) { return a || b; }
int logical_not(int a) { return !a; }

// Relational
int equals(int a, int b) { return a == b; }
int not_equals(int a, int b) { return a != b; }
int greater_than(int a, int b) { return a > b; }
int less_than(int a, int b) { return a < b; }
int greater_equals(int a, int b) { return a >= b; }
int less_equals(int a, int b) { return a <= b; }

// More integer functions
int factorial(int n) { if (n < 0) return -1; int f = 1; for (int i = 1; i <= n; i++) f *= i; return f; }
int gcd(int a, int b) { while (b != 0) { int t = b; b = a % b; a = t; } return a; }
int lcm(int a, int b) { return (a * b) / gcd(a, b); }
int is_prime(int n) { if (n < 2) return 0; for (int i = 2; i*i <= n; i++) if (n % i == 0) return 0; return 1; }
int is_perfect_square(int n) { for (int i = 0; i*i <= n; i++) if (i*i == n) return 1; return 0; }
int reverse_integer(int n) { int r = 0; while (n != 0) { r = r*10 + n%10; n /= 10; } return r; }
int count_digits(int n) { if (n == 0) return 1; int c = 0; while (n != 0) { c++; n /= 10; } return c; }
int sum_of_digits(int n) { int s = 0; while (n != 0) { s += n % 10; n /= 10; } return s; }

// I/O and management
void read_variable(integer **int_loc, int *size, int *capacity, const char *name, int scope) {
    int value;
    printf("Enter value for %s: ", name);
    scanf("%d", &value);
    add_variable(int_loc, size, capacity, name, value, scope);
}

void print_variable(integer *int_loc, int size, const char *name) {
    integer *var = get_variable(int_loc, size, name);
    if (var) {
        printf("%s = %d\n", var->name, var->value);
    } else {
        printf("Variable %s not found.\n", name);
    }
}

void update_variable(integer *int_loc, int size, const char *name, int new_value) {
    integer *var = get_variable(int_loc, size, name);
    if (var) {
        var->value = new_value;
        printf("%s updated to %d\n", name, new_value);
    } else {
        printf("Variable %s not found.\n", name);
    }
}

void delete_variable(integer *int_loc, int *size, const char *name) {
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

void free_scope_variables(integer *int_loc, int *size, int scope) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if (int_loc[i].scope != scope) {
            int_loc[new_size++] = int_loc[i];
        }
    }
    *size = new_size;
    printf("Variables with scope %d removed.\n", scope);
}

void display_variables(integer *int_loc, int size) {
    if (size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", int_loc[i].name, int_loc[i].value, int_loc[i].scope);
    }
}

void free_all(integer **int_loc, int *capacity, int *size) {
    free(*int_loc);
    *int_loc = NULL;
    *capacity = 0;
    *size = 0;
    printf("All memory freed.\n");
}

// Main to test
int main() {
    integer *int_loc = NULL;
    int capacity = 0, size = 0;

    init_integer_array(&int_loc, &capacity, &size);

    add_variable(&int_loc, &size, &capacity, "a", 5, 1);
    add_variable(&int_loc, &size, &capacity, "b", 10, 1);
    display_variables(int_loc, size);

    printf("\nReading a new variable:\n");
    read_variable(&int_loc, &size, &capacity, "c", 2);

    update_variable(int_loc, size, "a", 15);
    print_variable(int_loc, size, "a");

    printf("\nDeleting variable 'b'\n");
    delete_variable(int_loc, &size, "b");
    display_variables(int_loc, size);

    printf("\nMath test on 'a' and 'c':\n");
    integer *a = get_variable(int_loc, size, "a");
    integer *c = get_variable(int_loc, size, "c");
    if (a && c) {
        printf("Sum = %d\n", add(a->value, c->value));
        printf("Product = %d\n", multiply(a->value, c->value));
        printf("Power = %d\n", power(a->value, 2));
        printf("GCD = %d\n", gcd(a->value, c->value));
    }

    printf("\nFreeing scope 1 variables:\n");
    free_scope_variables(int_loc, &size, 1);
    display_variables(int_loc, size);

    printf("\nFreeing all memory.\n");
    free_all(&int_loc, &capacity, &size);

    return 0;
}
