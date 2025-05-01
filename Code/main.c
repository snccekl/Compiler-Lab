#include <stdio.h>
#include <stdarg.h>
#include "Semantic.h"
#include "tree.h"
#include "config.h"
#include "ir.h"

void perror(const char *__s);
int yyrestart();
int yyparse();
int error = 0;

struct Node * Root = NULL;
Node* ast_root = NULL;
extern int yylineo;

int main(int argc, char** argv) {
    if(argc <=1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if(error == 0){
        initHashtable();
        
        if(PRINT_PARSE_TREE == 1) {
            printTree(Root, 0);
        }
        
        if(SEMANTIC_DEBUG_MODE == 1) {
            printf("\nstart semantic anlalyz\n");
        }

        Program(Root);

        ast_root = parseTreeToAst(Root);

        if(PRINT_AST)
            printAST(ast_root, 0, 0);

        initIRList();
        if(!has_struct) {
            tProgram(ast_root);
            printCode(argv[2]);
        }
    }
    return 0;
}

