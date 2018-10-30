#include <string.h>
#include "fstdstring.h"
#include "eval.h"
#include "expression.h"
#include "environment.h"
#include "fuzulitypes.h"

FuzuliValue *doStrcmpOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = (FuzuliValue*)eval((Expression*)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = (FuzuliValue*)eval((Expression*)LinkedListGet(expr->arguments, 1), env);
    FuzuliValue *result = FuzuliValueCreateInteger(strcmp(val1->svalue->chars, val2->svalue->chars));

    FuzuliValueFree(val1);
    FuzuliValueFree(val2);
    
    return result;
}


FuzuliValue *doStrlenOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = (FuzuliValue*)eval((Expression*)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *result = FuzuliValueCreateInteger(strlen(val1->svalue->chars));

    FuzuliValueFree(val1);

    return result;
}
