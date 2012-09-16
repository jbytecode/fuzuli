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
#include <list>

namespace fuzuli {

using namespace std;

bool Environment::isAutomaticGC = true;

Environment::Environment() {
	this->previous = NULL;
	this->first = false;
	this->preventGC(false);
}

Environment::Environment(Environment *base) {
	this->previous = base;
	this->first = false;
	this->preventGC(base->preventGC());
}

Environment::~Environment() {

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
	this->setVariable("true", new Token(1.0, INTEGER));
	this->setVariable("false", new Token(0.0, INTEGER));
	Token::NULL_TOKEN->setKillable(false);
}

Token *Environment::newToken(const char *val, enum TokenType type) {
	Token *tok = new(nothrow) Token(val, type);
	this->garbage.push_back(tok);
	return (tok);
}

Token *Environment::newToken(double val, enum TokenType type) {
		Token *tok = new(nothrow) Token(val, type);
		this->garbage.push_back(tok);
		return (tok);
}

void Environment::preventGC(bool p){
	this->prevent_garbage_collection = p;
}

bool Environment::preventGC(){
	return(this->prevent_garbage_collection);
}

int Environment::GC() {
	int numdeleted = 0;
	for (unsigned int i=0;i<this->subenvironments.size();i++){
		numdeleted += this->subenvironments[i]->GC();
	}
	//cout << "Deleting "<<this->garbage.size()<< " garbages "<<endl;
	list<Token*>::iterator it;
	for (it = this->garbage.begin(); it != this->garbage.end(); it++) {
		Token *tok = *it;
		if (tok->links <= 0 && tok->getKillable() == true) {
			//cout << "Deleting "<<tok->getContent()<<endl;
			this->garbage.erase(it);
			delete tok;
			it--;
			numdeleted++;
		}
	}
	for (unsigned int i=0; i< this->subenvironments.size();i++){
		Environment *tempe = this->subenvironments[i];
		if(tempe->fuzuliFunctions.size() == 0 && !tempe->preventGC()){
			this->subenvironments.erase(this->subenvironments.begin() + i);
			delete tempe;
			i--;
		}
	}
	return (numdeleted);
}

int Environment::doAutomaticGC(){
	if(Environment::isAutomaticGC && this->prevent_garbage_collection==false){
		return this->GC();
	}else{
		return -1;
	}
}

int Environment::doAutomaticGCwithProtection(Token *tok){
	if(Environment::isAutomaticGC && this->prevent_garbage_collection==false){
		int numGC = 0;
		tok->IncreaseReferences();
		numGC = this->GC();
		tok->ReduceReferences();
		return(numGC);
	}else{
		return -1;
	}
}

void Environment::setVariableInThisScope(const char*name, Token*value) {
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
	Environment *envir = new(nothrow) Environment(this);
	envir->deep = this->deep + 1;
	this->subenvironments.push_back(envir);
	return (envir);
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
	cout << "*** Environment ***"<< endl;
	cout << "Deep: "<<this->deep << endl;
	cout << "Sub Environments: "<< this->subenvironments.size() << endl;
	cout << "Functions: "<< this->fuzuliFunctions.size() << endl;
	cout << "Variables: "<< this->variables.size() << endl;
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

DumpExpression::DumpExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DUMP_EXPRESSION;
}

DumpExpression::~DumpExpression() {

}

Token* DumpExpression::eval(Environment *env) {
	env->dump();
	return (Token::NULL_TOKEN);
}

GCExpression::GCExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = GC_EXPRESSION;
}

GCExpression::~GCExpression() {

}

Token *GCExpression::eval(Environment *env) {
	int num = 0;
	Token *result = new Token(num, FLOAT);
	if(this->expressions->size() == 0){
		num = env->GC();
		result->setFloatValue(num);
	}else if (this->expressions->size() == 1){
		Token *onoffparam = this->expressions->at(0)->eval(env);
		if(onoffparam->getFloatValue() == 1.0){
			Environment::isAutomaticGC = true;
			result->setFloatValue(1.0);
			//cout << "Garbage Collector set to on"<<endl;
		}else if(onoffparam->getFloatValue() == 0.0){
			Environment::isAutomaticGC = false;
			//cout << "Garbage Collector set to off"<<endl;
			result->setFloatValue(0.0);
		}
	}
	return (result);
}

DeleteExpression::DeleteExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DELETE_EXPRESSION;
}

DeleteExpression::~DeleteExpression() {

}

Token *DeleteExpression::eval(Environment *env) {
	Token *obj =
			(dynamic_cast<IdentifierExpression*>(this->expressions->at(0)))->stringToken;
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
