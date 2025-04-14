#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static treeNode* root = NULL;

treeNode* createNode(char type[], char value[], treeNode* left, treeNode* right, treeNode* next) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    if (newNode == NULL) {
        fprintf(stderr,"Memory Allocation Failed\n");
        exit(1);
    }
    strncpy(newNode->type, type, 20);

    if (value) {
        strncpy(newNode->value, value, 50);
    } else {
        newNode->value[0] = '\0';
    }
    newNode->left = left;
    newNode->right = right;
    newNode->next = next;
    return newNode;
}

void setAST(treeNode* node) {
    root = node;
}

treeNode* getAST(void) {
    return root;
}

// Optional: pretty printer
void printTree(treeNode* node, int indent, int isLast) {
    if (!node) return;

    for (int i = 0; i < indent - 4; i++) printf(" ");
    if (indent > 0) printf("%s── ", isLast ? "└" : "├");

    printf("[%s", node->type);
    if (strlen(node->value)) printf(": %s", node->value);
    printf("]\n");

    if (node->left || node->right || node->next) {
        if (node->left) printTree(node->left, indent + 4, 0);
        if (node->right) printTree(node->right, indent + 4, node->next ? 0 : 1);
        if (node->next) printTree(node->next, indent + 4, 1);
    }
}
