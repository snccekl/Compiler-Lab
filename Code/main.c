#include<stdio.h>

void perror(const char *__s);
int yyrestart();
int yyparse();
int error = 0;
Node * Root = NULL;
extern void printTree();
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
        printTree();
    }
    return 0;
}

//API
Node* createNode(char* name,char * yytext){

}
//这个函数会接受多个参数，为 1(ChildNUm) + 1(parent) + ChildNum(子节点数量)
void addNode(int ChildNum, Node* parent, ...){

}

void printTree()//是否需要参数由你决定
