#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_capacity = 1;
int int_size = 0;
int_var *int_loc = NULL;

void int_init_storage() {
    if (int_loc != NULL) {
        printf("Error: Storage already initialized.\n");
        exit(1);
    }
    int_loc = (int_var*)malloc(int_capacity * sizeof(int_var));
    if (int_loc == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(1);
    }
}

void int_increase_capacity() {
    if (int_loc == NULL) {
        printf("Error: Attempt to resize uninitialized storage.\n");
        exit(1);
    }
    int_capacity *= 2;
    int_var *temp = (int_var*)realloc(int_loc, int_capacity * sizeof(int_var));
    if (temp == NULL) {
        printf("Error : Memory reallocation failed\n");
        exit(1);
    }
    int_loc = temp;
}

// Get variable by name and scope (exact match)
int_var* int_get_var(char *name, int scope) {
    for (int i = 0; i < int_size; i++) {
        if (strcmp(int_loc[i].int_name, name) == 0 && int_loc[i].int_scope == scope) {
            return &int_loc[i];
        }
    }
    return NULL;
}

// Get variable by name only (for testing)
int_var* int_get_var_by_name(char *name) {
    for (int i = 0; i < int_size; i++) {
        if (strcmp(int_loc[i].int_name, name) == 0) {
            return &int_loc[i];
        }
    }
    return NULL;
}

// Add variable with scope check
void int_add_variable(int_var *new_var) {
    if (int_get_var(new_var->int_name, new_var->int_scope)) {
        printf("Error: Variable %s already exists in scope %d!\n", new_var->int_name, new_var->int_scope);
        return;
    }

    if (int_size == int_capacity) {
        int_increase_capacity();
    }

    strcpy(int_loc[int_size].int_name, new_var->int_name);
    int_loc[int_size].int_value = new_var->int_value;
    int_loc[int_size].int_scope = new_var->int_scope;
    int_size++;
}

// Read new variable from user input
void int_read_variable(int_var *var) {
    printf("Enter value for %s: ", var->int_name);
    scanf("%d", &var->int_value);
    int_add_variable(var);
}

// Update variable by memory reference
void int_update_variable(int_var *var, int new_value) {
    if (var) {
        var->int_value = new_value;
        printf("Updated %s to %d\n", var->int_name, new_value);
    } else {
        printf("Variable not found.\n");
    }
}

// Print variable by memory reference
void int_print_variable(int_var *var) {
    if (var) {
        printf("Variable %s = %d\n", var->int_name, var->int_value);
    } else {
        printf("Variable not found.\n");
    }
}

// Delete variable by memory reference
void int_delete_variable(int_var *var) {
    if (!var) return;

    int index = -1;
    for (int i = 0; i < int_size; i++) {
        if (&int_loc[i] == var) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < int_size - 1; i++) {
            int_loc[i] = int_loc[i + 1];
        }
        int_size--;
        printf("Deleted variable.\n");
    }
}

// Free all variables of a specific scope
void int_free_scope(int scope) {
    int new_size = 0;
    for (int i = 0; i < int_size; i++) {
        if (int_loc[i].int_scope != scope) {
            int_loc[new_size++] = int_loc[i];
        }
    }
    int_size = new_size;
    printf("Variables with scope %d have been removed.\n", scope);
}

// Free all memory
void int_free_all() {
    free(int_loc);
    int_loc = NULL;
    int_size = 0;
    int_capacity = 1;
    printf("All memory has been freed.\n");
}

void int_display_variables() {
    if (int_size == 0) {
        printf("No variables stored.\n");
        return;
    }
    for (int i = 0; i < int_size; i++) {
        printf("Name: %s, Value: %d, Scope: %d\n", int_loc[i].int_name, int_loc[i].int_value, int_loc[i].int_scope);
    }
}

// Arithmetic
int int_add(int a, int b) { return a + b; }
int int_subtract(int a, int b) { return a - b; }
int int_multiply(int a, int b) { return a * b; }
int int_divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}
int int_modulus(int a, int b) { return a % b; }
int int_power(int a, int b) {
    int pow = 1;
    for (int i = 1; i <= b; i++) pow *= a;
    return pow;
}
int int_absolute(int a) { return abs(a); }

// Logical
int int_and(int a, int b) { return a && b; }
int int_or(int a, int b) { return a || b; }
int int_not(int a) { return !a; }

// Relational
int int_equals(int a, int b) { return a == b; }
int int_not_equals(int a, int b) { return a != b; }
int int_greater(int a, int b) { return a > b; }
int int_less(int a, int b) { return a < b; }
int int_greater_eq(int a, int b) { return a >= b; }
int int_less_eq(int a, int b) { return a <= b; }

// Extra
int int_factorial(int n) {
    if (n < 0) return -1;
    int f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}
int int_gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int int_lcm(int a, int b) {
    return (a * b) / int_gcd(a, b);
}
int int_is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
int int_is_square(int n) {
    for (int i = 0; i * i <= n; i++) {
        if (i * i == n) return 1;
    }
    return 0;
}
int int_reverse(int n) {
    int rev = 0;
    while (n) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return rev;
}
int int_digit_count(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n) {
        count++;
        n /= 10;
    }
    return count;
}
int int_digit_sum(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
