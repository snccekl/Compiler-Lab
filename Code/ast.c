#include "tree.h"
#include "ast.h"

Node* createAstNode(char* name, char* token, int line, int scope_id, int flag) {
    Node* AstNode = createNode(1, name, token);
    AstNode->line = line;
    AstNode->scope_id = scope_id;
    AstNode->flag = flag;
    return AstNode;
}

Node* CopyNode(Node* node) {
    Node* new_node = createAstNode(node->name, node->token, node->line, node->scope_id, node->flag);
    new_node->parent = node->parent;
    new_node->follow = node->follow;
    new_node->first_son = node->first_son;
    return new_node;
}

// Program         : ExtDefList
Node* parseTreeToAst(Node* root) {
    if(root==NULL) {
        return NULL;
    }
    
    Node* ast_root = createAstNode(root->name, root->token, root->line, root->scope_id, root->flag);

    if(!strcmp("ExtDefList" , root->first_son->name)) {
        Node* first_son = transferExtDefList(root->first_son, ast_root);
        ast_root->first_son = first_son;
    }
    return ast_root;
}

// ExtDefList  : ExtDef ExtDefList  
//             |  /* empty */   
Node* transferExtDefList(Node* node, Node* parent) {
    if(node == NULL) {
        return NULL;
    }

    Node* prs = transferExtDef(node->first_son, parent);
    Node* prs_follow = transferExtDefList(node->first_son->follow, parent);

    prs->parent = parent;
    prs->follow = prs_follow;
    return prs;
}

// ExtDef      : Specifier ExtDecList SEMI  
//             | Specifier SEMI             
//             | Specifier FunDec CompSt   
//             | Specifier FunDec SEMI 
Node* transferExtDef(Node* node, Node* parent) {
    Node* specifier = node->first_son;
    Node* prs_type = transferSpecifier(specifier);
    Node* prs = NULL;

    if(!strcmp(specifier->follow->name, "ExtDecList")) {
        prs = transferExtDecList(specifier->follow, parent, prs_type);
    }
    else if(!strcmp(specifier->follow->name, "SEMI")) {
        prs = prs_type;
        prs->parent = parent;
    }
    else if(!strcmp(specifier->follow->name, "FunDec")) {
        Node* func = specifier->follow;
        prs = transferFuncDec(func, parent, prs_type);

        if(!strcmp(func->follow->name, "CompSt")) {
            Node* compSt = transferCompSt(func->follow, prs);
            Node* pt = prs->first_son;
            while(pt->follow != NULL)
                pt = pt->follow;
            pt->follow = compSt;
        }
    }
    return prs;
}

// Specifier   : TYPE
//             | StructSpecifier
//             ;
Node* transferSpecifier(Node* node) {
    Node* first = node->first_son;

    if(!strcmp(first->name, "TYPE")) {
        Node* type = createAstNode("Type", first->token, first->line, node->scope_id, node->flag);
        return type;
    }
    else {
        Node* structer = transferStructSpecifier(first);
        return structer;
    }
}

// StructSpecifier : STRUCT OptTag LC DefList RC
//                 | STRUCT Tag
//                 ;
Node* transferStructSpecifier(Node* node) {
    Node* structer = node->first_son;
    Node* ast_struct = createAstNode("StructDecl", "", structer->line, node->scope_id, node->flag);

    // STRUCT Tag
    if(node->num_child == 2) {
        Node* id = structer->follow->first_son;
        Node* ID = createAstNode(id->name, id->token, id->line, node->scope_id, id->flag);

        ast_struct->first_son = ID;
        ID->parent = ast_struct;
    }

    // STRUCT OptTag LC DefList RC
    else {
        if(!strcmp(structer->follow->name, "OptTag")) {
            Node* id = structer->follow->first_son;
            Node* ID = createAstNode(id->name, id->token, id->line, node->scope_id, id->flag);

            ast_struct->first_son = ID;
            ID->parent = ast_struct;
        }

        Node* prs = structer;
        Node* field = createAstNode("FieldList", "", node->line, node->scope_id, -1);
        Node* defList = NULL;
        while(prs != NULL) {
            
            if(!strcmp(prs->name, "DefList")) {
                defList = transferDefList(prs, field);
                field->first_son = defList;
                field->line = defList->line;
                break;
            }
            prs = prs->follow;
        }
        prs = ast_struct->first_son;
        while(prs != NULL && prs->follow != NULL)
            prs = prs->follow;
        
        if(prs != NULL)
            prs->follow = field;
        else
            ast_struct->first_son = defList;
    }
    return ast_struct;
}

