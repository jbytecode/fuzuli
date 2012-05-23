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

namespace fuzuli {

using namespace std;

Expression::Expression() {
	this->resultToken = Token::NULL_TOKEN;
}

Expression::~Expression() {

}

void Expression::addExpression(Expression *exp){
	this->expressions.push_back(exp);
}

Token * Expression::eval(Environment *env){
	return(this->resultToken);
}

const char* Expression::toString() {
	stringstream ss;
	for (unsigned int i = 0; i < this->expressions.size(); i++) {
		ss << this->expressions[i]->toString() << endl;
	}
	return (ss.str().c_str());
}

} /* namespace fuzuli */
