#ifndef B24CS1053_B24ME1034_B24CM1054_B24CI1017_INT_LIST_H
#define B24CS1053_B24ME1034_B24CM1054_B24CI1017_INT_LIST_H

#define MAX_LIST_NAME 50
typedef struct {
    char name[50];
    int *value;
    int size;
    int capacity;
    int scope;
} intlist;

void init_intlist_storage();
void increase_intlist_capacity();
void add_intlist_variable(const char *name, int size, int init_val, int scope);
intlist* get_intlist_variable(const char *name, int current_scope);
void update_intlist_element_ptr(intlist *lst, int index, int value);
void delete_intlist_variable_ptr(intlist *lst);
void display_intlist_variables();
void free_intlist_variables_by_scope(int scope);
void free_all_intlist_memory();

void intlist_insert(intlist *lst, int index, int val);
void intlist_delete(intlist *lst, int index);
void intlist_remove_duplicates(intlist *lst) ;

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
