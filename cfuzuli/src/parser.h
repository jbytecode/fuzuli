/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   parser.h
 * Author: istar1
 *
 * Created on 23 Ekim 2018 Salı, 21:04
 */

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

