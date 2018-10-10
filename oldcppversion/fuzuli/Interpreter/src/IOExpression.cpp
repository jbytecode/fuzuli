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
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


namespace fuzuli {

using namespace std;

vector<string> RequireExpression::installedPackages;

void __PrintToken(stringstream *ss, FuzuliVariable &tok) {
	if (tok.type == INTEGER){
		*ss << tok.i;
	} else if (tok.type == FLOAT){
		*ss << tok.d;
	} else if (tok.type == STRING){
		*ss << tok.s;
	}else if (tok.type == COBJECT) {
		*ss << "@FuzuliNativeObject";
		*ss << "[" << tok.v << "]";
	} else if (tok.type == LIST) {
		*ss << "[";
		vector<FuzuliVariable> *v = (vector<FuzuliVariable>*)tok.v;
		for (unsigned int i=0; i< v->size();i++){
			__PrintToken(ss, v->at(i));
			*ss << " ";
		}
		*ss << "]";
	}
}

PrintExpression::PrintExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PRINT_EXPRESSION;
}

PrintExpression::~PrintExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable PrintExpression::eval(Environment *env) {
	stringstream ss;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable tok = this->expressions->at(i)->eval(env);
		__PrintToken(&ss, tok);
	}
	cout << ss.str().c_str();
	return (Expression::createNewNull());
}


PrintlnExpression::PrintlnExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PRINTLN_EXPRESSION;
}

PrintlnExpression::~PrintlnExpression() {
}

FuzuliVariable PrintlnExpression::eval(Environment *env) {
	stringstream ss;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable tok = this->expressions->at(i)->eval(env);
		__PrintToken(&ss, tok);
	}
	cout << ss.str().c_str() << endl;
	return(Expression::createNewNull());
}


RequireExpression::RequireExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->resultToken = new Token("FuzuliPackage", PACKAGE);
	this->type = REQUIRE_EXPRESSION;
}

RequireExpression::~RequireExpression() {

}

FuzuliVariable RequireExpression::eval(Environment *env) {
	FuzuliVariable libName = this->expressions->at(0)->eval(env);
	string name = string(libName.s);
	for (unsigned int i = 0; i < RequireExpression::installedPackages.size();
			i++) {
		if (RequireExpression::installedPackages[i] == name) {
			cout << "Fuzuli package " << libName.s
					<< " is already imported" << endl;
			return (Expression::createNewString(name.c_str()));
		}
	}
	RequireExpression::installedPackages.push_back(name);
	SourceCode *source = new SourceCode();
	source->readFromFile(libName.s);
	AstBuilder *ast = new AstBuilder(source);
	source->reset();
	while (1) {
		Expression *expr = ast->getNextExpression();
		if (!expr) {
			break;
		}
		expr->eval(env);
	}
	return (Expression::createNewInt(1));
}


}
