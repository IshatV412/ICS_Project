#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_NAME_LENGTH 50

//structure for each node of linked list
struct node {
    int value;
    struct node* ptr_next;
};

//struct for linked list 
typedef struct {
    char name[50];
    int length;
    int scope;
    struct node* head_ptr; //pointer to the head node
    struct node* tail_ptr; //pointer to the tail node
} linked_list;

// Vector operations
void initialise_ll_storage(linked_list** ll_storage,int* ll_capacity, int* ll_size);
void increase_ll_capacity(linked_list** ll_storage, int* ll_capacity);
void initialise_and_add_list(linked_list** ll_storage, int* ll_size, int* ll_capacity, char* name, int length, int scope);

// List operations
void insert_element(linked_list* list, int position, int value);
void modify_value(linked_list* list, int position, int value);
int read_node(linked_list* list, int position);
void search_element(linked_list* list, int value);
int get_First(linked_list* list, int value);

// Deletion and cleanup
void delete_node(linked_list* list, int position);
void delete_list(linked_list* list,linked_list** ll_storage,int* ll_size);
void empty_list(linked_list* list);

// Sorting and display
void sort_list(linked_list* list);
void print_values(linked_list* list);
void print_list(linked_list* list);
linked_list* get_linked_list(linked_list_vector* vector,char* name);


// Test function
void test_operations();

#endif // LINKED_LIST_H
