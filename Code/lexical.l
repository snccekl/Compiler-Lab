%{
    #include "syntax.tab.h" 
	#include "tree.h"
    void handle_yytext(char* identification, char* yytext){
        yylval.node = createNode(0, identification,yytext);
    }
    extern int error;
%}

%option yylineno
digit   [0-9]
letter  [_a-zA-Z]
id      {letter}({letter}|{digit})*
delim   [ \t\r\n]
ws      {delim}+
relop   >|<|==|>=|<=|!=
type    int|float
int     [1-9]{digit}*|0
float   {digit}+\.{digit}+

%%
"//" {
	char c = input();
	while (c!= '\n'){
		c = input();
    }
}

"/*" {
	char pre = input(), next = input();
	while (next) {
		if(pre == '*' && next == '/') {
            break;
        }
        pre = next;
        next = input();
	}
	if (!next) {
		printf("Error type B at line %d: Illegal /*.\n", yylineno);
		error++;
	}
}
{ws}    {handle_yytext("ws",yytext);}
";"     {handle_yytext("SEMI",yytext); return SEMI;}
","     {handle_yytext("COMMA",yytext); return COMMA;}
"="     {handle_yytext("ASSIGNOP",yytext); return ASSIGNOP;}
{relop} {handle_yytext("RELOP",yytext); return RELOP;}
"+"     {handle_yytext("PLUS",yytext); return PLUS;}
"-"     {handle_yytext("MINUS",yytext); return MINUS;}
"*"     {handle_yytext("STAR",yytext); return STAR;}
"/"     {handle_yytext("DIV",yytext); return DIV;}
"&&"    {handle_yytext("AND",yytext); return AND;}
"||"    {handle_yytext("OR",yytext); return OR;}
"."     {handle_yytext("DOT",yytext); return DOT;}
"!"     {handle_yytext("NOT",yytext); return NOT;}
{type}  {handle_yytext("TYPE",yytext); return TYPE;}
"("     {handle_yytext("LP",yytext); return LP;}
")"     {handle_yytext("RP",yytext); return RP;}
"["     {handle_yytext("LB",yytext); return LB;}
"]"     {handle_yytext("RB",yytext); return RB;}
"{"     {handle_yytext("LC",yytext); return LC;}
"}"     {handle_yytext("RC",yytext); return RC;}
struct  {handle_yytext("STRUCT",yytext); return STRUCT;}
return  {handle_yytext("RETURN",yytext); return RETURN;}
if      {handle_yytext("IF",yytext); return IF;}
else    {handle_yytext("ELSE",yytext); return ELSE;}
while   {handle_yytext("WHILE",yytext);return WHILE;}
{id}    {handle_yytext("ID",yytext); return ID;}
{int}   {handle_yytext("INT",yytext); return INT;}
{float} {handle_yytext("FLOAT",yytext); return FLOAT;}
[0-9]*[.]|[.][0-9]* {printf("Error type A at Line %d: Illegal floating number \'%s\'.\n", yylineno, yytext);error++;return FLOAT;}
.       {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext); error++;} 

%%