/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   token.h
 * Author: istar1
 *
 * Created on 23 Ekim 2018 Salı, 20:31
 */

#ifndef TOKEN_H
#define TOKEN_H

#ifdef __cplusplus
extern "C" {
#endif


    typedef struct Token {
        unsigned int type;
        const char *content;
    } Token;
    
    typedef enum {
        TOKEN_LPARAN,
        TOKEN_RPARAN,
        TOKEN_IDENTIFIER,
        TOKEN_NUMBER_CONSTANT,
        TOKEN_STRING,
        TOKEN_NULLCHARACTER
    } TokenType; 

    Token* TokenNew(unsigned int type, const char *content);
    Token* TokenNewFromChar(unsigned int type, char content);
    void TokenFree(Token *token);
    

#ifdef __cplusplus
}
#endif

#endif /* TOKEN_H */

