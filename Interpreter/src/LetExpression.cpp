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

namespace fuzuli {

using namespace std;

LetExpression::LetExpression(vector<Expression*> expr) {
	this->expressions = expr;
	//this->resultToken = Token::NULL_TOKEN;
	this->type = LET_EXPRESSION;
}

LetExpression::~LetExpression() {
	// TODO Auto-generated destructor stub
}

Token *LetExpression::eval(Environment *env) {
	Token *varname = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Token *result = this->expressions[1]->eval(env);
	Token *oldvariable = env->getVariable(varname->getContent());
	if (oldvariable->getKillable()) {
		oldvariable->ReduceReferences();
	}
	env->setVariable(varname->getContent(), result);
	if (result->getKillable()) {
		result->IncreaseReferences();
	}
	return (result);
}


DefExpression::DefExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = DEF_EXPRESSION;
}

DefExpression::~DefExpression() {

}

Token *DefExpression::eval(Environment *env) {
	Token *var =
			dynamic_cast<IdentifierExpression*>(this->expressions[0])->stringToken;
	Token *typeint = this->expressions[1]->eval(env);
	Token *allready = env->getVariableInThisScope(var->getContent());

	if (allready) {
		cout << var->getContent() << " is already defined" << endl;
		exit(-1);
	}
	env->setVariableInThisScope(var->getContent(), typeint);
	return (Token::NULL_TOKEN);
}


CloneExpression::CloneExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = CLONE_EXPRESSION;
}

CloneExpression::~CloneExpression() {

}

Token *CloneExpression::eval(Environment *env) {
	Token *tok = this->expressions[0]->eval(env);
	return (tok->clone());
}


} /* namespace fuzuli */
