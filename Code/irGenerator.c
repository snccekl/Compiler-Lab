#include "ir.h"
int tmp_num = 1;	//t 临时变量
// 你自己看看吧
void tProgram(Node *root) {
    if(root == NULL){
        return;
    }
    Node* dummy;
    dummy = root->first_son;
    while(dummy != NULL){
        if(!strcmp("FuncDecl" , dummy->name)){
            tFuncDecl(dummy);
        }
        else if(!strcmp("StructDecl",dummy->name)){
            tStructDecl(dummy);
        }
        else if(!strcmp("VarDecl",dummy->name)){
            tVarDecl(dummy);
            
        }
        dummy = dummy->follow;
    }
}

void tFuncDecl(Node* func) {
    // 初始化func_op
    Operand func_op = (Operand)malloc(sizeof(Operand_));
    func_op->kind = FUNCTION_OP;
    
    int scope_id = func->scope_id;
    Node* ID = func->first_son->follow;
    FieldList func_field = search(ID->token, 2, scope_id);
    strcpy(func_op->u.value, ID->token);
    // func->type = func_field->type;
    // 生成FUNCTION_IR, 这里的size怎么处理看一看 (当然也可能不处理)
    InterCode func_ir = (InterCode)malloc(sizeof(InterCode_));
    func_ir->kind = FUNCTION_IR;
    func_ir->operands[0] = func_op;
    insertCode(func_ir);

    // 处理参数和语法块(如果有)
    Node* prs = ID;
    while(prs != NULL) {
        // 如果有参数
        if(!strcmp(prs->name, "ParamList"))
            tParamList(prs);

        // 如果有语法块
        else if(!strcmp(prs->name, "Block"))
            tBlock(prs);
        prs = prs->follow;
    }
}

void tStructDecl(Node* structDecl) {
    // do nothing
}

Operand tVarDecl(Node* varDecl) {
    // 获取变量的各种属性
    int scope_id = varDecl->scope_id;
    Node* ID = varDecl->first_son->follow;
    FieldList field = search(ID->token, 0, scope_id);
    Type type = field->type;

    // 生成变量对应的operand
    Operand var = new_var();
    strcpy(var->u.value, ID->token);

    // 如果是通过函数参数进来的，直接返回即可
    if(!strcmp(varDecl->parent->name, "ParamList")) {
        return var;
    }

    Node* prs = ID->follow;

    // 处理数组和赋值
    while(prs != NULL) {

        // 处理数组
        if(!strcmp(prs->name, "ArrayDecl")) {
            tArrayDecl(prs, var);
        }

        // 处理赋值
        if(!strcmp(prs->name, "Init")) {
            tInit(prs, var);
        }
        prs = prs->follow;
    }
    return var;
}

// 用于处理数组定义的，请不要在数组调用的时候用，节点名字不一样的
void tArrayDecl(Node* arrayDecl, Operand var) {
    // 获取数组大小
    int size = 4;
    Node* prs = arrayDecl;
    while(prs != NULL) {
        prs = prs->first_son;
        size *= atoi(prs->token);
        prs = prs->follow;
    }

    // 生成Der ir
    InterCode dec_ir = (InterCode)malloc(sizeof(InterCode_));
    dec_ir->kind = DEC_IR;
    dec_ir->operands[0] = var;
    dec_ir->size = size;
    insertCode(dec_ir);
}

// 用于处理变量定义时赋值
void tInit(Node* init, Operand var) {
    // 先得到右值
    Operand assign_var = new_temp();
    tExp(init->first_son,assign_var);

    InterCode assign_ir = (InterCode)malloc(sizeof(InterCode_));
    assign_ir->kind = ASSIGN_IR;
    assign_ir->operands[0] = var;
    assign_ir->operands[1] = assign_var;
    insertCode(assign_ir);
}

void tParamList(Node* paramList) {
    Node* Param = paramList->first_son;
    while(Param != NULL) {
        if(!strcmp(Param->name, "VarDecl")) {
            // 获取参数
            Operand param = tVarDecl(Param);

            // 生成PARAM_IR
            InterCode param_ir = (InterCode)malloc(sizeof(InterCode_));
            param_ir->kind = PARAM_IR;
            param_ir->operands[0] = param;
            insertCode(param_ir);
        }
        Param = Param->follow;
    }
}

