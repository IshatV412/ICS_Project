#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int LL_capacity;
int LL_size;
linked_list** LL_Loc;

void initialise_ll_storage() {
    LL_capacity = 1;
    LL_size = 0;
    LL_Loc = (linked_list**)malloc(LL_capacity * sizeof(linked_list*));
    if (LL_Loc == NULL) {
        exit(1);
    }
}

void increase_ll_capacity() {
    LL_capacity *= 2;
    linked_list** temp = realloc(LL_Loc, LL_capacity * sizeof(linked_list*));
    if (temp == NULL) {
        exit(1);
    }
    LL_Loc = temp;
}

linked_list* create_list(char* name, int length, int scope) {
    if (LL_size == LL_capacity) {
        increase_ll_capacity();
    }

    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    if (list == NULL) {
        printf("Memory Allocation Failed for linked list.\n");
        return NULL;
    }

    strncpy(list->name, name, sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    list->scope = scope;
    list->length = 0;
    list->head_ptr = NULL;
    list->tail_ptr = NULL;

    for (int i = 0; i < length; i++) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node == NULL) {
            printf("Memory Allocation Failed for node.\n");
            return NULL;
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

    LL_Loc[LL_size++] = list;
    return list;
}

linked_list* get_list_by_name_scope(char* name, int scope) {
    linked_list* latest = NULL;
    for (int i = 0; i < LL_size; i++) {
        if (strcmp(LL_Loc[i]->name, name) == 0 && LL_Loc[i]->scope <= scope) {
            if (latest == NULL || LL_Loc[i]->scope > latest->scope) {
                latest = LL_Loc[i];
            }
        }
    }
    if (latest == NULL) {
        printf("Linked list with name \"%s\" not found.\n", name);
    }
    return latest;
}

void delete_list(linked_list* list) {
    if (list == NULL) return;

    struct node* temp = list->head_ptr;
    while (temp != NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }

    for (int i = 0; i < LL_size; i++) {
        if (LL_Loc[i] == list) {
            for (int j = i; j < LL_size - 1; j++) {
                LL_Loc[j] = LL_Loc[j + 1];
            }
            LL_size--;
            break;
        }
    }
    free(list);
}
void insert_element(linked_list* list, int index, int value) {
    if (list == NULL || index < 0 || index > list->length) {
        printf("Invalid list or index for insertion.\n");
        return;
    }

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = value;
    new_node->ptr_next = NULL;

    if (index == 0) {
        new_node->ptr_next = list->head_ptr;
        list->head_ptr = new_node;
        if (list->length == 0) list->tail_ptr = new_node;
    } else {
        struct node* temp = list->head_ptr;
        for (int i = 0; i < index - 1; i++) temp = temp->ptr_next;
        new_node->ptr_next = temp->ptr_next;
        temp->ptr_next = new_node;
        if (new_node->ptr_next == NULL) list->tail_ptr = new_node;
    }
    list->length++;
}
void modify_value(linked_list* list, int index, int value) {
    if (list == NULL || index < 0 || index >= list->length) {
        printf("Invalid index for modification.\n");
        return;
    }
    struct node* temp = list->head_ptr;
    for (int i = 0; i < index; i++) temp = temp->ptr_next;
    temp->value = value;
}
int read_node(linked_list* list, int index) {
    if (list == NULL || index < 0 || index >= list->length) {
        printf("Invalid index for reading.\n");
        return -1;
    }
    struct node* temp = list->head_ptr;
    for (int i = 0; i < index; i++) temp = temp->ptr_next;
    return temp->value;
}
void search_element(linked_list* list, int value) {
    if (list == NULL) return;

    struct node* temp = list->head_ptr;
    int index = 0, found = 0;

    while (temp != NULL) {
        if (temp->value == value) {
            printf("Value %d found at index %d\n", value, index);
            found = 1;
        }
        temp = temp->ptr_next;
        index++;
    }

    if (!found) {
        printf("Value %d not found in the list.\n", value);
    }
}
int get_First(linked_list* list, int value) {
    if (list == NULL) return -1;

    struct node* temp = list->head_ptr;
    int index = 0;

    while (temp != NULL) {
        if (temp->value == value) return index;
        temp = temp->ptr_next;
        index++;
    }
    return -1;
}
void delete_node(linked_list* list, int index) {
    if (list == NULL || index < 0 || index >= list->length) {
        printf("Invalid index for deletion.\n");
        return;
    }

    struct node* to_delete;
    if (index == 0) {
        to_delete = list->head_ptr;
        list->head_ptr = to_delete->ptr_next;
        if (list->length == 1) list->tail_ptr = NULL;
    } else {
        struct node* temp = list->head_ptr;
        for (int i = 0; i < index - 1; i++) temp = temp->ptr_next;
        to_delete = temp->ptr_next;
        temp->ptr_next = to_delete->ptr_next;
        if (temp->ptr_next == NULL) list->tail_ptr = temp;
    }
    free(to_delete);
    list->length--;
}
void empty_list(linked_list* list) {
    if (list == NULL) return;

    struct node* temp = list->head_ptr;
    while (temp != NULL) {
        struct node* next = temp->ptr_next;
        free(temp);
        temp = next;
    }
    list->head_ptr = NULL;
    list->tail_ptr = NULL;
    list->length = 0;
}
void sort_list(linked_list* list) {
    if (list == NULL || list->length < 2) return;

    for (struct node* i = list->head_ptr; i != NULL; i = i->ptr_next) {
        for (struct node* j = i->ptr_next; j != NULL; j = j->ptr_next) {
            if (i->value > j->value) {
                int temp = i->value;
                i->value = j->value;
                j->value = temp;
            }
        }
    }
}
void print_values(linked_list* list) {
    if (list == NULL) return;

    struct node* temp = list->head_ptr;
    printf("[ ");
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->ptr_next;
    }
    printf("]");
}
void print_list(linked_list* list) {
    if (list == NULL) {
        printf("NULL list.\n");
        return;
    }

    printf("List \"%s\" (Scope: %d, Length: %d): ", list->name, list->scope, list->length);
    print_values(list);
    printf("\n");
}

