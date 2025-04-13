#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intlist.h"
#define MAX_LIST_NAME 50
typedef struct {
    char name[50];
    int *value;
    int size;
    int capacity;
    int scope;
} intlist;

int intlist_capacity = 1;
int intlist_size = 0;
intlist *intlist_loc = NULL;

// Initialize storage
void init_intlist_storage() {
    intlist_loc = (intlist*) malloc(intlist_capacity * sizeof(intlist));
    if (!intlist_loc) exit(1);
}

// Resize storage
void increase_intlist_capacity() {
    intlist_capacity *= 2;
    intlist *temp = (intlist*) realloc(intlist_loc, intlist_capacity * sizeof(intlist));
    if (!temp) exit(1);
    intlist_loc = temp;
}

// Add a new list
void add_intlist_variable(const char *name, int size, int init_val, int scope) {
    for (int i = 0; i < intlist_size; i++) {
        if (strcmp(intlist_loc[i].name, name) == 0 && intlist_loc[i].scope == scope) {
            exit(1);
        }
    }

    if (intlist_size == intlist_capacity) {
        increase_intlist_capacity();
    }

    strncpy(intlist_loc[intlist_size].name, name, MAX_LIST_NAME - 1);
    intlist_loc[intlist_size].name[MAX_LIST_NAME - 1] = '\0';

    intlist_loc[intlist_size].value = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        intlist_loc[intlist_size].value[i] = init_val;
    }

    intlist_loc[intlist_size].size = size;
    intlist_loc[intlist_size].capacity = size;
    intlist_loc[intlist_size].scope = scope;
    intlist_size++;
}

// Retrieve pointer by name and highest available scope
intlist* get_intlist_variable(const char *name, int current_scope) {
    intlist *result = NULL;
    int highest_scope = -1;

    for (int i = 0; i < intlist_size; i++) {
        if (strcmp(intlist_loc[i].name, name) == 0 && intlist_loc[i].scope <= current_scope) {
            if (intlist_loc[i].scope > highest_scope) {
                highest_scope = intlist_loc[i].scope;
                result = &intlist_loc[i];
            }
        }
    }
    return result;
}

// Update value at index
void update_intlist_element_ptr(intlist *lst, int index, int value) {
    if (lst && index >= 0 && index < lst->size) {
        lst->value[index] = value;
    } else {
        exit(1);
    }
}

// Delete a variable
void delete_intlist_variable_ptr(intlist *lst) {
    if (!lst) exit(1);
    int found = 0;

    for (int i = 0; i < intlist_size; i++) {
        if (&intlist_loc[i] == lst) found = 1;
        if (found && i < intlist_size - 1) {
            intlist_loc[i] = intlist_loc[i + 1];
        }
    }

    if (found) intlist_size--;
    else exit(1);
}

// Display all variables
void display_intlist_variables() {
    if (intlist_size == 0) {
        printf("No int lists found.\n");
        return;
    }

    for (int i = 0; i < intlist_size; i++) {
        printf("Name: %s, Scope: %d, Values: ", intlist_loc[i].name, intlist_loc[i].scope);
        for (int j = 0; j < intlist_loc[i].size; j++) {
            printf("%d ", intlist_loc[i].value[j]);
        }
        printf("\n");
    }
}

// Free all variables of a scope
void free_intlist_variables_by_scope(int scope) {
    int new_size = 0;
    for (int i = 0; i < intlist_size; i++) {
        if (intlist_loc[i].scope != scope) {
            intlist_loc[new_size++] = intlist_loc[i];
        } else {
            free(intlist_loc[i].value);
        }
    }
    intlist_size = new_size;
}

// Free all memory
void free_all_intlist_memory() {
    for (int i = 0; i < intlist_size; i++) {
        free(intlist_loc[i].value);
    }
    free(intlist_loc);
    intlist_loc = NULL;
    intlist_capacity = 1;
    intlist_size = 0;
}

//Utility Functions

void intlist_insert(intlist *lst, int index, int val) {
    if (!lst || index < 0 || index > lst->size) return;
    lst->value = (int*) realloc(lst->value, (lst->size + 1) * sizeof(int));
    for (int i = lst->size; i > index; i--) {
        lst->value[i] = lst->value[i - 1];
    }
    lst->value[index] = val;
    lst->size++;
}

void intlist_delete(intlist *lst, int index) {
    if (!lst || index < 0 || index >= lst->size) return;
    for (int i = index; i < lst->size - 1; i++) {
        lst->value[i] = lst->value[i + 1];
    }
    lst->size--;
    lst->value = (int*) realloc(lst->value, lst->size * sizeof(int));
}

void intlist_remove_duplicates(intlist *lst) {
    for (int i = 0; i < lst->size; i++) {
        for (int j = i + 1; j < lst->size; j++) {
            if (lst->value[i] == lst->value[j]) {
                intlist_delete(lst, j);
                j--;
            }
        }
    }
}

// Simple math/analytics
int intlist_sum(int *arr, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) total += arr[i];
    return total;
}

int intlist_min(int *arr, int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] < min) min = arr[i];
    return min;
}

int intlist_max(int *arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] > max) max = arr[i];
    return max;
}

float intlist_average(int *arr, int size) {
    return (float)intlist_sum(arr, size) / size;
}

int intlist_getfirst(int *arr, int size, int val) {
    for (int i = 0; i < size; i++) if (arr[i] == val) return i;
    return -1;
}

int intlist_getlast(int *arr, int size, int val) {
    for (int i = size - 1; i >= 0; i--) if (arr[i] == val) return i;
    return -1;
}

void intlist_bubbleSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
}

void intlist_merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void intlist_mergeSort(int *arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        intlist_mergeSort(arr, left, mid);
        intlist_mergeSort(arr, mid + 1, right);
        intlist_merge(arr, left, mid, right);
    }
}
