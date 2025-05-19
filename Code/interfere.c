#include "reg.h"


int interference[MAX_VAR][MAX_VAR]; // 干涉图的邻接矩阵
int varColor[MAX_VAR];              // 染色结果（寄存器分配）

void buildInterferenceGraph() {
    for (LiveInfo* info = liveList; info; info = info->next) {
        Operand def = getDefinedOperand(info->code); // 当前语句定义的变量
        if (def == NULL) continue;

        // 遍历 out 集合：与 def 干涉
        for (int i = 0; i < info->out.count; ++i) {
            Operand live = info->out.vars[i];
            int a = getVarIndex(def), b = getVarIndex(live);
            if (a != b) {
                interference[a][b] = 1;
                interference[b][a] = 1;
            }
        }
    }
}

void colorGraph(int regNum) {
    for (int i = 0; i < MAX_VAR; ++i) {
        int used[32] = {0};

        // 查找相邻变量使用了哪些颜色（寄存器）
        for (int j = 0; j < MAX_VAR; ++j) {
            if (interference[i][j] && varColor[j] != -1)
                used[varColor[j]] = 1;
        }

        // 分配当前变量未被使用的寄存器
        int k;
        for (k = 0; k < regNum; ++k) {
            if (!used[k]) {
                varColor[i] = k;
                break;
            }
        }

        // 无法分配寄存器，需要溢出到内存
        if (k == regNum) varColor[i] = -1;
    }
}