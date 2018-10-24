#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "linkedlist.h"
#include "token.h"
#include "fstdlib.h"
#include "environment.h"

FuzuliValue* eval(Expression *expr, Environment *env){
    if(expr == NULL){
        printf("Expression is null, exiting eval();\n");
        return NULL;
    }
    unsigned int type = expr->type;
    LinkedList *args = expr->arguments;
    FuzuliValue *val = FuzuliValueCreateString("Undefined operation");
    
    if(expr->type == EXPR_IDENTIFIER){
        if(strcmp(expr->tag, "print") == 0){
            return doPrintOperation(expr, env);
        }else if(strcmp(expr->tag, "dump") == 0){
            return doDumpOperation(expr, env);
        }else{
            return doIdentifierOperation(expr, env);
        }
    }else if(expr->type == EXPR_NUMBER_CONSTANT){
        return doNumericConstantOperation(expr, env);
    }else if(expr->type == EXPR_STRING){
        return doStringConstantOperation(expr, env);
    }
    return val;
}