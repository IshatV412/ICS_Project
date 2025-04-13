#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_NAME_LENGTH 50

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

void initialise_ll_storage();
void increase_ll_capacity();

linked_list* create_list(char* name, int length, int scope);
linked_list* get_list_by_name_scope(char* name, int scope);

void delete_list(linked_list* list);
void insert_element(linked_list* list, int index, int value);
void modify_value(linked_list* list, int index, int value);
int read_node(linked_list* list, int index);
void search_element(linked_list* list, int value);
int get_First(linked_list* list, int value);
void delete_node(linked_list* list, int index);
void empty_list(linked_list* list);
void sort_list(linked_list* list);
void print_values(linked_list* list);
void print_list(linked_list* list);
void cleanup_all_lists();
void test();

#endif // LINKED_LIST_H