void tBlock(Node* block) {
    Node* prs = block->first_son;
    while(prs != NULL) {
        if(!strcmp(prs->name, "VarDecl"))
            tVarDecl(prs);
        else if(!strcmp(prs->name, "StructDecl"))
            tStructDecl(prs);
        else
            tStmt(prs);
        prs = prs->follow;
    }
}

void tStmt(Node* stmt) {
    // 处理代码块
    if(!strcmp(stmt->name, "Block")) {
        tBlock(stmt);
    }

    // 处理返回语句
    else if(!strcmp(stmt->name, "ReturnStmt")) {
        Operand exp = new_temp();
        tExp(stmt->first_son,exp);
        //Operand exp = tExp(stmt->first_son);
        InterCode return_ir = (InterCode)malloc(sizeof(InterCode_));
        return_ir->kind = RETURN_IR;
        return_ir->operands[0] = exp;
        insertCode(return_ir);
    }

    // 处理if语句
    else if(!strcmp(stmt->name, "If")) {
        // 生成label1
        Operand label1 = new_label();
        InterCode label1_ir = (InterCode)malloc(sizeof(InterCode_));
        label1_ir->kind = LABEL_IR;
        label1_ir->operands[0] = label1;

        // 生成label2
        Operand label2 = new_label();
        InterCode label2_ir = (InterCode)malloc(sizeof(InterCode_));
        label2_ir->kind = LABEL_IR;
        label2_ir->operands[0] = label2;
        
        Node* exp = stmt->first_son;
        Node* stmt1 = exp->follow;

        // 插入ir
        tCond(exp, label1, label2);
        insertCode(label1_ir);
        tStmt(stmt1);
        

        // 如果存在else语句
        if(stmt1->follow != NULL) {
            Node* stmt2 = stmt1->follow;

            // 生成label3
            Operand label3 = new_label();
            InterCode label3_ir = (InterCode)malloc(sizeof(InterCode_));
            label3_ir->kind = LABEL_IR;
            label3_ir->operands[0] = label3;

            // 生成GOTO语句
            InterCode goto_ir = (InterCode)malloc(sizeof(InterCode_));
            goto_ir->kind = GOTO_IR;
            goto_ir->operands[0] = label3;

            // 插入IR
            insertCode(goto_ir);
            insertCode(label2_ir);
            tStmt(stmt2);
            insertCode(label3_ir);
        }
        else
        insertCode(label2_ir);

    }

    else if(!strcmp(stmt->name, "While")) {
        // 生成label1
        Operand label1 = new_label();
        InterCode label1_ir = (InterCode)malloc(sizeof(InterCode_));
        label1_ir->kind = LABEL_IR;
        label1_ir->operands[0] = label1;

        // 生成label2
        Operand label2 = new_label();
        InterCode label2_ir = (InterCode)malloc(sizeof(InterCode_));
        label2_ir->kind = LABEL_IR;
        label2_ir->operands[0] = label2;

        // 生成label3
        Operand label3 = new_label();
        InterCode label3_ir = (InterCode)malloc(sizeof(InterCode_));
        label3_ir->kind = LABEL_IR;
        label3_ir->operands[0] = label3;

        // 生成goto_ir
        InterCode goto_ir = (InterCode)malloc(sizeof(InterCode_));
        goto_ir->kind = GOTO_IR;
        goto_ir->operands[0] = label1;

        // 插入ir
        Node* cond = stmt->first_son;
        Node* stmt1 = cond->follow;
        
        insertCode(label1_ir);
        tCond(cond, label2, label3);
        insertCode(label2_ir);
        tStmt(stmt1);
        insertCode(goto_ir);
        insertCode(label3_ir);
    }
    else {
        tExp(stmt,NULL);
    }
}


