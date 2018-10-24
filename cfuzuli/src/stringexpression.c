#include <stdlib.h>
#include "fuzulitypes.h"
#include "expression.h"
#include "string.h"
#include "linkedlist.h"

Expression *string_expression_new(char *value){
    Expression *expr = (Expression*) malloc(sizeof(Expression));
    String *stringvalue = StringNew(value);
    FuzuliValue *fvalue = FuzuliValueCreateString(value);

    LinkedList *arguments = LinkedListNew();
    fvalue->svalue = stringvalue;
   

    LinkedListAdd(arguments,fvalue);

    expr->type = EXPR_STRING;
    expr->arguments = arguments;
    
    return(expr);
}