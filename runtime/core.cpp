#include <vector>
#include <iostream>
#include <cstring>

#include "token.h"

using namespace std;

namespace fuzuli{
namespace core {

Token *print(vector<Token*> &allcall){
    Token *tok;
    for (unsigned int i=1; i < allcall.size(); i++){
        tok = allcall[i];
        cout <<  fuzuli::token_as_string(tok);
    }
    return(new_null_token());
}

Token *strlen_(vector<Token*> &allcall){
    Token *tok;
    Token *result = new_integer_token(0);
    tok = allcall[1];
    result->value.i_val = std::strlen(token_as_string(tok));    
    return(result);
}


} /* end of namespace core */
} /* end of namespace fuzuli */