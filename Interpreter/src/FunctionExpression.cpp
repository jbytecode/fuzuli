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
#include <sstream>
#include <cstdlib>
#include <string.h>

namespace fuzuli {

FuzuliFunction::FuzuliFunction() {
	// TODO Auto-generated constructor stub

}

FuzuliFunction::~FuzuliFunction() {
	// TODO Auto-generated destructor stub
}

const char *FuzuliFunction::getStringName() {
	Token *token = ((IdentifierExpression*) (this->name))->stringToken;
	return (token->getContent());
}

FunctionExpression::FunctionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FUNCTION_EXPRESSION;
	ss = new stringstream();
}

FunctionExpression::~FunctionExpression() {

}

FuzuliVariable FunctionExpression::eval(Environment *env) {
	FuzuliFunction *func = new FuzuliFunction();
	ss->str("");
	ss->clear();
	*ss
			<< ((IdentifierExpression*) this->expressions->at(0))->stringToken->getContent();
	*ss << this->expressions->at(1)->expressions->size();
	const char *css = ss->str().c_str();
	func->name = new StringExpression(new Token(css, STRING));

	func->params = this->expressions->at(1);
	func->body = this->expressions->at(2);
	func->environment = env;

	env->setFunction(css, func);
	FuzuliVariable willReturn;
	willReturn.type = FUZULIFUNCTION;
	willReturn.breakFlag = false;
	willReturn.returnFlag = false;
	return (willReturn);
}

FunctionCallExpression::FunctionCallExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FUNCTIONCALL_EXPRESSION;
	paramscount = this->expressions->size() - 1;
	fname = ((IdentifierExpression*) this->expressions->at(0))->stringToken;
	ss = new stringstream();
	*ss << fname->getContent();
	*ss << paramscount;
	this->str_func_name = ss->str();
}

FunctionCallExpression::~FunctionCallExpression() {

}

FuzuliVariable FunctionCallExpression::evalForClass(Environment* env) {
	Environment *object_env;
	FuzuliVariable result = Expression::createNewNull();
	FuzuliFunction *func;

	string fullname = string(fname->getContent());
	string _object = fullname.substr(0, fullname.find('.', 0));
	string _fun = fullname.substr(fullname.find('.', 0) + 1,
			fullname.length() - 1);
	FuzuliVariable obj = env->getVariable(_object.c_str());

	if (_object == "this") {
		object_env = env;
	} else {
		object_env = ((Environment*) (obj.v));
	}
	FuzuliVariable thisToken = Expression::createNewNull();
	thisToken.v = object_env; thisToken.type = COBJECT;
	object_env->setVariable("this", thisToken);

	ss->str("");
	ss->clear();
	*ss << _fun.c_str();
	*ss << paramscount;
	//func = object_env->fuzuliFunctions[(str_func_name.str())];
	func = object_env->getFunction(ss->str().c_str());

	if (func == NULL) {
		cout << "*** " << ss->str().c_str() << endl;
		cout << "Fuzuli Function " << _fun.c_str() << "(" << ss->str().c_str()
				<< ")" << " is not defined in " << _object.c_str() << endl;
		cout << "Contents of environment:" << endl;
		//object_env->dump();
		exit(-1);
	}

	env->createLocal();
	ParamsExpression *paramsExpr = (ParamsExpression*) func->params;
	paramsExpr->eval(env);
	for (unsigned int i = 0; i < paramsExpr->paramNames.size(); i++) {
		string *param = paramsExpr->paramNames[i];
		FuzuliVariable value = this->expressions->at(i + 1)->eval(env);
		object_env->setVariableForFunctionParams(param->c_str(), value);
	}

	result = func->body->eval(object_env);
	result.returnFlag = false;
	env->deleteLocal();
	return (result);
}

FuzuliVariable FunctionCallExpression::eval(Environment *env) {
	FuzuliVariable result = Expression::createNewNull();
	FuzuliFunction *func = env->getFunction(this->str_func_name.c_str());
	if (func == NULL) {
		if (strchr(fname->getContent(), '.') != 0) {
			return (this->evalForClass(env));
		} else {
			cout << "Fuzuli Function " << fname->getContent() << " with "
					<< paramscount << " parameters is not defined." << endl;
			exit(-1);
		}
	}
	env->createLocal();
	ParamsExpression *paramsExpr = (ParamsExpression*) func->params;
	for (unsigned int i = 0; i < paramsExpr->paramNames.size(); i++) {
		string *param = paramsExpr->paramNames[i];
		FuzuliVariable value = this->expressions->at(i + 1)->eval(env);
		env->setVariableInThisScope(param->c_str(), value);
	}

	result = func->body->eval(env);

	result.returnFlag = false;
	env->deleteLocal();
	return (result);
}

ParamsExpression::ParamsExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PARAMS_EXPRESSION;
	this->paramNames.clear();
	Token *temp;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		temp =
				((IdentifierExpression*) (this->expressions->at(i)))->stringToken;
		this->paramNames.push_back(new string(temp->getContent()));
	}
}

ParamsExpression::~ParamsExpression() {

}

FuzuliVariable ParamsExpression::eval(Environment* env) {
	return (Expression::createNewNull());
}

// Return Expression for Fuzuli Functions
ReturnExpression::ReturnExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = RETURN_EXPRESSION;
}

ReturnExpression::~ReturnExpression() {

}

FuzuliVariable ReturnExpression::eval(Environment *env) {
	FuzuliVariable tok = this->expressions->at(0)->eval(env);
	tok.returnFlag = true;
	tok.breakFlag = false;
	return (tok);
}

}
