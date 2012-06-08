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

FunctionExpression::FunctionExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

FunctionExpression::~FunctionExpression() {

}

Token *FunctionExpression::eval(Environment *env) {
	FuzuliFunction *func = new FuzuliFunction();
	stringstream str_func_name;
	str_func_name
			<< ((IdentifierExpression*) this->expressions[0])->stringToken->getContent();
	str_func_name << this->expressions[1]->expressions.size();

	func->name = new StringExpression(
			new Token(str_func_name.str().c_str(), STRING));
	func->params = this->expressions[1];
	func->body = this->expressions[2];
	func->environment = env;

	env->setFunction(str_func_name.str().c_str(), func);
	return (new Token("@FuzuliFunction", FUZULIFUNCTION));
}

FunctionCallExpression::FunctionCallExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

FunctionCallExpression::~FunctionCallExpression() {

}

Token *FunctionCallExpression::eval(Environment *env) {
	int paramscount = this->expressions.size() - 1;
	Environment *funcEnvironment = env->createNext();
	Token *result;
	Token *fname = ((IdentifierExpression*) this->expressions[0])->stringToken;
	stringstream str_func_name;
	str_func_name << fname->getContent();
	str_func_name << paramscount;
	FuzuliFunction *func = env->getFunction(str_func_name.str().c_str());
	if (func == NULL) {
		if (strchr(fname->getContent(), '.') != 0) {
			cout << "** Dot found" << endl;
			string fullname = string(fname->getContent());
			string _object = fullname.substr(0, fullname.find('.', 0));
			string _fun = fullname.substr(fullname.find('.', 0) + 1,
					fullname.length() - 1);
			Token *obj = env->getVariable(_object.c_str());
			cout << "** " << _object.c_str() << ":" << _fun.c_str() << ":"
					<< obj->getContent() << endl;
			Environment *object_env =
					reinterpret_cast<Environment*>(obj->object);

			stringstream str_func_name;
			str_func_name.clear();
			str_func_name << _fun.c_str();
			str_func_name << paramscount;
			func = object_env->fuzuliFunctions[(str_func_name.str().c_str())];
			if (func == NULL) {
				cout << "*** " << str_func_name.str().c_str() << endl;
				cout << "Fuzuli Function " << _fun.c_str() << "("<< str_func_name.str().c_str()<<")"
						<< " is not defined in " << _object.c_str() << endl;
				exit(-1);
			}
		}
	}
	if (func == NULL) {
		cout << "Fuzuli Function " << fname->getContent() << " is not defined."
				<< endl;
		exit(-1);
	}
	ParamsExpression *paramsExpr = (ParamsExpression*) func->params;
	paramsExpr->eval(env);
	for (unsigned int i = 0; i < paramsExpr->paramNames.size(); i++) {
		Token *param = paramsExpr->paramNames[i];
		Token *value = this->expressions[i + 1]->eval(env);
		funcEnvironment->setVariableForFunctionParams(param->getContent(),
				value->clone());
	}
	result = func->body->eval(funcEnvironment);
	result->returnFlag = 0;

	//Token *t = result->clone();
	//t->setKillable(false);
	return (result);
}

ParamsExpression::ParamsExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ParamsExpression::~ParamsExpression() {

}

Token *ParamsExpression::eval(Environment* env) {
	this->paramNames.clear();
	Token *temp;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		temp = ((IdentifierExpression*) (this->expressions[i]))->stringToken;
		//cout << "params: pushing "<< temp->getContent()<<endl;
		this->paramNames.push_back(temp);
	}
	return (temp);
}

/* Return Expression for Fuzuli Functions */
ReturnExpression::ReturnExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ReturnExpression::~ReturnExpression() {

}

Token *ReturnExpression::eval(Environment *env) {
	Token *tok = this->expressions[0]->eval(env);
	tok->returnFlag = 1;
	return (tok);
}

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

}
