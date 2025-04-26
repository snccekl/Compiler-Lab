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

// 用于梳理数组定义的，请不要在数组调用的时候用，节点名字不一样的
void tArrayDecl(Node* arrayDecl, Operand var) {
    
}

// 用于处理变量定义时赋值
void tInit(Node* init, Operand var) {

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

}