#ifndef FLOAT_H
#define FLOAT_H
#define MAX_NAME_LEN 50

// Structure definition for decimal type
typedef struct {
    char name[MAX_NAME_LEN];
    float value;
    int scope;
} decimal;

// Initialize float storage
void init_float_storage();
// Increase capacity when needed
void increase_float_capacity();
// Add a new float variable
void add_float_variable(char *name, float value, int scope);
// Get variable by name and highest available scope
decimal* get_float_variable(char* name, int scope);
// Update using pointer
void update_float_variable_ptr(decimal *var, float new_value);
// Print using pointer
void print_float_variable_ptr(decimal *var);
// Delete using pointer
void delete_float_variable_ptr(decimal *var);
// Display all variables
void display_variables();
// Free variables by scope
void free_variables(int scope);
// Free all memory
void free_all_memory();
// Arithmetic Operations
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);
float power(float a, float b);
float absolute(float a);

// Relational Operations
int equals(float a, float b);
int not_equals(float a, float b);
int greater_than(float a, float b);
int less_than(float a, float b);
int greater_equals(float a, float b);
int less_equals(float a, float b);
void test_float();
#endif // FLOAT_H
