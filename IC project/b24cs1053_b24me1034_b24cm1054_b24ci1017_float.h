#ifndef B24CS1053_B24ME1034_B24CM1054_B24CI1017_FLOAT_H
#define B24CS1053_B24ME1034_B24CM1054_B24CI1017_FLOAT_H
#define MAX_NAME_LEN 50

// Structure definition for decimal type
typedef struct {
    char name[MAX_NAME_LEN];
    float value;
    int scope;
} decimal;

void init_float_storage();
void increase_float_capacity();
void add_float_variable(char *name, float value, int scope);
decimal* get_float_variable(char* name, int scope);
void update_float_variable_ptr(decimal *var, float new_value);
void print_float_variable_ptr(decimal *var);
void delete_float_variable_ptr(decimal *var);
void display_variables();
void free_variables(int scope);
void free_all_memory();

float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);
float power(float a, float b);
float absolute(float a);

int equals(float a, float b);
int not_equals(float a, float b);
int greater_than(float a, float b);
int less_than(float a, float b);
int greater_equals(float a, float b);
int less_equals(float a, float b);
void test_float();

#endif // FLOAT_H
