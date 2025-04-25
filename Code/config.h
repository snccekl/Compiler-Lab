#ifndef CONFIG_H
#define CONFIG_H

// 用于管理全局各项信息的输出
#define DEBUG_MODE 0

// 用于管理语法分析树的输出
#define PRINT_PARSE_TREE (DEBUG_MODE | 0)

// 用于AST的输出
#define PRINT_AST (DEBUG_MODE | 1)

// 用于管理语义分析的插旗
#define SEMANTIC_DEBUG_MODE (DEBUG_MODE | 1)

// 注：请只修改数值部分，且数值只可能为0或1

// 用于字符串复制
char* strdup(const char* s);
#endif