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

