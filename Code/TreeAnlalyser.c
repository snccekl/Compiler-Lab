#include "Semantic.h"

// 用于处理语义错误
// 具体用法为： CrushError(错误编号),例：未定义行为 CrushError(1, node)
void CrushError(int type, Node* node) {
    if(type == 1) {
        printf("Error type 1 at Line %d\n",node->line);
    }
    else if(type == 2) {
        printf("Error type 2 at Line %d\n",node->line);
    }
    else if(type == 3) {
        printf("Error type 3 at Line %d\n", node->line);
    }
    else if(type == 4) {
        printf("Error type 4 at Line %d\n", node->line);
    }
    else if(type == 5) {
        printf("Error type 5 at Line %d\n",node->line);
    }
    else if(type == 6) {
        printf("Error type 6 at Line %d\n",node->line);
    }
    else if(type == 7) {
        printf("Error type 7 at Line %d\n",node->line);
    }
    else if(type == 8) {
        printf("Error type 8 at Line %d\n",node->line);
    }
    else if(type == 9) {
        printf("Error type 9 at Line %d\n",node->line);
    }
    else if(type == 10) {
        printf("Error type 10 at Line %d\n",node->line);
    }
    else if(type == 11) {
        printf("Error type 11 at Line %d\n",node->line);
    }
    else if(type == 12) {
        printf("Error type 12 at Line %d\n",node->line);
    }
    else if(type == 13) {
        printf("Error type 13 at Line %d\n",node->line);
    }
    else if(type == 14) {
        printf("Error type 14 at Line %d\n",node->line);
    }
    else if(type == 15) {
        printf("Error type 15 at Line %d\n",node->line);
    }
    else if(type == 16) {
        printf("Error type 16 at Line %d\n",node->line);
    }
    else if(type == 17) {
        printf("Error type 17 at Line %d\n",node->line);
    }
    else if(type == 18) {
        printf("Error type 18 at Line %d\n",node->line);
    }
}

//Program     : ExtDefList
void Program(Node *root){
    if(root==NULL){
        return;
    }
    if(!strcmp("ExtDefList" , root->first_son->name)){
        ExtDefList(root ->first_son);
    }
}

// ExtDefList  : ExtDef ExtDefList  
//             |  /* empty */       
//             ;
void ExtDefList(Node *node){
    if(node == NULL){
        return;
    }
    if(node->num_child == 2){
        ExtDef(node->first_son);
        ExtDefList(node->first_son->follow);
    }
}

// ExtDef      : Specifier ExtDecList SEMI  
//             | Specifier SEMI             
//             | Specifier FunDec CompSt   
//             | Specifier FunDec SEMI  
void ExtDef(Node *node){
    //先确定返回值
    Type specifier = Specifier(node->first_son);

    //Specifier ExtDecList SEMI  
    if(strcmp(node->first_son->follow->name,"ExtDecList") == 0){
        ExtDecList(node->first_son->follow,specifier);
    }
    //Specifier SEMI   不用管
    
    //Specifier FunDec CompSt 
    //Specifier FunDec SEMI  
    //FunDec是函数头，CompSt表示函数体
    else if(strcmp(node->first_son->follow->name,"FunDec") == 0) {
        enter_scope();
        if(strcmp(node->first_son->follow->follow->name,"CompSt")==0){
            //printf("22");
            FunDec(node->first_son->follow,specifier,DEFIN);
            CompSt(node->first_son->follow,specifier);
        }
        //不做声明任务(3.1),故认为是定义
        else{
            FunDec(node->first_son->follow,specifier,DEFIN);
        }
        exit_scope();
    }
}

// ExtDecList  : VarDec                  
//             | VarDec COMMA ExtDecList 
//             ;
void ExtDecList(Node * node,Type spec){
    FieldList field = VarDec(node->first_son,spec);
    if(ifexist(field->name,field->scope_id) != NULL)
        printf("Error type 3 at Line %d: Redefined variable %s.\n",node->first_son->line,field->name);
    else{
        insert(field);
    }
    if(node->num_child == 3){
        ExtDecList(node->first_son->follow->follow,spec);
    }
}

