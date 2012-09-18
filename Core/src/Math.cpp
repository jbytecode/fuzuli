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

Token *sind(Token *params, Environment *env);
Token *cosd(Token *params, Environment *env);
Token *sqrtd(Token *params, Environment *env);
Token *absd(Token *params, Environment *env);
Token *logd(Token *params, Environment *env);
Token *log10d(Token *params, Environment *env);
Token *log2d(Token *params, Environment *env);
Token *expd(Token *params, Environment *env);
Token *pi(Token *params, Environment *env);
Token *tand(Token *params, Environment *env);
Token *atand(Token *params, Environment *env);
Token *atan2d(Token *params, Environment *env);
Token *acosd(Token *params, Environment *env);
Token *asind(Token *params, Environment *env);
Token *coshd(Token *params, Environment *env);
Token *sinhd(Token *params, Environment *env);
Token *tanhd(Token *params, Environment *env);
Token *powd(Token *params, Environment *env);
Token *isinfd(Token *params, Environment *env);
Token *ceild(Token *params, Environment *env);
Token *roundd(Token *params, Environment *env);
Token *floord(Token *params, Environment *env);
}

OneParameters
Token *floord(Token *params, Environment *env) {
	double f_result = floor(params->tokens[0]->getFloatValue());
	return (env->newToken(f_result, FLOAT));
}

OneParameters
Token *roundd(Token *params, Environment *env) {
	double f_result = round(params->tokens[0]->getFloatValue());
	return (env->newToken(f_result, FLOAT));
}

OneParameters
Token *ceild(Token *params, Environment *env) {
	double f_result = ceil(params->tokens[0]->getFloatValue());
	return (env->newToken(f_result, FLOAT));
}

Token *powd(Token *params, Environment *env) {
	double num1 = params->tokens[0]->getFloatValue();
	double num2 = params->tokens[1]->getFloatValue();
	return (env->newToken(pow(num1, num2), FLOAT));
}

Token *tanhd(Token *params, Environment *env) {
	return (env->newToken(tanh(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *sinhd(Token *params, Environment *env) {
	return (env->newToken(sinh(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *coshd(Token *params, Environment *env) {
	return (env->newToken(cosh(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *asind(Token *params, Environment *env) {
	return (env->newToken(asin(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *acosd(Token *params, Environment *env) {
	return (env->newToken(acos(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *atand(Token *params, Environment *env) {
	return (env->newToken(atan(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *atan2d(Token *params, Environment *env) {
	double val = atan2(params->tokens[0]->getFloatValue(),
			params->tokens[1]->getFloatValue());
	return (env->newToken(val, FLOAT));
}

Token *tand(Token *params, Environment *env) {
	return (env->newToken(tan(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *sind(Token *params, Environment *env) {
	return (env->newToken(sin(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *cosd(Token *params, Environment *env) {
	return (env->newToken(cos(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *sqrtd(Token *params, Environment *env) {
	return (env->newToken(sqrt(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *absd(Token *params, Environment *env) {
	return (env->newToken(fabs(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *logd(Token *params, Environment *env) {
	return (env->newToken(log(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *log10d(Token *params, Environment *env) {
	return (env->newToken(log10(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *log2d(Token *params, Environment *env) {
	return (env->newToken(log2(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *expd(Token *params, Environment *env) {
	return (env->newToken(exp(params->tokens[0]->getFloatValue()), FLOAT));
}

Token *isinfd(Token *params, Environment *env) {
	int res = std::isinf(params->tokens[0]->getFloatValue());
	return (env->newToken(res, INTEGER));
}

Token *pi(Token *params, Environment *env) {
	return (env->newToken(3.141592653589793, FLOAT));
}

