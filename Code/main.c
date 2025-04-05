#include <stdio.h>
#include <stdarg.h>
#include "tree.h"

void perror(const char *__s);
int yyrestart();
int yyparse();
int error = 0;


// typedef struct TreeNode{
//     char* name;
//     char* token;
//     int line;
//     Node* parent;
//     Node* first_son;
//     Node* follow;
// } Node;

struct Node * Root = NULL;
// extern void printTree();
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
        printTree(Root, 0);
    }
    return 0;
}

