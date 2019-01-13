#ifndef FSTD_STRING_H
#define FSTD_STRING_H

#include "fuzulitypes.h"
#include "expression.h"
#include "environment.h"


FuzuliValue *doStrcmpOperation(Expression *expr, Environment *env);
FuzuliValue *doStrlenOperation(Expression *expr, Environment *env);
FuzuliValue *doCharAtOperation(Expression *expr, Environment *env);

#endif