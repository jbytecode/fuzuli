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

EvalExpression::EvalExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = EVAL_EXPRESSION;
}

EvalExpression::~EvalExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable EvalExpression::eval(Environment *env) {
	FuzuliVariable content = this->expressions->at(0)->eval(env);
	//
	// If x in (eval x) is string, x is parsed and being run.
	// Otherwise, x is a Fuzuli Expression.
	//
	if (content.type == STRING) {
		SourceCode source;
		string *s = new string(content.s);
		s->append("\n");
		source.readFromText(s);
		AstBuilder astBuilder(&source);
		Expression *expr;
		FuzuliVariable res = Expression::createNewNull();
		source.reset();

		while (1) {
			expr = astBuilder.getNextExpression();
			if (!expr) {
				break;
			}
			res = expr->eval(env);
			if (res.type == BREAKTOKEN) {
				break;
			}
		}
		return(res);
	} else if (content.type == COBJECT) {
		 // Content is a Fuzuli Expression.
		Expression *expr = static_cast<Expression*>(content.v);
		FuzuliVariable result = Expression::createNewNull();
		for (unsigned int i=0;i<expr->expressions->size();i++){
			result = expr->expressions->at(i)->eval(env);
		}
		return(result);
	}else{
		return Expression::createNewNull();
	}
}

ExpressionExpression::ExpressionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = EXPRESSION_EXPRESSION;
}

ExpressionExpression::~ExpressionExpression() {

}

FuzuliVariable ExpressionExpression::eval(Environment *env) {
	FuzuliVariable result = Expression::createNewNull();
	result.v = this;
	result.type = COBJECT;
	return (result);
}


} /* End of namspace Fuzuli */

