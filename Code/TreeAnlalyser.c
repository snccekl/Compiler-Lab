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
    /*
    如果把孩子节点弄成数组表述，fist_son == child[0]first_son->follow == child[1]?
    如果是，那不需要提醒我更改，否则请更改，谢谢。
    */
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
        //不做声明任务(3.1),故直接报错
        else{
            printf("Error type B at Line 6: Incomplete definition of function");
            //FunDec(node->first_son->follow,specifier,DECLA);
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
        //printf("goto StructSpecifier:line %d \n",node->child[0]->lineno);
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

        if(size == 0) {
            CrushError(12, type);
        }

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
    char* func_name = id_node->name;
    
    FieldList args = NULL;
    if(id_node->follow != NULL && strcmp(id_node->follow->follow->name, "VarList") == 0) {
        args = VarList(id_node->follow->follow);
    }


    FieldList existence = ifexist(func_name, current_id);
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

    FieldList func = (FieldList)malloc(sizeof(FieldList_));
    func->name = strdup(func_name);
    func->type = (Type)malloc(sizeof(Type_));
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


// CompSt          : LC DefList StmtList RC                
void CompSt(Node *node,Type ftype) {
    enter_scope();

    Node* defList = node->first_son->follow;
    Node* stmtList = defList->follow;

    DefList(defList);
    StmtList(stmtList);

    exit_scope();
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
    DecList(decList, spec, DEFIN);
}

// DecList         : Dec              
//                 | Dec COMMA DecList 
void DecList(Node *node, Type spec, int state) {
    Node* dec = node->first_son;

    Dec(dec, spec, state);
    if(dec->follow != NULL) {
        Node* decList = dec->follow->follow;
        DecList(decList, spec, state);
    }
}

// Dec             : VarDec             
//                 | VarDec ASSIGNOP Exp
void Dec(Node *node, Type spec, int state) {
    Node* var = node->first_son;
    FieldList varField = VarDec(var, spec);

    
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
Type Exp(Node *root);

// Args            : Exp COMMA Args
//                 | Exp           
