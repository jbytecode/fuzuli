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
#include <vector>
#include <sstream>
#include <string.h>
#include <typeinfo>

namespace fuzuli {

using namespace std;

map<string, FuzuliClass*> FuzuliClass::all_classes;

FuzuliClass::FuzuliClass() {

}

FuzuliClass::~FuzuliClass() {

}

ClassExpression::ClassExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = CLASS_EXPRESSION;
}

ClassExpression::~ClassExpression() {

}

FuzuliVariable ClassExpression::eval(Environment *env) {
	const char *name =
			reinterpret_cast<IdentifierExpression*>(this->expressions->at(0))->id;
	const char *extends_keyword =
			reinterpret_cast<IdentifierExpression*>(this->expressions->at(1))->id;
	if (strcmp(extends_keyword, "extends") != 0) {
		cout << "Class declaration must follow an 'extends' keyword at class "
				<< name << endl;
		return (Expression::createNewNull());
	}
	const char *extented_class =
			reinterpret_cast<IdentifierExpression*>(this->expressions->at(2))->id;

	FuzuliClass *cls = new FuzuliClass();
	cls->extends = string(extented_class);
	cls->name = string(name);
	cls->body = this->expressions->at(3);
	FuzuliClass::all_classes[cls->name] = cls;

	if (strcmp(extented_class, "Object") != 0) {
		FuzuliClass *parent = FuzuliClass::all_classes[extented_class];
		vector<Expression*> tmp_expr;
		for (unsigned int i = 0; i < parent->body->expressions->size(); i++) {
			cls->body->expressions->push_back(parent->body->expressions->at(i));
		}
	}

	return (Expression::createNewNull());
}

NewExpression::NewExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NEW_EXPRESSION;
}

NewExpression::~NewExpression() {

}

FuzuliVariable NewExpression::eval(Environment *env) {
	const char *className =
			reinterpret_cast<IdentifierExpression*>(this->expressions->at(0))->id;
	FuzuliClass *cls = FuzuliClass::all_classes[string(className)];
	if (cls == NULL) {
		cout << "Can not create an object from class " << className << endl;
		return (Expression::createNewNull());
	}
	Environment *cls_env = new Environment(env);
	cls->body->eval(cls_env);

	//Copying functions
	std::map<string, FuzuliFunction*>::iterator mip;
	for (mip = env->fuzuliFunctions.begin(); mip != env->fuzuliFunctions.end(); mip++){
		cls_env->fuzuliFunctions[mip->first] = mip->second;
	}
	//Copying variables
	for (unsigned int i=0;i<env->variables.size();i++){
		cls_env->variables.push_back(env->variables.at(i));
	}

	//Running Constructor
	vector<Expression*> *fexpr = new vector<Expression*>();
	stringstream ss;
	string constructorname = string(className);
	ss << constructorname << this->expressions->size() - 1;
	string constructor_internal_name = ss.str();

	if (cls_env->getFunction(constructor_internal_name.c_str()) != NULL) {
		fexpr->push_back(
				new IdentifierExpression(
						new Token(constructorname.c_str(), IDENTIFIER)));
		for (unsigned int i = 1; i < this->expressions->size(); i++) {
			fexpr->push_back(this->expressions->at(i));
		}
		FunctionCallExpression *fcall = new FunctionCallExpression(fexpr);
		fcall->eval(cls_env);
	}

	FuzuliVariable obj = Expression::createNewNull();
	obj.v = (void*) cls_env;
	obj.type = COBJECT;
	return (obj);
}

}
;

