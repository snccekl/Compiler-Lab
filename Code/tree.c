#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tree.h"
extern int yylineno;
//API
Node* createNode(char* name,char * yytext){
    Node* node = malloc(sizeof(Node));
    
    strcpy(node->name, name);
    strcpy(node->token, yytext);
    node->line = yylineno;

    node->parent = NULL;
    node->first_son = NULL;
    node->follow = NULL;

    return node;
    // return NULL;
}
//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(Node* parent, int ChildNum, ...){
    if(parent == NULL) {
        printf("what???\n");
        return ;
    }
    
    va_list childs;
    va_start(childs, ChildNum);

    struct Node* prs = parent->first_son;
    if(prs != NULL) {
        while(prs->follow != NULL)
            prs = prs->follow;
    }

    // printf("%s %d\n", parent->name, ChildNum);
    for(int i = 0; i < ChildNum; i++) {
        struct Node* child = va_arg(childs, struct Node*);

        if(child == NULL) {
            // printf("NULL child:%d\n", i + 1);
            continue;
        }
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
    if(prs == NULL) {
        printf("what???\n");
    }

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