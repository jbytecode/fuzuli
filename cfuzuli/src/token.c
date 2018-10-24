#include <stdlib.h>
#include <string.h>
#include "token.h"

Token* TokenNew(unsigned int type, const char *content){
    Token *tok = (Token*) malloc(sizeof(Token));
    char *ch = (char*) malloc(strlen(content) + 1);
    strcpy(ch, content);
    ch[strlen(content) + 1] = '\0';
    tok->type = type;
    tok->content = ch;
    return tok;
}

void TokenFree(Token *token){
    free((void*)token->content);
    free(token);
}
    
