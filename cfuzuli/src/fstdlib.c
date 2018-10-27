#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fstdlib.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "eval.h"
#include "ferror.h"

FuzuliValue *doIdentifierOperation(Expression *expr, Environment *env)
{
    LinkedList *alls = (LinkedList *)env->FuzuliValues;
    unsigned int len = LinkedListLength(alls);
    FuzuliValue *returnvalue = FuzuliValueCreateNull();
    for (unsigned int i = 0; i < len; i++)
    {
        FuzuliValue *val = (FuzuliValue *)LinkedListGet(alls, i);
        if (strcmp(val->tag, expr->tag) == 0)
        {
            returnvalue = val;
        }
    }
    if (returnvalue->type == FTYPE_NULL)
    {
        printf("Value is null in %s\n", expr->tag);
        exit(-1);
    }

    if (returnvalue->type == FTYPE_POINTER)
    {
        InternalFunctionPointer p = returnvalue->vvalue;
        return p(expr, env);
    }
    return returnvalue;
}

FuzuliValue *doStringConstantOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val = FuzuliValueCreateString(expr->tag);
    return val;
}

FuzuliValue *doNumericConstantOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val;
    if (strstr(expr->tag, ".") != NULL)
    {
        double d = atof(expr->tag);
        val = FuzuliValueCreateDouble(d);
    }
    else
    {
        int i = atoi(expr->tag);
        val = FuzuliValueCreateInteger(i);
    }
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

FuzuliValue *doPrintlnOperation(Expression *expr, Environment *env)
{
    FuzuliValue *value = doPrintOperation(expr, env);
    printf("\n");
    return value;
}

FuzuliValue *doDumpOperation(Expression *expr, Environment *env)
{
    LinkedList *list = env->FuzuliValues;
    unsigned int len = LinkedListLength(list);
    for (unsigned int i = 0; i < len; i++)
    {
        FuzuliValue *val = (FuzuliValue *)LinkedListGet(list, i);
        printf("%s: ", val->tag);
        FuzuliValuePrint(val);
        printf("\t");
        // There is no evaluation operation. Not freed.
    }
    printf("\n");
    return FuzuliValueCreateInteger(len);
}

FuzuliValue *doLetOperation(Expression *expr, Environment *env)
{
    Expression *ident = (Expression *)LinkedListGet(expr->arguments, 0);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *newval = FuzuliValueDuplicate(val2);

    newval->tag = (char *)malloc(strlen(ident->tag));
    strcpy(newval->tag, ident->tag);

    EnvironmentRegisterVariable(env, newval);
    newval->links++;
    FuzuliValueFree(val2);
    return (newval);
}

FuzuliValue *doEqualsOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueCreateInteger(FuzuliValueEquals(val1, val2));
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}

FuzuliValue *doIfOperation(Expression *expr, Environment *env)
{
    FuzuliValue *condition = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *result;
    unsigned int argumentLength = LinkedListLength(expr->arguments);
    if (argumentLength == 3)
    {
        if (condition->ivalue == 1)
        {
            FuzuliValue *yes = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
            free(condition);
            return yes;
        }
        else
        {
            FuzuliValue *no = eval((Expression *)LinkedListGet(expr->arguments, 2), env);
            free(condition);
            return no;
        }
    }
    else if (argumentLength == 2)
    {
        if (condition->ivalue == 1)
        {
            FuzuliValue *yes = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
            free(condition);
            return yes;
        }
    }
    else
    {
        ErrorAndTerminateExpression("If expression must have 1 or 2 arguments", -1, expr);
    }
    return result;
}

FuzuliValue *doWhileOperation(Expression *expr, Environment *env)
{
    FuzuliValue *condition;
    FuzuliValue *result = NULL;
    while (1)
    {
        condition = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
        if (condition->ivalue == 0)
        {
            break;
        }
        if (result != NULL)
        {
            free(result);
        }
        Expression *subexpr = (Expression *)LinkedListGet(expr->arguments, 1);
        if (strcmp(subexpr->tag, "break"))
        {
            break;
        }
        result = eval(subexpr, env);
        free(condition);
    }
    return result;
}

FuzuliValue *doTypeofOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    switch (val->type)
    {
    case FTYPE_DOUBLE:
        return FuzuliValueCreateString("double");
    case FTYPE_FLOAT:
        return FuzuliValueCreateString("float");
    case FTYPE_INT:
        return FuzuliValueCreateString("integer");
    case FTYPE_LONG:
        return FuzuliValueCreateString("long");
    case FTYPE_NULL:
        return FuzuliValueCreateString("null");
    case FTYPE_POINTER:
        return FuzuliValueCreateString("pointer");
    case FTYPE_STRING:
        return FuzuliValueCreateString("string");
    case FTYPE_UINT:
        return FuzuliValueCreateString("unsigned integer");
    default:
            return FuzuliValueCreateString("unknown");
    }
}


FuzuliValue* doListOperation(Expression *expr, Environment *env){
    FuzuliValue *returnValue = FuzuliValueCreateList();
    LinkedList *data = LinkedListNew();
    unsigned int elemCount = LinkedListLength(expr->arguments);
    for (unsigned int i = 0; i < elemCount; i++){
        FuzuliValue *Elem = eval((Expression*)LinkedListGet(expr->arguments, i), env);
        LinkedListAdd(data, Elem);
    }
    returnValue->vvalue = data;
    return returnValue;
}

FuzuliValue* doLengthOperation(Expression *expr, Environment *env){
    FuzuliValue *listElement = eval((Expression*)LinkedListGet(expr->arguments, 0), env);
    LinkedList *data = (LinkedList*)listElement->vvalue;
    FuzuliValue *returnvalue = FuzuliValueCreateInteger(LinkedListLength(data));
    return returnvalue;
}

FuzuliValue* doNthOperation(Expression *expr, Environment *env){
    Expression *listExpr = (Expression*)LinkedListGet(expr->arguments, 0);
    FuzuliValue *listElement = eval(listExpr, env);
    FuzuliValue *indiceElement = eval((Expression*)LinkedListGet(expr->arguments, 1), env);
    LinkedList *data = (LinkedList*)listElement->vvalue;
    unsigned int len = LinkedListLength(data);
    if(indiceElement->ivalue > len){
        printf("In: \n");
        ExpressionPrint(expr, 0);
        ErrorAndTerminate("Index out of bounds", -1);
    }
    FuzuliValue *returnvalue = LinkedListGet(data, (unsigned int)indiceElement->ivalue);
    return returnvalue;
}


FuzuliValue* doAppendOperation(Expression *expr, Environment *env){
    Expression *listExpr = (Expression*)LinkedListGet(expr->arguments, 0);
    FuzuliValue *listElement = eval(listExpr, env);
    FuzuliValue *newValElement = eval((Expression*)LinkedListGet(expr->arguments, 1), env);
    LinkedList *data = (LinkedList*)listElement->vvalue;
    LinkedListAdd(data, newValElement);
    return newValElement;
}

FuzuliValue* doPrependOperation(Expression *expr, Environment *env){
    Expression *listExpr = (Expression*)LinkedListGet(expr->arguments, 0);
    FuzuliValue *listElement = eval(listExpr, env);
    FuzuliValue *newValElement = eval((Expression*)LinkedListGet(expr->arguments, 1), env);
    LinkedList *data = (LinkedList*)listElement->vvalue;
    LinkedListPrepend(data, newValElement);
    return newValElement;
}