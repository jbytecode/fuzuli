#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "environment.h"
#include "fstdlib.h"
#include "fstdaritmatic.h"
#include "fstdstring.h"
#include "fmemory.h"

Environment *EnvironmentNew(Environment *parent)
{
    Environment *env = (Environment *)fmalloc(sizeof(Environment));
    env->parent = (struct Environment *)parent;
    env->FuzuliValues = LinkedListNew();
    return env;
}

void EnvironmentRegisterCommandLineArguments(Environment *env, int argc, char **argv)
{
    LinkedList *list = LinkedListNew();
    FuzuliValue *fval = FuzuliValueCreateList();
    for (unsigned int i = 0; i < argc; i++)
    {
        FuzuliValue *elem = FuzuliValueCreateString(argv[i]);
        LinkedListAdd(list, elem);
    }
    fval->vvalue = list;
    FuzuliValueSetTag(fval, "args");
    EnvironmentRegisterVariable(env, fval);
}

int EnvironmentIsGlobal(Environment *env)
{
    if (env->parent == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void EnvironmentRegisterVariable(Environment *env, FuzuliValue *value)
{
    FuzuliValue *fvalue;
    unsigned int copied = 0;
    unsigned len = LinkedListLength(env->FuzuliValues);
    if (value->tag != NULL)
    {
        LinkedListElement *llelement = env->FuzuliValues->first;
        for (unsigned int i = 0; i < len; i++)
        {
            FuzuliValue *tempvalue = (FuzuliValue *)llelement->value;
            if (strcmp(tempvalue->tag, value->tag) == 0)
            {
                FuzuliValueCopyContent(tempvalue, value);
                copied = 1;
                break;
            }
            llelement = llelement->next;
        }
    }
    if (copied == 0)
    {
        LinkedListAdd(env->FuzuliValues, value);
    }
}

void EnvironmentRegisterInternalFunction(Environment *env, void *function, char *tag)
{
    FuzuliValue *ptr = FuzuliValueCreatePointer((void *)function);
    FuzuliValueSetTag(ptr, tag);
    EnvironmentRegisterVariable(env, ptr);
}

void EnvironmentRegisterGlobals(Environment *env)
{
    /*
    * Creating Constants
    */
    FuzuliValue *truevalue = FuzuliValueCreateInteger(1);
    FuzuliValue *falsevalue = FuzuliValueCreateInteger(0);
    FuzuliValue *pivalue = FuzuliValueCreateDouble(3.14159265);

    /*
    * Creating pointers for basic internal functions
    */
    EnvironmentRegisterInternalFunction(env, doPlusOperation, "+");
    EnvironmentRegisterInternalFunction(env, doProductOperation, "*");
    EnvironmentRegisterInternalFunction(env, doSubstractOperation, "-");
    EnvironmentRegisterInternalFunction(env, doDivideOperation, "/");
    EnvironmentRegisterInternalFunction(env, doLessOperation, "<");
    EnvironmentRegisterInternalFunction(env, doBiggerOperation, ">");
    EnvironmentRegisterInternalFunction(env, doLessOrEqualsOperation, "<=");
    EnvironmentRegisterInternalFunction(env, doBiggerOrEqualsAOperation, ">=");
    EnvironmentRegisterInternalFunction(env, doEqualsOperation, "=");
    EnvironmentRegisterInternalFunction(env, doNotEqualsOperation, "!=");
    EnvironmentRegisterInternalFunction(env, doNotOperation, "not");

    EnvironmentRegisterInternalFunction(env, doDumpOperation, "dump");
    EnvironmentRegisterInternalFunction(env, doPrintOperation, "print");
    EnvironmentRegisterInternalFunction(env, doPrintlnOperation, "println");
    EnvironmentRegisterInternalFunction(env, doLetOperation, "let");
    EnvironmentRegisterInternalFunction(env, doIfOperation, "if");
    EnvironmentRegisterInternalFunction(env, doWhileOperation, "while");
    EnvironmentRegisterInternalFunction(env, doBreakOperation, "break");
    EnvironmentRegisterInternalFunction(env, doTypeofOperation, "typeof");
    EnvironmentRegisterInternalFunction(env, doListOperation, "list");
    EnvironmentRegisterInternalFunction(env, doPrintOperation, "print");
    EnvironmentRegisterInternalFunction(env, doLengthOperation, "length");
    EnvironmentRegisterInternalFunction(env, doNthOperation, "nth");
    EnvironmentRegisterInternalFunction(env, doAppendOperation, "append");
    EnvironmentRegisterInternalFunction(env, doPrependOperation, "prepend");
    EnvironmentRegisterInternalFunction(env, doMemoryOperation, "memory");
    EnvironmentRegisterInternalFunction(env, doRmOperation, "rm");
    EnvironmentRegisterInternalFunction(env, doIsNullOperation, "isnull");
    EnvironmentRegisterInternalFunction(env, doRangeOperatorOperation, ":");
    EnvironmentRegisterInternalFunction(env, doParamsOperation, "params");
    EnvironmentRegisterInternalFunction(env, doIncOperation, "inc");
    EnvironmentRegisterInternalFunction(env, doBlockOperation, "block");
    
    EnvironmentRegisterInternalFunction(env, doStrcmpOperation, "strcmp");
    EnvironmentRegisterInternalFunction(env, doStrlenOperation, "strlen");

    /*
    * Setting variable names
    */
    FuzuliValueSetTag(truevalue, "true");
    FuzuliValueSetTag(falsevalue, "false");
    FuzuliValueSetTag(pivalue, "pi");

    /*
    * Registering variables
    */
    EnvironmentRegisterVariable(env, truevalue);
    EnvironmentRegisterVariable(env, falsevalue);
    EnvironmentRegisterVariable(env, pivalue);

    LinkedList *list = env->FuzuliValues;
    unsigned int len = LinkedListLength(list);

    LinkedListElement *llelement = list->first;
    for (unsigned int i = 0; i < len; i++)
    {
        ((FuzuliValue *)llelement->value)->protected = 1;
        llelement = llelement->next;
    }
}
