#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_boolean.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_character.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_dictionary.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_float.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_int_list.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_integers.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_linked_list.h"
#include "b24cs1053_b24me1034_b24cm1054_b24ci1017_string.h"
#include "tree.h"
extern int yyparse();

#define MAX_VAR_LENGTH 1024
#define MAX_CHAR_VALUE 1024

// struct treeNode{
//     char type[20]; //stores the node type like assignment,declaration,etc
//     char value[50]; //stores the value of the node
//     struct treeNode* left; //point to the left branch in the tree
//     struct treeNode* right; //point to the right branch in the tree
//     struct treeNode* next; //next statement in the sequence
// };
//function to create a node for the tree
// struct treeNode* createNode(char type[], char value[], struct treeNode* left, struct treeNode* right, struct treeNode* next) {
//     struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));
//     if (newNode == NULL) {
//         fprintf(stderr,"Memory Allocation Failed\n");
//         exit(1);
//     }
//     strncpy(newNode->type,type,20);
//     if (value) {
//         strncpy(newNode->value,value,50);
//     }
//     else {
//         newNode->value[0] = '\0';
//     }
//     newNode->left = left;
//     newNode->right = right;
//     newNode->next = next;

//     return newNode;
// }

struct treeNode* gotonode(struct treeNode* root, struct treeNode* ptr, int depth){
    ptr = root;
    ptr = ptr->left;
    for (int i=0; i<depth-1; i++){
        ptr = ptr->next;
    }  
    return ptr; 
}
struct Function {
    char name[MAX_VAR_LENGTH];
    struct treeNode* parameters;
    struct treeNode* body;
    char returnType[20];
};

struct Function functionTable[100];
int functionCount = 0;
float returnValue = 0;
int hasReturned = 0;


