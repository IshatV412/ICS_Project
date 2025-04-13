#ifndef INT_LIST_H
#define INT_LIST_H

#define MAX_LIST_NAME 50
typedef struct {
    char name[50];
    int *value;
    int size;
    int capacity;
    int scope;
} intlist;



// Initialize storage
void init_intlist_storage();

// Resize storage
void increase_intlist_capacity();

// Add a new list
void add_intlist_variable(const char *name, int size, int init_val, int scope);
// Retrieve pointer by name and highest available scope
intlist* get_intlist_variable(const char *name, int current_scope);

// Update value at index
void update_intlist_element_ptr(intlist *lst, int index, int value);

// Delete a variable
void delete_intlist_variable_ptr(intlist *lst);

// Display all variables
void display_intlist_variables();

// Free all variables of a scope
void free_intlist_variables_by_scope(int scope);

// Free all memory
void free_all_intlist_memory();

//Utility Functions

void intlist_insert(intlist *lst, int index, int val);

void intlist_delete(intlist *lst, int index);

void intlist_remove_duplicates(intlist *lst) ;

// Simple math/analytics
int intlist_sum(int *arr, int size) ;

int intlist_min(int *arr, int size);

int intlist_max(int *arr, int size);

float intlist_average(int *arr, int size);

int intlist_getfirst(int *arr, int size, int val);

int intlist_getlast(int *arr, int size, int val);

void intlist_bubbleSort(int *arr, int size);

void intlist_merge(int *arr, int left, int mid, int right);

void intlist_mergeSort(int *arr, int left, int right);

#endif // INT_LIST_H