// Specifier   : TYPE
//             | StructSpecifier
//             ;
Type Specifier(Node *node){
    // TYPE
    if(strcmp(node->first_son->name,"TYPE")==0){
        Type spec = (Type)malloc(sizeof(Type_));
        spec->kind = BASIC;
        if(strcmp(node->first_son->token,"float")==0)
            spec->u.basic=FLOAT_TYPE;
        else //
            spec->u.basic=INT_TYPE;
        return spec;
    }
    // StructSpecifier
    else{
        //printf("goto StructSpecifier:line %d \n",node->first_son->lineno);
        Type t = StructSpecifier(node->first_son);
        Type t2 = (Type)malloc(sizeof(Type_));
        t2->kind =STRUCTURE;
        t2->u.structure = t->u.structure;
        return t2;
    }
}

// StructSpecifier : STRUCT OptTag LC DefList RC
//                 | STRUCT Tag
//                 ;
Type StructSpecifier(Node *node)
{
    Type spec = (Type)malloc(sizeof(Type_));
    spec->kind = STRUCTURE;
    //这里注意 如果opttag为空就会是NULL 会出错
    // STRUCT Tag
    if(node->first_son->follow !=NULL && strcmp(node->first_son->follow->name ,"Tag") == 0){
        Node * Tag = node->first_son->follow;
        Node * ID = Tag->first_son;
        char *str = ID->token;
        //结构体类型
        FieldList field = search(str,2);
        if(field == NULL){
            printf("Error type 17 at Line %d: Undefined structure %s.\n",ID->line,str);
            spec->u.structure = NULL;
            return spec;
        }
        else{
            if(field->type !=NULL){
                return field->type;
            }
        }
        spec->u.structure=NULL;
        return spec;
    }

    //STRUCT (OptTag) LC DefList RC
    //OptTag为NULL应该也占一个位置
    //这里作用域在struct内
    enter_scope();
    Node * defList = node->first_son->follow->follow->follow;
    spec->u.structure = NULL;
    while(defList != NULL){
        //Def DefList
        Node *def = defList->first_son;
        // Def     : Specifier DecList SEMI
        Type t = Specifier(def->first_son);
        Node * decList = def->first_son->follow;
        // DecList : Dec                 
        //         | Dec COMMA DecList        
        //         ;
        
        while(1){
            // Dec     : VarDec               
            //         | VarDec ASSIGNOP Exp  a = 5
            //         ;
            Node * dec = decList->first_son;
            Node * varDec = dec->first_son;
            FieldList field = VarDec(varDec,t);
            if(dec->num_child != 1){
                printf("Error type 15 at Line %d: Variable %s is initialized in struct.\n", def->line, field->name);
            }
            FieldList p = spec->u.structure;
            //确保域名没有重复定义
            while(p != NULL){
                if(strcmp(p->name,field->name) == 0){
                    printf("Error type 15 at Line %d: Redefined field %s.\n",varDec->line,field->name);
                    break;
                }
                p = p->tail;
            }
            //开始定义 struct 内部
            if( p == NULL){
                if(ifexist(field->name,field->scope_id)!=NULL){
                    printf("Error type 3 at Line %d: Redefined variable %s.\n", varDec->line, field->name);          
                }
                else{
                    insert(field);
                    field->tail = spec->u.structure;
                    spec->u.structure = field;
                }

            }
            if(decList->num_child == 3){
                decList = decList->first_son->follow->follow;
            }
            else{
                break;
            }
        }
        defList = defList->first_son->follow;
    }
    exit_scope();

    //这里是结构体类型名
    if(node->first_son->follow != NULL)//OptTag 类型名
    {
        OptTag(node->first_son->follow,spec);
    }
    return spec;
}


