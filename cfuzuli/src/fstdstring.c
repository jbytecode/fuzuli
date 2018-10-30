#include <string.h>
#include "fstdstring.h"
#include "eval.h"
#include "expression.h"
#include "environment.h"

FuzuliValue *doStrcmpOperation(Expression *expr, Environment *env){
    FuzuliValue *val1 = (FuzuliValue*)eval((Expression*)LinkedListGet(expr->arguments, 0), env);
    FuzuliValue *val2 = (FuzuliValue*)eval((Expression*)LinkedListGet(expr->arguments, 1), env);
    return FuzuliValueCreateInteger(strcmp(val1->svalue->chars, val2->svalue->chars));
}
