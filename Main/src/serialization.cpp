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
#include <stdlib.h>

using namespace std;
using namespace fuzuli;

namespace fuzuli {



Serializer::Serializer() {

}

Serializer::~Serializer() {

}

void Serializer::serializeFile(string infile, stringstream& channel) {
	channel << ".text" << endl << ".global main" << endl << "main:" << endl;
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
	emitAsm("/* End Program */", channel);
	emitAsm("movl $1, %eax", channel);
	emitAsm("movl $0, %ebx", channel);
	emitAsm("int $0x80", channel);
}

void Serializer::serializeExpression(Expression *expr, stringstream& channel) {
	//cout << "In serializeExpression, expr->type is " << expr->type << endl;
	if (expr->type == INTEGERCONSTANT_EXPRESSION) {
		int intval =
				dynamic_cast<IntegerConstantExpression*>(expr)->integerValue;
		channel << "pushl $" << getIntPart((double) intval, 1) << endl;
		channel << "pushl $" << getIntPart((double) intval, 2) << endl;
	} else if (expr->type == PLUS_EXPRESSION) {
		PlusExpression *pe = dynamic_cast<PlusExpression*>(expr);
		for (unsigned int i = 0; i < pe->expressions->size(); i++) {
			serializeExpression(pe->expressions->at(i), channel);
			if ((i % 2) == 0 && i > 0) {
				emitAsm("call add", channel);
			}
		}
		emitAsm("call __add", channel);
		emitAsm("pushl %eax", channel);
	} else if (expr->type == FLOATCONSTANT_EXPRESSION) {
		double doubleval =
				dynamic_cast<FloatConstantExpression*>(expr)->floatValue;
		channel << "pushl $" << getIntPart(doubleval, 1) << endl;
		channel << "pushl $" << getIntPart(doubleval, 2) << endl;
	} else if (expr->type == PRINTLN_EXPRESSION) {
		PrintlnExpression *pe = dynamic_cast<PrintlnExpression*>(expr);
		for (unsigned int i = 0; i < pe->expressions->size(); i++) {
			serializeExpression(pe->expressions->at(i), channel);
			emitAsm("call __println", channel);
		}

	}

}

Expression *Serializer::getNextExpression() {
	return NULL;
}

void Serializer::emitAsm(const char *as, stringstream &channel) {
	channel << as << endl;
}

void Serializer::pushInt(int i, stringstream &channel) {
	channel << "push " << i << endl;
}

int Serializer::getIntPart(double d, int i) {
	int *parts = (int*) &d;
	if (i == 1) {
		return (*parts);
	} else {
		parts++;
		return (*parts);
	}
}

double Serializer::combineInts(int p1, int p2) {
	double val;
	memcpy(&val, &p1, sizeof(int));
	memcpy(&val + sizeof(int), &p2, sizeof(int));
	return (val);
}

} /* end of namespace fuzuli */