// ExtDecList  : VarDec                  
//             | VarDec COMMA ExtDecList 
//             ;
Node* transferExtDecList(Node* node, Node* parent, Node* type) {
    Node* varDec= node->first_son;
    Node* var = transferVarDec(varDec, parent, type);

    if(node->num_child == 3) {
        Node* follow_type = CopyNode(type);
        Node* follow = transferExtDecList(varDec->follow->follow, parent, follow_type);
        var->follow = follow;
    }
    return var;
}

// VarDec    : ID
//           | VarDec LB INT RB
//a  a[10][20]...
Node* transferVarDec(Node* node, Node* parent, Node* type) {
    Node* first = node->first_son;
    Node* var = NULL;

    if(!strcmp(first->name, "ID")) {
        Node* ID = createAstNode(first->name, first->token, first->line, node->scope_id, -1);
        var = createAstNode("VarDecl", "", node->line, node->scope_id, node->flag);
        
        var->parent = parent;
        var->first_son = type;
        
        type->parent = var;
        type->follow = ID;
        
        ID->parent = var;
    }
    else if(!strcmp(first->name, "VarDec")) {
        var = transferVarDec(first, parent, type);

        Node* array = createAstNode("ArrayDecl", "", first->line, node->scope_id, -1);
        Node* array_size = first->follow->follow;
        Node* ast_size = createAstNode("Size", array_size->token, array_size->line, node->scope_id, -1);

        array->first_son = ast_size;

        Node* prs = var->first_son;
        Node* prs_parent = var;
        while(prs != NULL) {
            if(!strcmp(prs->name, "ArrayDecl")) 
            {   
                prs_parent = prs;
                prs = prs->first_son;
            }
            if(prs->follow == NULL) {
                prs->parent = prs_parent;
                prs->follow = array;
                break;
            }

            else
                prs = prs->follow;
        }
    }
    return var;
}


// FunDec     : ID LP VarList RP
//            | ID LP RP 
Node* transferFuncDec(Node* node, Node* parent, Node* type) {
    Node* func = createAstNode("FuncDecl", "", node->line, node->scope_id, node->flag);

    Node* id = node->first_son;
    Node* ID = createAstNode(id->name, id->token, id->line, node->scope_id, -1);

    func->parent = parent;
    func->first_son = type;
    type->parent = func;
    type->follow = ID;
    ID->parent = func;

    if(node->num_child == 4) {
        Node* paramList = createAstNode("ParamList", "", node->line, node->scope_id, -1);
        paramList->parent = func;
        paramList->first_son = transferVarList(node->first_son->follow->follow, paramList);
        ID->follow = paramList;
    }
    return func;
}

// VarList         : ParamDec COMMA VarList
//                 | ParamDec
Node* transferVarList(Node* node, Node* parent) {
    // ParamDec        : Specifier VarDec
    Node* paramDec = node->first_son;
    Node* type = transferSpecifier(paramDec->first_son);
    Node* param = transferVarDec(paramDec->first_son->follow, parent, type);
    
    if(node->num_child == 3) {
        Node* follow = transferVarList(paramDec->follow->follow, parent);
        param->follow = follow;
    }
    return param;
}

// CompSt          : LC DefList Stmt RC
Node* transferCompSt(Node* node, Node* parent) {
    Node* compSt = createAstNode("Block", "", node->line, node->scope_id, -1);
    compSt->parent = parent;
    
    Node* defList = NULL;
    Node* stmt = NULL;
    
    Node* prs = node->first_son;
    while(prs != NULL) {
        if(!strcmp(prs->name, "DefList")) {
            defList = transferDefList(prs, compSt);
        }
        else if(!strcmp(prs->name, "StmtList")) {
            stmt = transferStmtList(prs, compSt);
        }
        prs = prs->follow;
    }
    if(defList != NULL) {
        compSt->first_son = defList;

        prs = defList;
        while(prs ->follow != NULL)
            prs = prs->follow;
        prs->follow = stmt;
    }
    else {
        compSt->first_son = stmt;
    }
    return compSt;
}

