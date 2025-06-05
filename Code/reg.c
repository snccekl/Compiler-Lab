#include "assemble.h"


#define REG_BEGIN 8
#define REG_END 25

int last = REG_BEGIN;
Register* regList[32];
varList* varListReg = NULL;
varList* varListMem = NULL;
int offset = 0;

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
    Varible* var = (Varible*)malloc(sizeof(Varible));
    var->reg = reg;
    var->op = op;
    var->next = NULL;
    if (!varList->head) varList->head = varList->tail = var;
    else {
        varList->tail->next = var;
        varList->tail = var;
    }
}

void delVarible(varList* varList, Varible* target) {
    if (!varList || !target) return;
    Varible *prev = NULL, *curr = varList->head;
    while (curr) {
        if (curr == target) {
            if (prev) prev->next = curr->next;
            else varList->head = curr->next;
            if (varList->tail == curr) varList->tail = prev;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int assignReg(Operand op) {
    int reg = last;
    last = (last + 1 > REG_END ? REG_BEGIN : last + 1);
    return reg;
}

int saveToReg(FILE* fp, Operand op) {
    int reg = assignReg(op);
    fprintf(fp, "  lw %s, -%d($fp)\n", regList[reg]->name, op->u.var_no * 4);
    return reg;
}

void saveToStack(FILE* fp, int reg, Operand op) {
    fprintf(fp, "  sw %s, -%d($fp)\n", regList[reg]->name, op->u.var_no * 4);
}