#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


void initialise_ll_storage(linked_list** ll_storage,int* ll_capacity, int* ll_size) {
    *ll_capacity = 1;
    *ll_size = 0;
    *ll_storage = (linked_list*)malloc((*ll_capacity) * sizeof(linked_list));
    if (*ll_storage == NULL) {
        exit(1);
    }
}

void increase_ll_capacity(linked_list** ll_storage, int* ll_capacity) {
    *ll_capacity *= 2;
    linked_list* temp = realloc(*ll_storage,(*ll_capacity) * sizeof(linked_list));
    if (temp == NULL) {
        exit(1);
    }
    *ll_storage = temp;
}




void initialise_and_add_list(linked_list** ll_storage, int* ll_size, int* ll_capacity, char* name, int length, int scope) {
    if (*ll_size == *ll_capacity) {
        increase_ll_capacity(ll_storage, ll_capacity);
    }

    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    if (list == NULL) {
        printf("Memory Allocation Failed for linked list.\n");
        return;
    }

    strncpy(list->name, name, sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    list->length = 0;
    list->head_ptr = NULL;
    list->tail_ptr = NULL;

    for (int i = 0; i < length; i++) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node == NULL) {
            printf("Memory Allocation Failed for node.\n");
            return;
        }
        new_node->value = 0;
        new_node->ptr_next = NULL;

        if (list->head_ptr == NULL) {
            list->head_ptr = new_node;
            list->tail_ptr = new_node;
        } else {
            list->tail_ptr->ptr_next = new_node;
            list->tail_ptr = new_node;
        }
        list->length++;
    }

    (ll_storage)[*ll_size] = list;
    (*ll_size)++;
}

//function to insert element at a given position
void insert_element(linked_list* list, int position, int value) {
    if (position < 0 || position > list->length) { //validating position
        printf("Invalid Position");
        return;
    }
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); //creating the new node
    if (new_node == NULL) {
        printf("Memory Allocation Failed");
        return;
    }

    new_node->value = value;
    new_node->ptr_next = NULL;
    if (position == 0) { //if to be added at the beginning change the head pointer as well
        new_node->ptr_next = list->head_ptr;
        list->head_ptr = new_node;
        list->length = list->length + 1;
        return;
    }
    else if (position == list->length) { //if to be added at the end change the tail pointer
        list->tail_ptr->ptr_next = new_node;
        list->tail_ptr = new_node;
        list->length = list->length + 1;
        return;
    }
    else {
        struct node* temp = list->head_ptr; //temp struct to traverse through the list to get to the position needed
        for (int i = 0; i < position - 1 && temp!=NULL; i++) {
            temp = temp->ptr_next;
        }
        new_node->ptr_next = temp->ptr_next;
        temp->ptr_next = new_node;
        list->length = list->length + 1;
        return;
    }
}
//function to modify the value at a given position
void modify_value(linked_list* list, int position, int value) {
    
    if (position < 0 || position >= list->length) { //validating position
        printf("Invalid Position");
        return;
    }
    
    struct node* temp = list->head_ptr; //temp struct to traverse through the linked list
    for (int i = 0; i < position; i++) {
        temp = temp->ptr_next;
    }
    temp->value = value;
    return;
}
//function to get the value at a given position
int read_node(linked_list* list, int position) {
    if (position<0 || position >= list->length) {
        printf("Invalid Position");
        return -1;
    }

    struct node* temp = list->head_ptr;
    for (int i = 0; i < position; i++) {
        temp = temp->ptr_next;
    }
    return temp->value;
}

void search_element(linked_list* list, int value) {
    struct node* temp = list->head_ptr;
    while(temp!=NULL) {
        if (value == temp->value) {
            printf("Element Found.\n");
            return;
        }
        temp = temp->ptr_next;
    }
    printf("Element not found.\n");
    return;
}

int get_First(linked_list* list, int value) {
    struct node* temp = list->head_ptr;
    int index = 0;
    while(temp!=NULL) {
        if (value == temp->value) {
            return index;
        }
        temp = temp->ptr_next;
        index++;
    }
    printf("Element not in list.\n");
    return -1;
}

//function to print the entire linked list
void print_values(linked_list* list) {
    struct node* temp = list->head_ptr;
    for (int i = 0; i < list->length; i++) {
        printf("%d -> ",temp->value);
        temp = temp->ptr_next;
    }
    printf("\n\n");
    return;
}

