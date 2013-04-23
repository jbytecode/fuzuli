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

BlockExpression::BlockExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BLOCK_EXPRESSION;
}

BlockExpression::~BlockExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable BlockExpression::eval(Environment *env) {
	FuzuliVariable result = Expression::createNewNull();
	env->createLocal();
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		result = this->expressions->at(i)->eval(env);
		if (result.breakFlag || result.returnFlag) {
			env->deleteLocal();
			return (result);
		}
	}
	env->deleteLocal();
	return (result);
}

/*
 GroupExpression::GroupExpression(vector<Expression*> *expr) {
 this->expressions = expr;
 this->type = GROUP_EXPRESSION;
 }

 GroupExpression::~GroupExpression() {
 // TODO Auto-generated destructor stub
 }

 Token *GroupExpression::eval(Environment *env) {
 Token *result = Token::NULL_TOKEN;
 for (unsigned int i = 0; i < this->expressions->size(); i++) {
 result = this->expressions->at(i)->eval(env);
 if (result) {
 if (result->breakFlag == 1) {
 env->doAutomaticGCwithProtection(result);
 return (result);
 } else if (result->returnFlag == 1) {
 env->doAutomaticGCwithProtection(result);
 return (result);
 }
 }
 }
 return (result);
 }

 */
} /* namespace fuzuli */
