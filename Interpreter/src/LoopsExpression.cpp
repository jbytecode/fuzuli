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

ForExpression::ForExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ForExpression::~ForExpression() {
	// TODO Auto-generated destructor stub
}

Token *ForExpression::eval(Environment *env) {
	Environment *forEnvironment;
	if (!env->next) {
		forEnvironment = env->createNext();
	} else {
		forEnvironment = env->next;
	}
	this->expressions[0]->eval(forEnvironment); /* Starter */
	Token *condition;
	Token *result = Token::NULL_TOKEN;
	while (1) {
		condition = this->expressions[1]->eval(forEnvironment);
		if (condition->getIntValue() == 0) {
			break;
		}
		for (unsigned int i = 3; i < this->expressions.size(); i++) {
			result = this->expressions[i]->eval(forEnvironment);
			if (result->breakFlag) {
				result->breakFlag = 0;
				return (result);
				break;
			}
		}
		this->expressions[2]->eval(forEnvironment);
	}
	if (!result) {
		result = Token::NULL_TOKEN;
	}
	return (result);
}

ForEachExpression::ForEachExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ForEachExpression::~ForEachExpression() {

}

Token *ForEachExpression::eval(Environment *env) {
	Environment *foreachenv = env->createNext();
	Token *iden = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Token *in = ((IdentifierExpression*) this->expressions[1])->stringToken;
	if (strcmp(in->getContent(), "in") != 0) {
		cout << "Keyword 'in' required in foreach expression" << endl;
		exit(-1);
	}
	Token *list = this->expressions[2]->eval(env);
	for (unsigned int i = 0; i < list->tokens.size(); i++) {
		foreachenv->setVariable(iden->getContent(), list->tokens[i]);
		for (unsigned int u = 3; u < this->expressions.size(); u++) {
			Token *result = this->expressions[u]->eval(foreachenv);
			if (result->breakFlag) {
				result->breakFlag = 0;
				return (result);
				break;
			}
		}
	}
	return (Token::NULL_TOKEN);
}

DoTimesExpression::DoTimesExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

DoTimesExpression::~DoTimesExpression() {

}

Token *DoTimesExpression::eval(Environment *env) {
	Environment *dotimesEnvironment = env->createNext();
	Token *condition;
	Token *result;
	Token *iden =
			(dynamic_cast<IdentifierExpression*>(this->expressions[0]))->stringToken;
	Token *max = this->expressions[1]->eval(env);
	condition = dotimesEnvironment->newToken(0.0, INTEGER);
	dotimesEnvironment->setVariableInThisScope(iden->getContent(), condition);
	condition->IncreaseReferences();
	while (1) {
		for (unsigned int i = 2; i < this->expressions.size(); i++) {
			result = this->expressions[i]->eval(dotimesEnvironment);
			if (result->breakFlag) {
				result->breakFlag = 0;
				return (result);
				break;
			}
		}
		result = dotimesEnvironment->getVariableInThisScope(iden->getContent());
		result->setIntValue(result->getIntValue() + 1);
		if (result->getIntValue() >= max->getIntValue()) {
			break;
		}
	}
	return (this->resultToken);
}

WhileExpression::WhileExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

WhileExpression::~WhileExpression() {
	// TODO Auto-generated destructor stub
}

Token *WhileExpression::eval(Environment *env) {
	Environment *whileEnvironment = env->createNext();
	Token *condition;
	Token *result = Token::NULL_TOKEN;
	while (1) {
		condition = this->expressions[0]->eval(whileEnvironment);
		if (condition->getIntValue() == 0) {
			break;
		}

		for (unsigned int ui = 1; ui < this->expressions.size(); ui++) {
			result = this->expressions[ui]->eval(whileEnvironment);
			if (result->breakFlag == 1) {
				result->breakFlag = 0;
				return (result);
			}

		}

	}
	return (result);
}

BreakExpression::BreakExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BreakExpression::~BreakExpression() {
	// TODO Auto-generated destructor stub
}

Token *BreakExpression::eval(Environment *env) {
	Token *result = env->newToken("@BREAK", BREAKTOKEN);
	result->breakFlag = 1;
	return (result);
}

} /* namespace fuzuli */

