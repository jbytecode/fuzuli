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
#include <cstdlib>
#include <sstream>
#include <vector>

namespace fuzuli {

using namespace std;
extern vector<Token*> Environment::garbage;

Environment::Environment() {
	this->previous = NULL;
	this->next = NULL;
	this->first = false;
}

Environment::Environment(Environment *base) {
	this->previous = base;
	this->next = NULL;
	this->first = false;
}

Environment::~Environment() {
	this->variables.clear();
	this->fuzuliFunctions.clear();
	this->previous->next = NULL;
	delete this->next;
}

void Environment::setFirst() {
	this->first = true;
	this->deep = 0;
	this->registerGlobals();
	this->previous = NULL;
}

bool Environment::isFirst() {
	return (this->first);
}

void Environment::registerGlobals() {
	this->setVariable("INTEGER", new Token(1.0, INTEGER));
	this->setVariable("FLOAT", new Token(2.0, INTEGER));
	this->setVariable("STRING", new Token(3.0, INTEGER));
	this->setVariable("LIST", new Token(4.0, LIST));
	this->setVariable("NULL", new Token(5.0, NULLTOKEN));
}

Token *Environment::newToken(const char *val, enum TokenType type) {
	Token *tok = new Token(val, type);
	Environment::garbage.push_back(tok);
	return (tok);
}

Token *Environment::newToken(double val, enum TokenType type) {
	Token *tok = new Token(val, type);
	Environment::garbage.push_back(tok);
	return (tok);
}

int Environment::GC() {
	int numdeleted = 0;
	int n=0;
	start:
	n=0;
	for (unsigned int i = 0; i < Environment::garbage.size(); i++) {
		Token *tok = Environment::garbage[i];
		//if (tok != NULL) {
			if (tok->links <= 0 && tok->getKillable()==true) {
				Environment::garbage.erase(Environment::garbage.begin()+ i);
				delete tok;
				numdeleted++;
				n++;
			}
		}
	//}
	if (n>0) {
		goto start;
	}
	for (unsigned int i=0;i<Environment::garbage.size(); i++){
		if(Environment::garbage[i] == NULL){
			garbage.assign(i,new Token("Silindi.",STRING));
		}
	}
	return (numdeleted);
}

void Environment::setVariableInThisScope(const char*name, Token*value) {
	if (this->variableExists(name)) {
		delete this->variables[string(name)];
	}
	this->variables[string(name)] = value;
}

Token *Environment::getVariableInThisScope(const char *name) {
	if (this->variableExists(name)) {
		return (this->variables[string(name)]);
	} else {
		return (NULL);
	}
}

Environment *Environment::searchBackEnvironments(const char *name) {
	Environment *env = this;
	while (env) {
		if (env->variableExists(name)) {
			return (env);
		}
		env = env->previous;
	}
	return (NULL);
}

Environment* Environment::setVariable(const char *name, Token *value) {
	Environment *env = searchBackEnvironments(name);
	if (env) {
		env->variables[string(name)] = value;
		return (env);
	} else {
		this->variables[string(name)] = value;
		return (this);
	}
}

Token *Environment::getVariable(const char *name) {
	if (this->variableExists(name)) {
		return (this->variables[string(name)]);
	} else {
		Environment *env = this->searchBackEnvironments(name);
		if (env) {
			Token *tok = env->variables[string(name)];
			return (tok);
		} else {
			return (Token::NULL_TOKEN);
		}
	}
}

Environment *Environment::createNext() {
	this->next = new Environment(this);
	this->next->deep = this->deep + 1;
	return (this->next);
}

FuzuliFunction *Environment::searchFuncBackEnvironments(const char *name) {
	FuzuliFunction *func = NULL;
	func = this->fuzuliFunctions[string(name)];
	if (!func) {
		if (!this->isFirst()) {
			func = this->previous->searchFuncBackEnvironments(name);
			return (func);
		}
	}
	return (func);
}

void Environment::setFunction(const char *name, FuzuliFunction *value) {
	FuzuliFunction *existing = searchFuncBackEnvironments(name);
	if (!existing) {
		this->fuzuliFunctions[string(name)] = value;
	} else {
		existing->name = value->name;
		existing->environment = value->environment;
		existing->name = value->name;
		existing->params = value->params;
	}
}

void Environment::setVariableForFunctionParams(const char* name, Token *value) {
	this->variables[name] = value;
}

FuzuliFunction *Environment::getFunction(const char *name) {
	FuzuliFunction *tok = searchFuncBackEnvironments(name);
	return (tok);
}

void Environment::setArgcArgv(int argc, char **argv) {
	this->setVariable("argc", new Token(argc, INTEGER));
	Token *tok = new Token("@FuzuliList", LIST);
	for (int i = 0; i < argc; i++) {
		tok->tokens.push_back(new Token(argv[i], STRING));
	}
	this->setVariable("argv", tok);
}

void Environment::dump() {
	Environment *env = this;
	while (env) {
		map<string, Token*>::iterator it;
		for (it = env->variables.begin(); it != env->variables.end(); it++) {
			cout << env->deep << " - " << it->first << " ";
			if (it->second) {
				cout << it->second->getContent() << " Kll:";
				cout << it->second->getKillable() << " Links:";
				cout << it->second->links;
			}
			cout << endl;
		}
		cout << "Other objects:" << endl;
		for (unsigned int i = 0; i < Environment::garbage.size(); i++) {
			cout << Environment::garbage[i]->getContent() << " Kll:";
			cout << Environment::garbage[i]->getKillable() << " Links: ";
			cout << Environment::garbage[i]->links << endl;
		}

		env = env->previous;
	}
	Token *tok = Token::NULL_TOKEN;
	tok->toString();
}

bool Environment::variableExists(const char *name) {
	map<string, Token*>::iterator it;
	for (it = this->variables.begin(); it != this->variables.end(); it++) {
		if (it->first == string(name)) {
			return (true);
		}
	}
	return (false);
}

DumpExpression::DumpExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

DumpExpression::~DumpExpression() {

}

Token* DumpExpression::eval(Environment *env) {
	env->dump();
	return (Token::NULL_TOKEN);
}

GCExpression::GCExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

GCExpression::~GCExpression() {

}

Token *GCExpression::eval(Environment *env) {
	int num = env->GC();
	Token *result = env->newToken(num, FLOAT);
	return (result);
}

DeleteExpression::DeleteExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

DeleteExpression::~DeleteExpression() {

}

Token *DeleteExpression::eval(Environment *env) {
	Token *obj =
			(dynamic_cast<IdentifierExpression*>(this->expressions[0]))->stringToken;
	cout << "Investigating :" << obj->getContent() << endl;
	if (env->getVariable(obj->getContent())) {
		//cout << obj->getContent() << " is variable. killing..." << endl;
		delete env->getVariable(obj->getContent());
		Environment *tokenv = env->searchBackEnvironments(obj->getContent());
		tokenv->variables.erase(string(obj->getContent()));
	} else if (env->getFunction(obj->getContent())) {
		cout << obj->getContent() << " is a function. Nothing to do..." << endl;
	}
	return (Token::NULL_TOKEN);
}

} /* namespace fuzuli */
