#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "boolean.h"
#include "character.h"
#include "dictionary.h"
#include "float.h"
#include "float.h"
#include "int_list.h"
#include "integers.h"
#include "linked_list.h"

#define MAX_VAR_LENGTH 1024
#define MAX_CHAR_VALUE 1024

struct treeNode{
    char type[20]; //stores the node type like assignment,declaration,etc
    char value[50]; //stores the value of the node
    struct treeNode* left; //point to the left branch in the tree
    struct treeNode* right; //point to the right branch in the tree
    struct treeNode* next; //next statement in the sequence
};
//function to create a node for the tree
struct treeNode* createNode(char type[], char value[], struct treeNode* left, struct treeNode* right, struct treeNode* next) {
    struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));
    if (newNode == NULL) {
        fprintf(stderr,"Memory Allocation Failed\n");
        exit(1);
    }
    strncpy(newNode->type,type,20);
    if (value) {
        strncpy(newNode->value,value,50);
    }
    else {
        newNode->value[0] = '\0';
    }
    newNode->left = left;
    newNode->right = right;
    newNode->next = next;

    return newNode;
}

struct treeNode* gotonode(struct treeNode* root, struct treeNode* ptr, int depth){
    ptr = root;
    ptr = ptr->left;
    for (int i=0; i<depth-1; i++){
        ptr = ptr->next;
    }  
    return ptr; 
}


float eval_expr(struct treeNode* ptr){
    // Evaluate left and right subtrees
    float left = convert(ptr->left);
    if (strcmp(ptr->type, "INT")==0||strcmp(ptr->type, "FLOAT")==0||strcmp(ptr->type, "CHAR")==0) {
        // Leaf node with integer value
        return atof(ptr->value);
    }
    float left = eval_expr(ptr->left);
    float right = eval_exptr(ptr->right);

    // update functionality from file 
           if (strcmp(ptr->type, "ADD") == 0) {
       return left + right;
    } else if (strcmp(ptr->type, "SUB") == 0) {
        return left-right;
    } else if (strcmp(ptr->type, "MULT") == 0) {
        return left*right;
    } else if (strcmp(ptr->type, "DIV") == 0) {
        return right != 0 ? left / right : 0; // handle divide by zero
    } else if (strcmp(ptr->type, "MOD") == 0) {
        return right != 0 ? (int)left % (int)right : 0;
    } else if (strcmp(ptr->type, "LT") == 0) {
        return left < right;
    } else if (strcmp(ptr->type, "LTE") == 0) {
        return left <= right;
    } else if (strcmp(ptr->type, "GT") == 0) {
        return left > right;
    } else if (strcmp(ptr->type, "GTE") == 0) {
        return left >= right;
    } else if (strcmp(ptr->type, "EQ") == 0) {
        return left == right;
    } else if (strcmp(ptr->type, "NEQ") == 0) {
        return left != right;
    } else if (strcmp(ptr->type, "AND") == 0) {
        return left && right;
    } else if (strcmp(ptr->type, "OR") == 0) {
        return left || right;
    }

    return 0; // fallback
}

//Boolean
struct boolean* bool_loc;
int bool_capacity = 1;  // Initial storage capacity
int bool_size = 0;  // Number of currently stored variables
bool_loc = NULL;
// bool_init_storage(bool_loc, bool_capacity);

// Character
int *char_capacity;
int *char_size;
character **char_loc = NULL;
init_char_storage(char_loc, char_capacity, char_size);
// Dictionary
// Float
// int_list
// integers
// linked_list
// string


void executeTree(struct treeNode* root) {

    struct treeNode* ptr = root;
    int current_depth = 0;// determines the level of the tree where i am at.
    int scope=0;// scope is incremented everytime block is encountered and vice versa

    while (ptr != NULL) {
        if (strcmp(ptr->type, "PROGRAM") == 0) {
            ptr = ptr->left;
        }
        else if (strcmp(ptr->type, "VAR_DEC") == 0) {
            if (strcmp(ptr->value, "IDENTIFIER") == 0) {
                if (strcmp(ptr->left, "exp") == 0) {
                    // check inside all the struct vectors if there is a variable name that matches
                    // return no 
                } else {
                    // write code for ll_get
                }
            } else {
                // ask how to handle statements
            }
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LIST_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "DICT_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "SHOW") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASK") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "ASSIGN") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "IF") == 0) {
            ptr = ptr->left;
            float val = eval_expr(ptr);
            gotonode(root, ptr, current_depth);
            if (val){
                ptr = ptr->right;
                executeTree(ptr);
                gotonode(root, ptr, current_depth);
                ptr = ptr->next;
            }
        }
        else if (strcmp(ptr->type, "IF-ELSE") == 0) {
            // evaluate condition, then either left or right block
            ptr = ptr->left;
            float val = eval_expr(ptr);
            gotonode(root, ptr, current_depth);
            if (val){
                ptr = ptr->right;
                executeTree(ptr);
                gotonode(root, ptr, current_depth);
                ptr = ptr->next;
            }
            else{
                ptr = ptr->next;
                executeTree(ptr);
                ptr = ptr->next;
            }
        }
        else if (strcmp(ptr->type, "WHILE") == 0) {
            // use gotonode to loop while evaluating condition and executing block
            ptr = ptr->left;
            float val = eval_expr(ptr);
            if (val){
                executeTree(ptr);
                gotonode(root, ptr, current_depth);
                current_depth--;
            } 
        }
        else if (strcmp(ptr->type, "FOR") == 0) {
            ptr = ptr->left;
            // gather loop info

            gotonode(root, ptr, current_depth);
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LOOP_INFO") == 0) {
            // used inside for loop, contains VAR and RANGE
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RANGE") == 0) {
            // define start and end of range
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "NEXT") == 0) {
            ptr = ptr->next;

        }
        else if (strcmp(ptr->type, "LEAVE") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FUNC_DEC") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "FUNC_DATA") == 0) {
            // contains parameters and return type
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RET_TYPE") == 0) {
            // type returned by function
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "CALL") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "RETURN") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SORT") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SEARCH") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_INSERT") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_SET") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_DEL") == 0) {
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "LL_GET") == 0) {
            // used inside ptressions or assignments
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "BLOCK") == 0) {
            scope++;
            // execute the function
            scope--;
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "PARAMETER") == 0) {
            // single function parameter (IDENTIFIER and DATATYPE)
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "VAR") == 0) {
            // use of a variable. refer to the vector of structs 
            ptr = ptr->next;
        }
        else if (strcmp(ptr->type, "INDEX") == 0) {
            // access via index (e.g., list[i], dict[key])
            ptr = ptr->next;
        }
        // else if (strcmp(ptr->type, "ADDRESS") == 0) {
        //     // &variable (pointer address)
        //     ptr = ptr->next;
        // }
        // else if (strcmp(ptr->type, "DEREFERENCE") == 0) {
        //     // *pointer
        //     ptr = ptr->next;
        // }
        else {
            fprintf(stderr, "Unhandled node type: %s\n", ptr->type);
            ptr = ptr->next;
        }

        current_depth++;
    }
    return 0;
}
