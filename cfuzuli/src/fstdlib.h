#ifndef FSTDLIB_H
#define FSTDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "constants.h"
#include "fuzulitypes.h"
#include "expression.h"
#include "environment.h"

// Other standart library files
#include "fstdaritmatic.h"
#include "fstdstring.h"


/*
General function pointer template
for evaluators
*/   
typedef FuzuliValue* (*InternalFunctionPointer)(Expression *expr, Environment *env); 

FuzuliValue* doNumericConstantOperation(Expression *expr, Environment *env);
FuzuliValue* doIdentifierOperation(Expression *expr, Environment *env);
FuzuliValue* doStringConstantOperation(Expression *expr, Environment *env);
FuzuliValue* doPrintOperation(Expression *expr, Environment *env);
FuzuliValue *doPrintlnOperation(Expression *expr, Environment *env);
FuzuliValue* doDumpOperation(Expression *expr, Environment *env);
FuzuliValue* doLetOperation(Expression *expr, Environment *env);
FuzuliValue* doIfOperation(Expression *expr, Environment *env);
FuzuliValue* doWhileOperation(Expression *expr, Environment *env);
FuzuliValue* doTypeofOperation(Expression *expr, Environment *env);
FuzuliValue* doListOperation(Expression *expr, Environment *env);
FuzuliValue* doLengthOperation(Expression *expr, Environment *env);
FuzuliValue* doNthOperation(Expression *expr, Environment *env);
FuzuliValue* doAppendOperation(Expression *expr, Environment *env);
FuzuliValue* doPrependOperation(Expression *expr, Environment *env);
FuzuliValue* doMemoryOperation(Expression *expr, Environment *env);
FuzuliValue* doRmOperation(Expression *expr, Environment *env);
FuzuliValue* doIsNullOperation(Expression *expr, Environment *env);
FuzuliValue* doRangeOperatorOperation(Expression *expr, Environment *env);
FuzuliValue* doParamsOperation(Expression *expr, Environment *env);
FuzuliValue* doIncOperation(Expression *expr, Environment *env);


#ifdef __cplusplus
}
#endif

#endif /* TOKEN_H */



