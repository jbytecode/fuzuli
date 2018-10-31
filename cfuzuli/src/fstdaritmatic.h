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
FuzuliValue* doLessOperation(Expression *expr, Environment *env);
FuzuliValue* doBiggerOperation(Expression *expr, Environment *env);
FuzuliValue* doLessOrEqualsOperation(Expression *expr, Environment *env);
FuzuliValue* doBiggerOrEqualsAOperation(Expression *expr, Environment *env);
FuzuliValue* doNotOperation(Expression *expr, Environment *env);
FuzuliValue* doNotEqualsOperation(Expression *expr, Environment *env);
#endif
