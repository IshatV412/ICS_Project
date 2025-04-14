#ifndef B24CS1053_B24ME1034_B24CM1054_B24CI1017_TREE_H
#define B24CS1053_B24ME1034_B24CM1054_B24CI1017_TREE_H

typedef struct treeNode {
    char type[20];
    char value[50];
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* next;
} treeNode;

treeNode* createNode(char type[], char value[], treeNode* left, treeNode* right, treeNode* next);
treeNode* getAST(void);
void setAST(treeNode* node);  // Optional, if you want to manually assign
void printTree(treeNode* node, int indent, int isLast);

#endif
