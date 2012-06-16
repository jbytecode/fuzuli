/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/FuzuliTypes.h"
#include <vector>
#include <sstream>

namespace fuzuli {

using namespace std;

BlockExpression::BlockExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BlockExpression::~BlockExpression() {
	// TODO Auto-generated destructor stub
}

Token *BlockExpression::eval(Environment *env) {
	Token *result = Token::NULL_TOKEN;
	Environment *blockEnvironment = env->createNext();
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		result = this->expressions[i]->eval(blockEnvironment);
		if (result) {
			if (result->breakFlag==1) {
				return (result->clone());
			}else if (result->returnFlag==1){
				return(result->clone());
			}
		}
	}
	return (result);
}

void BlockExpression::emitCpp(stringstream *ss){
	(*ss)<<"{"<<endl;
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss)<<"}"<<endl;
}

} /* namespace fuzuli */
