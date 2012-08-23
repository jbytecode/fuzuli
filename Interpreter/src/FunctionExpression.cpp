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
	this->type = FUNCTION_EXPRESSION;
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
			env->newToken(str_func_name.str().c_str(), STRING));
	func->params = this->expressions[1];
	func->body = this->expressions[2];
	func->environment = env;

	env->setFunction(str_func_name.str().c_str(), func);
	Token *willReturn = env->newToken("@FuzuliFunction", FUZULIFUNCTION);
	willReturn->setKillable(false);
	return (willReturn);
}

FunctionCallExpression::FunctionCallExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = FUNCTIONCALL_EXPRESSION;
}

FunctionCallExpression::~FunctionCallExpression() {

}

Token *FunctionCallExpression::evalForClass(Environment* env) {
	int paramscount = this->expressions.size() - 1;
	Environment *object_env;
	Token *result;
	Token *fname = ((IdentifierExpression*) this->expressions[0])->stringToken;
	FuzuliFunction *func;

	string fullname = string(fname->getContent());
	string _object = fullname.substr(0, fullname.find('.', 0));
	string _fun = fullname.substr(fullname.find('.', 0) + 1,
			fullname.length() - 1);
	Token *obj = env->getVariable(_object.c_str());

	if(_object == "this"){
		object_env = env;
	}else{
		object_env = ((Environment*) (obj->object))->next;
	}
	Token *thisToken = env->newToken("@FuzuliObject", FUZULIFUNCTION);
	thisToken->object = object_env;
	object_env->setVariable("this", thisToken);

	stringstream str_func_name;
	str_func_name.clear();
	str_func_name << _fun.c_str();
	str_func_name << paramscount;
	//func = object_env->fuzuliFunctions[(str_func_name.str())];
	func = object_env->getFunction(str_func_name.str().c_str());

	if (func == NULL) {
		cout << "*** " << str_func_name.str().c_str() << endl;
		cout << "Fuzuli Function " << _fun.c_str() << "("
				<< str_func_name.str().c_str() << ")" << " is not defined in "
				<< _object.c_str() << endl;
		cout << "Contents of environment:"<<endl;
		//object_env->dump();
		exit(-1);
	}


	ParamsExpression *paramsExpr = (ParamsExpression*) func->params;
	paramsExpr->eval(env);
	for (unsigned int i = 0; i < paramsExpr->paramNames.size(); i++) {
		Token *param = paramsExpr->paramNames[i];
		Token *value = this->expressions[i + 1]->eval(env);
		object_env->setVariableForFunctionParams(param->getContent(),
				value);
	}
	result = func->body->eval(object_env);
	result->returnFlag = 0;

	result->IncreaseReferences();
	//object_env->doAutomaticGC();
	//result->ReduceReferences();
	return (result);
}

Token *FunctionCallExpression::eval(Environment *env) {
	int paramscount = this->expressions.size() - 1;
	Token *result;
	Token *fname = ((IdentifierExpression*) this->expressions[0])->stringToken;
	stringstream str_func_name;
	str_func_name << fname->getContent();
	str_func_name << paramscount;
	FuzuliFunction *func = env->getFunction(str_func_name.str().c_str());
	if (func == NULL) {
		if (strchr(fname->getContent(), '.') != 0) {
			return (this->evalForClass(env));
		} else {
			cout << "Fuzuli Function " << fname->getContent()
					<< " with "<<paramscount<<" parameters is not defined." << endl;
			exit(-1);
		}
	}
	Environment *funcEnvironment = env->createNext();
	ParamsExpression *paramsExpr = (ParamsExpression*) func->params;
	paramsExpr->eval(env);
	for (unsigned int i = 0; i < paramsExpr->paramNames.size(); i++) {
		Token *param = paramsExpr->paramNames[i];
		Token *value = this->expressions[i + 1]->eval(env);
		funcEnvironment->setVariableForFunctionParams(param->getContent(),
				value);
	}

	result = func->body->eval(funcEnvironment);
	result->returnFlag = 0;

	result->IncreaseReferences();
	funcEnvironment->doAutomaticGC();
	result->ReduceReferences();
	return (result);
}

ParamsExpression::ParamsExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = PARAMS_EXPRESSION;
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
	this->type = RETURN_EXPRESSION;
}

ReturnExpression::~ReturnExpression() {

}

Token *ReturnExpression::eval(Environment *env) {
	Token *tok = this->expressions[0]->eval(env);
	tok->returnFlag = 1;
	//tok->IncreaseReferences();
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
