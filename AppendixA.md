# AST 使用指南

## Exp

### 1. Exp1 op Exp2
~~~
Exp ASSIGNOP Exp      
Exp AND Exp           
Exp OR Exp            
Exp RELOP Exp         
Exp PLUS Exp          
Exp MINUS Exp         
Exp STAR Exp          
Exp DIV Exp  
~~~

转成
~~~
op
├──Exp1
└──Exp2
~~~

### 2. LP Exp RP
~~~
LP Exp RP
~~~
转成
~~~
Exp
~~~

### 3. Op Exp
~~~
MINUS Exp %prec UMINUS
NOT Exp     
~~~
转成
~~~
UnaryOp
├──Op
└──Exp
~~~

### 4. FuncCall
~~~
ID LP Args RP         
ID LP RP
~~~
转成
~~~
FuncCall
├──ID: func name
└──Args  (可选)
~~~
注：FuncCall节点自带func name和返回类型，该结构是为了统一性，但也可以严格使用search

即：
~~~
search(ID, funcCall->scope_id, funcFLag)
~~~

### 5. Exp1 LB Exp2 RB (Array)
~~~
Exp LB Exp RB
~~~
转成
~~~
ArrayAccess
├──Exp1
└──index:
   └──Exp2
~~~

### 6. Exp DOT ID
~~~
Exp DOT ID
~~~
转成
~~~
Access
├──Exp
└──ID
~~~

### 7. Single
~~~
ID                    
INT                   
FLOAT
~~~
转成
~~~
Single
~~~

### 8. Args
~~~
Args    : Exp COMMA Args  
        | Exp  
~~~
转成
~~~
Args
├──Exp1
├──Exp2
...
~~~

## Stmt

### 1. Exp SEMI
不发生变化

### 2. CompSt
参考下面的CompSt

### 3. RETURN Exp SEMI 
~~~
RETURN Exp SEMI 
~~~
转成
~~~
ReturnStmt
└──Exp
~~~

### 4. if/while
~~~
IF LP Exp RP Stmt %prec LOWER_THAN_ELSE 
IF LP Exp RP Stmt1 ELSE Stmt2
WHILE LP Exp RP Stmt  
~~~
转成
~~~
If/While
├──Exp
└──Block
   └──Stmt

If/While
├──Exp       (cond)
├──Block     (if_true)
│  └──Stmt1
└──Block     (if_false)
   └──Stmt2
~~~

注：这里的Type只是一个树节点，并不能将其等效于语义分析的Type，如果想像语义分析的Type一样请说一声，目前懒得搞了（（（

## CompSt
~~~
LC DefList Stmt RC
~~~
转成
~~~
Block
├──VarDecl1
├──VarDecl2
...
├──Stmt1
├──Stmt2
...
~~~

## VarDec
~~~
VarDec    : ID
          | VarDec LB INT RB
~~~
转成
~~~
VarDecl
├──Type
├──ID
└──ArrayDecl
   ├──Size
   └──ArrayDecl
   ...
~~~

## Struct
~~~
StructSpecifier  : STRUCT OptTag LC DefList RC
                 | STRUCT Tag
~~~
转成
~~~
StructDecl
├──ID
└──FieldList // 如果不是结构体定义则不存在该节点
   ├──Decl1
   └──Decl2
   ...
~~~

## Fucntion
~~~
FunDec     : ID LP VarList RP
           | ID LP RP 
~~~
转成
~~~
FuncDecl
├──Type
├──ID
└──ParamList // 如果存在参数
   ├──Decl1
   └──Decl2
   ...
~~~
如果存在函数体
~~~
FuncDecl
├──Type: int
├──ID: main
├──ParamList
└──Block
~~~

## Program (程序入口)
~~~
Program         : ExtDefList
~~~
转成
~~~
Program
├──Decl1
├──Decl2
...
~~~

## 例子
源码
~~~
int dummy;
int check1;
struct Node {
    int a, b, c;
    float d;
};
int check2;
int test[10][10][10];

int func(int a, int b) { return a + b; }

