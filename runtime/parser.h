#include <string>
#include <iostream>

#include "token.h"
#include "sourcecode.h"

using namespace std;

namespace fuzuli {
    namespace parser {
       
        void init_parser(string code);
       
        char readc ();
       
        Token *get_next_token();

        void parse();
        
    } // end of namespace parser
} // end of namespace fuzuli