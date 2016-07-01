#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include "token.h"

using namespace std;

namespace fuzuli {
    namespace sourcecode{
        
        std::string loadcode (const char *filename){
            string line;
            stringstream buffer;
            
            ifstream freader(filename);
            
            buffer << freader.rdbuf();
            freader.close();
            
            return(buffer.str());
        }  

    } /* end of namespace sourcode */
} /* end of namespace fuzuli */