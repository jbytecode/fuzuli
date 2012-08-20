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
	Token *content = this->expressions[0]->eval(env);
	/*
	 * If x in (eval x) is string, x is parsed and being run.
	 * Otherwise, x is a Fuzuli Expression.
	 */
	if (content->getType() == STRING) {
		SourceCode source;
		string *s = new string(content->getContent());
		s->append("\n");
		source.readFromText(s);
		AstBuilder astBuilder(&source);
		Expression *expr;
		Token *res = Token::NULL_TOKEN;
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
	} else if (content->getType() == COBJECT) {
		/*
		 * Content is a Fuzuli Expression.
		 */
		Expression *expr = static_cast<Expression*>(content->object);
		Token *result = NULL;
		for (unsigned int i=0;i<expr->expressions.size();i++){
			result = expr->expressions[i]->eval(env);
		}
		return(result);
	}
}

ExpressionExpression::ExpressionExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ExpressionExpression::~ExpressionExpression() {

}

Token *ExpressionExpression::eval(Environment *env) {
	Token *result = env->newToken("@FuzuliExpression", COBJECT);
	result->object = this;
	return (result);
}

} /* End of namspace Fuzuli */