// OptTag  : ID          
//         | /* empty */ 
//         ;
void OptTag(Node *node,Type spec){
    //结构体类型名 必须唯一
    if(node == NULL) return;
    FieldList field = (FieldList)malloc(sizeof(FieldList_));
    field->scope_id = current_id;
    field->type =spec;
    field->type->kind = STR_SPE;//这表示是类型名 必须唯一
    char *s =node->first_son->token;
    field->name = s;
    if(ifexist(field->name ,current_id) !=NULL){
        printf("Error type 16 at Line %d: Duplicated name %s.\n",node->first_son->line,field->name);
    }
    else{
        insert(field);
    }
}

// VarDec    : ID
//             | VarDec LB INT RB
//a  a[10][20]...

FieldList VarDec(Node *type,Type spec) {
    Node* first = type->first_son;
    if(strcmp(type->name, "ID") == 0) {
        FieldList field = (FieldList)malloc(sizeof(FieldList_));
        field->scope_id = current_id;
        field->type = spec;
        // field->type->kind = STR_SPE;//这表示是类型名 必须唯一
        char *s = type->first_son->token;
        field->name = s;
        return field;
    }
    else if(strcmp(type->name, "VarDec") == 0) {
        FieldList field = VarDec(first, spec);

        Node* size_node = first->follow->follow;
        int size = atoi(size_node->name);

        // if(size == 0) {
        //     CrushError(12, type);
        // }

        Type array_type = (Type)malloc(sizeof(Type_));
        array_type->kind = ARRAY;

        array_type->u.array.size = size;
        array_type->u.array.elem = field->type;

        field->type = array_type;
        return field;
    }
    return NULL;
}

// 检查函数参数与已有函数是否匹配
// 内部函数，不用写在接口处
int args_matched(FieldList first, FieldList second) {
    while(first != NULL && second != NULL) {
        if(!TypeEqual(first->type, second->type)) {
            return 0;
        }
        first = first->tail;
        second = second->tail;
    }
    if(first != NULL || second != NULL)
        return 0;
    return 1;
}

// 获取函数参数数量
// 内部函数
int GetParamNum(FieldList args) {
    int cnt = 0;
    while(args != NULL) {
        cnt++;
        args = args->tail;
    }
    return cnt;
}

// FunDec          : ID LP VarList RP
//                 | ID LP RP              
void FunDec(Node *node,Type spec,int state) {
    Node* id_node = node->first_son;
    char* func_name = id_node->token;

    FieldList func = (FieldList)malloc(sizeof(FieldList_));
    func->name = strdup(func_name);
    func->type = (Type)malloc(sizeof(Type_));
    func->scope_id = sc_table[current_id].parent_id;

    FieldList args = NULL;
    if(id_node->follow != NULL && strcmp(id_node->follow->follow->name, "VarList") == 0) {
        args = VarList(id_node->follow->follow);
    }

    FieldList existence = ifexist(func_name, func->scope_id);
    if(existence != NULL) {
        if(existence->type->kind != FUNCTION) {
            CrushError(4, node);
        }
        else if(state == DEFIN) {
            CrushError(4, node);
        }
        else if(!args_matched(existence->type->u.function.params, args)) {
            CrushError(9, node);
        }
        return ;
    }

    func->type->kind = FUNCTION;
    func->type->u.function.funcType = spec;  // 函数返回类型
    func->type->u.function.params = args;  // 解析参数列表
    func->type->u.function.paramNum = GetParamNum(args);
    func->type->u.function.lineno = node->line;

    // 插入符号表
    insert(func);
}

// VarList         : ParamDec COMMA VarList
//                 | ParamDec
FieldList VarList(Node* node) {
    Node* prs = node->first_son;
    FieldList prs_field = ParamDec(prs);

    if(prs->follow != NULL && prs->follow->follow != NULL) {
        Node* next = prs->follow->follow;
        FieldList next_field = VarList(next);

        prs_field->tail = next_field;
    }
    return prs_field;
}


