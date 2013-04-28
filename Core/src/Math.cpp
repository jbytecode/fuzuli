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

FuzuliVariable sind(FuzuliVariable params, Environment *env);
FuzuliVariable cosd(FuzuliVariable params, Environment *env);
FuzuliVariable sqrtd(FuzuliVariable params, Environment *env);
FuzuliVariable absd(FuzuliVariable params, Environment *env);
FuzuliVariable logd(FuzuliVariable params, Environment *env);
FuzuliVariable log10d(FuzuliVariable params, Environment *env);
FuzuliVariable log2d(FuzuliVariable params, Environment *env);
FuzuliVariable expd(FuzuliVariable params, Environment *env);
FuzuliVariable pi(FuzuliVariable params, Environment *env);
FuzuliVariable tand(FuzuliVariable params, Environment *env);
FuzuliVariable atand(FuzuliVariable params, Environment *env);
FuzuliVariable atan2d(FuzuliVariable params, Environment *env);
FuzuliVariable acosd(FuzuliVariable params, Environment *env);
FuzuliVariable asind(FuzuliVariable params, Environment *env);
FuzuliVariable coshd(FuzuliVariable params, Environment *env);
FuzuliVariable sinhd(FuzuliVariable params, Environment *env);
FuzuliVariable tanhd(FuzuliVariable params, Environment *env);
FuzuliVariable powd(FuzuliVariable params, Environment *env);
FuzuliVariable isinfd(FuzuliVariable params, Environment *env);
FuzuliVariable ceild(FuzuliVariable params, Environment *env);
FuzuliVariable roundd(FuzuliVariable params, Environment *env);
FuzuliVariable floord(FuzuliVariable params, Environment *env);
}

OneParameters
FuzuliVariable floord(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = floor(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

OneParameters
FuzuliVariable roundd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = round(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

OneParameters
FuzuliVariable ceild(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = ceil(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable pi(FuzuliVariable params, Environment *env) {
	return Expression::createNewDouble(3.141592653589793);
}

FuzuliVariable sind(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = sin(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable cosd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = cos(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable powd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double num1 = Expression::getDoubleValue(vect->at(0));
	double num2 = Expression::getDoubleValue(vect->at(1));
	return Expression::createNewDouble(pow(num1, num2));
}

FuzuliVariable tanhd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = tanh(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable sinhd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = sinh(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable coshd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = cosh(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable asind(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = asin(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable acosd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = acos(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable atand(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = atan(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable atan2d(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double num1 = Expression::getDoubleValue(vect->at(0));
	double num2 = Expression::getDoubleValue(vect->at(1));
	return Expression::createNewDouble(atan2(num1, num2));
}

FuzuliVariable tand(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = tan(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable sqrtd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = sqrt(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable absd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = abs(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable logd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = log(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable log10d(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = log10(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable log2d(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = log2(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable expd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = exp(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

FuzuliVariable isinfd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	double f_result = std::isinf(Expression::getDoubleValue(vect->at(0)));
	return Expression::createNewDouble(f_result);
}

