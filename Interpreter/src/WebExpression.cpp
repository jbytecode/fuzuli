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
#include <cstring>
#include <cgicc/Cgicc.h>  			/* Woow we have CGI! */
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/HTTPCookie.h>

namespace fuzuli {

using namespace cgicc;

Cgicc *FuzuliCgi = NULL;

WebExpression::WebExpression(const char *html) {
	this->html = html;
	this->resultToken = new Token(html, STRING);
}

WebExpression::~WebExpression() {

}

Token *WebExpression::eval(Environment *env) {
	cout << this->html;
	return (this->resultToken);
}

RequestExpression::RequestExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	if (!FuzuliCgi) {
		FuzuliCgi = new Cgicc();
	}
}

RequestExpression::~RequestExpression() {
}

Token *RequestExpression::eval(Environment *env) {
	Token *varname = this->expressions[0]->eval(env);
	const_form_iterator iterator = FuzuliCgi->getElement(varname->getContent());
	if(iterator == FuzuliCgi->getElements().end()) {
	   resultToken = Token::NULL_TOKEN;
	   return(resultToken);
	}
	this->resultToken->setContent(iterator[0].getStrippedValue().c_str());
	this->resultToken->setType(STRING);
	return (this->resultToken);
}

SetCookieExpression::SetCookieExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	if (!FuzuliCgi) {
		FuzuliCgi = new Cgicc();
	}
}

SetCookieExpression::~SetCookieExpression() {

}

Token *SetCookieExpression::eval(Environment *env) {
	Token *var = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Token *val = this->expressions[1]->eval(env);
	//cout << HTTPCookie(var->getContent(), val->getContent()) << endl;
	cout << "Set-Cookie: " << var->getContent() << "=" << val->getContent()
			<< "\n";
	return (this->resultToken);
}

GetCookieExpression::GetCookieExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	if (!FuzuliCgi) {
		FuzuliCgi = new Cgicc();
	}
}

GetCookieExpression::~GetCookieExpression() {

}

Token *GetCookieExpression::eval(Environment *env) {
	Token *var = ((IdentifierExpression*) this->expressions[0])->stringToken;
	CgiEnvironment cgienv = FuzuliCgi->getEnvironment();
	const cookie_iterator iter;
	for (unsigned int i = 0; i < cgienv.getCookieList().size(); i++) {
		HTTPCookie c = cgienv.getCookieList()[i];
		if (c.getName() == string(var->getContent())) {
			resultToken->setType(STRING);
			resultToken->setContent((c.getValue()).c_str());
		}
	}
	return (this->resultToken);
}

IncludeExpression::IncludeExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
}

IncludeExpression::~IncludeExpression() {

}

Token *IncludeExpression::eval(Environment *env) {
	Token *file = this->expressions[0]->eval(env);
	SourceCode *source = new SourceCode();
	source->readFromFile(file->getContent());
	AstBuilder *builder = new AstBuilder(source);
	Expression *expr;
	source->reset();
	while (1) {
		expr = builder->getNextExpression();
		if (!expr) {
			break;
		}
		expr->eval(env);
	}
	return (this->resultToken);
}

IssetExpression::IssetExpression(vector<Expression*>expr){
	this->expressions = expr;
	this->resultToken = new Token(0.0, INTEGER);
}

IssetExpression::~IssetExpression(){

}

Token *IssetExpression::eval(Environment *env){
	Token *varname = this->expressions[0]->eval(env);
	if(varname->getType() != NULLTOKEN){
		this->resultToken->setIntValue(1);
	}else{
		this->resultToken->setIntValue(0);
	}
	return(this->resultToken);
}

}

