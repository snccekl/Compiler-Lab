#ifndef TREE_H
#define TREE_H

struct Node{
    char name[256];
    char token[256];
    int line;
    struct Node* parent;
    struct Node* first_son;
    struct Node* follow;
};
typedef struct Node Node;
Node* createNode(char* name,char * yytext);

//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(struct Node* parent, int ChildNum, ...);

void printTree(struct Node* prs, int floor);

#endif