%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "lex.yy.c"
    extern int yylineno;
    extern Node* Root;
    extern int error;

    void yyerror(char const *msg){
        if(strcmp(msg,"syntax error") == 0){
            printf("Error type B at Line %d: %s\n", yylineno,msg);
        }
    }
%}

%union {
    struct Node* node;
}

%token <node> INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT UMINUS
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%%

Program         : ExtDefList                    {$$ = createNode(1, "Program",""); addNode($$, 1, $1); Root = $$;}
                | error                         {error++;yyerror("error");}
                ;

ExtDefList      : ExtDef ExtDefList             {$$ = createNode(1, "ExtDefList",""); addNode($$, 2, $1, $2);}
                | /* empty */                   {$$ = NULL;}
                ;

ExtDef          : Specifier ExtDecList SEMI     {$$ = createNode(1, "ExtDef","");addNode($$, 3, $1, $2, $3);}
                | Specifier SEMI                {$$ = createNode(1, "ExtDef","");addNode($$, 2, $1, $2);}
                | Specifier FunDec CompSt       {$$ = createNode(1, "ExtDef","");addNode($$, 3, $1, $2, $3);}
                /*| Specifier error               {error++;yyerror("Syntax error.");}*/
                |error
                ;

ExtDecList      : VarDec                        {$$ = createNode(1, "ExtDecList","");addNode($$, 1, $1);}
                | VarDec COMMA ExtDecList       {$$ = createNode(1, "ExtDecList","");addNode($$, 3, $1, $2, $3);}
                ;


Specifier       : TYPE                          {$$ = createNode(1, "Specifier","");addNode($$, 1, $1);}
                | StructSpecifier               {$$ = createNode(1, "Specifier","");addNode($$, 1, $1);}
                | error
                ;

StructSpecifier : STRUCT OptTag LC DefList RC   {$$ = createNode(1, "StructSpecifier","");addNode($$, 5, $1, $2, $3, $4, $5);}
                | STRUCT Tag                    {$$ = createNode(1, "StructSpecifier","");addNode($$, 2, $1, $2);}
                ;
            
OptTag          : ID                            {$$ = createNode(1, "OptTag","");addNode($$, 1, $1);}
                | /* empty */                   {$$ = NULL;}
                ;

Tag             : ID                            {$$ = createNode(1, "Tag","");addNode($$, 1, $1);}
                ;


VarDec          : ID                            {$$ = createNode(1, "VarDec","");addNode($$, 1, $1);}    
                | VarDec LB INT RB              {$$ = createNode(1, "VarDec","");addNode($$, 4, $1, $2, $3, $4);}
                | error                         {error++;yyerror("error");}
                ;

FunDec          : ID LP VarList RP              {$$ = createNode(1, "FunDec","");addNode($$, 4, $1, $2, $3, $4);}
                | ID LP RP                      {$$ = createNode(1, "FunDec","");addNode($$, 3, $1, $2, $3);}
                ;
            
VarList         : ParamDec COMMA VarList        {$$ = createNode(1, "VarList","");addNode($$, 3, $1, $2, $3);}
                | ParamDec                      {$$ = createNode(1, "VarList","");addNode($$, 1, $1);} 
                | error                         {error++;yyerror("error");}  
                ;

ParamDec        : Specifier VarDec              {$$ = createNode(1, "ParamDec","");addNode($$, 2, $1, $2);}  
                | error                         {error++;yyerror("error");}
                ;

CompSt          : LC DefList StmtList RC        {$$ = createNode(1, "CompSt","");addNode($$, 4, $1, $2, $3, $4);}
                | error                         {error++;yyerror("error");}
                ;

StmtList        : Stmt StmtList                 {$$ = createNode(1, "StmtList","");addNode($$, 2, $1, $2);}  
                | /* empty */                   {$$ = NULL;}
                ;

Stmt            : Exp SEMI                      {$$ = createNode(1, "Stmt","");addNode($$, 2, $1, $2);}
                | CompSt                        {$$ = createNode(1, "Stmt","");addNode($$, 1, $1);}
                | RETURN Exp SEMI               {$$ = createNode(1, "Stmt","");addNode($$, 3, $1, $2, $3);} 
                | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$ = createNode(1, "Stmt","");addNode($$, 5, $1, $2, $3, $4, $5);}
                | IF LP Exp RP Stmt ELSE Stmt   {$$ = createNode(1, "Stmt","");addNode($$, 7, $1, $2, $3, $4, $5, $6, $7);}
                | IF LP Exp RP error ELSE Stmt  {error++;yyerror("Missing \";\".");}
                | WHILE LP Exp RP Stmt          {$$ = createNode(1, "Stmt","");addNode($$, 5, $1, $2, $3, $4, $5);}
                ;


DefList         : Def DefList                   {$$ = createNode(1, "DefList","");addNode($$, 2, $1, $2);}
                | /* empty */                   {$$ = NULL;}
                ;

Def             : Specifier DecList SEMI        {$$ = createNode(1, "Def","");addNode($$, 3, $1, $2, $3);}
                ;
            
DecList         : Dec                           {$$ = createNode(1, "DecList","");addNode($$, 1, $1);}
                | Dec COMMA DecList             {$$ = createNode(1, "DecList","");addNode($$, 3, $1, $2, $3);}
                ;

Dec             : VarDec                        {$$ = createNode(1, "Dec","");addNode($$, 1, $1);}
                | VarDec ASSIGNOP Exp           {$$ = createNode(1, "Dec","");addNode($$, 3, $1, $2, $3);}
                ;

Exp             : Exp ASSIGNOP Exp              {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp AND Exp                   {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp OR Exp                    {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp RELOP Exp                 {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp PLUS Exp                  {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp MINUS Exp                 {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp STAR Exp                  {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp DIV Exp                   {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | LP Exp RP                     {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | MINUS Exp %prec UMINUS        {$$=createNode(1, "Exp","");addNode($$, 2, $1, $2);}
                | NOT Exp                       {$$=createNode(1, "Exp","");addNode($$, 2, $1, $2);}
                | ID LP Args RP                 {$$=createNode(1, "Exp","");addNode($$, 4, $1, $2, $3, $4);}
                | ID LP RP                      {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | Exp LB Exp RB                 {$$=createNode(1, "Exp","");addNode($$, 4, $1, $2, $3, $4);}
                | Exp DOT ID                    {$$=createNode(1, "Exp","");addNode($$, 3, $1, $2, $3);}
                | ID                            {$$=createNode(1, "Exp","");addNode($$, 1, $1);}
                | INT                           {$$=createNode(1, "Exp","");addNode($$, 1, $1);}
                | FLOAT                         {$$=createNode(1, "Exp","");addNode($$, 1, $1);}
                | error                         {error++;yyerror("error");}
                ;
    
Args            : Exp COMMA Args                {$$=createNode(1, "Args","");addNode($$, 3, $1, $2, $3);}
                | Exp                           {$$=createNode(1, "Args","");addNode($$, 1, $1);}
                ;

%%