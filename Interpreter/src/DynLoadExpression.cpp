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
#include <dlfcn.h>
#include <cstdlib>
#include <cstring>
#include <sstream>

namespace fuzuli {

static vector<DynLoadExpression*> installedLibraries;

DynLoadExpression::DynLoadExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = new Token("@FuzuliDynamicLibrary", DLL);
}

DynLoadExpression::~DynLoadExpression() {

}

Token *DynLoadExpression::eval(Environment *env) {
	Token *dllName = this->expressions[0]->eval(env);
	stringstream ss;
	for (unsigned int i = 0; i < installedLibraries.size(); i++) {
		if (strcmp(installedLibraries[i]->libraryName, dllName->getContent())
				== 0) {
			//cout << "this is already loaded. returning old"<<endl;
			return (installedLibraries[i]->resultToken);
		}
	}
	this->libraryName = dllName->getContent();
#ifdef __linux
	ss << "lib" << dllName->getContent() << ".so";
#else
	ss<<dllName->getContent()<<".dll";
#endif
	libraryHandle = dlopen(ss.str().c_str(), RTLD_LAZY);
	if (!libraryHandle) {
		cout << "DynLoad Error: " << endl;
		cout << dlerror() << endl;
		exit(-1);
	}
	resultToken->expr = this;
	installedLibraries.push_back(this);
	return (resultToken);
}

CExpression::CExpression(vector<Expression*> expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
}

CExpression::~CExpression() {

}

Token *CExpression::eval(Environment *env) {
	typedef Token* (*Function)(Token*, Environment*);
	DynLoadExpression *dynExpr =
			dynamic_cast<DynLoadExpression*>(this->expressions[0]->eval(env)->expr);
	Token *funcName = this->expressions[1]->eval(env);
	Token *params = env->newToken("@LIST", LIST);
	for (unsigned int i = 0; i < this->expressions.size() - 2; i++) {
		Token *p = this->expressions[i + 2]->eval(env);
		params->tokens.push_back(p);
		//cout << "Adding "<<p->getContent()<<" to params"<<endl;
	}
	Function function = reinterpret_cast<Function>(dlsym(dynExpr->libraryHandle,
			funcName->getContent()));
	if (!function) {
		cout << "External Function call error:" << endl;
		cout << dlerror() << endl;
		exit(-2);
	}
	Token *result = function(params, env);
	//cout << "C result "<<result->getContent()<<" as registered as "<<ss.str().c_str()<<endl;
	return (result);
}

}

