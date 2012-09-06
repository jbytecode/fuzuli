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
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

namespace fuzuli {

using namespace std;

stringstream cgi_post_content;

void clean_white_spaces(string &s) {
	stringstream tss;
	tss << s;
	tss >> s;
}

WebExpression::WebExpression(const char *html) {
	this->html = html;
	this->type = WEB_EXPRESSION;
}

WebExpression::~WebExpression() {

}

Token *WebExpression::eval(Environment *env) {
	cout << this->html;
	return (Token::NULL_TOKEN);
}


RequestExpression::RequestExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	this->type = REQUEST_EXPRESSION;
}

RequestExpression::~RequestExpression() {
}

Token *RequestExpression::eval(Environment *env) {
	Token *var = this->expressions[0]->eval(env);
	string allcookies = string(getenv("QUERY_STRING"));
	stringstream ss(allcookies);
	string empty = "";
	string result = "";
	int keyfound = 0;
	const int bufsize = 10;
	while (std::getline(ss, empty, '&')) {
		stringstream iss(empty);
		string key;
		if (std::getline(iss, key, '=')) {
			clean_white_spaces(key);
			if (strcmp(key.c_str(), var->getContent()) == 0) {
				keyfound = 1;
				string value;
				std::getline(iss, value, '=');
				result = value;
				return (env->newToken(result.c_str(), STRING));
			}
		}
	}
	ss.clear();

	if (cgi_post_content.str().size() == 0) {
		char c[bufsize];
		while (1) {
			cin.read(c, bufsize);
			if(c[0]=='\0'){
				break;
			}
			cgi_post_content << c;
			for(int j=0;j<bufsize;j++){
				c[j]='\0';
			}
		}
	}

	while (std::getline(cgi_post_content, empty, '&')) {
		stringstream iss(empty);
		string key;
		if (std::getline(iss, key, '=')) {
			clean_white_spaces(key);
			if (strcmp(key.c_str(), var->getContent()) == 0) {
				keyfound = 1;
				string value;
				std::getline(iss, value, '=');
				result = value;
				return (env->newToken(result.c_str(), STRING));
			}
		}
	}

	if (keyfound != 0) {
		return (env->newToken("", STRING));
	}

	return (Token::NULL_TOKEN);
}

SetCookieExpression::SetCookieExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	this->type = SETCOOKIE_EXPRESSION;
}

SetCookieExpression::~SetCookieExpression() {

}

Token *SetCookieExpression::eval(Environment *env) {
	Token *var = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Token *val = this->expressions[1]->eval(env);
	cout << "Set-Cookie: " << var->getContent() << "=" << val->getContent()
			<< "\n";
	return (this->resultToken);
}

GetCookieExpression::GetCookieExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = GETCOOKIE_EXPRESSION;
}

GetCookieExpression::~GetCookieExpression() {

}

Token *GetCookieExpression::eval(Environment *env) {
	Token *var = ((IdentifierExpression*) this->expressions[0])->stringToken;
	string allcookies = string(getenv("HTTP_COOKIE"));
	stringstream ss(allcookies);
	string empty;
	string result;
	while (std::getline(ss, empty, ';')) {
		stringstream iss(empty);
		string key;
		if (std::getline(iss, key, '=')) {
			clean_white_spaces(key);
			if (strcmp(key.c_str(), var->getContent()) == 0) {
				string value;
				std::getline(iss, value, '=');
				result = string(value);
				break;
			}
		}
	}
	return (env->newToken(result.c_str(), STRING));
}

IncludeExpression::IncludeExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	this->type = INCLUDE_EXPRESSION;
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

IssetExpression::IssetExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->type = ISSET_EXPRESSION;
}

IssetExpression::~IssetExpression() {

}

Token *IssetExpression::eval(Environment *env) {
	Token *varname = this->expressions[0]->eval(env);
	Token *result = env->newToken(0.0, INTEGER);
	if (varname->getType() != NULLTOKEN) {
		result->setIntValue(1);
	} else {
		result->setIntValue(0);
	}
	return (result);
}

}

