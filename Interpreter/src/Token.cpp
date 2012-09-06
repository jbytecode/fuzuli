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
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace fuzuli {
using namespace std;

static int count = 0;
Token *Token::NULL_TOKEN = new Token("NULL", NULLTOKEN);
int Token::doubleprecision = 10;
double Token::epsilon = 0.00001;

Token::Token() {
	count++;
	returnFlag = 0;
	breakFlag = 0;
	links = 0;
}

Token::~Token() {
	count--;
}

Token::Token(string *content, enum TokenType type) {
	this->ss = new stringstream();
	this->content = content;
	this->type = type;
	count++;
	returnFlag = 0;
	breakFlag = 0;
	killable = true;
	links = 0;
}

Token::Token(const char *content, enum TokenType type) {
	this->ss = new stringstream();
	this->content = new string(content);
	this->type = type;
	count++;
	returnFlag = 0;
	breakFlag = 0;
	killable = true;
	links = 0;
}

Token::Token(double num, enum TokenType type) {
	this->ss = new stringstream();
	if (type == INTEGER) {
		*ss << (int) num;
	} else if (type == FLOAT) {
		ss->precision(Token::doubleprecision);
		*ss << (double) num;
	} else {
		*ss << num;
	}
	this->content = new string(ss->str());
	this->type = type;
	count++;
	returnFlag = 0;
	breakFlag = 0;
	killable = true;
	links = 0;
}

const char* Token::toString() {
	stringstream ss;
	ss << "Content:" << *this->content << " Type:" << this->type;
	cout << "Tokens " << count << endl;
	string result = ss.str();
	return (result.c_str());
}

Token *Token::clone() {
	Token *tok = new Token(this->getContent(), this->getType());
	for (unsigned int i = 0; i < this->tokens.size(); i++) {
		tok->tokens.push_back(this->tokens[i]->clone());
	}
	tok->breakFlag = this->breakFlag;
	tok->returnFlag = this->returnFlag;
	tok->object = this->object;
	tok->returnToken = this->returnToken;
	tok->links = this->links;

	return (tok);
}

enum TokenType Token::getType() {
	return (this->type);
}

const char *Token::getContent() {
	return (this->content->c_str());
}

void Token::setType(enum TokenType type) {
	this->type = type;
}

void Token::setContent(const char *content) {
	this->content->clear();
	this->content->append(content);
}

int Token::getIntValue() {
	int value = atoi(this->content->c_str());
	return (value);
}

double Token::getFloatValue() {
	double value = atof(this->content->c_str());
	return (value);
}

void Token::setIntValue(int i) {
	this->ss->str("");
	this->content->clear();
	*ss << i;
	this->content->append(ss->str());
	this->type = INTEGER;
}

void Token::setFloatValue(double d) {
	this->ss->str("");
	ss->precision(Token::doubleprecision);
	this->content->clear();
	*ss << d;
	this->content->append(ss->str());
	this->type = FLOAT;
}

int Token::Equal(Token *tok) {
	if (this->type == tok->type) {
		if (this->type == INTEGER) {
			return (std::fabs(this->getIntValue() - tok->getIntValue())
					<= Token::epsilon);
		} else if (this->type == FLOAT) {
			return (std::fabs(this->getFloatValue() - tok->getFloatValue())
					<= Token::epsilon);
		} else {
			if (strcmp(this->getContent(), tok->getContent()) == 0) {
				return (1);
			} else {
				return (0);
			}
		}
	} else {
		if (strcmp(this->getContent(), tok->getContent()) == 0) {
			return (1);
		} else {
			return (0);
		}
	}
}

int Token::getLineNumber() {
	return (this->line);
}

void Token::setLineNumber(int num) {
	this->line = num;
}

void Token::incLineNumber() {
	this->line++;
}

void Token::setKillable(bool killableState) {
	this->killable = killableState;
}

bool Token::getKillable() {
	return (this->killable);
}

void Token::ReduceReferences(){
	this->links--;
	for (unsigned int i=0;i<this->tokens.size();i++){
		if(this->tokens[i]->getType()!=NULLTOKEN){
			this->tokens[i]->ReduceReferences();
		}
	}
}

void Token::IncreaseReferences(){
	this->links++;
	for (unsigned int i=0;i<this->tokens.size();i++){
		if(this->tokens[i]->getType()!=NULLTOKEN){
			this->tokens[i]->IncreaseReferences();
		}
	}
}

} /* namespace fuzuli */
