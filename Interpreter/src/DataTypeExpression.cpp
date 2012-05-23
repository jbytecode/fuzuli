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
#include <iostream>
#include <cstring>

namespace fuzuli {

IntegerExpression::IntegerExpression() {

}

IntegerExpression::IntegerExpression(Token *tok) {
	this->token = tok;
	if(strchr(tok->getContent(), 'x')>0){
		int x;
		stringstream ss;
		ss<< std::hex << tok->getContent();
		ss>>x;
		tok->setIntValue( x );
	}
	this->integerValue = this->token->getIntValue();
}

IntegerExpression::~IntegerExpression() {
	// TODO Auto-generated destructor stub
}

Token *IntegerExpression::eval(Environment *env){
	//this->token->setIntValue(this->integerValue);
	Token *tok = env->newToken(this->integerValue, INTEGER);
	return(tok);
}


void IntegerExpression::emitCpp(stringstream *ss){
	(*ss)<< this->integerValue;
}




FloatExpression::FloatExpression() {

}

FloatExpression::FloatExpression(Token *tok) {
	this->token = tok;
	this->floatValue = tok->getFloatValue();
}

FloatExpression::~FloatExpression() {
	// TODO Auto-generated destructor stub
}

Token *FloatExpression::eval(Environment *env){
	//this->token->setFloatValue(this->floatValue);
	Token *tok = env->newToken(this->floatValue, FLOAT);
	return(tok);
}

void FloatExpression::emitCpp(stringstream *ss){
	(*ss)<< this->floatValue;
}


StringExpression::StringExpression(Token *tok) {
	this->stringValue = string(tok->getContent());
	this->stringToken = tok;
}

StringExpression::~StringExpression() {

}

Token *StringExpression::eval(Environment *env){
	//this->stringToken->setContent(this->stringValue.c_str());
	Token *tok = env->newToken(this->stringValue.c_str(), STRING);
	return(tok);
}


void StringExpression::emitCpp(stringstream *ss){
	(*ss) << "\"" << this->stringToken->getContent() << "\"";
}


IdentifierExpression::IdentifierExpression(Token *tok) {
	this->stringToken = tok;
}

IdentifierExpression::~IdentifierExpression() {

}

Token *IdentifierExpression::eval(Environment *env){
	Token *result = env->getVariable(this->stringToken->getContent());
	return(result);
}

void IdentifierExpression::emitCpp(stringstream *ss){
	(*ss) << this->stringToken->getContent();
}




VariableExpression::VariableExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

VariableExpression::~VariableExpression() {
	// TODO Auto-generated destructor stub
}

Token *VariableExpression::eval(Environment *env){
	Token *name = this->expressions[0]->eval(env);
	Token *variable = env->getVariable(name->getContent());
	return(variable);
}


TypeofExpression::TypeofExpression(vector<Expression*> expr){
	this->expressions = expr;
	this->resultToken = new Token(0.0,INTEGER);
}

TypeofExpression::~TypeofExpression(){

}

Token *TypeofExpression::eval(Environment *env){
	Token *tok = this->expressions[0]->eval(env);
	this->resultToken->setIntValue(tok->getType());
	return(resultToken);
}


TypeExpression::TypeExpression(vector<Expression*> expr){
	this->expressions = expr;
}

TypeExpression::~TypeExpression(){

}

Token *TypeExpression::eval(Environment *env){
	Token *var = this->expressions[0]->eval(env);
	Token *type = this->expressions[1]->eval(env);
	int index = type->getIntValue();
	enum TokenType selectedType = static_cast<TokenType>(index);
	if(selectedType==INTEGER){
		int a = var->getIntValue();
		var->setIntValue(a);
	}else if(selectedType==FLOAT){
		double a = var->getFloatValue();
		var->setFloatValue(a);
	}
	var->setType(selectedType);
	return(var);
}


} /*
 namespace fuzuli */
