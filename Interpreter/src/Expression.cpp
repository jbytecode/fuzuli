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
#include <string.h>
#include <stdlib.h>

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


const char* Expression::getStringValue(FuzuliVariable &v){
	stringstream ss;
	if(v.type == FLOAT){
		ss << v.d;
	}else if (v.type == INTEGER){
		ss << v.i;
	}else if (v.type == STRING){
		return(v.s);
	}else{
		return(0);
	}
	const char *retvalue = ss.str().c_str();
	return(retvalue);
}



FuzuliVariable Expression::createNewInt(int value){
	FuzuliVariable f;
	f.type = INTEGER;
	f.i = value;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

FuzuliVariable Expression::createNewDouble(double value){
	FuzuliVariable f;
	f.type = FLOAT;
	f.d = value;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

FuzuliVariable Expression::createNewString(const char *c){
	FuzuliVariable f;
	f.type = STRING;
	char *cnew = (char*) malloc (strlen(c) * sizeof(char) + 1);
	strcpy (cnew, c);
	cnew[strlen(c)] = '\0';
	f.s = cnew;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

FuzuliVariable Expression::createNewNull(){
	FuzuliVariable f; f.type = NULLTOKEN;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

FuzuliVariable Expression::createNewList(){
	FuzuliVariable f; f.type = LIST;
	vector<FuzuliVariable> *v = new vector<FuzuliVariable>();
	f.v = v;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

FuzuliVariable Expression::createNewCObject(void *ptr){
	FuzuliVariable f; f.type = COBJECT;
	f.returnFlag = false;
	f.breakFlag = false;
	return(f);
}

void Expression::setVariableName(const char *name, FuzuliVariable &f){
	char *cnew = (char*) malloc (strlen(name) * sizeof(char));
	strcpy (cnew, name);
	f.name = (const char*)cnew;
}

bool Expression::equalFuzuliVars(FuzuliVariable &f1, FuzuliVariable &f2){
	if (f1.type == f2.type){
		if(f1.type == INTEGER){
			return ( f1.i == f2.i);
		}else if(f1.type == FLOAT){
			return ( f1.d == f2.d);
		}else if(f1.type == STRING){
			if(strcmp(f1.s, f2.s)==0){
				return(true);
			}else{
				return(false);
			}
		}
	}else{
		return(Expression::getDoubleValue(f1) == Expression::getDoubleValue(f2));
	}
}

} /* namespace fuzuli */
