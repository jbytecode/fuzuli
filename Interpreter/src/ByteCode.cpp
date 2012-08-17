 /* Fuzuli: A general purpose interpreter
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
#include <stdlib.h>
#include <string.h>
#include <sstream>

namespace fuzuli {

using namespace std;

Serialization::Serialization(){

}

Serialization::~Serialization(){

}

void Serialization::serialize(ostream *os){
	cout << "No Serialization defined for this expression" << endl;
}

Expression *Serialization::deserialize(istream *is){
	cout << "No Serialization defined for this expression" << endl;
	exit(-1);
	return NULL;
}


void IntegerExpression::serialize(ostream *os){
	int code = INTEGER_EXPRESSION;
	os->write((char*)&code, sizeof((int)INTEGER_EXPRESSION));
	os->write((char*)&this->integerValue, sizeof(&this->integerValue));
}

Expression* IntegerExpression::deserialize(istream *is){
	return NULL;
}

void FloatExpression::serialize(ostream *os){
	int code = FLOAT_EXPRESSION;
	os->write((char*)&code, sizeof((int)FLOAT_EXPRESSION));
	os->write((char*)&this->floatValue, sizeof(&this->floatValue));
}

Expression* FloatExpression::deserialize(istream *is){
	return NULL;
}


void StringExpression::serialize(ostream *os){
	int size = this->stringValue.size();
	int code = STRING_EXPRESSION;
	os->write((char*)&code, sizeof(int));
	os->write((char*)&size, sizeof(int));
	*os << this->stringValue.c_str();
}

Expression* StringExpression::deserialize(istream *is){
	return NULL;
}

void IdentifierExpression::serialize(ostream *os){
	int size = strlen(this->stringToken->getContent());
	int code = IDENTIFIER_EXPRESSION;
	os->write((char*)&code, sizeof(int));
	os->write((char*)&size, sizeof(int));
	*os << this->stringToken->getContent();
}

Expression* IdentifierExpression::deserialize(istream *is){
	return NULL;
}

void LetExpression::serialize(ostream *os){
	int size = this->expressions.size();
	int code = LET_EXPRESSION;
	os->write((char*)&code, sizeof(int));
	os->write((char*)&size, sizeof(int));
	for (unsigned int i=0;i<this->expressions.size();i++){
		dynamic_cast<Serialization*>(this->expressions[i])->serialize(os);
	}
}

Expression* LetExpression::deserialize(istream *is){
	return NULL;
}

void PrintExpression::serialize(ostream *os){
	int size = this->expressions.size();
	int code = PRINT_EXPRESSION;
	os->write((char*)&code, sizeof(int));
	os->write((char*)&size, sizeof(int));
	for (unsigned int i=0;i<this->expressions.size();i++){
		dynamic_cast<Serialization*>(this->expressions[i])->serialize(os);
	}
}

Expression* PrintExpression::deserialize(istream *is){
	return NULL;
}


} /* End of namespace fuzuli */
