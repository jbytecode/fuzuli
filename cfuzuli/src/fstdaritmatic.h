#ifndef FSTD_ARITHMATIC_H
#define FSTD_ARITHMATIC_H

#include "fuzulitypes.h"
#include "expression.h"
#include "environment.h"

FuzuliValue* doPlusOperation(Expression *expr, Environment *env);
FuzuliValue *doSubstractOperation(Expression *expr, Environment *env);
FuzuliValue* doProductOperation(Expression *expr, Environment *env);
FuzuliValue *doDivideOperation(Expression *expr, Environment *env);
FuzuliValue* doEqualsOperation(Expression *expr, Environment *env);

#endif
