#ifndef REG_H
#define REG_H

#include "assemble.h"

extern int IRsize;
extern InterCode *IRList;

// 基本块划分

// 基本块内的中间代码
typedef struct InterCodeList_ {
    InterCode code;
    struct InterCodeList_* next;
} InterCodeList;

// 基本块
typedef struct BasicBlock {
    InterCodeList* codeList;
    struct BasicBlock* next;

    struct BasicBlock* succ[2]; // 最多两个后继
    int succ_count;
    int id;  // 唯一编号
} BasicBlock;

extern BasicBlock* blockList;

void generateBasicBlocks();


// 活跃变量分析 
typedef struct VarSet {
    Operand vars[256];  // 可调大小
    int count;
} VarSet;

typedef struct LiveInfo {
    InterCode* code;
    VarSet use;
    VarSet def;
    VarSet in;
    VarSet out;
    struct LiveInfo* next;
} LiveInfo;

typedef struct CodeLiveInfoNode {
    InterCode* code;
    LiveInfo info;
    struct CodeLiveInfoNode* next;
} CodeLiveInfoNode;

extern LiveInfo* liveList;


int getVarIndex(Operand op);
Operand getDefinedOperand(InterCode code);
void getUsedOperands(InterCode code, Operand* used);


void initUseDef(InterCode* code, VarSet* use, VarSet* def);
void analyzeLiveness(BasicBlock* blocks);

// 干涉图和图着色算法
#define MAX_VAR 1024

#endif