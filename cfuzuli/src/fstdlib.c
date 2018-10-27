#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fstdlib.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "eval.h"
#include "ferror.h"

FuzuliValue* doIdentifierOperation(Expression *expr, Environment *env){
    LinkedList *alls = (LinkedList*) env->FuzuliValues;
    unsigned int len = LinkedListLength(alls);
    FuzuliValue *returnvalue = FuzuliValueCreateNull();
    for (unsigned int i = 0; i < len; i++){
        FuzuliValue *val = (FuzuliValue*) LinkedListGet(alls, i);
        if(strcmp(val->tag, expr->tag) == 0){
            returnvalue = val;
        }
    }
    if(returnvalue->type == FTYPE_NULL){
        printf("Variable is null in %s\n", expr->tag);
        exit(-1);
    }

    if(returnvalue->type == FTYPE_POINTER){
        InternalFunctionPointer p = returnvalue->vvalue;
        return p(expr, env);
    }
    return returnvalue;
}

FuzuliValue* doStringConstantOperation(Expression *expr, Environment *env){
    FuzuliValue *val = FuzuliValueCreateString(expr->tag);
    return val;
}

FuzuliValue *doNumericConstantOperation(Expression *expr, Environment *env)
{
    double d = atof(expr->tag);
    FuzuliValue *val = FuzuliValueCreateDouble(d);
    return val;
}

FuzuliValue *doPlusOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueCreateDouble(val1->dvalue + val2->dvalue);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);  
    return result;
}

FuzuliValue *doProductOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueCreateDouble(val1->dvalue * val2->dvalue);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);  
    return result;
}

FuzuliValue *doPrintOperation(Expression *expr, Environment *env)
{
    unsigned int len = LinkedListLength(expr->arguments);
    FuzuliValue *value;
    for (unsigned int i = 0; i < len; i++)
    {
        Expression *exprsub = (Expression *)LinkedListGet(expr->arguments, i);
        value = eval(exprsub, env);
        FuzuliValuePrint(value);
        FuzuliValueFree(value);
    }
    return value;
}

FuzuliValue *doDumpOperation(Expression *expr, Environment *env)
{
    LinkedList *list = env->FuzuliValues;
    unsigned int len = LinkedListLength(list);
    for (unsigned int i = 0; i < len; i++){
        FuzuliValue *val = (FuzuliValue*)LinkedListGet(list, i);
        printf("%s: ", val->tag);
        FuzuliValuePrint(val);
        printf("\t");
        // There is no evaluation operation. Not freed.
    }
    printf("\n");
    return FuzuliValueCreateInteger(len);
}

FuzuliValue *doLetOperation(Expression *expr, Environment *env){
    Expression *ident = (Expression *)LinkedListGet(expr->arguments, 0);
    
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *newval = FuzuliValueDuplicate(val2);

    newval->tag = (char*)malloc(strlen(ident->tag));
    strcpy(newval->tag, ident->tag);
    
    EnvironmentRegisterVariable(env, newval);
    newval->links++;
    FuzuliValueFree(val2);
    return(newval);
}

FuzuliValue* doEqualsOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueCreateInteger(FuzuliValueEquals(val1, val2));
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);  
    return result;
}