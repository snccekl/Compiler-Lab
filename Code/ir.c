#include "ir.h"
#include "Semantic.h"

#define SIZE 10
int lnum = 1;	//标号
int tnum = 1;	//t 临时变量
int vnum = 1;	//v 变量

InterCode *IRList; // IR表 动态数组
int IRsize;
int IRMAXSIZE;
void repr(Operand op, FILE *fp);

extern FieldList hashTable[HASH_SIZE];
extern int scope_id;
extern int current_id;
extern scope sc_table[50];

void initIRList() {
	IRList = (InterCode*)malloc(SIZE * sizeof(InterCode));
	if (IRList == NULL) {
		printf("error\n");
		return;
	}
	IRMAXSIZE = SIZE;
	IRsize = 0;

    scope_id = 0;
    scope sc;
    sc.id = 0;
    sc.parent_id = -1;
    sc.w[0] = 0;
    sc.wno =1;
    current_id = 0;
    sc_table[current_id] = sc;
}

void insertCode(InterCode ir) {
	if (IRsize >= IRMAXSIZE) {
		IRList = (InterCode*)realloc(IRList, sizeof(InterCode)*IRMAXSIZE * 2);
		IRMAXSIZE = IRMAXSIZE * 2;
	}
	IRList[IRsize] = ir;
	IRsize++;
}
void deletelastCode(){
	IRsize--;
	IRList[IRsize] = NULL;
}

void repr(Operand op, FILE *fp) {
	if (op == NULL) {
		fputs("t0	", fp);
		return;
	}
	char str[50];
	memset(str, 0, sizeof(str));
	switch (op->kind) {

	case VARIABLE_OP:
		if (op->u.value != NULL) {
			sprintf(str, "%s", op->u.value);
			fputs(str, fp);
		}
		break;
	case TEMPVAR_OP:
		sprintf(str, "temp%d", op->u.var_no);
		fputs(str, fp);
		break;
	case CONSTANT_OP:
		sprintf(str, "#%s", op->u.value);
		fputs(str, fp);
		break;
	case ADDR_OP:
		sprintf(str, "*temp%d", op->u.var_no);
		fputs(str, fp);
		break;
	case QU_ADDR_OP:
		sprintf(str, "&%s", op->u.value);
		fputs(str, fp);
		break;
	case LABEL_OP:
		sprintf(str, "label%d", op->u.label_no);
		fputs(str, fp);
		break;
	case FUNCTION_OP:
		sprintf(str, "%s", op->u.value);
		fputs(str, fp);
		break;
	}
}
void printCode(char *filename) {
	FILE *fp;
	if (strcmp(filename, "stdout") == 0) {
		fp = stdout;
	}
	else {
		fp = fopen(filename, "w");
	}
	if (fp == NULL) {
		printf("open file error!\n");
		return;
	}
	for (int i = 0; i < IRsize; i++) {
		InterCode ir = IRList[i];
		if (ir == NULL) {
			continue;
		}
		switch (ir->kind) 
		{
		case LABEL_IR:
			fputs("LABEL ", fp);
			repr(ir->operands[0], fp);
			fputs(" : ", fp);
			break;
		case FUNCTION_IR:
			fputs("FUNCTION ", fp);
			repr(ir->operands[0], fp);
			fputs(" : ", fp);
			break;
		case ASSIGN_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			break;
		case PLUS_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" + ", fp);
			repr(ir->operands[2], fp);
			break;
		case MINUS_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" - ", fp);
			repr(ir->operands[2], fp);
			break;
		case STAR_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" * ", fp);
			repr(ir->operands[2], fp);
			break;
		case DIV_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" / ", fp);
			repr(ir->operands[2], fp);
			break;
		case ADDR_IR2:
			repr(ir->operands[0], fp);
			fputs(" := &", fp);
			repr(ir->operands[1], fp);
			break;
		case ADDR_IR3:
			repr(ir->operands[0], fp);
			fputs(" := &", fp);
			repr(ir->operands[1], fp);
			fputs(" + ", fp);
			repr(ir->operands[2], fp);
			break;
		case ADDR_VALUE_IR:
			repr(ir->operands[0], fp);
			fputs(" := *", fp);
			repr(ir->operands[1], fp);
			break;
		case MEMORY_IR:
			fputs("*", fp);
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			break;
		case GOTO_IR:
			fputs("GOTO ", fp);
			repr(ir->operands[0], fp);
			break;
		case IF_GOTO_IR:
			fputs("IF ", fp);
			repr(ir->operands[0], fp);
			fputs(" ", fp);
			fputs(ir->relop, fp);
			fputs(" ", fp);
			repr(ir->operands[1], fp);
			fputs(" GOTO ", fp);
			repr(ir->operands[2], fp);
			break;
		case RETURN_IR:
			fputs("RETURN ", fp);
			repr(ir->operands[0], fp);
			break;
		case DEC_IR:
			fputs("DEC ", fp);
			repr(ir->operands[0], fp);
			char str[10];
			memset(str, 0, sizeof(str));
			sprintf(str, " %d ", ir->size);
			fputs(str, fp);
			break;
		case ARG_IR:
			fputs("ARG ", fp);
			repr(ir->operands[0], fp);
			break;
		case CALL_IR:
			repr(ir->operands[0], fp);
			fputs(" := CALL ", fp);
			repr(ir->operands[1], fp);
			break;
		case PARAM_IR:
			fputs("PARAM ", fp);
			repr(ir->operands[0], fp);
			break;
		case READ_IR:
			fputs("READ ", fp);
			repr(ir->operands[0], fp);
			break;
		case WRITE_IR:
			fputs("WRITE ", fp);
			repr(ir->operands[0], fp);
			break;
		case DEBUG_IR:
			fputs("DEBUG", fp);
			fputs(ir->operands[0]->u.value,fp);
			break;
		}
		fputs("\n", fp);
	}
	fclose(fp);
}


int getSpace(Type type) {
	if (type == NULL) {
		return 0;
	}
	if (type->kind  == ARRAY)//数组 
    {
		int size = type->u.array.size * getSpace(type->u.array.elem);

		return size;
	}
	else if(type->kind == BASIC){
		if(type->u.basic == INT_TYPE)
		{
			return 4;
		}
	}
	return 1;
}

//这个search应该和之前差不多，你看看能不能补一下
FieldList allsearch(char *name ,int flag){

}

Operand new_var() {
	Operand v = (Operand)malloc(sizeof(Operand_));
	v->kind = VARIABLE_OP;
	return v;
}

Operand new_temp(){
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = TEMPVAR_OP;
	t->u.var_no = tnum++;
	return t;
}

Operand new_label(){
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = LABEL_OP;
	t->u.label_no = lnum++;
	return t;
}

Operand new_constant(int i){
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = CONSTANT_OP;
	sprintf(t->u.value ,"%d",i);
	return t;
}

// 你自己看看吧
// void tProgram(Node *root){
//     if(root == NULL){
//         return;
//     }
//     Node* dummy;
//     dummy = root->first_son;
//     while(dummy != NULL){
//         if(!strcmp("FuncDecl" , dummy->name)){
//             tFunDec(dummy);
//         }
//         else if(!strcmp("StructDecl",dummy->name)){
//             tStructDecl(dummy);
//         }
//         else if(!strcmp("VarDecl",dummy->name)){
//             Type spec = tVardec(dummy);
            
//         }
//         dummy = dummy->follow;
//     }
// }


