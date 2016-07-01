#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "sourcecode.h"

using namespace std;

namespace fuzuli {
    namespace parser {
        unsigned char pos1;
        unsigned char pos2;
        std::string sourcecode;

        void init_parser(string code){
            pos1 = 0;
            pos2 = 0;
            sourcecode = code;
        }

        char readc (){
            if(pos1 <= sourcecode.length()){
                return(sourcecode[pos1]);
            }else{
                return(-1);
            }
        }

        void eat (){
            pos1++;
            if(pos1 > sourcecode.length()){
                cout << "Cannot eat source code, char expected at pos "<< pos1 << " but ";
                cout << "length of source is " << sourcecode.length() << endl;
                std::exit(-1);
            }
        }

        Token *get_next_token(){
            Token *tok = new Token();
            char c;
            stringstream ss;
            c = readc();
            if(isspace(c)){
                eat();
                return(get_next_token());
            }else if(c=='('){
                eat();
                tok->type = LPARAN;
                return(tok);
            }else if (c==')'){
                eat();
                tok->type = RPARAN;
                return(tok);
            }else if (isalpha(c)){
                ss << c;
                eat();
                while(true){
                    c = readc();
                    if(isalnum(c) || c == '_'){
                        ss << c;
                        eat();
                    }else{
                        break;
                    }
                }
                tok->type = IDENTIFIER;
                tok->value.ptr_val = (void*)ss.str().c_str();
                return(tok); 
            }else if (c == '"'){
                eat();
                while(true){
                    c = readc();
                    if(c=='"'){
                        eat();
                        break;
                    }
                    ss << c;
                    eat();
                }
                tok->type = STRING;
                tok->value.ptr_val = (void*) ss.str().c_str();
                return(tok);
            }
            tok->type = _NULL;
            return(tok);
        }

        void parse(){
            Token *tok;
            while(true){
                tok = get_next_token();
                if(tok->type == _NULL){
                    break;
                }
                cout << "Token Read: " << tok->type << " ";
                if(tok->type == IDENTIFIER || tok->type == STRING){
                    cout << (char*)tok->value.ptr_val;
                }
                cout << endl;
            }
        }
    } // end of namespace parser
} // end of namespace fuzuli