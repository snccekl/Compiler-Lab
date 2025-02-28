#include<stdio.h>

void perror(const char *__s);
int yyrestart();
int yyparse();
int error = 0;
Node * Root = NULL;
extern void printTree();//这个函数在tree.c中定义？或者在这里定义？我不太确定
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
        printTree();//可以考虑单独写个tree.c文件?也可以就在这里把树的结构写好？我不太确定，因此所有的头文件我都没有写
    }
    return 0;
}