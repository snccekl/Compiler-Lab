#ifndef TREE_H
#define TREE_H

typedef struct TreeNode{
    char* name;
    char* token;
    int line;
    Node* parent;
    Node* first_son;
    Node* follow;
} Node;

Node* createNode(char* name,char * yytext);

//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(int ChildNum, Node* parent, ...);

void printTree(Node* prs, int floor);

#endif