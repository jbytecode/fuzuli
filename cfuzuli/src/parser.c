#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "parser.h"
#include "expression.h"
#include "linkedlist.h"
#include "token.h"

ParserState *ParserStateNew(unsigned int end)
{
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->end = end;
    state->index = 0;
    return (state);
}

LinkedList *getExpressionList(LinkedList *tokenlist, ParserState *state)
{
    LinkedList *exprs = LinkedListNew();
    Expression *e;
    while (TRUE)
    {
        e = getNextExpression(tokenlist, state);
        if (e == NULL)
        {
            return exprs;
        }
        LinkedListAdd(exprs, (void *)e);
        state->index++;
    }
    return (exprs);
}

Expression *getNextExpression(LinkedList *tokenlist, ParserState *state)
{
    Expression *expr;
    if (state->index > state->end - 1)
    {
        return NULL;
    }
    Token *previousToken;
    Token *tok = (Token *)LinkedListGet(tokenlist, state->index);
    LinkedList *others;
    //printf("We get: %s, state: %u, end: \n", tok->content, state->index);
    unsigned int type = tok->type;
    switch (type)
    {
    case TOKEN_LPARAN:
        state->index++;
        return getNextExpression(tokenlist, state);
        break;
    case TOKEN_RPARAN:
        //expr = ExpressionNew(EXPR_END);
        //state->index++;
        //return expr;
        return NULL;
        break;
    case TOKEN_IDENTIFIER:
        previousToken = (Token *)LinkedListGet(tokenlist, (state->index - 1));
        expr = ExpressionNew(EXPR_IDENTIFIER);
        ExpressionSetTag(expr, (char *)tok->content);
        if (previousToken->type == TOKEN_LPARAN)
        {
            state->index++;
            others = getExpressionList(tokenlist, state);
            if (others != NULL)
            {
                for (unsigned int i = 0; i < LinkedListLength(others); i++)
                {
                    LinkedListAdd(expr->arguments, (void *)LinkedListGet(others, i));
                }
            }
        }
        return (expr);
        break;
    case TOKEN_NUMBER_CONSTANT:
        expr = ExpressionNew(EXPR_NUMBER_CONSTANT);
        ExpressionSetTag(expr, (char *)tok->content);
        return (expr);
        break;
    case TOKEN_STRING:
        expr = ExpressionNew(EXPR_STRING);
        ExpressionSetTag(expr, (char *)tok->content);
        return (expr);
        break;
    }
    return expr;
}