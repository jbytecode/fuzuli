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

Token *AndExpression::eval(Environment *env) {
	int allTrue = 1;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		Token *tok = this->expressions->at(i)->eval(env);
		if (tok->getIntValue() == 0) {
			allTrue = 0;
			break;
		}
	}
	return (env->newToken(allTrue, INTEGER));
}

AsterixExpression::AsterixExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = ASTERIX_EXPRESSION;
}

AsterixExpression::~AsterixExpression() {
	// TODO Auto-generated destructor stub
}

Token * AsterixExpression::eval(Environment *env) {
	double product = 1.0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		product *= expressions->at(i)->eval(env)->getFloatValue();
	}
	return (env->newToken(product, FLOAT));
}

DivisionExpression::DivisionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DIVISION_EXPRESSION;
}

DivisionExpression::~DivisionExpression() {
	// TODO Auto-generated destructor stub
}

Token *DivisionExpression::eval(Environment *env) {
	Token *tok1 = this->expressions->at(0)->eval(env);
	Token *tok2 = this->expressions->at(1)->eval(env);
	return (env->newToken(tok1->getFloatValue() / tok2->getFloatValue(), FLOAT));
}

NotExpression::NotExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NOT_EXPRESSION;
}

NotExpression::~NotExpression() {
	// TODO Auto-generated destructor stub
}

Token *NotExpression::eval(Environment *env) {
	Token *tok = this->expressions->at(0)->eval(env);
	int intValue = tok->getIntValue();
	if (intValue == 0) {
		intValue = 1;
	} else {
		intValue = 0;
	}
	return (env->newToken(intValue, INTEGER));
}

OrExpression::OrExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = OR_EXPRESSION;
}

OrExpression::~OrExpression() {
	// TODO Auto-generated destructor stub
}

Token *OrExpression::eval(Environment *env) {
	int atLeastOneTrue = 0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		Token *tok = this->expressions->at(i)->eval(env);
		if (tok->getIntValue() == 1) {
			atLeastOneTrue = 1;
			break;
		}
	}
	return (env->newToken(atLeastOneTrue, INTEGER));
}

PlusExpression::PlusExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PLUS_EXPRESSION;
}

PlusExpression::~PlusExpression() {
	// TODO Auto-generated destructor stub
}

Token *PlusExpression::eval(Environment *env) {
	double sum = 0.0;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		sum += expressions->at(i)->eval(env)->getFloatValue();
	}
	return (env->newToken(sum, FLOAT));
}

IncExpression::IncExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = INC_EXPRESSION;
}

IncExpression::~IncExpression() {
	// TODO Auto-generated destructor stub
}

Token *IncExpression::eval(Environment *env) {
	Token *val = this->expressions->at(0)->eval(env);
	Token *result;
	if (!val->getKillable()) {
		Token *name = ((IdentifierExpression*) this->expressions->at(0))->stringToken;
		Environment *varenv = env->searchBackEnvironments(name->getContent());
		result = env->newToken(val->getFloatValue() + 1.0, FLOAT);
		val->ReduceReferences();
		result->IncreaseReferences();
		varenv->setVariableInThisScope(name->getContent(), result);
	} else {
		//val->setFloatValue(val->getFloatValue() + 1);
		++*val;
		result = val;
	}
	return (result);
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

Token *DecExpression::eval(Environment *env) {
	Token *val = this->expressions->at(0)->eval(env);
	Token *result;
	if (!val->getKillable()) {
		Token *name = ((IdentifierExpression*) this->expressions->at(0))->stringToken;
		Environment *varenv = env->searchBackEnvironments(name->getContent());
		result = env->newToken(val->getFloatValue() + 1.0, FLOAT);
		val->ReduceReferences();
		result->IncreaseReferences();
		varenv->setVariableInThisScope(name->getContent(), result);
	} else {
		//val->setFloatValue(val->getFloatValue() - 1);
		--*val;
		result = val;
	}
	return (result);
}

SubtractionExpression::SubtractionExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = SUBTRACTION_EXPRESSION;
}

SubtractionExpression::~SubtractionExpression() {
	// TODO Auto-generated destructor stub
}

Token *SubtractionExpression::eval(Environment *env) {
	double diff = expressions->at(0)->eval(env)->getFloatValue();
		for (unsigned int i = 1; i < this->expressions->size(); i++) {
			diff -= expressions->at(i)->eval(env)->getFloatValue();
		}
	return (env->newToken(diff, FLOAT));
}

EqualsExpression::EqualsExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = EQUALS_EXPRESSION;
}

EqualsExpression::~EqualsExpression() {
	// TODO Auto-generated destructor stub
}

Token *EqualsExpression::eval(Environment *env) {
	Token *tok1 = this->expressions->at(0)->eval(env);
	Token *tok2 = this->expressions->at(1)->eval(env);
	return (env->newToken(*tok1 == *tok2, FLOAT));
}

