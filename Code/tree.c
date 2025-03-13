#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tree.h"
extern int yylineno;
//API
struct Node* createNode(char* name,char * yytext){
    struct Node* node = malloc(sizeof(struct Node));
    
    node->name = name;
    node->token = yytext;
    node->line = yylineno;

    node->parent = NULL;
    node->first_son = NULL;
    node->follow = NULL;
}
//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(struct Node* parent, int ChildNum, ...){
    va_list childs;
    va_start(childs, ChildNum);

    struct Node* prs = NULL;
    for(int i = 0; i < ChildNum; i++) {
        struct Node* child = va_arg(childs, struct Node*);

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
void printTree(struct Node* prs, int floor) {
    for(int i = 0; i < floor; i++)
        printf("  ");
    
    printf("%s\n", prs->name);
    if(prs->first_son != NULL) {
        struct Node* child = prs->first_son;
        while(child != NULL) {
            printTree(child, floor + 1);
            child = child->follow;
        }
    }
}