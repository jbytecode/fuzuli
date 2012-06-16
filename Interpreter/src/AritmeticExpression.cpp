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

AndExpression::AndExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

AndExpression::~AndExpression() {
	// TODO Auto-generated destructor stub
}

Token *AndExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	int allTrue = 1;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		Token *tok = this->expressions[i]->eval(env);
		if (tok->getIntValue() == 0) {
			allTrue = 0;
			break;
		}
	}
	result->setIntValue(allTrue);
	return (result);
}

void AndExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		dynamic_cast<CppEmitter*>(this->expressions[i])->emitCpp(ss);
		if (i != this->expressions.size() - 1) {
			(*ss) << " && ";
		}
	}
	(*ss) << ")";
}

AsterixExpression::AsterixExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

AsterixExpression::~AsterixExpression() {
	// TODO Auto-generated destructor stub
}

Token * AsterixExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	double product = 1.0;
	double val = 0.0;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		Token *t = expressions[i]->eval(env);
		val = t->getFloatValue();
		product *= val;
	}

	result->setFloatValue(product);
	return (result);
}

void AsterixExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		CppEmitter *ce = dynamic_cast<CppEmitter*>(this->expressions[i]);
		ce->emitCpp(ss);
		if (i != this->expressions.size() - 1)
			(*ss) << "*";
	}
	(*ss) << ")";
}

DivisionExpression::DivisionExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

DivisionExpression::~DivisionExpression() {
	// TODO Auto-generated destructor stub
}

Token *DivisionExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	Token *tok1 = this->expressions[0]->eval(env);
	Token *tok2 = this->expressions[1]->eval(env);
	result->setFloatValue(tok1->getFloatValue() / tok2->getFloatValue());
	return (result);
}

void DivisionExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss) << " / ";
	dynamic_cast<CppEmitter*>(this->expressions[1])->emitCpp(ss);
	(*ss) << ")";
}

NotExpression::NotExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

NotExpression::~NotExpression() {
	// TODO Auto-generated destructor stub
}

Token *NotExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	Token *tok = this->expressions[0]->eval(env);
	int intValue = tok->getIntValue();
	if (intValue == 0) {
		intValue = 1;
	} else  {
		intValue = 0;
	}
	result->setIntValue(intValue);
	return (result);
}

void NotExpression::emitCpp(stringstream *ss) {
	(*ss) << "!(";
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss) << ")";
}

OrExpression::OrExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

OrExpression::~OrExpression() {
	// TODO Auto-generated destructor stub
}

Token *OrExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	int atLeastOneTrue = 0;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		Token *tok = this->expressions[i]->eval(env);
		if (tok->getIntValue() == 1) {
			atLeastOneTrue = 1;
			break;
		}
	}
	result->setIntValue(atLeastOneTrue);
	return (result);
}

void OrExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		dynamic_cast<CppEmitter*>(this->expressions[i])->emitCpp(ss);
		if (i != this->expressions.size() - 1) {
			(*ss) << " || ";
		}
	}
	(*ss) << ")";
}

PlusExpression::PlusExpression(vector<Expression *> expr) {
	this->expressions = expr;

}

PlusExpression::~PlusExpression() {
	// TODO Auto-generated destructor stub
}

Token *PlusExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	double sum = 0.0;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		Token *t = expressions[i]->eval(env);
		sum += t->getFloatValue();
	}
	result->setFloatValue(sum);
	return (result);
}

void PlusExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		CppEmitter *ce = dynamic_cast<CppEmitter*>(this->expressions[i]);
		ce->emitCpp(ss);
		if (i != this->expressions.size() - 1)
			(*ss) << "+";
	}
	(*ss) << ")";
}

IncExpression::IncExpression(vector<Expression *> expr) {
	this->expressions = expr;
}

IncExpression::~IncExpression() {
	// TODO Auto-generated destructor stub
}

Token *IncExpression::eval(Environment *env) {
	Token *name = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Environment *varenv = env->searchBackEnvironments(name->getContent());
	Token *val = this->expressions[0]->eval(env);
	Token *result = env->newToken (val->getFloatValue()+1.0, FLOAT);
	val->ReduceReferences();
	result->IncreaseReferences();
	varenv->setVariable(name->getContent(), result);
	return(result);
}

void IncExpression::emitCpp(stringstream *ss) {
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss) << "++";
}

