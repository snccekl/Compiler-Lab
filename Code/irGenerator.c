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
            tFunDec(dummy);
        }
        else if(!strcmp("StructDecl",dummy->name)){
            tStructDecl(dummy);
        }
        else if(!strcmp("VarDecl",dummy->name)){
            tVardec(dummy);
            
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
    }
}