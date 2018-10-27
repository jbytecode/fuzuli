
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

