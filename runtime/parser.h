#ifndef __parser_h__
#define __parser_h__

#include <string>
#include <iostream>

#include "token.h"
#include "sourcecode.h"
#include "expression.h"

using namespace std;

namespace fuzuli {
    namespace parser {
       
        void init_parser(string code);
       
        char readc ();
       
        Token *get_next_token();

        Token *parse();

        fuzuli::expression::Expression *parse_expression();
        
    } // end of namespace parser
} // end of namespace fuzuli

#endif