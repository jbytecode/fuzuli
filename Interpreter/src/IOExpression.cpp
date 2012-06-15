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
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

namespace fuzuli {
using namespace std;

vector<string> RequireExpression::installedPackages;

void __PrintToken(stringstream *ss, Token *tok) {
	if (tok->getType() == INTEGER) {
		*ss << tok->getIntValue();
	} else if (tok->getType() == FLOAT) {
		*ss << tok->getFloatValue();
	} else if (tok->getType() == COBJECT) {
		*ss << "@FuzuliNativeObject";
	} else if (tok->getType() == LIST) {
		*ss << "[";
		for (unsigned int i = 0; i < tok->tokens.size(); i++) {
			__PrintToken(ss, tok->tokens[i]);
			if (i != tok->tokens.size() - 1) {
				*ss << ", ";
			}
		}
		*ss << "]";
	} else {
		*ss << tok->getContent();
	}
}

PrintExpression::PrintExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

PrintExpression::~PrintExpression() {
	// TODO Auto-generated destructor stub
}

Token *PrintExpression::eval(Environment *env) {
	stringstream ss;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		Token *tok = this->expressions[i]->eval(env);
		__PrintToken(&ss, tok);
	}
	cout << ss.str().c_str();
	return (Token::NULL_TOKEN);
}

void PrintExpression::emitCpp(stringstream *ss) {
	(*ss) << "print(";
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		dynamic_cast<CppEmitter*>(this->expressions[i])->emitCpp(ss);
	}
	(*ss) << ");" << endl;
}

RequireExpression::RequireExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = new Token("FuzuliPackage", PACKAGE);
}

RequireExpression::~RequireExpression() {

}

Token *RequireExpression::eval(Environment *env) {
	Token *libName = this->expressions[0]->eval(env);
	string name = string(libName->getContent());
	for (unsigned int i = 0; i < RequireExpression::installedPackages.size();
			i++) {
		if (RequireExpression::installedPackages[i] == name) {
			cout << "Fuzuli package " << libName->getContent()
					<< " is already imported" << endl;
			return (Token::NULL_TOKEN);
		}
	}
	RequireExpression::installedPackages.push_back(name);
	SourceCode *source = new SourceCode();
	source->readFromFile(libName->getContent());
	AstBuilder *ast = new AstBuilder(source);
	source->reset();
	while (1) {
		Expression *expr = ast->getNextExpression();
		if (!expr) {
			break;
		}
		expr->eval(env);
	}
	return (this->resultToken);
}

ForkExpression::ForkExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ForkExpression::~ForkExpression() {
	cout << "Called fork destructor" << endl;
}

Token *ForkExpression::eval(Environment *env) {
	Environment *forkEnvironment = env->createNext();
	int pid;
	pid = fork();
	if (pid == 0) {
		this->expressions[0]->eval(forkEnvironment);
		kill(getpid(), SIGKILL);
	}
	if (pid < 0) {
		cout << "Error occoured in creating thread" << endl;
	}
	return (new Token(pid, INTEGER));
}

WaitExpression::WaitExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

WaitExpression::~WaitExpression() {

}

Token *WaitExpression::eval(Environment *env) {
	Token* pid = this->expressions[0]->eval(env);
	int result = waitpid(pid->getIntValue(), 0, 0);
	return (new Token(result, INTEGER));
}

}
