#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "fmemory.h"

Token* TokenNew(unsigned int type, const char *content){
    Token *tok = (Token*) fmalloc(sizeof(Token));
    char *ch = (char*) fmalloc(strlen(content) + 1);
    strcpy(ch, content);
    ch[strlen(content) + 1] = '\0';
    tok->type = type;
    tok->content = ch;
    return tok;
}

Token* TokenNewFromChar(unsigned int type, char content){
    Token *tok = (Token*) fmalloc(sizeof(Token));
    char *ch = (char*) fmalloc(2);
    ch[0] = content;
    ch[1] = '\0';
    tok->type = type;
    tok->content = ch;
    return tok;
}


void TokenFree(Token *token){
    ffree((void*)token->content);
    ffree(token);
}
    
