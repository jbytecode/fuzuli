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
#include <cstdlib>
#include <sstream>

namespace fuzuli {

using namespace std;

EvalExpression::EvalExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
}

EvalExpression::~EvalExpression() {
	// TODO Auto-generated destructor stub
}

Token *EvalExpression::eval(Environment *env) {
	Token *str_code = this->expressions[0]->eval(env);
	SourceCode source;
	string *s = new string(str_code->getContent()); s->append("\n");
	source.readFromText(s);
	AstBuilder astBuilder(&source);
	Expression *expr;
	Token *res;
	source.reset();

	while (1) {
		expr = astBuilder.getNextExpression();
		if (!expr) {
			break;
		}
		res = expr->eval(env);
		if (res->getType() == BREAKTOKEN) {
			break;
		}
	}
	if (res) {
		return (res);
	} else {
		return (this->resultToken);
	}
}

}
