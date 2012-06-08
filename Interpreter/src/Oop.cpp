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

namespace fuzuli {

using namespace std;

map<string, FuzuliClass*> FuzuliClass::all_classes;

FuzuliClass::FuzuliClass() {

}

FuzuliClass::~FuzuliClass() {

}

ClassExpression::ClassExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ClassExpression::~ClassExpression() {

}

Token *ClassExpression::eval(Environment *env) {
	Token *name =
			reinterpret_cast<IdentifierExpression*>(this->expressions[0])->stringToken;
	Token *extends_keyword =
			reinterpret_cast<IdentifierExpression*>(this->expressions[1])->stringToken;
	if (strcmp(extends_keyword->getContent(), "extends") != 0) {
		cout << "Class declaration must follow an 'extends' keyword at line "
				<< extends_keyword->getLineNumber() << endl;
		return (Token::NULL_TOKEN);
	}
	Token *extented_class =
			reinterpret_cast<IdentifierExpression*>(this->expressions[2])->stringToken;

	if(strcmp(extented_class->getContent(), "Object") !=0){
		cout << "Extending from classes rather than Object is not supported yet"<<endl;
	}
	FuzuliClass *cls = new FuzuliClass();
	cls->extends = string(extented_class->getContent());
	cls->name = string(name->getContent());
	cls->body = this->expressions[3];
	FuzuliClass::all_classes[cls->name] = cls;
	return (Token::NULL_TOKEN);
}

NewExpression::NewExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

NewExpression::~NewExpression() {

}

Token *NewExpression::eval(Environment *env) {
	Token *className =
			reinterpret_cast<IdentifierExpression*>(this->expressions[0])->stringToken;
	FuzuliClass *cls = FuzuliClass::all_classes[className->getContent()];
	if (cls == NULL) {
		cout << "Can not create an object from class "
				<< className->getContent() << endl;
		return (Token::NULL_TOKEN);
	}
	Environment *cls_env = env->createNext();
	cls->body->eval(cls_env);
	Token *obj = new Token("@FuzuliObject", FUZULIFUNCTION);
	obj->object = (void*)cls_env;
	return (obj);
}

};

