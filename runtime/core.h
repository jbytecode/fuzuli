#ifndef __core_h__
#define __core_h__

#include <vector>
#include "token.h"

using namespace std;

namespace fuzuli {
namespace core{
    Token *print(vector<Token*> &allcall);
    Token *strlen_(vector<Token*> &allcall);
}
}


#endif