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
