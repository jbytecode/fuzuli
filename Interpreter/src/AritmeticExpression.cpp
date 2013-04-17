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
#include <cstdlib>
#include <sstream>
#include <cmath>

namespace fuzuli {

using namespace std;


AndExpression::AndExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = AND_EXPRESSION;
}


AndExpression::~AndExpression() {
	// TODO Auto-generated destructor stub
}


FuzuliVariable AndExpression::eval(Environment *env) {
	int allTrue = 1;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable tok = this->expressions->at(i)->eval(env);
		if (this->getIntValue(tok) == 0) {
			allTrue = 0;
			break;
		}
	}
	FuzuliVariable result;
	result.i = allTrue;
	result.type = INTEGER;
	return (result);
}



AsterixExpression::AsterixExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = ASTERIX_EXPRESSION;
}

AsterixExpression::~AsterixExpression() {
	// TODO Auto-generated destructor stub
}


FuzuliVariable AsterixExpression::eval(Environment *env) {
	double product = 1.0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable fv = expressions->at(i)->eval(env);
		product *= this->getDoubleValue(fv);
	}
	FuzuliVariable result; result.type = FLOAT; result.d = product;
	return (result);
}

DivisionExpression::DivisionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DIVISION_EXPRESSION;
}

DivisionExpression::~DivisionExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable DivisionExpression::eval(Environment *env) {
	FuzuliVariable tok1 = this->expressions->at(0)->eval(env);
	FuzuliVariable tok2 = this->expressions->at(1)->eval(env);
	FuzuliVariable fv; fv.type=FLOAT;
	fv.d= this->getDoubleValue(tok1) / this->getDoubleValue(tok2);
	return (fv);
}

NotExpression::NotExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NOT_EXPRESSION;
}

NotExpression::~NotExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable NotExpression::eval(Environment *env) {
	FuzuliVariable tok = this->expressions->at(0)->eval(env);
	int intValue = this->getIntValue(tok);
	if (intValue == 0) {
		intValue = 1;
	} else {
		intValue = 0;
	}
	FuzuliVariable fv; fv.type = INTEGER; fv.i = intValue;
	return (fv);
}

OrExpression::OrExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = OR_EXPRESSION;
}

OrExpression::~OrExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable OrExpression::eval(Environment *env) {
	int atLeastOneTrue = 0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable tok = this->expressions->at(i)->eval(env);
		if (this->getIntValue(tok) == 1) {
			atLeastOneTrue = 1;
			break;
		}
	}
	FuzuliVariable fv; fv.type = INTEGER; fv.i = atLeastOneTrue;
	return (fv);
}

PlusExpression::PlusExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PLUS_EXPRESSION;
}

PlusExpression::~PlusExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable PlusExpression::eval(Environment *env) {
	double sum = 0.0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable fv = expressions->at(i)->eval(env);
		sum += this->getDoubleValue(fv);
	}
	FuzuliVariable result; result.type = FLOAT; result.d=sum;
	return (result);
}

IncExpression::IncExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = INC_EXPRESSION;
}

IncExpression::~IncExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable IncExpression::eval(Environment *env) {
	FuzuliVariable val = this->expressions->at(0)->eval(env);
	val.d = this->getDoubleValue(val) + 1.0;
	val.type = FLOAT;
	return (val);
}

// MinusMinus Expression
// i--
DecExpression::DecExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DEC_EXPRESSION;
}

DecExpression::~DecExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable DecExpression::eval(Environment *env) {
	FuzuliVariable val = this->expressions->at(0)->eval(env);
	val.d = this->getDoubleValue(val) - 1.0;
	return (val);
}

SubtractionExpression::SubtractionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = SUBTRACTION_EXPRESSION;
}

SubtractionExpression::~SubtractionExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable SubtractionExpression::eval(Environment *env) {
	FuzuliVariable fv = expressions->at(0)->eval(env);
	double diff = this->getDoubleValue(fv);
	for (unsigned int i = 1; i < this->expressions->size(); i++) {
		fv = expressions->at(i)->eval(env);
		diff -= this->getDoubleValue( fv );
	}
	FuzuliVariable result; result.type = FLOAT; result.d=diff;
	return(result);
}

EqualsExpression::EqualsExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = EQUALS_EXPRESSION;
}

EqualsExpression::~EqualsExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable EqualsExpression::eval(Environment *env) {
	FuzuliVariable tok1 = this->expressions->at(0)->eval(env);
	FuzuliVariable tok2 = this->expressions->at(1)->eval(env);
	FuzuliVariable result; result.type = FLOAT;
	result.d= (this->getDoubleValue(tok1) == this->getDoubleValue(tok2));
	return (result);
}

