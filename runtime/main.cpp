#include <iostream>
#include "sourcecode.h"
#include "parser.h"
#include "token.h"
#include "expression.h"

using namespace fuzuli;
using namespace fuzuli::parser;

int main(int argc, char **argv){
    if(argc <= 1){
        std::cout << "Usage: fuzuli filename.fzl" << std::endl;
    }else{
        string code = fuzuli::sourcecode::loadcode(argv[1]);
        fuzuli::parser::init_parser(code);
        fuzuli::expression::Expression *expr = fuzuli::parser::parse_expression();
        cout << "Expression type: " << expr->type << endl;
        cout << "Expression constant: " << expr->constant.cc << endl;
        cout << "Expression params count :" << expr->expressions.size() << endl;
    }
    return(0);
}