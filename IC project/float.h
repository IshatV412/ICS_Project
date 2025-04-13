#ifndef FLOAT_H
#define FLOAT_H

#define MAX_NAME_LEN 50

// Structure definition for decimal type
typedef struct {
    char name[MAX_NAME_LEN];
    float value;
    int scope;
} decimal;

// Initialization and Memory Management
decimal* init_decimal_storage(int* capacity, int* size);
decimal* increase_capacity(decimal* arr, int* capacity);
void free_all(decimal* arr);
int free_scope(decimal* arr, int size, int scope);

// Add, Get, Update, Delete
decimal* add_decimal_variable(decimal* arr, int* size, int* capacity, const char* name, float value, int scope);
decimal* get_decimal_variable(decimal* arr, int size, const char* name);
void update_decimal_variable(decimal* arr, int size, const char* name, float value);
int delete_decimal_variable(decimal* arr, int size, const char* name);

// I/O and Display
void display(decimal* arr, int size);
decimal* read_decimal_variable(decimal* arr, int* size, int* capacity, const char* name, int scope);
void print_decimal_variable(decimal* arr, int size, const char* name);

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