NotEqualsExpression::NotEqualsExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NOTEQUALS_EXPRESSION;
}

NotEqualsExpression::~NotEqualsExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable NotEqualsExpression::eval(Environment *env) {
	FuzuliVariable tok1 = this->expressions->at(0)->eval(env);
	FuzuliVariable tok2 = this->expressions->at(1)->eval(env);
	FuzuliVariable result; result.type = FLOAT;
	result.d= (!(this->getDoubleValue(tok1) == this->getDoubleValue(tok2)));
	return (result);
}

LessExpression::LessExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LESS_EXPRESSION;
}

LessExpression::~LessExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable LessExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
	FuzuliVariable second = this->expressions->at(1)->eval(env);
	FuzuliVariable result; result.type = FLOAT;
	result.d= (this->getDoubleValue(first) < this->getDoubleValue(second));
	return(result);
}

LessOrEqualExpression::LessOrEqualExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LESSOREQUAL_EXPRESSION;
}

LessOrEqualExpression::~LessOrEqualExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable LessOrEqualExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = FLOAT;
		result.d= (this->getDoubleValue(first) <= this->getDoubleValue(second));
		return(result);
}

BiggerExpression::BiggerExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BIGGER_EXPRESSION;
}

BiggerExpression::~BiggerExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable BiggerExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = FLOAT;
		result.d= (this->getDoubleValue(first) > this->getDoubleValue(second));
		return(result);
}

BigOrEqualExpression::BigOrEqualExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BIGOREQUAL_EXPRESSION;
}

BigOrEqualExpression::~BigOrEqualExpression() {
// TODO Auto-generated destructor stub
}

FuzuliVariable BigOrEqualExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = FLOAT;
		result.d= (this->getDoubleValue(first) >= this->getDoubleValue(second));
		return(result);
}

ModulaExpression::ModulaExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = MODULA_EXPRESSION;
}

ModulaExpression::~ModulaExpression() {

}

FuzuliVariable ModulaExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = FLOAT;
		result.d= fmod(this->getDoubleValue(first) , this->getDoubleValue(second));
		return(result);
}

BitAndExpression::BitAndExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITAND_EXPRESSION;
}

BitAndExpression::~BitAndExpression() {

}

FuzuliVariable BitAndExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= (this->getIntValue(first) & this->getIntValue(second));
		return(result);
}

BitNotExpression::BitNotExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITNOT_EXPRESSION;
}

BitNotExpression::~BitNotExpression() {

}

FuzuliVariable BitNotExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= ~ (this->getIntValue(first));
		return(result);
}

BitOrExpression::BitOrExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITOR_EXPRESSION;
}

BitOrExpression::~BitOrExpression() {

}

FuzuliVariable BitOrExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= (this->getIntValue(first) | this->getIntValue(second));
		return(result);
}

BitXORExpression::BitXORExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITXOR_EXPRESSION;
}

BitXORExpression::~BitXORExpression() {

}

FuzuliVariable BitXORExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= (this->getIntValue(first) ^ this->getIntValue(second));
		return(result);
}

BitShiftLeftExpression::BitShiftLeftExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITSHIFTLEFT_EXPRESSION;
}

BitShiftLeftExpression::~BitShiftLeftExpression() {

}

FuzuliVariable BitShiftLeftExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= (this->getIntValue(first) << this->getIntValue(second));
		return(result);
}

BitShiftRightExpression::BitShiftRightExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITSHIFTRIGHT_EXPERSSION;
}

BitShiftRightExpression::~BitShiftRightExpression() {

}

FuzuliVariable BitShiftRightExpression::eval(Environment *env) {
	FuzuliVariable first = this->expressions->at(0)->eval(env);
		FuzuliVariable second = this->expressions->at(1)->eval(env);
		FuzuliVariable result; result.type = INTEGER;
		result.i= (this->getIntValue(first) >> this->getIntValue(second));
		return(result);
}

/*

SetPrecisionExpression::SetPrecisionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = SETPRECISION_EXPRESSION;
}

SetPrecisionExpression::~SetPrecisionExpression() {

}

Token *SetPrecisionExpression::eval(Environment *env) {
	Token *param = this->expressions->at(0)->eval(env);
	Token::doubleprecision = param->getIntValue();
	return (Token::NULL_TOKEN);
}

SetEpsilonExpression::SetEpsilonExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = SETEPSILON_EXPRESSION;
}

SetEpsilonExpression::~SetEpsilonExpression() {

}

Token *SetEpsilonExpression::eval(Environment *env) {
	Token *param = this->expressions->at(0)->eval(env);
	Token::epsilon = atof(param->getContent());
	return (Token::NULL_TOKEN);
}
*/

} /* namespace fuzuli */
