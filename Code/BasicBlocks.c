#include "reg.h"

BasicBlock* blockList = NULL;

static InterCodeList* makeNode(InterCode code) {
    InterCodeList* node = (InterCodeList*)malloc(sizeof(InterCodeList));
    node->code = code;
    node->next = NULL;
    return node;
}

// 基本块划分主函数
void generateBasicBlocks() {
    BasicBlock* curBlock = NULL; // 当前正在构建的基本块
    int id = 0;

    if(IRsize == 0)
        return ;

    for(int i = 0; i < IRsize; i++) {
        InterCode p = IRList[i];

        // 如果当前没有块，创建新块
        if (curBlock == NULL) {
            curBlock = (BasicBlock*)malloc(sizeof(BasicBlock));
            curBlock->id = id++;
            curBlock->codeList = NULL;
            curBlock->next = blockList;
            blockList = curBlock;
        }

        InterCodeList* node = makeNode(p); // 包装成链表节点

        // 添加到当前基本块的 codeList 中
        if (curBlock->codeList == NULL) {
            curBlock->codeList = node;
        } else {
            InterCodeList* tail = curBlock->codeList;
            while (tail->next) tail = tail->next;
            tail->next = node;
        }

        // 如果遇到跳转类语句，结束当前基本块
        if (p->kind == GOTO_IR || p->kind == IF_GOTO_IR || p->kind == RETURN_IR) {
            curBlock = NULL;  // 下一条语句将开始新的块
        }
    }
}
