
#ifndef LEXER_H
#define LEXER_H

#include "linkedlist.h"
#include "string.h"
#include "token.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct LexerState_ {
        unsigned int startPosition;
        unsigned int currentPosition;
        unsigned int lastPosition;
        unsigned int lineNumber;
        char *sourcecode;
    }LexerState;

    
    LexerState *LexerCreateState(unsigned int start, unsigned int current, unsigned int last);
    LinkedList *LexerExtractTokens(String* sourcecode);
    char LexerConsumeChar(LexerState *state);
    void LexerPutbackChar(LexerState *state);
    Token* LexerGetNextToken(LexerState *state);
    LinkedList *LexerExtractTokens(String *sourcecode);

#ifdef __cplusplus
}
#endif

#endif /* LEXER_H */

