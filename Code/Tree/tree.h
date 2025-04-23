#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Config/config.h"

struct Node{
    char name[256];
    char token[256];
    int type, line;
    int num_child;
    struct Node* parent;
    struct Node* first_son;
    struct Node* follow;
};
typedef struct Node Node;

// createNode 用于创建节点
Node* createNode(int type, char* name,char * yytext);

// addNode 用于为父亲节点添加子节点
// 这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(struct Node* parent, int ChildNum, ...);

// printTree 用于输出树
void printTree(struct Node* prs, int floor);

// 用于将语法分析树(parse_tree)转为抽象语法树(AST)
Node* parseTreeToAst(Node* root);

#endif