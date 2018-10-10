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

DynLoadExpression::DynLoadExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->resultToken = new Token("@FuzuliDynamicLibrary", DLL);
	this->type = DYNLOAD_EXPRESSION;
}

DynLoadExpression::~DynLoadExpression() {

}

FuzuliVariable DynLoadExpression::eval(Environment *env) {
	FuzuliVariable dllName = this->expressions->at(0)->eval(env);
	stringstream ss;
	for (unsigned int i = 0; i < installedLibraries.size(); i++) {
		if (strcmp(installedLibraries[i]->libraryName, dllName.s )
				== 0) {
			//cout << "this is already loaded. returning old"<<endl;
			FuzuliVariable result = Expression::createNewNull();
			result.type = DLL;
			result.v = installedLibraries.at(i);
			return (result);
		}
	}
	this->libraryName = dllName.s;
#ifdef __linux
	ss << "lib" << dllName.s << ".so";
#else
	ss<<dllName.s<<".dll";
#endif
	libraryHandle = dlopen(ss.str().c_str(), RTLD_LAZY);
	if (!libraryHandle) {
		cout << "DynLoad Error: " << endl;
		cout << dlerror() << endl;
		exit(-1);
	}
	FuzuliVariable result = Expression::createNewNull();
	result.type = DLL;
	result.v = this;
	installedLibraries.push_back(this);
	return (result);
}

CExpression::CExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
	this->type = C_EXPRESSION;
}

CExpression::~CExpression() {

}

FuzuliVariable CExpression::eval(Environment *env) {
	typedef FuzuliVariable (*Function)(FuzuliVariable, Environment*);
	DynLoadExpression *dynExpr =
			(DynLoadExpression*)(this->expressions->at(0)->eval(env).v);
	FuzuliVariable funcName = this->expressions->at(1)->eval(env);
	FuzuliVariable params = Expression::createNewList();
	vector <FuzuliVariable> *vect = new vector<FuzuliVariable>();
	params.v = vect;
	for (unsigned int i = 0; i < this->expressions->size() - 2; i++) {
		FuzuliVariable p = this->expressions->at(i + 2)->eval(env);
		vect->push_back(p);
		//cout << "Adding "<<p->getContent()<<" to params"<<endl;
	}
	Function function = reinterpret_cast<Function>(dlsym(dynExpr->libraryHandle,
			funcName.s));
	if (!function) {
		cout << "External Function call error:" << endl;
		cout << dlerror() << endl;
		exit(-2);
	}

	FuzuliVariable result = function(params, env);
	return (result);
}


}

