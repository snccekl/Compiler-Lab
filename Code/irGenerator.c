#include "ir.h"

// 你自己看看吧
void tProgram(Node *root) {
    if(root == NULL){
        return;
    }
    Node* dummy;
    dummy = root->first_son;
    while(dummy != NULL){
        if(!strcmp("FuncDecl" , dummy->name)){
            tFunDecl(dummy);
        }
        else if(!strcmp("StructDecl",dummy->name)){
            tStructDecl(dummy);
        }
        else if(!strcmp("VarDecl",dummy->name)){
            tVardecl(dummy);
            
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

    strcmp(func_op->u.value, ID->token);
    func->type = func_field->type;

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
    insertCode(dec_ir);
}

// 用于处理变量定义时赋值
void tInit(Node* init, Operand var) {
    // 先得到右值
    Operand assign_var = tExp(init->first_son);
    
    // 在IR中加入赋值语句
    tTwoOperands(var, assign_var, ASSIGN_IR);
}

void tParamList(Node* paramList) {
    Node* Param = paramList->first_son;
    while(Param != NULL) {
        if(!strcmp(Param->name, "VarDecl")) {
            // 获取参数
            Operand param = tVarDecl(param);

            // 生成PARAM_IR
            InterCode param_ir = (InterCode)malloc(sizeof(InterCode_));
            param_ir->kind = PARAM_IR;
            param_ir->operands[0] = param;
            insertCode(param_ir);
        }
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
        Operand exp = tExp(stmt->first_son);

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
            insert(label3_ir);
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
        tExp(stmt);
    }
}


void tCond(Node* cond, Operand label_true, Operand label_false) {
    // TODO
}

Operand tExp(Node* exp) {
    // TODO
    return NULL;
}


void tArgs(Node* args) {
    Node* prs = args->first_son;
    while(prs != NULL) {
        Operand arg = tExp(prs);

        InterCode arg_ir = (InterCode)malloc(sizeof(InterCode_));
        arg_ir->kind = ARG_IR;
        arg_ir->operands[0] = arg;
        insertCode(arg_ir);

        prs = prs->follow;
    }
}