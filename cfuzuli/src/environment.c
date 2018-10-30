#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "environment.h"
#include "fstdlib.h"
#include "fstdaritmatic.h"
#include "fstdstring.h"
#include "fmemory.h"

Environment *EnvironmentNew(Environment *parent){
    Environment *env = (Environment*)fmalloc(sizeof(Environment));
    env->parent = (struct Environment*) parent;
    env->FuzuliValues = LinkedListNew();
    return env;
}

void EnvironmentRegisterCommandLineArguments(Environment *env, int argc, char **argv){
    LinkedList *list = LinkedListNew();
    FuzuliValue *fval = FuzuliValueCreateList();
    for (unsigned int i = 0; i < argc; i++){
        FuzuliValue *elem = FuzuliValueCreateString(argv[i]);
        LinkedListAdd(list, elem);
    }
    fval->vvalue = list;
    FuzuliValueSetTag(fval, "args");
    EnvironmentRegisterVariable(env, fval);
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
    if(value->tag != NULL){
    for (unsigned int i = 0; i < len; i++){
        FuzuliValue *tempvalue = (FuzuliValue*)LinkedListGet(env->FuzuliValues, i);
        if(strcmp(tempvalue->tag, value->tag) == 0){
            FuzuliValueCopyContent(tempvalue, value);
            copied = 1;
            break;
        }
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
    FuzuliValue *subtractFunctionPtr = FuzuliValueCreatePointer((void*)doSubstractOperation);
    FuzuliValue *divideFunctionPtr = FuzuliValueCreatePointer((void*)doDivideOperation);
    FuzuliValue *dumpFunctionPtr = FuzuliValueCreatePointer((void*)doDumpOperation);
    FuzuliValue *printFunctionPtr = FuzuliValueCreatePointer((void*)doPrintOperation);
    FuzuliValue *printlnFunctionPtr = FuzuliValueCreatePointer((void*)doPrintlnOperation);
    FuzuliValue *letFunctionPtr = FuzuliValueCreatePointer((void*)doLetOperation);
    FuzuliValue *equalsFunctionPtr = FuzuliValueCreatePointer((void*)doEqualsOperation);
    FuzuliValue *ifFunctionPtr = FuzuliValueCreatePointer((void*)doIfOperation);
    FuzuliValue *whileFunctionPtr = FuzuliValueCreatePointer((void*)doWhileOperation);
    FuzuliValue *typeofFunctionPtr = FuzuliValueCreatePointer((void*)doTypeofOperation);
    FuzuliValue *listFunctionPtr = FuzuliValueCreatePointer((void*)doListOperation);
    FuzuliValue *lengthFunctionPtr = FuzuliValueCreatePointer((void*)doLengthOperation);
    FuzuliValue *nthFunctionPtr = FuzuliValueCreatePointer((void*)doNthOperation);
    FuzuliValue *appendFunctionPtr = FuzuliValueCreatePointer((void*)doAppendOperation);
    FuzuliValue *prependFunctionPtr = FuzuliValueCreatePointer((void*)doPrependOperation);
    FuzuliValue *memoryFunctionPtr = FuzuliValueCreatePointer((void*)doMemoryOperation);
    FuzuliValue *rmFunctionPtr = FuzuliValueCreatePointer((void*)doRmOperation);
    FuzuliValue *isnullFunctionPtr = FuzuliValueCreatePointer((void*)doIsNullOperation);
    FuzuliValue *rangeFunctionPtr = FuzuliValueCreatePointer((void*)doRangeOperatorOperation);
    FuzuliValue *paramsFunctionPtr = FuzuliValueCreatePointer((void*)doParamsOperation);
    FuzuliValue *incFunctionPtr = FuzuliValueCreatePointer((void*)doIncOperation);
    FuzuliValue *strcmpFunctionPtr = FuzuliValueCreatePointer((void*)doStrcmpOperation);
    FuzuliValue *strlenFunctionPtr = FuzuliValueCreatePointer((void*)doStrlenOperation);

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
    FuzuliValueSetTag(subtractFunctionPtr, "-");
    FuzuliValueSetTag(divideFunctionPtr, "/");
    FuzuliValueSetTag(dumpFunctionPtr, "dump");
    FuzuliValueSetTag(printFunctionPtr, "print");
    FuzuliValueSetTag(printlnFunctionPtr, "println");
    FuzuliValueSetTag(letFunctionPtr, "let");
    FuzuliValueSetTag(equalsFunctionPtr, "=");
    FuzuliValueSetTag(ifFunctionPtr, "if");
    FuzuliValueSetTag(whileFunctionPtr, "while");
    FuzuliValueSetTag(typeofFunctionPtr, "typeof");
    FuzuliValueSetTag(listFunctionPtr, "list");
    FuzuliValueSetTag(lengthFunctionPtr, "length");
    FuzuliValueSetTag(nthFunctionPtr, "nth");
    FuzuliValueSetTag(appendFunctionPtr, "append");
    FuzuliValueSetTag(prependFunctionPtr, "prepend");
    FuzuliValueSetTag(memoryFunctionPtr, "memory");
    FuzuliValueSetTag(rmFunctionPtr, "rm");
    FuzuliValueSetTag(isnullFunctionPtr, "isnull");
    FuzuliValueSetTag(rangeFunctionPtr, ":");
    FuzuliValueSetTag(paramsFunctionPtr, "params");
    FuzuliValueSetTag(incFunctionPtr, "inc");
    FuzuliValueSetTag(strcmpFunctionPtr, "strcmp");
    FuzuliValueSetTag(strlenFunctionPtr, "strlen");

    /*
    * Registering variables and internal functions
    */
    EnvironmentRegisterVariable(env, truevalue);
    EnvironmentRegisterVariable(env, falsevalue);
    EnvironmentRegisterVariable(env, pivalue);

    EnvironmentRegisterVariable(env, productFunctionPtr);
    EnvironmentRegisterVariable(env, plusFunctionPtr);
    EnvironmentRegisterVariable(env, subtractFunctionPtr);
    EnvironmentRegisterVariable(env, divideFunctionPtr);
    EnvironmentRegisterVariable(env, dumpFunctionPtr);
    EnvironmentRegisterVariable(env, printFunctionPtr);
    EnvironmentRegisterVariable(env, printlnFunctionPtr);
    EnvironmentRegisterVariable(env, letFunctionPtr);
    EnvironmentRegisterVariable(env, equalsFunctionPtr);
    EnvironmentRegisterVariable(env, ifFunctionPtr);
    EnvironmentRegisterVariable(env, whileFunctionPtr);
    EnvironmentRegisterVariable(env, typeofFunctionPtr);
    EnvironmentRegisterVariable(env, listFunctionPtr);
    EnvironmentRegisterVariable(env, lengthFunctionPtr);
    EnvironmentRegisterVariable(env, nthFunctionPtr);
    EnvironmentRegisterVariable(env, appendFunctionPtr);
    EnvironmentRegisterVariable(env, prependFunctionPtr);
    EnvironmentRegisterVariable(env, memoryFunctionPtr);
    EnvironmentRegisterVariable(env, rmFunctionPtr);
    EnvironmentRegisterVariable(env, isnullFunctionPtr);
    EnvironmentRegisterVariable(env, rangeFunctionPtr);
    EnvironmentRegisterVariable(env, paramsFunctionPtr);
    EnvironmentRegisterVariable(env, incFunctionPtr);
    EnvironmentRegisterVariable(env, strcmpFunctionPtr);
    EnvironmentRegisterVariable(env, strlenFunctionPtr);
    

    LinkedList *list = env->FuzuliValues;
    unsigned int len = LinkedListLength(list);
    for (unsigned int i = 0; i < len; i++){
        ((FuzuliValue*)LinkedListGet(list, i))->protected = 1;
    }
}

