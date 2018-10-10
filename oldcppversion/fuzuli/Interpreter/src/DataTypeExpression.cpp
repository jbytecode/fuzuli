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
	this->token->setKillable(false);
	this->type = INTEGER_EXPRESSION;
}

IntegerExpression::~IntegerExpression() {
	// TODO Auto-generated destructor stub
}



FuzuliVariable IntegerExpression::eval(Environment *env){
	FuzuliVariable fv = Expression::createNewInt(this->integerValue);
	return(fv);
}


IntegerConstantExpression::IntegerConstantExpression() {

}

IntegerConstantExpression::IntegerConstantExpression(Token *tok) {
	this->token = tok;
	if(strchr(tok->getContent(), 'x')>0){
		int x;
		stringstream ss;
		ss<< std::hex << tok->getContent();
		ss>>x;
		tok->setIntValue( x );
	}
	this->integerValue = this->token->getIntValue();
	this->token->setKillable(false);
	this->type = INTEGERCONSTANT_EXPRESSION;
}

IntegerConstantExpression::~IntegerConstantExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable IntegerConstantExpression::eval(Environment *env){
	FuzuliVariable f = Expression::createNewInt(this->integerValue);
	return(f);
}



FloatExpression::FloatExpression() {

}

FloatExpression::FloatExpression(Token *tok) {
	this->token = tok;
	this->floatValue = tok->getFloatValue();
	this->token->setKillable(false);
	this->type = FLOAT_EXPRESSION;
}

FloatExpression::~FloatExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable FloatExpression::eval(Environment *env){
	FuzuliVariable fv = Expression::createNewDouble(this->floatValue);
	return(fv);
}


FloatConstantExpression::FloatConstantExpression() {

}

FloatConstantExpression::FloatConstantExpression(Token *tok) {
	this->token = tok;
	this->floatValue = tok->getFloatValue();
	this->token->setKillable(false);
	this->type = FLOATCONSTANT_EXPRESSION;
}

FloatConstantExpression::~FloatConstantExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable FloatConstantExpression::eval(Environment *env){
	FuzuliVariable f = Expression::createNewDouble(this->floatValue);
	return(f);
}



StringExpression::StringExpression(Token *tok) {
	this->stringValue = string(tok->getContent());
	this->stringToken = tok;
	this->stringToken->setKillable(false);
	this->type = STRING_EXPRESSION;
}

StringExpression::~StringExpression() {

}

FuzuliVariable StringExpression::eval(Environment *env){
	FuzuliVariable result = Expression::createNewString(this->stringValue.c_str());
	return(result);
}



IdentifierExpression::IdentifierExpression(Token *tok) {
	this->stringToken = tok;
	tok->setKillable(false);
	this->type = IDENTIFIER_EXPRESSION;
	this->id = tok->getContent();
	this->last_envir = NULL;
}

IdentifierExpression::~IdentifierExpression() {

}

FuzuliVariable IdentifierExpression::eval(Environment *env){
	FuzuliVariable f = env->getVariable(id);
	return(f);
}




TypeofExpression::TypeofExpression(vector<Expression*> *expr){
	this->expressions = expr;
	this->type = TYPEOF_EXPRESSION;
}

TypeofExpression::~TypeofExpression(){

}

FuzuliVariable TypeofExpression::eval(Environment *env){
	FuzuliVariable tok = this->expressions->at(0)->eval(env);
	FuzuliVariable result = Expression::createNewInt(tok.type);
	return(result);
}


TypeExpression::TypeExpression(vector<Expression*> *expr){
	this->expressions = expr;
	this->type = TYPE_EXPRESSION;
}

TypeExpression::~TypeExpression(){

}

FuzuliVariable TypeExpression::eval(Environment *env){
	const char* name = ((IdentifierExpression*)this->expressions->at(0))->id;
	FuzuliVariable type = this->expressions->at(1)->eval(env);
	int pos = env->getVariablePosition(name);
	FuzuliVariable v= env->variables.at(pos);
	v.type = Expression::getIntValue(type);
	env->variables.at(pos) = v;
	return(Expression::createNewNull());
}


}
/*namespace fuzuli */
