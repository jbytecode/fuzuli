#include <stdlib.h>
#include "ferror.h"
#include "expression.h"
#include "linkedlist.h"
#include "fuzulitypes.h"

void ErrorAndTerminate(const char *errmessage,  int errorcode){
    printf("*** Termination due to error: '%s'\n", errmessage);
    printf("*** Exiting with error code %d\n", errorcode);
    exit(errorcode);    
}

void ErrorAndTerminateExpression(const char *errmessage,  int errorcode, Expression *expr){
    printf("In expression '%s' with arguments: ", expr->tag);
    LinkedList *arguments = (LinkedList*) expr->arguments;
    unsigned int len = LinkedListLength(arguments);
    for (unsigned int i = 0; i < len; i++){
        Expression *subexpr = (Expression*)LinkedListGet(arguments, i);
        printf("\t%s", subexpr->tag); 
    }
    printf("\n");
    ErrorAndTerminate(errmessage, errorcode);
}

void ErrorAndTerminateAfterTypeCheck(FuzuliValue *val1, FuzuliValue *val2, Expression *expr){
    if(val1->type != val2->type){
        ErrorAndTerminateExpression("Variable types are different", -1, expr);
    }
}