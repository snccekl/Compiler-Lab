#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tree.h"
extern int yylineno;
//API
Node* createNode(int type, char* name,char * yytext){
    Node* node = malloc(sizeof(Node));
    node->num_child = 0;
    strcpy(node->name, name);
    strcpy(node->token, yytext);
    node->type = type;
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
    parent->num_child = ChildNum;
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
            parent->num_child--;
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
    parent->line = parent->first_son->line;
    va_end(childs);
}

//是否需要参数由你决定
void printTree(Node* prs, int floor) {
    if(prs == NULL) {
        printf("what???\n");
    }

    for(int i = 0; i < floor; i++)
        printf("  ");
    
    printf("%s", prs->name);
    if(prs->type == 1) {
        printf(" (%d)", prs->line);
    }
    
    else {
        if(!strcmp(prs->name, "ID"))
            printf(": %s", prs->token);
        
        else if(!strcmp(prs->name, "TYPE"))
            printf(": %s", prs->token);

        else if(!strcmp(prs->name, "INT"))
            printf(": %d", atoi(prs->token));
        
        else if(!strcmp(prs->name, "FLOAT"))
            printf(": %f", atof(prs->token));
    }
    
    printf("\n");
    if(prs->first_son != NULL) {
        struct Node* child = prs->first_son;
        while(child != NULL) {
            printTree(child, floor + 1);
            child = child->follow;
        }
    }
}


void printAST(Node* prs, int floor, unsigned long long pipe) {
    if(prs == NULL) {
        printf("what???\n");
    }

    for(int i = 0; i < floor - 1; i++) {
        if((pipe & (1 << i)) != 0)
            printf("│  ");
        else
            printf("   ");
    }

    if(floor != 0) {
        if(prs->follow != NULL)
            printf("├──");
        else
            printf("└──");
    }
    printf("%s", prs->name);
    if(strlen(prs->token) != 0)
        printf(": %s", prs->token);
    printf("\n");

    if(prs->first_son != NULL) {
        Node* child = prs->first_son;
        while(child != NULL) {
            
            unsigned long long new_pipe = pipe;
            if(child->follow != NULL)
                new_pipe |= 1 << floor;
            printAST(child, floor + 1, new_pipe);
            child = child->follow;
        }
    }
}