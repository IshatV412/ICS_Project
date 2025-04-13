#ifndef INT_LIST_H
#define INT_LIST_H

#define MAX_LENGTH 50

// Structure to represent a dynamic list
typedef struct {
    char name[MAX_LENGTH]; // Name of the list
    char dtype;            // Data type (for future use)
    int size;              // Size of the list
    int *ptr;              // Pointer to dynamically allocated array
} List;

// Initialization
List* init(int arr_size);
int* initialize(int *ptr, int arr_size, int val);
int* clone(int *ptr, int arr_size);

// Insert / Delete
void insert(List *lst, int index, int val);
void element_delete(List *lst, int index);

// Search
int getfirst(int *ptr, int arr_size, int val);
int getlast(int *ptr, int arr_size, int val);

// Sort
void bubbleSort(int *ptr, int size);
void mergeSort(int *arr, int left, int right);
void merge(int *arr, int left, int mid, int right);

// Stats
int sum(int *ptr, int size);
int min(int *ptr, int size);
int max(int *ptr, int size);
float average(int *ptr, int size);

// Utilities
void removeDuplicates(List *lst);
void display(int *ptr, int size);

#endif // INT_LIST_H
