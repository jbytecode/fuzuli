
#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "expression.h"
#include "linkedlist.h"
    typedef struct ParserState{
        unsigned int index;
        unsigned int end;
    }ParserState;
    
    ParserState *ParserStateNew(unsigned int end);
    LinkedList *getExpressionList(LinkedList *tokenlist, ParserState *state);
    Expression *getNextExpression(LinkedList *tokenlist, ParserState *state);


#ifdef __cplusplus
}
#endif

#endif /* PARSER_H */

