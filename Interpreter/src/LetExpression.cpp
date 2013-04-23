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
#include <stdlib.h>
#include <string.h>

namespace fuzuli {

using namespace std;


LetExpression::LetExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	//this->resultToken = Token::NULL_TOKEN;
	this->type = LET_EXPRESSION;
}

LetExpression::~LetExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable LetExpression::eval(Environment *env) {
	const char *varname = ((IdentifierExpression*) this->expressions->at(0))->id;
	FuzuliVariable result = this->expressions->at(1)->eval(env);
	env->setVariable(varname, result);
	return (result);
}



DefExpression::DefExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DEF_EXPRESSION;
}

DefExpression::~DefExpression() {

}

FuzuliVariable DefExpression::eval(Environment *env) {
	const char* var =
			dynamic_cast<IdentifierExpression*>(this->expressions->at(0))->id;
	FuzuliVariable typeint = this->expressions->at(1)->eval(env);
	FuzuliVariable allready = env->getVariableInThisScope(var);

	if (allready.type != NULLTOKEN) {
		cout << var << " is already defined" << endl;
		exit(-1);
	}
	FuzuliVariable f = Expression::createNewInt(0);
	env->setVariableInThisScope(var, f);
	return (f);
}

/*
CloneExpression::CloneExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = CLONE_EXPRESSION;
}

CloneExpression::~CloneExpression() {

}

Token *CloneExpression::eval(Environment *env) {
	Token *tok = this->expressions->at(0)->eval(env);
	return (tok->clone());
}

*/
} /* namespace fuzuli */
