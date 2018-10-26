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
    FuzuliValue *returnValue;

    if(expr->type == EXPR_IDENTIFIER){
        returnValue = doIdentifierOperation(expr, env);
        return returnValue;
    }else if(expr->type == EXPR_NUMBER_CONSTANT){
        returnValue = doNumericConstantOperation(expr, env);
        return returnValue;
    }else if(expr->type == EXPR_STRING){
        returnValue = doStringConstantOperation(expr, env);
        return returnValue;
    }
    return FuzuliValueCreateString("Undefined operation");
}