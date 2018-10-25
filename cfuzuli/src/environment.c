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
    /*
    * Creating Constants
    */
    FuzuliValue *truevalue = FuzuliValueCreateInteger(1);
    FuzuliValue *falsevalue = FuzuliValueCreateInteger(0);
    FuzuliValue *pivalue = FuzuliValueCreateDouble(3.14159265);

    /*
    * Creating pointers for basic internal functions
    */
    FuzuliValue *productFunctionPtr = FuzuliValueCreatePointer((void *)doProductOperation);
    FuzuliValue *plusFunctionPtr = FuzuliValueCreatePointer((void*)doPlusOperation);
    FuzuliValue *dumpFunctionPtr = FuzuliValueCreatePointer((void*)doDumpOperation);
    FuzuliValue *printFunctionPtr = FuzuliValueCreatePointer((void*)doPrintOperation);

    /*
    * Setting variable names
    */
    FuzuliValueSetTag(truevalue, "true");
    FuzuliValueSetTag(falsevalue, "false");
    FuzuliValueSetTag(pivalue, "pi");

    /*
    * Setting internal function names
    */
    FuzuliValueSetTag(productFunctionPtr, "*");
    FuzuliValueSetTag(plusFunctionPtr, "+");
    FuzuliValueSetTag(dumpFunctionPtr, "dump");
    FuzuliValueSetTag(printFunctionPtr, "print");

    /*
    * Registering variables and internal functions
    */
    EnvironmentRegisterVariable(env, truevalue);
    EnvironmentRegisterVariable(env, falsevalue);
    EnvironmentRegisterVariable(env, pivalue);

    EnvironmentRegisterVariable(env, productFunctionPtr);
    EnvironmentRegisterVariable(env, plusFunctionPtr);
    EnvironmentRegisterVariable(env, dumpFunctionPtr);
    EnvironmentRegisterVariable(env, printFunctionPtr);
}

