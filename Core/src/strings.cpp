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

#include "FuzuliTypes.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;
using namespace fuzuli;

extern "C" {
Token *ltrim(Token *p,Environment *env);
Token *rtrim(Token *p,Environment *env);
Token *strcatd(Token *p,Environment *env);
Token *lcase(Token *p,Environment *env);
Token *ucase(Token *p,Environment *env);
Token *left(Token *p,Environment *env);
Token *right(Token *p,Environment *env);
Token *strlend(Token *p,Environment *env);
Token *substrd(Token *p,Environment *env);
Token *strreverse(Token *p,Environment *env);
Token *instr(Token *p, Environment *env);
}

TwoParameters
Token *instr(Token *p, Environment *env){
	string first = string(p->tokens[0]->getContent());
	string second = string(p->tokens[1]->getContent());
	int pos = first.find(second);
	stringstream ss; ss<<pos;
	Token *result = env->newToken(ss.str().c_str(),INTEGER);
	return(result);
}

OneParameters
Token *strreverse(Token *p,Environment *env){
	string s = string(p->tokens[0]->getContent());
	std::reverse(s.begin(), s.end());
	Token *result = new Token(s.c_str(),STRING);
	return(result);
}

ThreeParameters
Token *substrd(Token *p,Environment *env) {
	Token *result = new Token("",STRING);
	Token *param = p->tokens[0];
	Token *start = p->tokens[1];
	Token *stop = p->tokens[2];
	int _start = start->getIntValue();
	int _stop = stop->getIntValue();
	string s = string(param->getContent());
	result->setContent(s.substr(_start, (_stop) - (_start)).c_str());
	return (result);
}


OneParameters
Token *strlend(Token *p,Environment *env) {
	Token *str = p->tokens[0];
	Token *result = new Token(strlen(str->getContent()), INTEGER);
	return (result);
}

TwoParameters
Token *right(Token *p,Environment *env) {
	Token *str = p->tokens[0];
	Token *n = p->tokens[1];
	Token *result = new Token("", STRING);
	string s = string(str->getContent());
	string s1 = s.substr(strlen(str->getContent()) - n->getIntValue(),
			n->getIntValue());
	result->setContent(s1.c_str());
	return (result);
}

TwoParameters
Token *left(Token *p,Environment *env) {
	Token *str = p->tokens[0];
	Token *n = p->tokens[1];
	Token *result = new Token("", STRING);
	result->setContent(
			string(str->getContent()).substr(0, n->getIntValue()).c_str());
	return (result);
}

OneParameters
Token *ucase(Token *p,Environment *env) {
	const char *content = p->tokens[0]->getContent();
	char *newcontent = (char*) malloc(strlen(content) * sizeof(char));
	Token *result = new Token(content, STRING);
	for (unsigned int i = 0; i < strlen(content); i++) {
		newcontent[i] = toupper(content[i]);
	}
	result->setContent((const char*) newcontent);
	return (result);
}

OneParameters
Token *lcase(Token *p,Environment *env) {
	const char *content = p->tokens[0]->getContent();
	char *newcontent = (char*) malloc(strlen(content) * sizeof(char));
	Token *result = new Token(content, STRING);
	for (unsigned int i = 0; i < strlen(content); i++) {
		newcontent[i] = tolower(content[i]);
	}
	result->setContent((const char*) newcontent);
	return (result);
}

MoreThanThreeParameters
Token *strcatd(Token *p,Environment *env) {
	Token *result = new Token("", STRING);
	stringstream ss;
	for (unsigned int i = 0; i < p->tokens[0]->tokens.size(); i++) {
		ss << p->tokens[0]->tokens[i]->getContent();
	}
	result->setContent(ss.str().c_str());
	return (result);
}

OneParameters
Token *ltrim(Token *p,Environment *env) {
	Token *result = new Token("", STRING);
	const char *content = p->tokens[0]->getContent();
	char *pointer = (char*) content;
	unsigned int index = 0;
	while (isspace(*pointer)) {
		if (*pointer == '\0') {
			break;
		}
		pointer++;
		index++;
	}
	string s = string(content);
	result->setContent(s.substr(index, s.size() - index).c_str());
	return (result);
}

OneParameters
Token *rtrim(Token *p,Environment *env) {
	Token *result = new Token("", STRING);
	const char *content = p->tokens[0]->getContent();
	char *pointer = (char*) content;
	pointer += strlen(content) - 1;
	unsigned int index = strlen(content);
	while (isspace(*pointer)) {
		if (*pointer == '\0') {
			break;
		}
		pointer--;
		index--;
	}
	string s = string(content);
	result->setContent(s.substr(0, index).c_str());
	return (result);
}

