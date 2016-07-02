#ifndef __token_h__
#define __token_h__

#include <string>

namespace fuzuli {


enum _TokenType {
    LPARAN,
    RPARAN,
    IDENTIFIER,
    STRING,
    _NULL
};

typedef enum _TokenType TokenType;

struct _Token {
    TokenType type;
    union  {
        int i_val;
        double d_val;
        void *ptr_val;
    } value;
};

typedef struct _Token Token;


} // End of namespace fuzuli

#endif