void tCond(Node* node, Operand label_true, Operand label_false) {
    // TODO
        //Exp1 RELOP Exp2
        
        // t1 = new_temp()
        // t2 = new_temp()
        // code1 = translate_Exp(Exp1, sym_table, t1)
        // code2 = translate_Exp(Exp2, sym_table, t2)
        // op = get_relop(RELOP);
        // code3 = [IF t1 op t2 GOTO label_true]
        // return code1 + code2 + code3 + [GOTO label_false]
        if(strcmp(node->name, "RELOP") == 0){
            Operand t1 = new_temp();
            Operand t2 = new_temp();
            tExp(node->first_son,t1);//code1
            tExp(node->first_son->follow,t2);//code2
            char * op = node->token;
            InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
            code3->kind = IF_GOTO_IR;
            code3->operands[0] = t1;
            code3->operands[1] = t2;
            code3->operands[2] = label_true;
            strcpy(code3->relop,op);
            insertCode(code3);
    
            InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
            code4->kind = GOTO_IR;
            code4->operands[0] = label_false;
            insertCode(code4);
        }
        //NOT Exp1
        //translate_Cond(Exp1, label_false, label_true, sym_table)
        else if (strcmp(node->first_son->name, "NOT") == 0){
            Node* exp1 = node->first_son->follow;
            tCond(exp1,label_false,label_true);
        }
        //Exp1 AND Exp2
        // label1 = new_label()
        // code1 = translate_Cond(Exp1, label1, label_false, sym_table)
        // code2 = translate_Cond(Exp2, label_true, label_false, sym_table)
        // return code1 + [LABEL label1] + code2
        else if(strcmp(node->name, "AND") == 0){
            Operand label1 = new_label();
            tCond(node->first_son,label1,label_false);
            InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
            code3->kind = LABEL_IR;
            code3->operands[0] = label1;
            insertCode(code3);
            tCond(node->first_son->follow,label_true,label_false);
        }
        //Exp1 OR Exp2
        // label1 = new_label()
        // code1 = translate_Cond(Exp1, label_true, label1, sym_table)
        // code2 = translate_Cond(Exp2, label_true, label_false, sym_table)
        // return code1 + [LABEL label1] + code2
        else if(strcmp(node->name, "OR") == 0){
            Operand label1 = new_label();
            tCond(node->first_son,label_true,label1);
            InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
            code3->kind = LABEL_IR;
            code3->operands[0] = label1;
            insertCode(code3);
            tCond(node->first_son->follow,label_true,label_false);
        }
        else{
            // t1 = new_temp()
            // code1 = translate_Exp(Exp, sym_table, t1)
            // code2 = [IF t1 != #0 GOTO label_true]
            // return code1 + code2 + [GOTO label_false]
            Operand t1 = new_temp();
            tExp(node->first_son,t1);
            InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
            code2->kind = IF_GOTO_IR;
            code2->operands[0] = t1;
            strcpy(code2->relop ,"!=");
            //#0
            Operand t2 = (Operand)malloc(sizeof(Operand_));
            t2->kind = CONSTANT_OP;
            strcpy(t2->u.value ,"0");
            code2->operands[1] = t2;
            code2->operands[2] = label_true;
            insertCode(code2);
            InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
            code3->kind = GOTO_IR;
            code3->operands[0] = label_false;
            insertCode(code3);
        }
}

