#include "assemble.h"

extern int IRsize;
extern InterCode *IRList;

VarList* varListReg;//寄存器变量表
VarList* varListMem;//内存的变量表
int offset;
Register* regList[32];
int last;


char* REG_NAME[32] = 
{   "$0",  "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2",
    "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5",
    "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void insertIndexCode(int index,InterCode ir)
{
    insertCode(IRList[IRsize-1]);//用insert方法塞最后一个 使其后挪
    for(int i = IRsize-2;i>index;i--)
    {
        IRList[i] = IRList[i-1];
    }
    IRList[index] = ir;
}

int transition(Operand op,int index,int opth)
{
    if (op == NULL) {
		printf("debug op == NULL");
		return 0;
	}
	switch (op->kind) {
        case VARIABLE_OP://变量名
            if (op->u.value != NULL) {
                sprintf(op->name, "%s", op->u.value);
            }
            break;
    }
}


