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
#include <stdarg.h>

namespace fuzuli {

using namespace std;


Expression::Expression() {
	this->resultToken = Token::NULL_TOKEN;
	this->type = UNDEFINED_EXPRESSION;
}

Expression::~Expression() {

}


FuzuliVariable Expression::eval(Environment *env){
	FuzuliVariable f;
	f.i = 0;
	f.type = INTEGER;
	return(f);
}

const char* Expression::toString() {
	stringstream ss;
	ss << "Expression::toString() is not implemented yet";
	return (ss.str().c_str());
}


double Expression::getDoubleValue(FuzuliVariable &v){
	if(v.type == FLOAT){
		return(v.d);
	}else if (v.type == INTEGER){
		return((double)v.i);
	}else if (v.type == STRING){
		return(atof(v.s));
	}else{
		return(0);
	}
}

int Expression::getIntValue(FuzuliVariable &v){
	if(v.type == FLOAT){
		return((int)v.d);
	}else if (v.type == INTEGER){
		return(v.i);
	}else if (v.type == STRING){
		return(atoi(v.s));
	}else{
		return(0);
	}
}

} /* namespace fuzuli */
