#ifndef EVAL_H
#define EVAL_H

#include "fuzulitypes.h"
#include "expression.h"
#include "environment.h"

FuzuliValue* eval(Expression *expr, Environment *env);


#endif

