#include <string>
#include "token.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

namespace fuzuli{
    
    char *new_char_array(const char *str){
        char *c = (char*)malloc(1 + strlen(str));
        strcpy(c, str);
        return(c);
    }

    Token *new_integer_token(int i){
        Token *t = new Token;
        t->type = INTEGER;
        t->value.i_val = i;
        return(t);
    }

    Token *new_null_token(){
        Token *t = new Token();
        t->type = _NULL;
        return(t);
    }

    char *token_as_string(Token *tok){
        if(tok->type == STRING || tok->type == IDENTIFIER){
            int len = std::strlen((char*)tok->value.ptr_val);
            char *res = new char[len+1];
            std::strcpy(res, (char*)tok->value.ptr_val); 
            return(res);
        }else if (tok->type == INTEGER){
            char *buf = new char[3];
            std::sprintf(buf, "%d", tok->value.i_val);
            return(buf);
        }else if (tok->type == LPARAN){
            char *buf = new char[1];
            std::sprintf(buf, "(");
            return(buf);
        }else if (tok->type == RPARAN){
            char *buf = new char[1];
            std::sprintf(buf, ")");
            return(buf);
        }else if (tok->type == _NULL){
            char *buf = new char[4];
            std::sprintf(buf, "NULL");
            return(buf);
        }
        std::cout << "token_as_string can not determine what to do" << endl;
        return(NULL);
    }
}