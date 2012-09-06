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

Token *IntegerExpression::eval(Environment *env){
	return this->token;
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

Token *FloatExpression::eval(Environment *env){
	return(this->token);
}



StringExpression::StringExpression(Token *tok) {
	this->stringValue = string(tok->getContent());
	this->stringToken = tok;
	this->stringToken->setKillable(false);
	this->type = STRING_EXPRESSION;
}

StringExpression::~StringExpression() {

}

Token *StringExpression::eval(Environment *env){
	//this->stringToken->setContent(this->stringValue.c_str());
	//this->stringToken->IncreaseReferences();
	return this->stringToken;
	//Token *tok = env->newToken(this->stringValue.c_str(), STRING);
	//tok->setKillable(true);
	//return(tok);
}




IdentifierExpression::IdentifierExpression(Token *tok) {
	this->stringToken = tok;
	tok->setKillable(false);
	this->type = IDENTIFIER_EXPRESSION;
}

IdentifierExpression::~IdentifierExpression() {

}

Token *IdentifierExpression::eval(Environment *env){
	Token *result = env->getVariable(this->stringToken->getContent());
	return(result);
}




TypeofExpression::TypeofExpression(vector<Expression*> expr){
	this->expressions = expr;
	this->type = TYPEOF_EXPRESSION;
}

TypeofExpression::~TypeofExpression(){

}

Token *TypeofExpression::eval(Environment *env){
	Token *tok = this->expressions[0]->eval(env);
	Token *result = env->newToken (tok->getType(), INTEGER);
	return(result);
}


TypeExpression::TypeExpression(vector<Expression*> expr){
	this->expressions = expr;
	this->type = TYPE_EXPRESSION;
}

TypeExpression::~TypeExpression(){

}

Token *TypeExpression::eval(Environment *env){
	Token *name = ((IdentifierExpression*)this->expressions[0])->stringToken;
	Token *val = env->getVariable(name->getContent());
	Token *type = this->expressions[1]->eval(env);
	int index = type->getIntValue();
	val->setType((enum TokenType)index);
	return(Token::NULL_TOKEN);
}


}
/*namespace fuzuli */
