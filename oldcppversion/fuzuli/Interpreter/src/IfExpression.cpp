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

IfExpression::IfExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = IF_EXPRESSION;
}

IfExpression::~IfExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable IfExpression::eval(Environment *env) {
	FuzuliVariable condition;
	FuzuliVariable result;
	// if then form
	if (this->expressions->size() == 2) {
		condition = this->expressions->at(0)->eval(env);
		if (this->getIntValue(condition) == 1) {
			result = this->expressions->at(1)->eval(env);
		}
		//if then form
	} else if (this->expressions->size() == 3) {
		condition = this->expressions->at(0)->eval(env);
		if (this->getIntValue(condition) == 1) {
			result = this->expressions->at(1)->eval(env);
		} else {
			result = this->expressions->at(2)->eval(env);
		}
	} else {
		cout << "Bad If Statement." << endl;
	}
	return (result);
}



SwitchExpression::SwitchExpression(vector<Expression*> *expr){
	this->expressions = expr;
	this->type = SWITCH_EXPERSSION;
}

SwitchExpression::~SwitchExpression(){

}

FuzuliVariable SwitchExpression::eval(Environment *env){
	FuzuliVariable controlVar = this->expressions->at(0)->eval(env);
	FuzuliVariable result = Expression::createNewNull();
	for (unsigned int i=1; i<this->expressions->size(); i++){
		CaseExpression *ce = dynamic_cast<CaseExpression*> (this->expressions->at(i));
		FuzuliVariable controlCEVar = ce->expressions->at(0)->eval(env);
		if(Expression::equalFuzuliVars(controlVar, controlCEVar)){
			result = ce->expressions->at(1)->eval(env);
			break;
		}
	}
	return(result);
}

CaseExpression::CaseExpression(vector<Expression*> *expr){
	this->expressions = expr;
	this->type = CASE_EXPRESSION;
}

CaseExpression::~CaseExpression(){

}

FuzuliVariable CaseExpression::eval(Environment *env){
	FuzuliVariable result = this->expressions->at(1)->eval(env);
	return(result);
}


} /* namespace fuzuli */
