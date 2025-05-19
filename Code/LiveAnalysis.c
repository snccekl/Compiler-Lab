#include "reg.h"

int isSameOperand(Operand a, Operand b) {
    if(a == NULL || b == NULL)
        return 0;

    if( a->kind != b->kind)
        return 0;
    switch (a->kind) {
        case VARIABLE_OP:
        case TEMPVAR_OP:
            return a->u.var_no == b->u.var_no;
        case CONSTANT_OP:
            return a->constant == b->constant;
        case LABEL_OP:
            return a->u.label_no == b->u.label_no;
        case ADDR_OP:
        case FUNCTION_OP:
            return strcmp(a->name, b->name) == 0;
        default:
            return 0;
    }
    return 1;
}

void setCopy(VarSet* dst, const VarSet* src) {
    dst->count = 0;
    for (int i = 0; i < src->count; ++i) {
        dst->vars[dst->count++] = src->vars[i];
    }
}

void setInsert(VarSet* set, Operand op) {
    if (!op || (op->kind != VARIABLE_OP && op->kind != TEMPVAR_OP)) return;
    for (int i = 0; i < set->count; ++i)
        if (isSameOperand(set->vars[i], op)) return;
    set->vars[set->count++] = op;
}
void setUnion(VarSet* dst, VarSet* src) {
    for (int i = 0; i < src->count; ++i) {
        setInsert(dst, src->vars[i]);
    }
}

void setDiff(VarSet* dst, VarSet* src) {
    int k = 0;
    for (int i = 0; i < dst->count; ++i) {
        int found = 0;
        for (int j = 0; j < src->count; ++j) {
            if (isSameOperand(dst->vars[i], src->vars[j])) {
                found = 1;
                break;
            }
        }
        if (!found) dst->vars[k++] = dst->vars[i];
    }
    dst->count = k;
}

