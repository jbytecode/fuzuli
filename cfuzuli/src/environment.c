#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "environment.h"
#include "fstdlib.h"

Environment *EnvironmentNew(Environment *parent){
    Environment *env = (Environment*)malloc(sizeof(Environment));
    env->parent = (struct Environment*) parent;
    env->FuzuliValues = LinkedListNew();
    return env;
}

int EnvironmentIsGlobal(Environment *env){
    if(env->parent == NULL){
        return TRUE;
    }else{
        return FALSE;
    }
}

void EnvironmentRegisterVariable(Environment *env, FuzuliValue *value){
    FuzuliValue *fvalue;
    unsigned int copied = 0;
    unsigned len = LinkedListLength(env->FuzuliValues);
    for (unsigned int i = 0; i < len; i++){
        FuzuliValue *tempvalue = (FuzuliValue*)LinkedListGet(env->FuzuliValues, i);
        if(strcmp(tempvalue->tag, value->tag) == 0){
            FuzuliValueCopyContent(tempvalue, value);
            copied = 1;
            break;
        }
    }
    if(copied == 0){
        LinkedListAdd(env->FuzuliValues, value);
    }
}



void EnvironmentRegisterGlobals(Environment *env){
    FuzuliValue *truevalue = FuzuliValueCreateInteger(1);
    FuzuliValue *falsevalue = FuzuliValueCreateInteger(0);
    FuzuliValue *productFunctionPtr = FuzuliValueCreatePointer((void *)doProductOperation);
    FuzuliValue *plusFunctionPtr = FuzuliValueCreatePointer((void*)doPlusOperation);
    
    FuzuliValueSetTag(truevalue, "true");
    FuzuliValueSetTag(falsevalue, "false");
    FuzuliValueSetTag(productFunctionPtr, "*");
    FuzuliValueSetTag(plusFunctionPtr, "+");

    EnvironmentRegisterVariable(env, truevalue);
    EnvironmentRegisterVariable(env, falsevalue);
    EnvironmentRegisterVariable(env, productFunctionPtr);
    EnvironmentRegisterVariable(env, plusFunctionPtr);
}

