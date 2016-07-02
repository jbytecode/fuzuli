#ifndef __token_h__
#define __token_h__

#include <string>

namespace fuzuli {


enum _TokenType {
    LPARAN,         /* 0 */
    RPARAN,         /* 1 */
    IDENTIFIER,     /* 2 */
    STRING,         /* 3 */
    INTEGER_CONSTANT,
    DOUBLE_CONSTANT,
    INTEGER,
    DOUBLE,
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

char *new_char_array(const char *str);
Token *new_integer_token(int i);
Token *new_null_token();
char *token_as_string(Token *tok);

} // End of namespace fuzuli

#endif
