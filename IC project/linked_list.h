#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_NAME_LENGTH 50

// Node structure
struct node {
    int value;
    struct node* ptr_next;
};

// Linked list structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int length;
    struct node* head_ptr;
    struct node* tail_ptr;
} linked_list;

// Vector to store multiple linked lists
typedef struct {
    linked_list** lists;
    int size;
    int capacity;
} linked_list_vector;

// Vector operations
void initialise_vector(linked_list_vector** storage);
void initialise_and_add_list(linked_list_vector* vector, char* name, int length);

// List operations
void insert_element(linked_list* list, int position, int value);
void modify_value(linked_list* list, int position, int value);
int read_node(linked_list* list, int position);
void search_element(linked_list* list, int value);
int get_First(linked_list* list, int value);

// Deletion and cleanup
void delete_node(linked_list* list, int position);
void delete_list(linked_list* list, linked_list_vector* storage);
void empty_list(linked_list* list);

// Sorting and display
void sort_list(linked_list* list);
void print_values(linked_list* list);
void print_list(linked_list* list);
linked_list* get_linked_list(linked_list_vector* vector,char* name);


// Test function
void test_operations();

#endif // LINKED_LIST_H
