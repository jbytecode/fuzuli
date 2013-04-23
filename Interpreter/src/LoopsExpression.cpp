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
#include <cstring>
#include <cstdlib>
#include <vector>

namespace fuzuli {


using namespace std;

ForExpression::ForExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FOR_EXPRESSION;
}

ForExpression::~ForExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable ForExpression::eval(Environment *env) {
	env->createLocal();
	this->expressions->at(0)->eval(env);
	FuzuliVariable condition;
	FuzuliVariable result;
	unsigned int i=3;
	while (1) {
		condition = this->expressions->at(1)->eval(env);
		if (this->getIntValue(condition) == 0) {
			break;
		}
		i=3;
		while (i < this->expressions->size()) {
			result = this->expressions->at(i)->eval(env);
			if (result.breakFlag) {
				result.breakFlag = false;
				env->deleteLocal();
				return (result);
				break;
			}
			i++;
		}
		this->expressions->at(2)->eval(env);
	}
	env->deleteLocal();
	FuzuliVariable f; f.type = NULLTOKEN;
	return (f);
}


ForEachExpression::ForEachExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FOREACH_EXPRESSION;
	Token *in = ((IdentifierExpression*) this->expressions->at(1))->stringToken;
		if (strcmp(in->getContent(), "in") != 0) {
			cout << "Keyword 'in' required in foreach expression" << endl;
			exit(-1);
		}
}

ForEachExpression::~ForEachExpression() {

}

FuzuliVariable ForEachExpression::eval(Environment *env) {
	env->createLocal();
	FuzuliVariable result = Expression::createNewNull();
	const char *iden = ((IdentifierExpression*) this->expressions->at(0))->id;
	FuzuliVariable list = this->expressions->at(2)->eval(env);

	vector<FuzuliVariable> *listVector = (vector<FuzuliVariable>*)list.v;
	env->setVariableInThisScope(iden, listVector->at(0));

	for (unsigned int i = 0; i < listVector->size(); i++) {
		env->setVariable(iden, listVector->at(i));

		for (unsigned int u = 3; u < this->expressions->size(); u++) {
			result = this->expressions->at(u)->eval(env);
			if (result.breakFlag) {
				result.breakFlag = false;
				env->deleteLocal();
				return (result);
			}
		}

	}

	env->deleteLocal();
	return (result);
}



DoTimesExpression::DoTimesExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DOTIMES_EXPRESSION;
}

DoTimesExpression::~DoTimesExpression() {

}

FuzuliVariable DoTimesExpression::eval(Environment *env) {
	env->createLocal();
	FuzuliVariable condition;
	FuzuliVariable result;
	const char  *iden =
			(dynamic_cast<IdentifierExpression*>(this->expressions->at(0)))->id;
	FuzuliVariable max = this->expressions->at(1)->eval(env);
	condition = Expression::createNewInt(0);
	env->setVariableInThisScope(iden, condition);

	while (1) {
		for (unsigned int i = 2; i < this->expressions->size(); i++) {
			result = this->expressions->at(i)->eval(env);
			if (result.breakFlag) {
				result.breakFlag = false;
				env->deleteLocal();
				return (result);
				break;
			}
		}
		result = env->getVariableInThisScope(iden);
		result.i = ( Expression::getIntValue(result) + 1 ); result.type = INTEGER ;
		env->setVariable(iden, result);
		if (Expression::getIntValue(result) >= Expression::getIntValue(max)) {
			break;
		}
	}

	env->deleteLocal();
	return (result);
}


WhileExpression::WhileExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = WHILE_EXPRESSION;
}

WhileExpression::~WhileExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable WhileExpression::eval(Environment *env) {
	env->createLocal();
	FuzuliVariable condition;
	FuzuliVariable result = Expression::createNewNull();
	while (1) {
		condition = this->expressions->at(0)->eval(env);
		if (Expression::getIntValue(condition) == 0) {
			break;
		}

		for (unsigned int ui = 1; ui < this->expressions->size(); ui++) {
			result = this->expressions->at(ui)->eval(env);
			if (result.breakFlag) {
				result.breakFlag = false;
				env->deleteLocal();
				return (result);
			}

		}

	}
	env->deleteLocal();
	return (result);
}



BreakExpression::BreakExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BREAK_EXPRESSION;
}

BreakExpression::~BreakExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable BreakExpression::eval(Environment *env) {
	FuzuliVariable result;
	result.type = BREAKTOKEN;
	result.breakFlag = true;
	return (result);
}



} /* namespace fuzuli */

