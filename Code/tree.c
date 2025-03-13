#include <stdio.h>
#include <stdarg.h>
#include "tree.h"

//API
Node* createNode(char* name,char * yytext){
    Node* node = malloc(sizeof(Node));
    
    node->name = name;
    node->token = yytext;
    node->line = -1;

    node->parent = NULL;
    node->first_son = NULL;
    node->follow = NULL;
}
//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(int ChildNum, Node* parent, ...){
    va_list childs;
    va_start(childs, ChildNum);

    Node* prs = NULL;
    for(int i = 0; i < ChildNum; i++) {
        Node* child = va_arg(childs, Node*);

        child->parent = parent;
        if(parent->first_son == NULL) {
            parent->first_son = child;
            prs = child;
        }
        else {
            prs->follow = child;
            prs = prs->follow;
        }
    }
}

//是否需要参数由你决定
void printTree(Node* prs, int floor) {
    for(int i = 0; i < floor; i++)
        printf("  ");
    
    printf("%s\n", prs->name);
    if(prs->first_son != NULL) {
        Node* child = prs->first_son;
        while(child != NULL) {
            printTree(child, floor + 1);
            child = child->follow;
        }
    }
}