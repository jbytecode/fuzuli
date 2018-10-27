#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "linkedlist.h"

typedef enum {
    EXPR_STRING, 
    EXPR_IDENTIFIER, 
    EXPR_NUMBER_CONSTANT,
    EXPR_END
} EXPRESSION_TYPE;

typedef struct {
    unsigned int type;
    LinkedList *arguments;
    char *tag;
} Expression;


Expression *ExpressionNew(unsigned int type);
void ExpressionPrint(Expression *expr, unsigned int deepness);
void ExpressionSetTag(Expression *expr, char *tag);
Expression *ExpressionNewWithTag(unsigned int type, char *tag);

#endif
