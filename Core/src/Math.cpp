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
#include <cstdlib>
#include <cmath>
#include <vector>

#include <string>
#include <sstream>
#include <cstring>




using namespace std;
using namespace fuzuli;

extern "C" {

	Token *sind(Token *params,Environment *env);
	Token *cosd(Token *params,Environment *env);
	Token *sqrtd(Token *params,Environment *env);
	Token *absd(Token *params,Environment *env);
	Token *logd(Token *params,Environment *env);
	Token *log10d(Token *params,Environment *env);
	Token *log2d(Token *params,Environment *env);
	Token *expd(Token *params,Environment *env);
	Token *pi(Token *params,Environment *env);
	Token *tand(Token *params,Environment *env);
	Token *atand(Token *params,Environment *env);
	Token *atan2d(Token *params,Environment *env);
	Token *acosd(Token *params,Environment *env);
	Token *asind(Token *params,Environment *env);
	Token *coshd(Token *params,Environment *env);
	Token *sinhd(Token *params,Environment *env);
	Token *tanhd(Token *params,Environment *env);
	Token *powd(Token *params,Environment *env);
	Token *isinfd(Token *params,Environment *env);
	Token *ceild(Token *params, Environment *env);
	Token *roundd(Token *params, Environment *env);
	Token *floord(Token *params, Environment *env);
}

OneParameters
Token *floord(Token *params, Environment *env){
	double f_result = floor(params->tokens[0]->getFloatValue());
	Token *result = new Token(f_result, FLOAT);
	return(result);
}


OneParameters
Token *roundd(Token *params, Environment *env){
	double f_result = round(params->tokens[0]->getFloatValue());
	Token *result = new Token(f_result, FLOAT);
	return(result);
}

OneParameters
Token *ceild (Token *params, Environment *env){
	double f_result = ceil(params->tokens[0]->getFloatValue());
	Token *result = new Token(f_result, FLOAT);
	return(result);
}


Token *powd(Token *params,Environment *env){
	Token *result = new Token(0.0, FLOAT);
	double num1 = params->tokens[0]->getFloatValue();
	double num2 = params->tokens[1]->getFloatValue();
	result->setFloatValue(pow(num1, num2));
	return(result);
}

Token *tanhd(Token *params,Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(tanh(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *sinhd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(sinh(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *coshd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(cosh(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *asind(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(asin(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *acosd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(acos(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *atand(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(atan(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *atan2d(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	double val = atan2(params->tokens[0]->getFloatValue(),params->tokens[1]->getFloatValue());
	resultToken->setFloatValue(val);
	return(resultToken);
}

Token *tand(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(tan(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *sind(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(sin(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *cosd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(cos(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *sqrtd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(sqrt(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *absd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(fabs(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *logd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(log(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *log10d(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(log10(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *log2d(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(log2(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *expd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, FLOAT);
	resultToken->setFloatValue(exp(params->tokens[0]->getFloatValue()));
	return(resultToken);
}

Token *isinfd(Token *params, Environment *env){
	Token *resultToken = new Token(0.0, INTEGER);
	int res = isinf(params->tokens[0]->getFloatValue());
	resultToken->setIntValue(res);
	return(resultToken);
}

Token *pi(Token *params, Environment *env){
	Token *resultToken = env->newToken(0.0,FLOAT);
	resultToken->setFloatValue(3.141592);
	return(resultToken);
}


