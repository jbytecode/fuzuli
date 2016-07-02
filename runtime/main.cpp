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
        Token *t1 = fuzuli::parser::run_expression();
        //Token *t2 = fuzuli::parser::run_expression();
        //Token *t3 = fuzuli::parser::run_expression();
        cout << "Return of 1 "<< (t1 == NULL) << endl;
        //cout << "Return of 2 "<< t2->type << endl;
        //cout << "Return of 3 "<< t3->type << endl;
    }
    cout << "Done." << endl;
    return(0);
}