NotEqualsExpression::NotEqualsExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NOTEQUALS_EXPRESSION;
}

NotEqualsExpression::~NotEqualsExpression() {
	// TODO Auto-generated destructor stub
}

Token *NotEqualsExpression::eval(Environment *env) {
	Token *tok1 = this->expressions->at(0)->eval(env);
	Token *tok2 = this->expressions->at(1)->eval(env);
	return (env->newToken( !(*tok1 == *tok2) ,INTEGER));
}

LessExpression::LessExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LESS_EXPRESSION;
}

LessExpression::~LessExpression() {
	// TODO Auto-generated destructor stub
}

Token *LessExpression::eval(Environment *env) {
	Token *first = this->expressions->at(0)->eval(env);
	Token *second = this->expressions->at(1)->eval(env);
	return (env->newToken(*first < *second,INTEGER));
}

LessOrEqualExpression::LessOrEqualExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LESSOREQUAL_EXPRESSION;
}

LessOrEqualExpression::~LessOrEqualExpression() {
	// TODO Auto-generated destructor stub
}

Token *LessOrEqualExpression::eval(Environment *env) {
	Token *first = this->expressions->at(0)->eval(env);
	Token *second = this->expressions->at(1)->eval(env);
	return (env->newToken(*first <= *second,INTEGER));
}

BiggerExpression::BiggerExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BIGGER_EXPRESSION;
}

BiggerExpression::~BiggerExpression() {
	// TODO Auto-generated destructor stub
}

Token *BiggerExpression::eval(Environment *env) {
	Token *first = this->expressions->at(0)->eval(env);
	Token *second = this->expressions->at(1)->eval(env);
	return (env->newToken(*first > *second,INTEGER));
}

BigOrEqualExpression::BigOrEqualExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BIGOREQUAL_EXPRESSION;
}

BigOrEqualExpression::~BigOrEqualExpression() {
	// TODO Auto-generated destructor stub
}

Token *BigOrEqualExpression::eval(Environment *env) {
	Token *first = this->expressions->at(0)->eval(env);
	Token *second = this->expressions->at(1)->eval(env);
	return (env->newToken(*first >= *second,INTEGER));
}

ModulaExpression::ModulaExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = MODULA_EXPRESSION;
}

ModulaExpression::~ModulaExpression() {

}

Token *ModulaExpression::eval(Environment *env) {
	Token *first = this->expressions->at(0)->eval(env);
	Token *second = this->expressions->at(1)->eval(env);
	return (env->newToken(fmod(first->getFloatValue(), second->getFloatValue()), FLOAT));
}

BitAndExpression::BitAndExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITAND_EXPRESSION;
}

BitAndExpression::~BitAndExpression() {

}

Token *BitAndExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	Token *val2 = this->expressions->at(1)->eval(env);
	return(env->newToken(val1->getIntValue() & val2->getIntValue(),INTEGER));
}

BitNotExpression::BitNotExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITNOT_EXPRESSION;
}

BitNotExpression::~BitNotExpression() {

}

Token *BitNotExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	return (env->newToken(~val1->getIntValue(), INTEGER));
}

BitOrExpression::BitOrExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITOR_EXPRESSION;
}

BitOrExpression::~BitOrExpression() {

}

Token *BitOrExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	Token *val2 = this->expressions->at(1)->eval(env);
	return (env->newToken(val1->getIntValue() | val2->getIntValue(), INTEGER));
}

BitXORExpression::BitXORExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITXOR_EXPRESSION;
}

BitXORExpression::~BitXORExpression() {

}

Token *BitXORExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	Token *val2 = this->expressions->at(1)->eval(env);
	return (env->newToken(val1->getIntValue() ^ val2->getIntValue(), INTEGER));
}

BitShiftLeftExpression::BitShiftLeftExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITSHIFTLEFT_EXPRESSION;
}

BitShiftLeftExpression::~BitShiftLeftExpression() {

}

Token *BitShiftLeftExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	Token *val2 = this->expressions->at(1)->eval(env);
	return (env->newToken(val1->getIntValue() << val2->getIntValue(), INTEGER));
}

BitShiftRightExpression::BitShiftRightExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = BITSHIFTRIGHT_EXPERSSION;
}

BitShiftRightExpression::~BitShiftRightExpression() {

}

Token *BitShiftRightExpression::eval(Environment *env) {
	Token *val1 = this->expressions->at(0)->eval(env);
	Token *val2 = this->expressions->at(1)->eval(env);
	return (env->newToken(val1->getIntValue() >> val2->getIntValue(), INTEGER));
}

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

} /* namespace fuzuli */
