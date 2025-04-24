// 该接口文件仅用于辅助AST的生成，切勿在别的地方使用该头文件

#ifndef AST_H
#define AST_H

#include "tree.h"

Node* createAstNode(char* name, char* token, int line, int scope_id, int flag);

Node* transferExtDefList(Node* node, Node* parent);
Node* transferExtDef(Node* node, Node* parent);

Node* transferSpecifier(Node* node);
Node* transferStructSpecifier(Node* node);

Node* transferExtDecList(Node* node, Node* parent, Node* type);
Node* transferVarDec(Node* node, Node* parent, Node* type);

Node* transferFuncDec(Node* node, Node* parent, Node* type);
Node* transferVarList(Node* node, Node* parent);

Node* transferCompSt(Node* node, Node* parent);
Node* transferDefList(Node* node, Node* parent);
Node* transferDecList(Node* node, Node* parent, Node* type);

Node* transferStmtList(Node* node, Node* parent);
Node* transferStmt(Node* node, Node* parent);

Node* transferExp(Node* node, Node* parent);
Node* transferArgs(Node* node, Node* parent);


#endif