int setEqual(VarSet* a, VarSet* b) {
    if (a->count != b->count) return 0;
    for (int i = 0; i < a->count; ++i) {
        int found = 0;
        for (int j = 0; j < b->count; ++j) {
            if (isSameOperand(a->vars[i], b->vars[j])) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

CodeLiveInfoNode* liveMap = NULL;
Operand varTable[MAX_VAR];
int varCount = 0;

int getVarIndex(Operand op) {
    if (op == NULL) return -1;
    if (op->kind != VARIABLE_OP && op->kind != TEMPVAR_OP)
        return -1;
    for (int i = 0; i < varCount; ++i) {
        if (isSameOperand(varTable[i], op))
            return i;
    }
    if (varCount < MAX_VAR) {
        varTable[varCount] = op;
        return varCount++;
    } else {
        fprintf(stderr, "Too many variables for register allocation.\n");
        exit(1);
    }
}

Operand getDefinedOperand(InterCode code) {
    if(code == NULL) return NULL;
    switch(code->kind) {
        case ASSIGN_IR:
        case PLUS_IR:
        case MINUS_IR:
        case STAR_IR:
        case DIV_IR:
        case CALL_IR:
        case ADDR_IR2:
        case ADDR_IR3:
        case ADDR_VALUE_IR:
        case READ_IR:
            return code->operands[0];
        default:
            return NULL;
    }
}

void getUsedOperands(InterCode code, Operand* used) {
    for (int i = 0; i < 3; ++i) used[i] = NULL;
    switch (code->kind) {
        case ASSIGN_IR:
            used[0] = code->operands[1]; break;
        case PLUS_IR:
        case MINUS_IR:
        case STAR_IR:
        case DIV_IR:
            used[0] = code->operands[1];
            used[1] = code->operands[2]; break;
        case IF_GOTO_IR:
            used[0] = code->operands[0];
            used[1] = code->operands[1]; break;
        case RETURN_IR:
        case ARG_IR:
        case WRITE_IR:
            used[0] = code->operands[0]; break;
        default:
            break;
    }
}

LiveInfo* getLiveInfo(InterCode* code) {
    for (CodeLiveInfoNode* node = liveMap; node; node = node->next)
        if (node->code == code) return &node->info;
    CodeLiveInfoNode* newNode = malloc(sizeof(CodeLiveInfoNode));
    newNode->code = code;
    newNode->next = liveMap;
    newNode->info.in.count = newNode->info.out.count = 0;
    newNode->info.use.count = newNode->info.def.count = 0;
    liveMap = newNode;
    return &newNode->info;
}

void initUseDef(InterCode* code, VarSet* use, VarSet* def) {
    use->count = def->count = 0;
    Operand used[3];
    getUsedOperands(code, used);
    Operand defined = getDefinedOperand(code);
    for (int i = 0; i < 3; i++) {
        if (used[i] != NULL)
            setInsert(use, used[i]);
    }
    if (defined != NULL)
        setInsert(def, defined);
}

BasicBlock* findBlockByLabel(BasicBlock* blocks, Operand label) {
    for (BasicBlock* blk = blocks; blk != NULL; blk = blk->next) {
        if (blk->codeList == NULL) continue;
        InterCode code = blk->codeList->code;
        if (code->kind == LABEL_IR && isSameOperand(code->operands[0], label)) {
            return blk;
        }
    }
    return NULL;
}

void buildCFG(BasicBlock* blocks) {
    for (BasicBlock* blk = blocks; blk != NULL; blk = blk->next) {
        blk->succ_count = 0;
        blk->succ[0] = blk->succ[1] = NULL;
        if (blk->codeList == NULL) continue;

        InterCodeList* last = blk->codeList;
        while (last->next != NULL)
            last = last->next;
        InterCode code = last->code;

        if (code->kind == GOTO_IR) {
            BasicBlock* target = findBlockByLabel(blocks, code->operands[0]);
            if (target) blk->succ[blk->succ_count++] = target;
        } else if (code->kind == IF_GOTO_IR) {
            BasicBlock* target = findBlockByLabel(blocks, code->operands[3]);
            if (target) blk->succ[blk->succ_count++] = target;
            if (blk->next) blk->succ[blk->succ_count++] = blk->next;
        } else if (code->kind != RETURN_IR) {
            if (blk->next) blk->succ[blk->succ_count++] = blk->next;
        }
    }
}

void initLiveness(BasicBlock* blocks) {
    for (BasicBlock* blk = blocks; blk; blk = blk->next) {
        for (InterCodeList* node = blk->codeList; node; node = node->next) {
            LiveInfo* info = getLiveInfo(node->code);
            initUseDef(node->code, &info->use, &info->def);
        }
    }
    buildCFG(blocks);
}

void analyzeLiveness(BasicBlock* blocks) {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (BasicBlock* blk = blocks; blk; blk = blk->next) {
            for (InterCodeList* node = blk->codeList; node; node = node->next) {
                LiveInfo* info = getLiveInfo(node->code);
                VarSet oldIn, oldOut;
                setCopy(&oldIn, &info->in);
                setCopy(&oldOut, &info->out);

                info->out.count = 0;
                if (node->next) {
                    setUnion(&info->out, &getLiveInfo(node->next->code)->in);
                } else {
                    for (int i = 0; i < blk->succ_count; ++i) {
                        BasicBlock* succ_blk = blk->succ[i];
                        if (succ_blk && succ_blk->codeList)
                            setUnion(&info->out, &getLiveInfo(succ_blk->codeList->code)->in);
                    }
                }

                VarSet tmp;
                setCopy(&tmp, &info->out);
                setDiff(&tmp, &info->def);
                setCopy(&info->in, &info->use);
                setUnion(&info->in, &tmp);

                if (!setEqual(&oldIn, &info->in) || !setEqual(&oldOut, &info->out))
                    changed = 1;
            }
        }
    }
}
