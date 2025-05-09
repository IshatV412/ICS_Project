#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_dictionary.h"

int dict_capacity = 1; // Initial storage capacity
int dict_size = 0; // Number of currently stored dictionaries
dictionary_C_C **dict_storage = NULL; // Pointer to dynamically allocated array

void initialise_dict_storage() {
    dict_capacity = 1;
    dict_size = 0;
    dict_storage = (dictionary_C_C*)malloc((dict_capacity) * sizeof(dictionary_C_C));
    if (*dict_storage == NULL) {
        exit(1);
    }
}

void increase_dict_capacity() {
    dict_capacity *= 2;
    dictionary_C_C* temp = realloc(*dict_storage,(dict_capacity) * sizeof(dictionary_C_C));
    if (temp == NULL) {
        exit(1);
    }
    *dict_storage = temp;
}
dictionary_C_C* get_dict( char* name, int scope) {
    if (dict_size == NULL || name == NULL) {
        printf("Invalid storage or name.\n");
        return NULL;
    }
    dictionary_C_C* latest = NULL;

    for (int i = 0; i < dict_size; i++) {
        if ((strcmp(dict_storage[i]->name, name) == 0) && dict_storage[i]->scope <= scope ) {
            if (latest == NULL || dict_storage[i]->scope > latest->scope) {
                latest = dict_storage[i];
            }
        }
    }
    if (latest == NULL) {
        printf("Linked list with name \"%s\" not found.\n", name);
    }
    return latest;
}

void increase_len(dictionary_C_C *dict, int len){
    node_C_C *node = dict->start; //putting node at start
    for(int i=0; i<len-1; i++){
        if(node->next == NULL){ //seeing if it is NULL
            node_C_C *new_node = (node_C_C*)malloc(sizeof(node_C_C)); //if yes, allocate some memory
            node->next = new_node; //update the next of current node
            node->next->key = NULL; //update the new node values
            node->next->value = NULL;
            node->next->next = NULL;
            dict->len++; //inc len
        }
        node = node->next; //just go to the next node
    }
}

dictionary_C_C* create_dictionary_C_C(int len, char name[50], int scope){
    if (dict_size == dict_capacity) {
        increase_dict_capacity(dict_storage,dict_capacity);
    }
    dictionary_C_C* dict = (dictionary_C_C*)malloc(sizeof(dictionary_C_C));
    strcpy(dict->name, name); //apparently you need to use strcpy...
    dict->start = (node_C_C*)malloc(sizeof(node_C_C)); //initialising the first node
    dict->len = 1;
    dict->start->key = NULL;
    dict->start->value = NULL;
    dict->start->next = NULL;
    increase_len(dict, len); //increasing the size if needed
    return dict; //returning the address of dict
}

void insert_C_C(dictionary_C_C *dict, char *key, char *value){
    node_C_C *node = dict->start;
    while(node != NULL && node->key != NULL){ //either there is an empty node, or all nodes are full
        if(node != NULL){
            if(node->key != NULL){
                if(strcmp(node->key,key)==0){
                    free(node->value);
                    node->value = strdup(value);
                    return;
                }
            }
        }
        node = node->next; //keep on traversing
    }
    if(node == NULL){ //if all nodes are full
        increase_len(dict,(dict->len) + 1); //increase the length
        node = dict->start; //then basically traverse to the last node
        while(node != NULL && node->key != NULL){
            node = node->next;
        }
    }
    node->key = strdup(key);
    node->value = strdup(value);
}

char* getvalue_C_C(dictionary_C_C *dict, char *key){
    node_C_C *node = dict->start;
    while(node != NULL){ //traverse the list
        if(node->key != NULL && strcmp(node->key, key) == 0){ //if the key is found
            return node->value; //return the value
        }
        node = node->next; //else go to the next node
    }
    return NULL; //if key is not found
}

char* getkey_C_C(dictionary_C_C *dict, char *key){
    node_C_C *node = dict->start;
    while(node != NULL){ //traverse the list
        if(node->key != NULL && strcmp(node->key, key) == 0){ //if the key is found
            return node->key; //return the value
        }
        node = node->next; //else go to the next node
    }
    return NULL; //if key is not found
}

void free_dict_C_C(dictionary_C_C *dict){
    node_C_C *n1 = dict->start;
    node_C_C *n2 = n1->next;
    while(n1 != NULL){ //traverse the list
        free(n1);
        n1 = n2;
        if(n1 != NULL){
            n2 = n1->next;
        }
    }
    // free(dict->start);
    free(dict);
}

void printing_C_C(dictionary_C_C *dict){
    printf("\n");
    printf("Name : %s\nLength : %d\n",dict->name,dict->len);
    node_C_C *node = dict->start;
    while(node != NULL){
        printf("Key : %s\nValue : %s\n",node->key,node->value);
        node = node->next;
    }
    printf("\n\n");
}

int delete_C_C(dictionary_C_C *dict, char *key) {
    node_C_C *node = dict->start;
    while (node != NULL) {
        if(strcmp(node->key,key)==0) {
            node->key = NULL;
            node->value = NULL;
            return 1; //returns 1 if successfull
        }
        node = node->next;
    }
    return 0; //else returns 0
}

void free_dict_storage(int scope) {
    for (int i = 0; i < dict_size; i++) {
        if(scope <= dict_storage[i]->scope) { //if the scope is same, free the dictionary
            free_dict_C_C(dict_storage[i]);
            dict_storage[i] = NULL;
            dict_size--;
        }
    }
}
// Function to free all memory allocated for dictionaries


void test_dict_C_C(){ //a test to see if it works
    dictionary_C_C* dict_array = NULL;
    int dict_capacity, dict_size;

    // Initialize dictionary array
    initialise_dict_storage(&dict_array, &dict_capacity, &dict_size);
    dictionary_C_C *dict;
    dict = create_dictionary_C_C(1,"dict1", 1); //create a dictionary
    printing_C_C(dict);
    char *key = "key1", *value = "value1";
    insert_C_C(dict,key,value);
    printing_C_C(dict);
    char *key2 = "key2", *value2 = "value2";
    char *value3 = "Value3";
    insert_C_C(dict,key,value3);
    insert_C_C(dict,key2,value2);
    printing_C_C(dict);
    delete_C_C(dict,key);
    printing_C_C(dict);
    free_dict_C_C(dict);
    printf("All done");
}
