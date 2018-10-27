#ifndef FSTDLIB_H
#define FSTDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "constants.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "environment.h"

/*
General function pointer template
for evaluators
*/   
typedef FuzuliValue* (*InternalFunctionPointer)(Expression *expr, Environment *env); 

FuzuliValue* doNumericConstantOperation(Expression *expr, Environment *env);
FuzuliValue* doIdentifierOperation(Expression *expr, Environment *env);
FuzuliValue* doStringConstantOperation(Expression *expr, Environment *env);
FuzuliValue* doPlusOperation(Expression *expr, Environment *env);
FuzuliValue* doProductOperation(Expression *expr, Environment *env);
FuzuliValue* doPrintOperation(Expression *expr, Environment *env);
FuzuliValue* doDumpOperation(Expression *expr, Environment *env);
FuzuliValue* doLetOperation(Expression *expr, Environment *env);
FuzuliValue* doEqualsOperation(Expression *expr, Environment *env);
FuzuliValue* doIfOperation(Expression *expr, Environment *env);

#ifdef __cplusplus
}
#endif

#endif /* TOKEN_H */



