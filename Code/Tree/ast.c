#include "tree.h"

Node* ast_root;

void parseTreeToAst(Node* root) {
    if(root==NULL) {
        return;
    }
    
    ast_root = createNode(1, root->name, root->token);
}