void cleanup_all_lists() {
    for (int i = 0; i < LL_size; i++) {
        delete_list(LL_Loc[i]);
    }
    free(LL_Loc);
    LL_Loc = NULL;
    LL_capacity = 0;
    LL_size = 0;
}
void test() {
    // Step 1: Initialize the LL_Loc system
    initialise_ll_storage();

    // Step 2: Create two lists with different scopes
    linked_list* list1 = create_list("MyList", 4, 0);
    linked_list* list2 = create_list("MyList", 3, 2); // Same name, different scope

    // Step 3: Print their initial contents
    printf("Initial Lists:\n");
    print_list(list1);
    print_list(list2);

    // Step 4: Insert new elements into both lists
    insert_element(list1, 2, 42);
    insert_element(list2, 1, 77);

    // Step 5: Modify existing values
    modify_value(list1, 0, 11);
    modify_value(list2, 2, 88);

    // Step 6: Sort lists
    sort_list(list1);
    sort_list(list2);

    // Step 7: Print modified lists
    printf("\nAfter Insertions, Modifications & Sorting:\n");
    print_list(list1);
    print_list(list2);

    // Step 8: Search and get first occurrence
    printf("\nSearching 42 in list1:\n");
    search_element(list1, 42);
    printf("Index of 42: %d\n", get_First(list1, 42));

    // Step 9: Retrieve list by name & scope
    linked_list* latest_list = get_list_by_name_scope("MyList", 1); // Should return list1
    if (latest_list != NULL) {
        printf("\nList retrieved by name & scope:\n");
        print_list(latest_list);
    }

    // Step 10: Delete one list
    printf("\nDeleting list2...\n");
    delete_list(list2);

    // Step 11: Cleanup all lists
    cleanup_all_lists();
    printf("\nAll memory freed. Program ended successfully.\n");

    return;
}