// MinusMinus Expression
// i--
DecExpression::DecExpression(vector<Expression *> expr) {
	this->expressions = expr;
}

DecExpression::~DecExpression() {
	// TODO Auto-generated destructor stub
}

Token *DecExpression::eval(Environment *env) {
	Token *name = ((IdentifierExpression*) this->expressions[0])->stringToken;
	Environment *varenv = env->searchBackEnvironments(name->getContent());
	Token *val = this->expressions[0]->eval(env);
	Token *result = env->newToken (val->getFloatValue() - 1.0, FLOAT);
	val->ReduceReferences();
	result->IncreaseReferences();
	varenv->setVariable(name->getContent(), result);
	return(result);
}

void DecExpression::emitCpp(stringstream *ss) {
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss) << "--";
}

SubtractionExpression::SubtractionExpression(vector<Expression*> expr) {
	this->expressions = expr;

}

SubtractionExpression::~SubtractionExpression() {
	// TODO Auto-generated destructor stub
}

Token *SubtractionExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	if (this->expressions.size() != 2) {
		cout << "Subtraction - takes only two parameters but "
				<< this->expressions.size() << " parameters found" << endl;
		return (NULL);
	}
	Token *tok1 = this->expressions[0]->eval(env);
	Token *tok2 = this->expressions[1]->eval(env);
	result->setFloatValue(tok1->getFloatValue() - tok2->getFloatValue());
	return (result);
}

void SubtractionExpression::emitCpp(stringstream *ss) {
	(*ss) << "(";
	dynamic_cast<CppEmitter*>(this->expressions[0])->emitCpp(ss);
	(*ss) << " - ";
	dynamic_cast<CppEmitter*>(this->expressions[1])->emitCpp(ss);
	(*ss) << ")";
}

EqualsExpression::EqualsExpression(vector<Expression *> expr) {
	this->expressions = expr;
}

EqualsExpression::~EqualsExpression() {
	// TODO Auto-generated destructor stub
}

Token *EqualsExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	result->setIntValue(0);
	Token *tok1 = this->expressions[0]->eval(env);
	Token *tok2 = this->expressions[1]->eval(env);
	if (tok1->Equal(tok2)) {
		result->setIntValue(1);
	}
	return (result);
}

void EqualsExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " == ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

NotEqualsExpression::NotEqualsExpression(vector<Expression *> expr) {
	this->expressions = expr;
}

NotEqualsExpression::~NotEqualsExpression() {
	// TODO Auto-generated destructor stub
}

Token *NotEqualsExpression::eval(Environment *env) {
	Token *result = env->newToken(1.0, INTEGER);
	Token *tok1 = this->expressions[0]->eval(env);
	Token *tok2 = this->expressions[1]->eval(env);
	if (tok1->Equal(tok2)) {
		result->setIntValue(0);
	}else{
		result->setIntValue(1);
	}
	return (result);
}

void NotEqualsExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " != ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

LessExpression::LessExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

LessExpression::~LessExpression() {
	// TODO Auto-generated destructor stub
}

Token *LessExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	Token *first = this->expressions[0]->eval(env);
	Token *second = this->expressions[1]->eval(env);
	if (first->getFloatValue() < second->getFloatValue()) {
		result->setIntValue(1);
	} else {
		result->setIntValue(0);
	}
	return (result);
}

void LessExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " < ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

LessOrEqualExpression::LessOrEqualExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

LessOrEqualExpression::~LessOrEqualExpression() {
	// TODO Auto-generated destructor stub
}

Token *LessOrEqualExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	Token *first = this->expressions[0]->eval(env);
	Token *second = this->expressions[1]->eval(env);
	if (first->getFloatValue() <= second->getFloatValue()) {
		result->setIntValue(1);
	} else {
		result->setIntValue(0);
	}
	return (result);
}

void LessOrEqualExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " <= ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BiggerExpression::BiggerExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BiggerExpression::~BiggerExpression() {
	// TODO Auto-generated destructor stub
}

Token *BiggerExpression::eval(Environment *env) {
	Token *result = env->newToken(-1, INTEGER);
	Token *first = this->expressions[0]->eval(env);
	Token *second = this->expressions[1]->eval(env);
	if (first->getFloatValue() > second->getFloatValue()) {
		result->setIntValue(1);
	} else {
		result->setIntValue(0);
	}
	return (result);
}

void BiggerExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " > ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BigOrEqualExpression::BigOrEqualExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BigOrEqualExpression::~BigOrEqualExpression() {
	// TODO Auto-generated destructor stub
}

Token *BigOrEqualExpression::eval(Environment *env) {
	Token *result = env->newToken(-1, INTEGER);
	Token *first = this->expressions[0]->eval(env);
	Token *second = this->expressions[1]->eval(env);
	if (first->getFloatValue() >= second->getFloatValue()) {
		result->setIntValue(1);
	} else {
		result->setIntValue(0);
	}
	return (result);
}

void BigOrEqualExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " >= ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

ModulaExpression::ModulaExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

ModulaExpression::~ModulaExpression() {

}

Token *ModulaExpression::eval(Environment *env) {
	Token *result = env->newToken(-1, FLOAT);
	Token *first = this->expressions[0]->eval(env);
	Token *second = this->expressions[1]->eval(env);
	result->setFloatValue(
			fmod(first->getFloatValue(), second->getFloatValue()));
	return (result);
}

void ModulaExpression::emitCpp(stringstream *ss) {
	cout << "% cppemit is not defined yet" << endl;
}

BitAndExpression::BitAndExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitAndExpression::~BitAndExpression() {

}

Token *BitAndExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *val2 = this->expressions[1]->eval(env);
	Token *result = env->newToken(val1->getIntValue() & val2->getIntValue(),
			INTEGER);
	return (result);
}

void BitAndExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " & ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BitNotExpression::BitNotExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitNotExpression::~BitNotExpression() {

}

Token *BitNotExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *result = env->newToken(~val1->getIntValue(), INTEGER);
	return (result);
}

void BitNotExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	(*ss) << " & ";
	emitter->emitCpp(ss);
}

BitOrExpression::BitOrExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitOrExpression::~BitOrExpression() {

}

Token *BitOrExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *val2 = this->expressions[1]->eval(env);
	Token *result = env->newToken(val1->getIntValue() | val2->getIntValue(),
			INTEGER);
	return (result);
}

void BitOrExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " | ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BitXORExpression::BitXORExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitXORExpression::~BitXORExpression() {

}

Token *BitXORExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *val2 = this->expressions[1]->eval(env);
	Token *result = env->newToken(val1->getIntValue() ^ val2->getIntValue(),
			INTEGER);
	return (result);
}

void BitXORExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " ^ ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BitShiftLeftExpression::BitShiftLeftExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitShiftLeftExpression::~BitShiftLeftExpression() {

}

Token *BitShiftLeftExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *val2 = this->expressions[1]->eval(env);
	Token *result = env->newToken(val1->getIntValue() << val2->getIntValue(),
			INTEGER);
	return (result);
}

void BitShiftLeftExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " << ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}

BitShiftRightExpression::BitShiftRightExpression(vector<Expression*> expr) {
	this->expressions = expr;
}

BitShiftRightExpression::~BitShiftRightExpression() {

}

Token *BitShiftRightExpression::eval(Environment *env) {
	Token *val1 = this->expressions[0]->eval(env);
	Token *val2 = this->expressions[1]->eval(env);
	Token *result = env->newToken(val1->getIntValue() >> val2->getIntValue(),
			INTEGER);
	return (result);
}

void BitShiftRightExpression::emitCpp(stringstream *ss) {
	CppEmitter *emitter = dynamic_cast<CppEmitter*>(this->expressions[0]);
	emitter->emitCpp(ss);
	(*ss) << " >> ";
	emitter = dynamic_cast<CppEmitter*>(this->expressions[1]);
	emitter->emitCpp(ss);
}


SetPrecisionExpression::SetPrecisionExpression(vector<Expression*> expr){
	this->expressions = expr;
}

SetPrecisionExpression::~SetPrecisionExpression(){

}

Token *SetPrecisionExpression::eval(Environment *env){
	Token *param = this->expressions[0]->eval(env);
	Token::doubleprecision = param->getIntValue();
	return(Token::NULL_TOKEN);
}


SetEpsilonExpression::SetEpsilonExpression(vector<Expression*> expr){
	this->expressions = expr;
}

SetEpsilonExpression::~SetEpsilonExpression(){

}

Token *SetEpsilonExpression::eval(Environment *env){
	Token *param = this->expressions[0]->eval(env);
	Token::epsilon = atof(param->getContent());
	return(Token::NULL_TOKEN);
}

} /* namespace fuzuli */