int main(int check3) {
    float dummy = 0.0;
    int a = 1, b, c;
    
    struct Node check4;
    {
        int dummy[10];
        dummy[0] = dummy[0] + 1;
    }
    
    check4.a = func(a, b);
    test[1][2][a + 1] = 10;
    if(a < 0)
        a = a + 1;
    else
        a = a - 1;
    
    while(a > 5) {
        a = a - 1;
    }
}
~~~
AST
~~~
Program
├──VarDecl
│  ├──Type: int
│  └──ID: dummy
├──VarDecl
│  ├──Type: int
│  └──ID: check1
├──StructDecl
│  ├──ID: Node
│  └──FieldList (Scope  1)
│     ├──VarDecl
│     │  ├──Type: int
│     │  └──ID: a
│     ├──VarDecl
│     │  ├──Type: int
│     │  └──ID: b
│     ├──VarDecl
│     │  ├──Type: int
│     │  └──ID: c
│     └──VarDecl
│        ├──Type: float
│        └──ID: d
├──VarDecl
│  ├──Type: int
│  └──ID: check2
├──VarDecl
│  ├──Type: int
│  ├──ID: test
│  └──ArrayDecl
│     ├──Size: 10
│     └──ArrayDecl
│        ├──Size: 10
│        └──ArrayDecl
│           └──Size: 10
├──FuncDecl
│  ├──Type: int
│  ├──ID: func
│  ├──ParamList
│  │  ├──VarDecl
│  │  │  ├──Type: int
│  │  │  └──ID: a
│  │  └──VarDecl
│  │     ├──Type: int
│  │     └──ID: b
│  └──Block (Scope  2)
│     └──ReturnStmt
│        └──PLUS: +
│           ├──ID: a (Type: INT)
│           └──ID: b (Type: INT)
└──FuncDecl
   ├──Type: int
   ├──ID: main
   ├──ParamList
   │  └──VarDecl
   │     ├──Type: int
   │     └──ID: check3
   └──Block (Scope  3)
      ├──VarDecl
      │  ├──Type: float
      │  ├──ID: dummy
      │  └──Init
      │     └──FLOAT: 0.0
      ├──VarDecl
      │  ├──Type: int
      │  ├──ID: a
      │  └──Init
      │     └──INT: 1
      ├──VarDecl
      │  ├──Type: int
      │  └──ID: b
      ├──VarDecl
      │  ├──Type: int
      │  └──ID: c
      ├──VarDecl
      │  ├──StructDecl
      │  │  └──ID: Node
      │  └──ID: check4
      ├──Block (Scope  4)
      │  ├──VarDecl
      │  │  ├──Type: int
      │  │  ├──ID: dummy
      │  │  └──ArrayDecl
      │  │     └──Size: 10
      │  └──ASSIGNOP: =
      │     ├──ArrayAccess
      │     │  ├──ID: dummy (Type: ARRAY)
      │     │  └──Index
      │     │     └──INT: 0
      │     └──PLUS: +
      │        ├──ArrayAccess
      │        │  ├──ID: dummy (Type: ARRAY)
      │        │  └──Index
      │        │     └──INT: 0
      │        └──INT: 1
      ├──ASSIGNOP: =
      │  ├──Access
      │  │  ├──ID: check4 (Type: STRUCT)
      │  │  └──ID: a
      │  └──FuncCall: func (Type: INT)
      │     ├──ID: func
      │     └──Args
      │        ├──ID: a (Type: INT)
      │        └──ID: b (Type: INT)
      ├──ASSIGNOP: =
      │  ├──ArrayAccess
      │  │  ├──ArrayAccess
      │  │  │  ├──ArrayAccess
      │  │  │  │  ├──ID: test (Type: ARRAY)
      │  │  │  │  └──Index
      │  │  │  │     └──INT: 1
      │  │  │  └──Index
      │  │  │     └──INT: 2
      │  │  └──Index
      │  │     └──PLUS: +
      │  │        ├──ID: a (Type: INT)
      │  │        └──INT: 1
      │  └──INT: 10
      ├──If
      │  ├──RELOP: <
      │  │  ├──ID: a (Type: INT)
      │  │  └──INT: 0
      │  ├──Block (Scope  3)
      │  │  └──ASSIGNOP: =
      │  │     ├──ID: a (Type: INT)
      │  │     └──PLUS: +
      │  │        ├──ID: a (Type: INT)
      │  │        └──INT: 1
      │  └──Block (Scope  3)
      │     └──ASSIGNOP: =
      │        ├──ID: a (Type: INT)
      │        └──MINUS: -
      │           ├──ID: a (Type: INT)
      │           └──INT: 1
      └──While
         ├──RELOP: >
         │  ├──ID: a (Type: INT)
         │  └──INT: 5
         └──Block (Scope  5)
            └──ASSIGNOP: =
               ├──ID: a (Type: INT)
               └──MINUS: -
                  ├──ID: a (Type: INT)
                  └──INT: 1
~~~

例子有点复杂可能得细看（）