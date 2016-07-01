#include <iostream>
#include "sourcecode.h"
#include "parser.h"

int main(int argc, char **argv){
    if(argc <= 1){
        std::cout << "Usage: fuzuli filename.fzl" << std::endl;
    }else{
        string code = fuzuli::sourcecode::loadcode(argv[1]);
        fuzuli::parser::init_parser(code);
        fuzuli::parser::parse();
    }
    return(0);
}