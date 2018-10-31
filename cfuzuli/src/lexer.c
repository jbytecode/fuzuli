#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"
#include "string.h"
#include "lexer.h"
#include "constants.h"
#include "token.h"
#include "ferror.h"
#include "fmemory.h"


LexerState *LexerCreateState(unsigned int start, unsigned int current, unsigned int last) {
    LexerState *state = (LexerState*) (fmalloc(sizeof (LexerState)));
    state->startPosition = start;
    state->currentPosition = current;
    state->lastPosition = last;
    state->lineNumber = 0;
    return (state);
}

LinkedList *LexerExtractTokens(String *sourcecode) {
    unsigned int len = sourcecode->length;
    LexerState *state = LexerCreateState(0, 0, len - 1);
    state->sourcecode = sourcecode->chars;
    LinkedList *listOfTokens = LinkedListNew();
    while (TRUE) {
        Token *tok = LexerGetNextToken(state);
        if(tok == NULL || tok->type == TOKEN_NULLCHARACTER){
            break;
        }
        LinkedListAdd(listOfTokens, tok);
    }
    return listOfTokens;
}

char LexerConsumeChar(LexerState *state) {
    if (state->currentPosition > state->lastPosition) {
        return '\0';
    }
    char result = state->sourcecode[state->currentPosition];
    state->currentPosition++;
    return result;
}

char LexerLookNextChar(LexerState *state) {
    if (state->currentPosition  > state->lastPosition) {
        return '\0';
    }
    char result = state->sourcecode[state->currentPosition];
    return result;
}


void LexerPutbackChar(LexerState *state) {
    state->currentPosition--;
    if (state->currentPosition < state->startPosition) {
        state->currentPosition = state->startPosition;
    }
}

Token* LexerGetNextToken(LexerState *state) {
    char currentChar = LexerConsumeChar(state);
    String *result;
    Token *tok;
    if (currentChar == '(') {
        tok = TokenNew(TOKEN_LPARAN, "(");
    } else if (currentChar == ')') {
        tok = TokenNew(TOKEN_RPARAN, ")");
    } else if(isalpha(currentChar)){
        result = StringNew("");
        while(isalnum(currentChar)){
            StringAppendChar(result, currentChar);
            currentChar = LexerConsumeChar(state);
        }
        LexerPutbackChar(state);
        tok = TokenNew(TOKEN_IDENTIFIER, result->chars);
    }else if(currentChar == '"'){
        result = StringNew("");
        currentChar = LexerConsumeChar(state);
        while(currentChar != '"'){
            if(currentChar == '\\'){
                char nextChar = LexerConsumeChar(state);
                if(nextChar == 'n'){
                    currentChar = '\n';
                }else if (nextChar == 'r'){
                    currentChar = '\r';
                }else if (nextChar == 't'){
                    currentChar = '\t';
                }
            }
            StringAppendChar(result, currentChar);
            currentChar = LexerConsumeChar(state);
            if(state->currentPosition > state->lastPosition){
                char message[1024];
                sprintf(message, "Incomplete string constant at line %u.", state->lineNumber + 1);
                ErrorAndTerminate(message, -1);
            }
        }
        tok = TokenNew(TOKEN_STRING, result->chars);
    }else if(isspace(currentChar)){
        if(currentChar == '\n'){
            state->lineNumber++;
        }
        return LexerGetNextToken(state);
    }else if(isdigit(currentChar)){
        result = StringNewFromChar(currentChar);
        currentChar = LexerConsumeChar(state);
        while(isdigit(currentChar) || currentChar == '.'){
            StringAppendChar(result, currentChar);
            currentChar = LexerConsumeChar(state);
        }
        LexerPutbackChar(state);
        tok = TokenNew(TOKEN_NUMBER_CONSTANT, result->chars);
    }else if(currentChar == '!'){
        char next = LexerLookNextChar(state);
        if(next == '='){
            currentChar = LexerConsumeChar(state);
            tok = TokenNew(TOKEN_IDENTIFIER, "!=");
            currentChar = LexerConsumeChar(state);
        }
    }else if(currentChar == '#'){
        while(1){
            if(currentChar == '\n' || currentChar == '\r'){
                state->lineNumber++;
                break;
            }
            currentChar = LexerConsumeChar(state);
        }
        return LexerGetNextToken(state);
    }else if (ispunct(currentChar)){
        char next = LexerLookNextChar(state);
        if(ispunct(next)){
            char compount[3];
            compount[0] = currentChar;
            compount[1] = next;
            compount[2] = '\0';
            tok = TokenNew(TOKEN_IDENTIFIER, (const char*)&compount);
            currentChar = LexerConsumeChar(state);
        }else{
            tok = TokenNewFromChar(TOKEN_IDENTIFIER, currentChar);
        }
    }else if (currentChar == '\0') {
        result = StringNewFromChar('\0');
        tok = TokenNew(TOKEN_NULLCHARACTER, "\0");
    } else {
        printf("Char '%c' (%d) not found at position '%ud' in source '%s'\n", currentChar, (int) currentChar,
                state->currentPosition, state->sourcecode);
        result = StringNew("\0");
    }
    return tok;
}



