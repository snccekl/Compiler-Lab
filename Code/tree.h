#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

struct Node{
    char name[256];
    char token[256];
    int type, line;
    int num_child;

    int flag;
    int scope_id;
    struct Node* parent;
    struct Node* first_son;
    struct Node* follow;
};
typedef struct Node Node;

extern int has_struct;

// createNode 用于创建节点
Node* createNode(int type, char* name,char * yytext);

// addNode 用于为父亲节点添加子节点
// 这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(struct Node* parent, int ChildNum, ...);

// printTree 用于输出树
void printTree(struct Node* prs, int floor);

// 用于将语法分析树(parse_tree)转为抽象语法树(AST)
Node* parseTreeToAst(Node* root);

// 用于输出AST，floor: 层数， pipe: 用来辅助输出树的，初始为0
void printAST(Node* prs, int floor, unsigned long long pipe);

#endif