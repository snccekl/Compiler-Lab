#include "Semantic.h" 

FieldList hashTable[HASH_SIZE];
int scope_id = 0;
int current_id = 0;
scope sc_table[50];

//散列函数
//代码第7行的常数（0x3fff）确定了符号表的大小（即16384）
unsigned int hash_pjw(char *name){
	unsigned int val = 0, i;
	for(;*name;++name){
		val = (val << 2) + *name;
		if(i=val & ~0x3fff){
			val = (val ^ (i>>12)) & 0x3fff;
		}
		return val % HASH_SIZE;
	}
}

void initHashtable(){
	for(int i=0; i<HASH_SIZE; i++){
		hashTable[i] = NULL;
	}
    scope sc;
    sc.id = 0;
    sc.parent_id = -1;//表示自己是最外层的
    sc.w[0] = 0;
    sc.wno =1;
    current_id = 0;
    sc_table[current_id] = sc;
}
void enter_scope(){
    scope_id++;  //2
    scope sc;
    sc.id = scope_id; //sc.id = 2
    sc.parent_id = current_id;//sc.parent_id = 0
    current_id = scope_id;     // current_id = 2 
    sc.wno = sc_table[sc.parent_id].wno + 1; //sc.wno = sc_table[0].wno +1
    for(int i=0;i<sc.wno-1;i++)
    {
        sc.w[i] = sc_table[sc.parent_id].w[i];
    }
    sc.w[sc.wno-1] = sc.id; 

    sc_table[current_id] = sc;

}

void exit_scope(){
    scope sc = sc_table[current_id];
    if(current_id == 0 ) {
        printf("scope error");
    }
    current_id = sc.parent_id;
}

int insert(FieldList f){
	if(f==NULL || f->name == NULL)
		return 0;
	unsigned int key;
	key = hash_pjw(f->name);
    if(f->type->kind != FUNCTION){
        while(1){
            if(hashTable[key] == NULL){
                hashTable[key] = f;
                return 1;
            }
            key = (++key)%HASH_SIZE;
        }
    }
    else{
        while(1){
            if(hashTable[key] == NULL){
                hashTable[key] = f;
                return 1;
            }
            if(strcmp(hashTable[key]->name,f->name)==0){
                    //这里判断除了DEFIN 其他其实是多余的
                if(TypeEqual(hashTable[key]->type,f->type)==1  
                    && hashTable[key]->type->u.function.state == DECLA
                    && f->type->u.function.state == DEFIN)
                {
                    hashTable[key] = f;
                    return 1;
                }   
            }
            key = (++key)%HASH_SIZE;
        }

    }
	return 0;
}

FieldList search(char *name
,int flag// flag=1:function flag =2: 结构体 flag=0:变量 
)
{
	if(name == NULL){
		return NULL;
	}
	unsigned int key;
    key = hash_pjw(name);
	FieldList p=hashTable[key];
	while(p!=NULL){
		if(strcmp(name,p->name)==0){
            scope sc = sc_table[current_id];
            //从内层往外层找
            for(int i=sc.wno-1;i>=0;i--){
                if(p->scope_id == sc.w[i]){
                    if(flag != 2 && p->type->kind == STR_SPE){
                        return NULL;//与结构类型重名是不行的
                    }
                    //应该是直接返回？
                    // if(flag == 1 && p->type->kind == FUNCTION)
                    // return p;
                    // if(flag == 0 && p->type->kind == BASIC)
                    return p;

                }
            }
		}
		key=(++key)%HASH_SIZE;
		p=hashTable[key];
	}
	return NULL;
}

FieldList ifexist(char *name,int id){
	if(name == NULL){
		return NULL;
	}
	unsigned int key;
    key = hash_pjw(name);
	FieldList p=hashTable[key];
	while(p!=NULL){
		if(strcmp(name,p->name)==0)
        {
           // printf("debug name:%s p:%d id:%d\n",name,p->scope_id,id);
            if(p->scope_id == id || p->type->kind == STR_SPE)//与结构类型重名不行
            {
                return p;
            }
		}
		key=(++key)%HASH_SIZE;
		p=hashTable[key];
	}
	return NULL;
}


void printSymbol(){
    printf("-------------\n");
	for(int i=0;i<HASH_SIZE;i++)
    {
		if(hashTable[i]!=NULL)printf("%d %s\n",hashTable[i]->type->kind,hashTable[i]->name);
    }
    printf("-------------\n");

}

int TypeEqual(Type t1,Type t2){
	if((t1==NULL)||(t2==NULL)) return 0;
	if(t1->kind != t2->kind) return 0;
    if(t1->kind == BASIC){
        return (t1->u.basic == t2->u.basic);
    }
    if(t1->kind == ARRAY){
        return (TypeEqual(t1->u.array.elem,t2->u.array.elem));
    }
    if(t1->kind == STRUCTURE || t1->kind == STR_SPE){
        FieldList p1 = t1->u.structure;
        FieldList p2 = t2->u.structure;
        return strcmp(p1->name,p2->name) == 0;
        
    }
    if(t1 ->kind ==FUNCTION){
        //参数类型和个数相等
        if(t1->u.function.paramNum != t2->u.function.paramNum) return 0;
        if(TypeEqual(t1->u.function.funcType,t2->u.function.funcType) == 0) return 0;

        FieldList p1 = t1->u.function.params;
        FieldList p2 = t2->u.function.params;
        for(int i = 0; i<t1->u.function.paramNum;i++)
        {
            if(TypeEqual(p1->type,p2->type) == 0) return 0;
            p1 = p1->tail; p2 = p2->tail;
        }
        return 1;
    }
    printf("debug\n");
    return 0;
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
