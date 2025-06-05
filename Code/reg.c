#include "assemble.h"


#define REG_BEGIN 8
#define REG_END 25

// int last = REG_BEGIN;
// Register* regList[32];
// varList* varListReg = NULL;
// varList* varListMem = NULL;

// 初始化寄存器
void initRegisters() {
    const char* REG_NAME[32] = {
        "$0", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    for (int i = 0; i < 32; ++i) {
        regList[i] = (Register*)malloc(sizeof(Register));
        regList[i]->name = (char*)REG_NAME[i]; // 静态分配可直接赋值
        regList[i]->isEmpty = 1;
    }
    regList[0]->isEmpty = 0;

    varListReg = (varList*)malloc(sizeof(varList)); varListReg->head = NULL; varListReg->tail = NULL;
    varListMem = (varList*)malloc(sizeof(varList)); varListMem->head = NULL; varListMem->tail = NULL;
    offset = 0;
}

void clearVarList(varList* varList) {
    if (!varList) return;
    Varible* p = varList->head;
    while (p) {
        Varible* tmp = p;
        p = p->next;
        free(tmp);
    }
    varList->head = varList->tail = NULL;
}

void addVarible(varList* varList, int reg, Operand op) {
    Varible* newVar = (Varible*)malloc(sizeof(Varible));
    newVar->reg = reg;
    newVar->op = op;
    newVar->next = NULL;
    if (varList->head == NULL) 
        varList->head = newVar;
    else 
        varList->tail->next = newVar;
    varList->tail = newVar;
}
void delVarible(varList* varList, Varible* var) {
    if (var == varList->head)
        varList->head = varList->head->next;
    else {
        Varible* temp = varList->head;
        while (temp&&temp->next != var) 
            temp = temp->next;
        if (varList->tail == var) 
            varList->tail = temp;
        temp->next = var->next;
    }
    var->next = NULL;
    free(var);
}

void saveToStack(FILE *fp, int reg, Operand op)
{
    Varible *temp;
    for (temp = varListMem->head; temp != NULL ; temp = temp->next){
        if (strcmp(temp->op->name, op->name) == 0) break;
    }
    fprintf(fp, "  sw %s, %d($gp)\n", regList[reg]->name, temp->reg);
}


int saveToReg(FILE* fp, Operand op) {
    if(op == NULL)
        return -1;

    if (op->kind != CONSTANT_OP){
        int reg = assignReg(op);
        for(Varible* temp = varListMem->head;temp!=NULL;temp=temp->next)
            if (strcmp(temp->op->name, op->name)==0){
                    fprintf(fp, "  lw %s, %d($gp)\n", regList[reg]->name, temp->reg);
                    return reg;
                }
        return reg;
    }
    else{
        if (op->constant == 0)
            return ZERO;
        int reg = assignReg(op);
        fprintf(fp, "  li %s, %d\n", regList[reg]->name, op->constant);
        return reg;
    }
}

int assignReg(Operand op) {
    for (int i = T0; i <= T9; ++i) {
        if (regList[i]->isEmpty) {
            regList[i]->isEmpty = 0;
            addVarible(varListReg, i, op);
            return i;
        }
    }
    Varible* temp = varListReg->head;
    int reg = temp->reg;
    delVarible(varListReg, temp);
    addVarible(varListReg, reg, op);
    return reg;
}