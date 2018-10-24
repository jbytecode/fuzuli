#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expression.h"
#include "linkedlist.h"

Expression *ExpressionNew(unsigned int type){
    Expression *expr = (Expression*)malloc(sizeof(Expression));
    expr->type = type;
    LinkedList *list = LinkedListNew();
    expr->arguments = list;
    return(expr);
}

Expression *ExpressionNewWithTag(unsigned int type, char *tag){
    Expression *expr = ExpressionNew(type);
    ExpressionSetTag(expr, tag);
    return(expr);
}


void ExpressionSetTag(Expression *expr, char *tag){
    expr->tag = (char*)malloc(strlen(tag));
    strcpy(expr->tag, tag);
}

void ExpressionPrint(Expression *expr){
    unsigned int len = LinkedListLength(expr->arguments);
    printf("Expression{type: %u, NumArgs: %u, Tag: %s}[", expr->type, len, expr->tag);
    for (unsigned int i = 0; i < len; i++){
        Expression *subexpr = (Expression*)LinkedListGet(expr->arguments, i);
        ExpressionPrint(subexpr);
    }
    printf("]\n");
}