// DefList         : Def DefList
//                 | /* empty */
// Def             : Specifier DecList SEMI
Node* transferDefList(Node* node, Node* parent) {
    if(node == NULL)
        return NULL;
    
    Node* def = node->first_son;

    Node* Type = def->first_son;
    Node* type = transferSpecifier(Type);
    Node* var = transferDecList(Type->follow, parent, type);

    Node* prs = var;
    while(prs->follow != NULL)
        prs = prs->follow;
    
    prs->follow = transferDefList(def->follow, parent);
    return var;
}

// DecList         : Dec
//                 | Dec COMMA DecList
// Dec             : VarDec
//                 | VarDec ASSIGNOP Exp 
Node* transferDecList(Node* node, Node* parent, Node* type) {
    if(node == NULL)
        return NULL;
    
    Node* dec = node->first_son;
    Node* varDec = dec->first_son;
    Node* var = transferVarDec(dec->first_son, parent, type);

    // VarDec ASSIGNOP Exp 
    if(dec->num_child == 3) {
        Node* old_exp = varDec->follow->follow;
        Node* init = createAstNode("Init", "", old_exp->line, old_exp->scope_id, -1);

        Node* exp = transferExp(old_exp, init);
        Node* prs = var->first_son;
        while(prs->follow != NULL)
            prs = prs->follow;

        
        prs->follow = init;
        init->first_son = exp;
    }

    // Dec COMMA DecList
    if(node->num_child == 3) {
        Node* follow_type = CopyNode(type);
        Node* follow = transferDecList(dec->follow->follow, parent, follow_type);
        var->follow = follow;
    }
    return var;
}

// StmtList        : Stmt StmtList
//                 | /* empty */
Node* transferStmtList(Node* node, Node* parent) {
    if(node == NULL)
        return NULL;
    
    Node* Stmt = node->first_son;
    Node* stmt = transferStmt(Stmt, parent);
    Node* follow = transferStmtList(Stmt->follow, parent);

    stmt->follow = follow;
    return stmt;
}