// ParamDec        : Specifier VarDec
FieldList ParamDec(Node* node) {
    Type spec = Specifier(node->first_son);
    FieldList var = VarDec(node->first_son->follow, spec);
    
    // 检查参数名是否重复
    if (ifexist(var->name, current_id) != NULL) {
        // printf("Error type 3 at Line %d: Redefined parameter %s.\n", node->line, var->name);
        CrushError(3, node);
    } else {
        insert(var);  // 参数插入当前作用域（函数作用域）
    }
    return var;
}


// CompSt          : LC DefList Stmt RC                
void CompSt(Node *node,Type ftype) {
    enter_scope();

    Node* defList = node->first_son->follow;
    Node* stmtList = defList->follow;

    DefList(defList);
    Node * stmtlist =node->first_son->follow->follow;
    while(stmtlist!=NULL)
    {
        Stmt(stmtlist->first_son,ftype);
        stmtlist = stmtlist->first_son->follow;
    }

    exit_scope();
}

// Stmt    : Exp SEMI                                
//         | CompSt                                  
//         | RETURN Exp SEMI                         
//         | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE 
//         | IF LP Exp RP Stmt ELSE Stmt                        
//         | WHILE LP Exp RP Stmt                    
//         ;  
void Stmt(Node *node,Type ftype) {
    if (strcmp(node->first_son->name, "CompSt") == 0){
        CompSt(node->first_son,ftype);
    }
    else if (strcmp(node->first_son->name, "Exp") == 0){//Exp SEMI 
        Exp(node->first_son);
    }
    else if (strcmp(node->first_son->name, "RETURN") == 0){
        Type rtype = Exp(node->first_son->follow);
        if(TypeEqual(ftype,rtype)== 0){
            if(rtype != NULL)//可能有问题
                printf("Error type 8 at Line %d: Type mismatched for return.\n", node->line);
        }
    }
    //仅有int型变量才能进行逻辑运算或者作为if和while语句的条件；
    else{
        //WHILE LP Exp RP Stmt 
        //IF LP Exp RP Stmt
        Exp(node->first_son->follow->follow);
        Stmt(node->first_son->follow->follow->follow->follow,ftype);
        //IF LP Exp RP Stmt ELSE Stmt 
        if(node->num_child ==7)
            Stmt(node->first_son->follow->follow->follow->follow->follow->follow,ftype);
    }
}

// DefList         : Def DefList
//                 | /* empty */
void DefList(Node *node) {
    if(node == NULL) {
        return ;
    }
    Node* def = node->first_son;
    Node* defList = def->follow;

    Def(def);
    DefList(defList);
}

// Def             : Specifier DecList SEMI
void Def(Node *node) {
    Type spec = Specifier(node->first_son);

    Node* decList = node->first_son->follow;
    DecList(decList, spec);
}

// DecList         : Dec              
//                 | Dec COMMA DecList 
void DecList(Node *node,Type spec) {
    Node* dec = node->first_son;

    Dec(dec, spec);
    if(dec->follow != NULL) {
        Node* decList = dec->follow->follow;
        DecList(decList, spec);
    }
}

// Dec             : VarDec             
//                 | VarDec ASSIGNOP Exp
void Dec(Node *node,Type spec) {
    if(node == NULL) return;
    Node* var = node->first_son;
    FieldList varField = VarDec(var, spec);
    if(node->num_child == 3){
        // 如果在struct内部 则要报错 但我已经考虑了这种情况
        // 故而必然不在struct内部
        // 考虑类型匹配
        // 这里的类型匹配考虑的是初始化的时候

        Type right = Exp(node->first_son->follow->follow);
        if(TypeEqual(varField->type,right) == 0){
			printf("Error type 5 at Line %d: mismatch in assignment.\n",node->line);
        }
    }
    if(ifexist(varField->name,varField->scope_id)!=NULL){
        printf("Error type 3 at Line %d: Redefined variable %s.\n", node->line, varField->name);
    }
    else{
        insert(varField);
    }
}

