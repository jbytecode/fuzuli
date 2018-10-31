#include "fstdaritmatic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fstdlib.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "eval.h"
#include "ferror.h"
#include "fmemory.h"

FuzuliValue *doPlusOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueSumNumeric(val1, val2);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue *doProductOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueProdNumeric(val1, val2);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue *doSubstractOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueSubtractNumeric(val1, val2);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}

FuzuliValue *doDivideOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    ErrorAndTerminateAfterTypeCheck(val1, val2, expr);
    FuzuliValue *result = FuzuliValueDivideNumeric(val1, val2);
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}

FuzuliValue *doEqualsOperation(Expression *expr, Environment *env)
{
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(FuzuliValueEquals(val1, val2));
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}

FuzuliValue* doLessOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(
            (int)(FuzuliValueGetNumericValue(val1) < (int)FuzuliValueGetNumericValue(val2))
    );
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue* doBiggerOperation(Expression *expr, Environment *env){
FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(
            (int)(FuzuliValueGetNumericValue(val1) > FuzuliValueGetNumericValue(val2))
    );
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue* doLessOrEqualsOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(
            (int)(FuzuliValueGetNumericValue(val1) <= FuzuliValueGetNumericValue(val2))
    );
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue* doBiggerOrEqualsAOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(
            (int)(FuzuliValueGetNumericValue(val1) >= FuzuliValueGetNumericValue(val2))
    );
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}


FuzuliValue* doNotOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    int numvalue = (int)FuzuliValueGetNumericValue(val1);
    FuzuliValue *result;
    if(numvalue == 0){
        result = FuzuliValueCreateInteger(1);
    }else{
        result = FuzuliValueCreateInteger(0);
    }
    FuzuliValueFree(val1);
    return result;
}

FuzuliValue* doNotEqualsOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = eval((Expression *)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = eval((Expression *)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(FuzuliValueEquals(val1, val2));
    if(result->ivalue == 0){
        result->ivalue = 1;
    }else{
        result->ivalue = 0;
    }
    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    return result;
}