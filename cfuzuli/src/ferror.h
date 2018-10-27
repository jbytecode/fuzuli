#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include "expression.h"
#include "fuzulitypes.h"

void ErrorAndTerminate(const char *errmessage,  int errorcode);
void ErrorAndTerminateExpression(const char *errmessage, int errorcode, Expression *expr);
void ErrorAndTerminateAfterTypeCheck(FuzuliValue *val1, FuzuliValue *val2, Expression *expr);

#endif