// Exp             : Exp ASSIGNOP Exp      
//                 | Exp AND Exp           
//                 | Exp OR Exp            
//                 | Exp RELOP Exp         
//                 | Exp PLUS Exp          
//                 | Exp MINUS Exp         
//                 | Exp STAR Exp          
//                 | Exp DIV Exp           
//                 | LP Exp RP             
//                 | MINUS Exp %prec UMINUS
//                 | NOT Exp               
//                 | ID LP Args RP         
//                 | ID LP RP              
//                 | Exp LB Exp RB         
//                 | Exp DOT ID            
//                 | ID                    
//                 | INT                   
//                 | FLOAT
Type Exp(Node *node){
    if(node == NULL) return NULL;
    if (node->num_child ==3 && strcmp(node->first_son->follow->name, "ASSIGNOP") == 0){   
        Node * exp1 = node->first_son;
        Node * exp2 = node->first_son->follow->follow;
        //赋值号左边出现一个只有右值的表达式。
        //ID | Exp DOT ID  |  Exp LB Exp RB
        if(exp1->num_child == 1 && !(strcmp(exp1->first_son->name, "ID") == 0) ){
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->line);
        }
        if(exp1->num_child == 3 && !(strcmp(exp1->first_son->follow->name, "DOT") == 0) ){
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->line);
        }
        if(exp1->num_child == 4 && !(strcmp(exp1->first_son->follow->name, "LB") == 0) ){
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->line);
        }
        //赋值号两边的表达式类型不匹配。
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if(TypeEqual(t1,t2) == 0){
            //防止重复报错
            if(t1!=NULL && t2!=NULL)
			printf("Error type 5 at Line %d: mismatch in assignment\n",node->line);
            return NULL;
        }
        else{
            return t1;
        }
    }
    //Exp AND|OR|RELOP Exp
    if (node->num_child ==3 &&
       ( strcmp(node->first_son->follow->name, "AND") == 0 | strcmp(node->first_son->follow->name, "OR") == 0 
       |strcmp(node->first_son->follow->name, "RELOP") == 0 ))
    {
// 操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变
// 量相加减，或数组（或结构体）变量与数组（或结构体）变量相加减）。
        Node * exp1 = node->first_son;
        Node * exp2 = node->first_son->follow->follow;
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if(TypeEqual(t1,t2) == 0){
            if(t1!=NULL) //todo:可能有问题
			printf("Error type 7 at Line %d: mismatch in operands\n",node->line);
            return NULL;
        }
        else {
            Type t = (Type)malloc(sizeof(Type_));
            t ->kind =BASIC;
            t->u.basic=INT_TYPE;
            return t;
        }
    }
    // +-*/
    if (node->num_child ==3 &&(
(strcmp(node->first_son->follow->name, "PLUS") == 0) || (strcmp(node->first_son->follow->name, "MINUS") == 0) || (strcmp(node->first_son->follow->name, "STAR") == 0) || (strcmp(node->first_son->follow->name, "DIV") == 0))
    )
    {
        Node * exp1 = node->first_son;
        Node * exp2 = node->first_son->follow->follow;
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if (TypeEqual(t1, t2) == 0){
            printf("Error type 7 at Line %d: mismatch in operands.\n", node->line);
            return NULL;
        }
        else{
            return t1;
        }
    }
    //         | LP Exp RP         (a)
    //         | MINUS Exp         -a
    //         | NOT Exp           ~a
    if ((strcmp(node->first_son->name, "LP") == 0) || (strcmp(node->first_son->name, "MINUS") == 0) || (strcmp(node->first_son->name, "NOT") == 0) )
    {
        Node * exp1 = node->first_son->follow;
        Type t1 = Exp(exp1);
        return t1;
    }