//function to print all the details of the list
void print_list(linked_list* list) {
    printf ("%s %d\n",list->name,list->length);
    print_values(list);
}

void sort_list(linked_list* list) {
    struct node* current = list->head_ptr;
    struct node* index = NULL;
    while (current != NULL) { //tried bubble sort kinda thing, it is not bubble sort but it works lol its some random sort method
        index = current->ptr_next;
        while (index != NULL) {
            if (current->value > index->value) {
                int temp = current->value;
                current->value = index->value;
                index->value = temp;
            }
            index = index->ptr_next;
        }
        current = current->ptr_next;
    }
}

//function to delete a specific node
void delete_node(linked_list* list,int position) {
    if (position < 0 || position >= list->length) {
        printf("Invalid position");
        return;
    }
    struct node* temp = list->head_ptr;

    if (position == 0) {
        list->head_ptr = temp->ptr_next;
        list->length = list->length - 1;
        if (list->length == 0) {
            list->tail_ptr = NULL;
        }
        free(temp);
        return;
    }
    for (int i = 0; i < position - 1; i++) {
        temp = temp->ptr_next;
    }
    struct node* delete_node = temp->ptr_next;
    temp->ptr_next = delete_node->ptr_next;

    if (delete_node->ptr_next == list->tail_ptr) {
        list->tail_ptr = temp;
    }
    list->length = list->length - 1;
    free(delete_node);
}
//function to delete the list itself
void delete_list(linked_list* list,linked_list** ll_storage,int* ll_size) {
    if (list == NULL) {
        return;
    }
    struct node* temp = list->head_ptr;
    //freeing all the nodes of the list
    while(temp!=NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }
    for (int i = 0; i < *ll_size; i++) {
        if (ll_storage[i] == list) {
            for (int j = i; j < *ll_size - 1; j++) {
                ll_storage[j] = ll_storage[j + 1];
            }
            (*ll_size)--;
            break;
        }
    }
    free(list);
}

void empty_list(linked_list* list) {
    if (list == NULL) {
        return;
    }
    struct node* temp = list->head_ptr;
    //freeing all the nodes of the list
    while(temp!=NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }
    list->head_ptr = NULL;
    list->tail_ptr = NULL;
    list->length = 0;
}
linked_list* get_linked_list(linked_list** ll_storage, int* ll_size, char* name, int scope) {
    if (ll_size == NULL || name == NULL) {
        printf("Invalid storage or name.\n");
        return NULL;
    }
    linked_list* latest = NULL;

    for (int i = 0; i < *ll_size; i++) {
        if ((strcmp(ll_storage[i]->name, name) == 0) && ll_storage[i]->scope <= scope ) {
            if (latest == NULL || ll_storage[i]->scope > latest->scope) {
                latest = ll_storage[i];
            }
        }
    }
    if (latest == NULL) {
        printf("Linked list with name \"%s\" not found.\n", name);
    }
    return latest;
}


void test_operations() {
    linked_list** ll_storage;
    int capacity, size;
    initialise_ll_storage(ll_storage, &capacity, &size);

    initialise_and_add_list(ll_storage, &size, &capacity, "List1", 5,0);
    initialise_and_add_list(ll_storage, &size, &capacity, "List2", 3,1);

    for (int i = 0; i < size; i++) {
        print_list(ll_storage[i]);
    }

    insert_element(ll_storage[0], 2, 99);
    insert_element(ll_storage[1], 1, 42);
    modify_value(ll_storage[0], 3, 88);
    modify_value(ll_storage[1], 0, 77);

    for (int i = 0; i < size; i++) {
        print_list(ll_storage[i]);
    }

    sort_list(ll_storage[0]);
    sort_list(ll_storage[1]);
    for (int i = 0; i < size; i++) {
        print_list(ll_storage[i]);
    }

    delete_node(ll_storage[0], 2);
    print_list(ll_storage[0]);

    delete_list(ll_storage, &size, ll_storage[1]);
    printf("List2 deleted.\n");

    delete_list(ll_storage, &size, ll_storage[0]);
    free(ll_storage);
    printf("Memory freed and program terminated.\n");
}


//Coded by Parrva Chirag Shah (B24CS1053)