float eval_expr(struct treeNode* ptr){
    // Evaluate left and right subtrees
    if (strcmp(ptr->type, "INT")==0||strcmp(ptr->type, "FLOAT")==0||strcmp(ptr->type, "CHAR")==0) {
        // Leaf node with integer value
        return atof(ptr->value);
    }
    else if (strcmp(ptr->type,"VAR") == 0) {
        return (float)(get_int_var(ptr->value,1)->int_value);
    }
    float left = eval_expr(ptr->left);
    float right = eval_expr(ptr->right);

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

int executeTree(struct treeNode* root, int scope) { //scope starts at 0
    struct treeNode* ptr = root;
    int current_depth = 0;// determines the level of the tree where i am at.
    //int scope=0;// scope is incremented everytime block is encountered and vice versa

    if (ptr != NULL) {
        if (strcmp(ptr->type, "VAR_DEC") == 0) {
            if(strcmp(ptr->left->value, "integer") == 0) {
                int_add_variable(ptr->value, scope, 0);
            } else if (strcmp(ptr->left->value, "float") == 0) {
                add_float_variable(ptr->value, 0.00, scope);
                // Store in the appropriate data structure
            } else if (strcmp(ptr->left->value, "character") == 0) {
                // Initialize character variable
                add_char_variable(ptr->value, 'a', scope);
            }
            else if (strcmp(ptr->left->value, "boolean") == 0) {
                // Initialize boolean variable
                bool_add_variable(ptr->value, 0, scope);
                // Store in the appropriate data structure
            }
            else if (strcmp(ptr->left->value, "string") == 0) {
                // Initialize string variable
                char *s = "a";
                //add_string_variable(s,s,scope);
                // Store in the appropriate data structure
            }
            
            // else if (strcmp(ptr->left->type, "dictionary") == 0) {
            //     add_dict_C_C(1, ptr->value, scope);
            // }
            else if (strcmp(ptr->left->type, "linkedlist") == 0) {
                // Initialize linked list variable
                // Store in the appropriate data structure
            }
            
            executeTree(ptr->next,scope);
        }
        else if (strcmp(ptr->type,"LIST_DEC") == 0) {
            add_intlist_variable(ptr->value, atoi(ptr->right->value), 0, scope);
        }
        else if (strcmp(ptr->type, "SHOW") == 0) {
            struct treeNode* ptr1 = ptr->left;
            char c[1000]; 
            strcpy(c, ptr->value);
            for(int i=0; c[i]!='\0';i++){
                if (ptr1 == NULL) {
                if(c[i]=='\\' && c[i+1]=='n'){
                    printf("\n");
                    i++;
                }
                else if(c[i]=='\\' && c[i+1]=='t'){
                    printf("\t");
                    i++;
                }
                else{
                    printf("%c",c[i]);
                }
            }
                else {
             if(c[i]=='%' && c[i+1] == 'd'){
                    printf("%d", (get_int_var(ptr1->value,scope))->int_value);
                    ptr1 = ptr1->next;
                    i++;
                }
                else if(c[i]=='%' && c[i+1] == 'f'){
                    printf("%f", (get_float_variable(ptr1->value,scope))->value);
                    ptr1 = ptr1->next;
                    i++;
                }
                else if(c[i]=='%' && c[i+1] == 'c'){
                    printf("%c", (get_char_variable(ptr1->value,scope))->value);
                    ptr1 = ptr1->next;
                    i++;
                }
            }
                
            }
            executeTree(ptr->next,scope);
        }
        else if (strcmp(ptr->type, "ASK") == 0) {
            if(strcmp(ptr->value,"integer")==0){
                scanf("%d", &(get_int_var(ptr->left->value,scope)->int_value));
            }
            else if(strcmp(ptr->value,"float")==0){
                scanf("%f", &(get_float_variable(ptr->left->value,scope)->value));
            }
            else if(strcmp(ptr->value,"character")==0){
                char c[MAX_CHAR_VALUE];
                scanf("%s", c);
                add_char_variable(ptr->left->value, c[0], scope);
            }
            executeTree(ptr->next,scope);
        }
        else if (strcmp(ptr->type, "ASSIGN") == 0) {
            if(strcmp(ptr->left->type,"INDEX")==0){
                update_intlist_element_ptr(get_intlist_variable(ptr->left->value,scope), atoi(ptr->left->left->value), atoi(ptr->right->value));
            }
            else if(strcmp(ptr->left->type,"LL_GET")==0){
                int_update_variable(get_int_var(ptr->value,scope),read_node(get_list_by_name_scope(ptr->left->value,scope),atoi(ptr->left->left->value)));
            }
            else if(strcmp(ptr->left->type,"CALL")==0){
                //call
            }
            else{
                int_update_variable(get_int_var(ptr->value,scope),eval_expr(ptr->left));
            }
            executeTree(ptr->next,scope);
        }
        else if (strcmp(ptr->type, "IF") == 0) {
            float val = eval_expr(ptr->left);
            //gotonode(root, ptr, current_depth);
            if (val){
                if(!executeTree(ptr->right,scope++)){
                    executeTree(ptr->next,scope);
                }
                //gotonode(root, ptr, current_depth);
            }
            executeTree(ptr->next,scope);
        }
        else if (strcmp(ptr->type, "IF-ELSE") == 0) {
            if(eval_expr(ptr->left->left) == 1.0){
                if(!executeTree(ptr->left->right,scope++)){
                    executeTree(ptr->next,scope);
                }
            }
            else{
                if(!executeTree(ptr->right,scope++)){
                    executeTree(ptr->next,scope);
                }
            }
        }
        else if (strcmp(ptr->type, "WHILE") == 0) {
            float val = eval_expr(ptr->left);
            while (val){
                executeTree(ptr->right,scope++);
                val = eval_expr(ptr->left);
            }
        }
        else if (strcmp(ptr->type, "FOR") == 0) {
            // Initialize loop variable
            struct treeNode* initNode = ptr->left;
            int_add_variable(get_int_var(initNode->value, scope)->int_name, eval_expr(initNode->left), scope);
            if (initNode != NULL) {
                int_update_variable(get_int_var(initNode->value, scope), eval_expr(initNode->left));
            }
            // Loop condition
            float val = eval_expr(ptr->left->next);
            while (val) {
                executeTree(ptr->right, scope++);
                // Update loop variable
                struct treeNode* updateNode = ptr->left->next->next;
                if (updateNode != NULL) {
                    int_update_variable(get_int_var(updateNode->value, scope), eval_expr(updateNode->left));
                }
                val = eval_expr(ptr->left->next);
            }
        }
        else if (strcmp(ptr->type, "NEXT") == 0) {
            executeTree(ptr->next,scope--);

        }
        else if (strcmp(ptr->type, "LEAVE") == 0) {
            return 1;
        }
        // else if (strcmp(ptr->type, "FUNC_DEC") == 0) {
        //     struct Function newFunc;
        //     strncpy(newFunc.name, ptr->value, MAX_VAR_LENGTH);
        //     struct treeNode* funcData = ptr->left;   // This contains FUNC_DATA and RET_TYPE
        //     newFunc.body = ptr->right;               // Function body (block) is in the right field
        
        //     while (funcData != NULL) {
        //         if (strcmp(funcData->type, "FUNC_DATA") == 0) {
        //             newFunc.parameters = funcData->left; // Parameters list
        //         } else if (strcmp(funcData->type, "RET_TYPE") == 0) {
        //             strncpy(newFunc.returnType, funcData->value, 20);
        //         }
        //         funcData = funcData->next;
        //     }
        
        //     functionTable[functionCount++] = newFunc;
        //     executeTree(ptr->next,scope);
        // }
        // else if (strcmp(ptr->type, "RETURN") == 0) {
        //     if (ptr->left != NULL) {
        //         returnValue = eval_expr(ptr->left);
        //         hasReturned = 1;
        //     }
        //     return; 
        // }
        // else if (strcmp(ptr->type, "CALL") == 0) {
        //     struct Function* calledFunc = NULL;
        
        //     for (int i = 0; i < functionCount; i++) {
        //         if (strcmp(functionTable[i].name, ptr->value) == 0) {
        //             calledFunc = &functionTable[i];
        //             break;
        //         }
        //     }
        //     if (calledFunc == NULL) {
        //         fprintf(stderr, "Function not found: %s\n", ptr->value);
        //         ptr = ptr->next;
        //         return;
        //     }
        //     // Argument passing
        //     struct treeNode* argNode = ptr->left;
        //     struct treeNode* paramNode = calledFunc->parameters;
        
        //     while (argNode && paramNode) {
        //         float val = eval_expr(argNode);
        //         // This sets the function parameter as a local variable
        //         //some function to initialise functions for the functions and assigning them values of the arguments we passed
        //         argNode = argNode->next;
        //         paramNode = paramNode->next;
        //     }
        
        //     if (argNode || paramNode) {
        //         fprintf(stderr, "Argument count mismatch in function call: %s\n", ptr->value);
        //         ptr = ptr->next;
        //         return;
        //     }
        
        //     // Execute function body
        //     hasReturned = 0;
        //     executeTree(calledFunc->body,scope++);
        
        //     // Optionally use returnValue here
        //     float result = returnValue;
        
        //     ptr = ptr->next;
        // }
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

int main() {
    yyparse(); // this builds the AST
    treeNode* root = getAST(); // retrieve from tree.
    init_char_storage();
    bool_init_storage();
    init_float_storage();
    init_intlist_storage();
    int_init_storage();
    init_string_storage();
    executeTree(root,0);
    return 0;
}
