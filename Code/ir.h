#ifndef __IR_H__
#define __IR_H__
#include "Semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operand_* Operand;
typedef struct Operand_ {//操作数
	enum {VARIABLE_OP, TEMPVAR_OP, CONSTANT_OP, ADDR_OP//*
	,
	QU_ADDR_OP // &
	, LABEL_OP, FUNCTION_OP } kind;
	union {
		int var_no;		        //临时变量t
		int label_no;		    //标号l
		char value[32];		   //值 		
	}u;
	//int tempint;
	Type type;
}Operand_;

typedef struct InterCode_* InterCode;
typedef struct InterCode_ {
    //表1
	enum {
			LABEL_IR, FUNCTION_IR, ASSIGN_IR, PLUS_IR, MINUS_IR, STAR_IR, DIV_IR, 
            ADDR_IR2,    // x := &y
			ADDR_IR3,
            ADDR_VALUE_IR, // x := *y 
			MEMORY_IR, //*x := y 
            GOTO_IR, IF_IR, RETURN_IR, DEC_IR, ARG_IR, CALL_IR, PARAM_IR, READ_IR, WRITE_IR,DEBUG_IR
	}kind;
    Operand operands[3];
    int size;
    char relop[32];
}InterCode_;

void initIRList();
void insertCode(InterCode ir);
void printCode(char *filename);
void repr(Operand op,FILE *file);
void deletelastCode();
FieldList allsearch(char *name ,int flag);
int getSpace(Type type) ;

// 为什么没有变量值？变量值可能是函数调用或者别的，直接使用value代替值会不会有问题（
// 这个new_var我感觉不对劲，修改后再用
Operand new_var();
Operand new_temp();
Operand new_label();
Operand new_constant(int i);



// 你这框架有几个搞不懂的地方
// 首先函数定义需要插入到中间代码的，但是我找不到框架什么东西代表函数定义
// 其次变量var定义上是存在的，只是没插入中间代码里，但是var这里单纯用char来代替感觉有点指代不明？

// 树 这里用AST的节点（（（
void tProgram(Node *root);


Operand tVarDecl(Node* varDecl);
void tArrayDecl(Node* arrayDecl, Operand var);
void tInit(Node* init, Operand var);

void tFuncDecl(Node* func);
void tParamList(Node* paramList);



// void tCompSt(Node *node,Type spec);
// FieldList tVarDec(Node *node,Type spec);
// Type tStructDecl(Node *node);
// void tStmt(Node *node,Type spec);

// void tExp(Node * node, Operand  place);


// void tArgs(Node *node,Operand * arglist);
// void tCond(Node* node,Operand label_true,Operand label_false);
#endif