//         | ID                a     左值
//         | INT               1
//         | FLOAT             1.0
    if(node->num_child == 1 && (strcmp(node->first_son->name, "ID") == 0) ){
        //ID
        //找变量
        FieldList field = search(node->first_son->token,0);
        if(field == NULL){
            printf("Error type 1 at Line %d: Undefined variable %s.\n",node->line, node->first_son->token);
            return NULL;
        }
        return field->type;
    }
    if(strcmp(node->first_son->name, "INT") == 0){
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = INT_TYPE;
        return t;
    }
    if(strcmp(node->first_son->name, "FLOAT") == 0){
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = FLOAT_TYPE;
        return t;
    }


    if(strcmp(node->first_son->name, "ID") == 0){
//         | ID LP Args RP     a(b)
//         | ID LP RP          a()
        //找函数名
        FieldList field = search(node->first_son->token,1);
        if(field == NULL){
            printf("Error type 2 at Line %d: Undefined function %s.\n", node->line, node->first_son->token);
            return NULL;
        }
        if(field->type->kind!= FUNCTION){
            printf("Error type 11 at Line %d: %s is not a function.\n", node->first_son->line, field->name);
            return NULL;
        }
        Type rtype = field->type;
        
        //类型9 实参与形参匹配
        Type t = (Type)malloc(sizeof(Type_));
        t->kind = FUNCTION;
        t->u.function.paramNum =0;
        t->u.function.params = NULL;
        if(strcmp(node->first_son->follow->follow->name, "Args") == 0){
        //     Args    : Exp COMMA Args  
                    // | Exp             
                    // ;
            //填充type 跟前面struct类似
            Node * args = node->first_son->follow->follow;
            while(1){
                Type p = Exp(args->first_son);
                FieldList fp = (FieldList)malloc(sizeof(FieldList_));
                fp->scope_id = current_id;
                fp->name = "temp";
                fp->type = p;
                t->u.function.paramNum++;
                fp->tail = t->u.function.params;
                t->u.function.params = fp;

                if(args->num_child == 3){
                    args= args->first_son->follow->follow;
                }
                else{
                    break;
                }
            }
        }
        t->u.function.funcType= rtype->u.function.funcType;
        if(TypeEqual(t,rtype) == 0){
            if(!(t->u.function.paramNum==0 && rtype->u.function.paramNum==0)){
                printf("Error type 9 at Line %d: Params wrong in function %s.\n", node->line, node->first_son->token);
                t->u.function.funcType=NULL;
                return NULL;
            }
            else{
                return rtype->u.function.funcType;
            }
        }
        else{
          return rtype->u.function.funcType;
        }
    }
//         | Exp LB Exp RB     a[b]  左值
    if ( node->num_child ==4 &&
        ( strcmp(node->first_son->follow->name, "LB") == 0))
    {
        //Exp LB Exp RB 
        Node * exp1 = node->first_son;
       
        Type t1 = Exp(exp1);
        if(t1 == NULL) //说明前面a不存在
        {return NULL;}
        //对非数组型变量使用“[…]”（数组访问）操作符。
        if(t1->kind != ARRAY){
            printf("Error type 10 at Line %d: %s is not an array.\n", node->line, exp1->first_son->token);
            return NULL;
        }
        Type t2 = Exp(node->first_son->follow->follow);
        if( !(t2->kind ==BASIC && t2->u.basic == INT_TYPE)){
            printf("Error type 12 at Line %d: there is not an integer in [" "].\n", node->line);
            return NULL;
        }
        return t1->u.array.elem;
    }

    //         | Exp DOT ID        a.b   左值
    if (node->num_child ==3 &&(strcmp(node->first_son->follow->name, "DOT") == 0)){
        Node * exp1 = node->first_son;
        Type t1 = Exp(exp1);
        if(t1->kind != STRUCTURE){
            //或许todo : 看这个变量是否被定义
            printf("Error type 13 at Line %d: %s is not a struct.\n", node->line,exp1->first_son->token);
            return NULL;
        }
        FieldList p = t1->u.structure;
        char * str = node->first_son->follow->follow->token; 
        while(p!=NULL){
            if(strcmp(p->name,str) == 0)
            return p->type;
            p=p->tail;
        }
        printf("Error type 14 at Line %d: Non-existent field %s.\n", node->line, node->first_son->follow->follow->token);
        return NULL;
    }
    return NULL;
}
