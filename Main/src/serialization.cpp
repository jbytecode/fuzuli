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
#include "../include/serialization.h"
#include <cstring>

using namespace std;
using namespace fuzuli;

namespace fuzuli {

Serializer::Serializer() {

}

Serializer::~Serializer() {

}

void Serializer::IntToChars(int value, ostream& channel){
	char *p = (char*) &value;
	unsigned int i_size = sizeof(int);
	for (unsigned int i=0; i < i_size; i++){
		channel << *p;
		p++;
	}
}

void Serializer::DoubleToChars(double value, ostream& channel){
	char *p = (char*) &value;
	unsigned int i_size = sizeof(double);
	for (unsigned int i=0; i < i_size; i++){
		channel << *p;
		p++;
	}
}


void Serializer::serializeFile(string infile, ostream& channel) {
	this->code = new SourceCode();
	this->code->readFromFile(infile.c_str());
	this->builder = new AstBuilder(this->code);
	this->code->reset();
	while (true) {
		Expression *expr = this->builder->getNextExpression();
		if (!expr) {
			break;
		}
		this->serializeExpression(expr, channel);
	}
}

void Serializer::serializeExpression(Expression *expr, ostream& channel) {
	Serializer::IntToChars(expr->type, channel);
	switch (expr->type) {
	case INTEGER_EXPRESSION:
		Serializer::IntToChars( dynamic_cast<IntegerExpression*>(expr)->integerValue, channel);
		break;
	case INTEGERCONSTANT_EXPRESSION:
		Serializer::IntToChars(dynamic_cast<IntegerConstantExpression*>(expr)->integerValue, channel);
		break;
	case FLOAT_EXPRESSION:
		Serializer::DoubleToChars(dynamic_cast<FloatExpression*>(expr)->floatValue, channel);
		break;
	case FLOATCONSTANT_EXPRESSION:
		Serializer::DoubleToChars(dynamic_cast<FloatConstantExpression*>(expr)->floatValue, channel);
		break;
	case STRING_EXPRESSION:
		Serializer::IntToChars(dynamic_cast<StringExpression*>(expr)->stringValue.length(), channel);
		channel << dynamic_cast<StringExpression*>(expr)->stringValue.c_str();
		break;
	case IDENTIFIER_EXPRESSION:
		Serializer::IntToChars( strlen (dynamic_cast<IdentifierExpression*>(expr)->id), channel);
		channel << dynamic_cast<IdentifierExpression*>(expr)->id;
		break;
	default:
		Serializer::IntToChars(expr->expressions->size(), channel);
		for (unsigned int i=0;i<expr->expressions->size();i++){
			serializeExpression(expr->expressions->at(i), channel);
		}
		break;
	}
}

} /* end of namespace fuzuli */