void tExp(Node* node, Operand place) {
    // TODO
	if(node == NULL) return;
    //Exp ASSIGNOP EXP
	//Exp1 ：ID | Exp DOT ID  |  Exp LB Exp RB
    // variable = lookup(sym_table, Exp1.ID)
    // t1 = new_temp()
    // code1 = translate_Exp(Exp2, sym_table, t1)
    // code2 = [variable.name := t1] +4 [place := variable.name]
    // return code1 + code2
    if (strcmp(node->name, "ASSIGNOP") == 0){   
		if(strcmp(node->first_son->name, "ID") == 0){
			FieldList f = search(node->first_son->token,0,node->first_son->scope_id);
			Operand right = new_temp();
			tExp(node->first_son->follow,right);
			Operand left = (Operand)malloc(sizeof(Operand_));
			left->kind = VARIABLE_OP;
			strcpy(left->u.value,f->name);

			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = ASSIGN_IR;
			code2->operands[0] = left;
			code2->operands[1] = right;
			insertCode(code2);

			if(place != NULL){
				InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
				code3->kind = ASSIGN_IR;
				code3->operands[0] = place;
				code3->operands[1] = right;
				insertCode(code3);
			}
			return;
		}
        //Exp DOT ID
		else if(strcmp(node->first_son->name, "StructDecl") == 0){ 
			// 无结构体
		}
        //Exp LB Exp RB
		else if (strcmp(node->first_son->name, "ArrayAccess") == 0){
			Operand left = new_temp();
			tExp(node->first_son,left);
			Operand right = new_temp();
			tExp(node->first_son->follow,right);

			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = ASSIGN_IR;
			code2->operands[0] = left;
			code2->operands[1] = right; 
			insertCode(code2);
			if(place != NULL){
				InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
				code3->kind = ASSIGN_IR;
				code3->operands[0] = place;    //*x= y
				code3->operands[1] = right;
				insertCode(code3);
			}
		}
    }
    //Exp AND|OR|RELOP Exp
    if (( strcmp(node->name, "AND") == 0 | strcmp(node->name, "OR") == 0 
       |strcmp(node->name, "RELOP") == 0 )){
        // label1 = new_label()
        // label2 = new_label()
        // code0 = [place := #0]
        // code1 = translate_Cond(Exp, label1, label2, sym_table)
        // code2 = [LABEL label1] + [place := #1]
        // return code0 + code1 + code2 + [LABEL label2]
		Operand label1 = new_label();
		Operand label2 = new_label();
		InterCode code0 = (InterCode)malloc(sizeof(InterCode_));
		code0->kind = ASSIGN_IR;
		code0->operands[0] = place;
		code0->operands[1] = new_constant(0);
		insertCode(code0);
		tCond(node,label1,label2);
		//label1
		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);
		//place := #1place := #1
		InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
		code2->kind = ASSIGN_IR;
		code2->operands[0] = place;
		code2->operands[1] = new_constant(1);
		insertCode(code2);
		//label2
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);
		return;

    }
    // +-*/
    //         | Exp PLUS Exp      a+b
    //         | Exp MINUS Exp     a-b
    //         | Exp STAR Exp      a*b
    //         | Exp DIV Exp       a/b
    if (((strcmp(node->name, "PLUS") == 0) || (strcmp(node->name, "MINUS") == 0) || (strcmp(node->name, "STAR") == 0) || (strcmp(node->name, "DIV") == 0))){
		Node *Exp1 = node->first_son;
		Node *Exp2 = node->first_son->follow;

        // t1 = new_temp()
        // t2 = new_temp()
        // code1 = translate_Exp(Exp1, sym_table, t1)
        // code2 = translate_Exp(Exp2, sym_table, t2)
        // code3 = [place := t1 + t2]
        // return code1 + code2 + code3
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		tExp(Exp1,t1);
		tExp(Exp2,t2);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		if(strcmp(node->name, "PLUS") == 0)
			code3->kind = PLUS_IR;
		else if(strcmp(node->name, "MINUS") == 0)
			code3->kind = MINUS_IR;
		else if(strcmp(node->name, "STAR") == 0)
			code3->kind = STAR_IR;
		else 
			code3->kind = DIV_IR;
		code3->operands[0] = place;
		code3->operands[1] = t1;
		code3->operands[2] = t2;
		insertCode(code3);

		return;
    }
    // 这里不知道这个(a)的处理对不对
    //         | LP Exp RP         (a)
    //         | MINUS Exp         -a
    //         | NOT Exp           ~a
    if (!strcmp(node->name, "UnaryOp")){
        Node* Op = node->first_son;
		if(strcmp(Op->token, "NOT") == 0){
            Operand label1 = new_label();
            Operand label2 = new_label();
            InterCode code0 = (InterCode)malloc(sizeof(InterCode_));
            code0->kind = ASSIGN_IR;
            code0->operands[0] = place;
            code0->operands[1] = new_constant(0);
            insertCode(code0);
            tCond(node,label1,label2);
            //label1
            InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
            l1->kind = LABEL_IR;
            l1->operands[0] = label1;
            insertCode(l1);
            //place := #1place := #1
            InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
            code2->kind = ASSIGN_IR;
            code2->operands[0] = place;
            code2->operands[1] = new_constant(1);
            insertCode(code2);
            //label2
            InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
            l2->kind = LABEL_IR;
            l2->operands[0] = label2;
            insertCode(l2);
            return;
		}
		else if(strcmp(Op->token, "MINUS") == 0 || strcmp(Op->token, "-") == 0){
            // t1 = new_temp()
            // code1 = translate_Exp(Exp1, sym_table, t1)
            // code2 = [place := #0 - t1]
            // return code1 + code2
			Operand t1 = new_temp();
			tExp(node->first_son->follow,t1);
			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = MINUS_IR;
			code2->operands[0] = place;
			code2->operands[1] = new_constant(0);
			code2->operands[2] = t1;
			insertCode(code2);
		}
		return;
    }

    //         | ID                a     左值
    //         | INT               1
    //         | FLOAT             1.0
    if(strcmp(node->name, "ID") == 0){
        //ID
        //找变量 不会增加中间代码 只是填充内容然后让外面的增加
		FieldList f = search(node->token,0,node->scope_id);
        // if(f->type->kind == ARRAY) {
        //     printf("name: %s", f->name);
            
        //     Type prs = f->type;
        //     while(prs != NULL) {
        //         if(prs->kind == ARRAY)
        //             printf("[%d]", prs->u.array.size);
        //         else
        //             break;
        //         prs = prs->u.array.elem;
        //     }
        //     printf("\n");
        // }

		if (place != NULL) {
            place->kind = VARIABLE_OP;
            place->type = f->type;//满足(f->type->kind == ARRAY)   就要赋值type 一起赋值了
            strcpy(place->u.value, node->token);
		}
		return;
    }
    //INT
    if(strcmp(node->name, "INT") == 0){
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = INT_TYPE;

		if (place != NULL) {
			InterCode intIR = (InterCode)malloc(sizeof(InterCode_));
			intIR->kind = ASSIGN_IR;
			Operand intOp = (Operand)malloc(sizeof(Operand_));
			intOp->kind = CONSTANT_OP;
			strcpy(intOp->u.value, node->token);
			intIR->operands[1] = intOp;
			place->kind = TEMPVAR_OP;
			
            place->u.var_no = tmp_num++;

			intIR->operands[0] = place;
			insertCode(intIR);
		}
		return;
    }
    if(strcmp(node->name, "FuncCall") == 0){
        //         | ID LP Args RP     a(b) // 函数调用
        //         | ID LP RP          a()
        //找函数名
        FieldList field = search(node->first_son->token,1,node->first_son->scope_id);
        Type rtype = field->type;
		if (node->first_son->follow == NULL) {
            // function = lookup(sym_table, ID)
            // if (function.name == “read”) return [READ place]
            // return [place := CALL function.name]
			if (strcmp("read", node->first_son->token) == 0) {
				if (place != NULL) {
					InterCode readIR = (InterCode)malloc(sizeof(InterCode_));
					readIR->kind = READ_IR;
					place->kind = TEMPVAR_OP;
					place->u.var_no = tmp_num++;
					readIR->operands[0] = place;
					insertCode(readIR);
				}
			}
			else {
				Operand funcOp = (Operand)malloc(sizeof(Operand_));
				funcOp->kind = FUNCTION_OP;
				strcpy(funcOp->u.value, node->first_son->token);
				InterCode callIR = (InterCode)malloc(sizeof(InterCode_));
				callIR->kind = CALL_IR;
				callIR->operands[0] = place;
				callIR->operands[1] = funcOp;
				place->kind = TEMPVAR_OP;
				place->u.var_no = tmp_num++;
				insertCode(callIR);
			}
		}
        else{
			if (strcmp("write", node->first_son->token) == 0) {
				Operand argOp = (Operand)malloc(sizeof(Operand_));
				//只有一个参数
				Node *exp = node->first_son->follow;//Args -> exp
                if (strcmp(exp->first_son->name, "INT") == 0) { //code1
					tExp(exp, NULL);
					argOp->kind = CONSTANT_OP;
					sprintf(argOp->u.value, "%s", exp->first_son->token);
				}
				else {
					argOp->kind = TEMPVAR_OP;
                    exp = exp->first_son;
					tExp(exp, argOp);
				}
				InterCode writeIR = (InterCode)malloc(sizeof(InterCode_));
				writeIR->kind = WRITE_IR;
				writeIR->operands[0] = argOp;

				insertCode(writeIR);//write arg_list[1]

				if(place != NULL)//write 返回0
				{
					Operand t = new_constant(0);
					InterCode pl0 = (InterCode)malloc(sizeof(InterCode_));
					pl0->kind = ASSIGN_IR;
					pl0->operands[0] = t;
					insertCode(pl0);
				}
			}
			else{
                Node * args = node->first_son->follow;
				Operand* argslist = (Operand*)malloc(50* sizeof(Operand) );
				int i =0;
				while(1){	
					Operand t1 = new_temp();
					tExp(args->first_son,t1);
					argslist[i++] = t1; 
					if(args->first_son->follow != NULL)
					{
						args = args->first_son->follow;
					}
					else{
						break;
					}
				}
				for(int j=0;j<i;j++){
					InterCode code2 =(InterCode)malloc(sizeof(InterCode_));
					code2->kind = ARG_IR;
					code2->operands[0]=argslist[j];
					if(argslist[j]->kind ==ADDR_OP)//todo
					{
						argslist[j]->kind = TEMPVAR_OP;
					}
					insertCode(code2);
				}

				free(argslist);
				argslist = NULL;
				Operand funcOp = (Operand)malloc(sizeof(Operand_));
				funcOp->kind = FUNCTION_OP;
				strcpy(funcOp->u.value, node->first_son->token);

				InterCode callIR = (InterCode)malloc(sizeof(InterCode_));
				callIR->kind = CALL_IR;
				place->kind = TEMPVAR_OP;
				place->u.var_no = tmp_num++;
				callIR->operands[0] = place;
				callIR->operands[1] = funcOp;
				insertCode(callIR);
			}

        }
		return;
    }
	//         | Exp LB Exp RB     a[b]  左值
	//(bodies[o_cnt].points[i_cnt]).x 
    if ( strcmp(node->name, "ArrayAccess") == 0){
		//t1 数组首地址 最里层是ID t2 整型index
        Operand t1 = new_temp();
		tExp(node->first_son,t1);//code1
        
        Operand t2 = new_temp();
		tExp(node->first_son->follow->first_son,t2);//code2
		
        Operand t3 = new_temp();
		int size = getSpace(t1->type->u.array.elem);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = STAR_IR;
		code3->operands[0] = t3;
		code3->operands[1] = t2;
		code3->operands[2] = new_constant(size);
		insertCode(code3);
		if(t1->type->u.array.elem->kind == ARRAY){	
            //(bodies[o_cnt].points[i_cnt].x) 
			InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
			code4->kind = ADDR_IR3;
			place->type = t1->type->u.array.elem;
			code4->operands[0] = place;
			code4->operands[1] = t1;
			code4->operands[2] = t3;
			insertCode(code4);//作为地址
		}
		else{
			Operand t4 = new_temp();
			InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
			code4->kind = ADDR_IR3;
			code4->operands[0] = t4;
			code4->operands[1] = t1;
			code4->operands[2] = t3;
			
			place->kind = ADDR_OP;//在外面会取*作为值
			place->u.var_no=t4->u.var_no;
			insertCode(code4);
		}

    }
    //         | Exp DOT ID        a.b   左值
    //     不用考虑
    return;
}


void tArgs(Node* args) {
    Node* prs = args->first_son;
    while(prs != NULL) {
        Operand arg;
        tExp(prs,arg);

        InterCode arg_ir = (InterCode)malloc(sizeof(InterCode_));
        arg_ir->kind = ARG_IR;
        arg_ir->operands[0] = arg;
        insertCode(arg_ir);

        prs = prs->follow;
    }
}