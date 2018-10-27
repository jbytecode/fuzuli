
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "linkedlist.h"
#include "string.h"
#include "constants.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    struct Environment *parent;
    struct Environment *chield;
    LinkedList *FuzuliValues;
}Environment;

Environment *EnvironmentNew(Environment *parent);
int EnvironmentIsGlobal(Environment *env);
void EnvironmentRegisterVariable(Environment *env, FuzuliValue *value);
void EnvironmentRegisterGlobals(Environment *env);

#ifdef __cplusplus
}
#endif

#endif /* ENVIRONMENT_H */
