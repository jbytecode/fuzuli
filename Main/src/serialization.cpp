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

void Serializer::serializeFile(string infile, ostream& channel) {
	this->code = new SourceCode();
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
	switch (expr->type) {
	case INTEGER_EXPRESSION:
		channel << expr->type;
		channel << dynamic_cast<IntegerExpression*>(expr)->integerValue;
		break;
	case INTEGERCONSTANT_EXPRESSION:
		channel << expr->type;
		channel << dynamic_cast<IntegerConstantExpression*>(expr)->integerValue;
		break;
	case FLOAT_EXPRESSION:
		channel << expr->type;
		channel << dynamic_cast<FloatExpression*>(expr)->floatValue;
		break;
	case FLOATCONSTANT_EXPRESSION:
		channel << expr->type;
		channel << dynamic_cast<FloatConstantExpression*>(expr)->floatValue;
		break;
	case STRING_EXPRESSION:
		channel << expr->type;
		channel << dynamic_cast<StringExpression*>(expr)->stringValue.length();
		channel << dynamic_cast<StringExpression*>(expr)->stringValue.c_str();
		break;
	case IDENTIFIER_EXPRESSION:
		channel << expr->type;
		channel << strlen (dynamic_cast<IdentifierExpression*>(expr)->id);
		channel << dynamic_cast<IdentifierExpression*>(expr)->id;
		break;
	default:
		channel << expr->type;
		channel << expr->expressions->size();
		for (unsigned int i=0;i<expr->expressions->size();i++){
			serializeExpression(expr->expressions->at(i), channel);
		}
		break;
	}
}

} /* end of namespace fuzuli */