// Stmt    : Exp SEMI                                
//         | CompSt                                  
//         | RETURN Exp SEMI                         
//         | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE 
//         | IF LP Exp RP Stmt ELSE Stmt                        
//         | WHILE LP Exp RP Stmt                    
//         ;  
Node* transferStmt(Node* node, Node* parent) {
    Node* first = node->first_son;
    Node* stmt = NULL;

    // Exp SEMI  
    if(!strcmp(first->name, "Exp")) {
        stmt = transferExp(first, parent);
    }

    // CompSt 
    else if(!strcmp(first->name, "CompSt")) {
        stmt = transferCompSt(first, parent);
    }

    // RETURN Exp SEMI 
    else if(!strcmp(first->name, "RETURN")) {
        stmt = createAstNode("ReturnStmt", "", node->line, node->scope_id, -1);
        stmt->parent = parent;

        Node* exp = transferExp(first->follow, stmt);

        stmt->first_son = exp;
    }

    // IF LP Exp RP Stmt %prec LOWER_THAN_ELSE 
    // IF LP Exp RP Stmt ELSE Stmt   
    else if(!strcmp(first->name, "IF")) {
        stmt = createAstNode("If", "", node->line, node->scope_id, -1);
        stmt->parent = parent;

        Node* cond = transferExp(first->follow->follow, stmt);
        Node* then = transferStmt(first->follow->follow->follow->follow, stmt);
        Node* Else = NULL;
        if(node->num_child == 7) {
            Else = transferStmt(first->follow->follow->follow->follow->follow->follow, stmt);
        }
        stmt->first_son = cond;
        cond->follow = then;
        then->follow = Else;
    }

    // WHILE LP Exp RP Stmt   
    else if(!strcmp(first->name, "WHILE")) {
        stmt = createAstNode("While", "", node->line, node->scope_id, -1);
        stmt->parent = parent;

        Node* cond = transferExp(first->follow->follow, stmt);
        Node* then = transferStmt(first->follow->follow->follow->follow, stmt);

        stmt->first_son = cond;
        cond->follow = then;
    }

    // build block for if_stmt and while_stmt
    if(!strcmp(parent->name, "If") || !strcmp(parent->name, "While")) {
        if(strcmp(first->name, "CompSt")) {
            Node* block = createAstNode("Block", "", first->line, node->scope_id, -1);
            block->parent = stmt->parent;
            block->first_son = stmt;
            stmt->parent = block;
            stmt = block;
        }
    }

    return stmt;
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
Node* transferExp(Node* node, Node* parent) {
    Node* exp = NULL;

    Node* first = node->first_son;

    // Exp ASSIGNOP Exp      
    // Exp AND Exp           
    // Exp OR Exp            
    // Exp RELOP Exp         
    // Exp PLUS Exp          
    // Exp MINUS Exp         
    // Exp STAR Exp          
    // Exp DIV Exp  
    if(node->num_child == 3 && !strcmp(first->follow->follow->name, "Exp")) {
        Node* second = first->follow->follow;
        Node* Op = first->follow;

        Node* op = createAstNode(Op->name, Op->token, Op->line, node->scope_id, -1);
        Node* first_exp = transferExp(first, op);
        Node* second_exp = transferExp(second, op);
        
        op->parent = parent;
        op->first_son = first_exp;
        first_exp->follow = second_exp;

        exp = op;
    }

    // LP Exp RP
    else if(!strcmp(first->name, "LP")) {
        exp = transferExp(first->follow, parent);
    }

    // MINUS Exp %prec UMINUS
    // NOT Exp               
    else if(node->num_child == 2 && !strcmp(first->follow->name, "Exp")) {
        exp = createAstNode("UnaryOp", "", node->line, node->scope_id, -1);

        Node* op = createAstNode(first->name, first->token, first->line, node->scope_id, -1);
        Node* first_exp = transferExp(first->follow, exp);

        exp->parent = parent;
        exp->first_son = op;
        op->parent = exp;
        op->follow = first_exp;
    }

    // ID LP Args RP         
    // ID LP RP
    else if(!strcmp(first->name, "ID") && node->num_child > 1) {
        exp = createAstNode("FuncCall", first->token, node->line, node->scope_id, 2);
        Node* ID = createAstNode(first->name, first->token, first->line, node->scope_id, -1);
        Node* args = NULL;
        if(node->num_child == 4) {
            args = createAstNode("Args", "", first->follow->follow->line, node->scope_id, -1);
            Node* first_arg = transferArgs(first->follow->follow, args);
            
            args->parent = exp;
            args->first_son = first_arg;
        }
        exp->parent = parent;
        exp->first_son = ID;
        ID->parent = exp;
        ID->follow = args;
    }
    
    // Exp LB Exp RB 
    else if(!strcmp(first->name, "Exp") && node->num_child == 4) {
        exp = createAstNode("ArrayAccess", "", first->line, node->scope_id, -1);
        Node* first_son = transferExp(first, exp);
        Node* Index = createAstNode("Index", "", first->follow->follow->line, node->scope_id, -1);
        Node* index = transferExp(first->follow->follow, Index);

        exp->parent = parent;
        exp->first_son = first_son;
        first_son->follow = Index;
        Index->parent = exp;
        Index->first_son = index;
    }
    
    // Exp DOT ID
    else if(node->num_child == 3 && !strcmp(first->follow->name, "DOT")) {
        exp = createAstNode("Access", "", first->line, node->scope_id, -1);
        Node* first_son = transferExp(first, exp);
        Node* id = first->follow->follow;
        Node* access_id = createAstNode(id->name, id->token, id->line, node->scope_id, -1);

        exp->parent = parent;
        exp->first_son = first_son;
        first_son->follow = access_id;
        access_id->parent = parent;
    }

    // ID                    
    // INT                   
    // FLOAT
    else if(node->num_child == 1) {
        exp = createAstNode(first->name, first->token, first->line, node->scope_id, node->flag);
        exp->parent = parent;
    }

    return exp;
}

// Args    : Exp COMMA Args  
//         | Exp             
Node* transferArgs(Node* node, Node* parent) {
    Node* first = node->first_son;
    Node* arg = transferExp(first, parent);
    Node* follow = NULL;
    if(node->num_child == 3) {
        follow = transferArgs(first->follow->follow, parent);
    }

    arg->follow = follow;
    return arg;
}