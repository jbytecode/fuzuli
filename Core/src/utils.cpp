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
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;
using namespace fuzuli;

extern "C" {
FuzuliVariable shuffle(FuzuliVariable p, Environment *env);
FuzuliVariable sortd(FuzuliVariable p, Environment *env);
FuzuliVariable sorta(FuzuliVariable p, Environment *env);
}

bool TokenSorter_a(FuzuliVariable i, FuzuliVariable j) {
	return (Expression::getDoubleValue(i) < Expression::getDoubleValue(j));
}

bool TokenSorter_d(FuzuliVariable i, FuzuliVariable j) {
	return (Expression::getDoubleValue(i) > Expression::getDoubleValue(j));
}

FuzuliVariable sorta(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *params = (vector<FuzuliVariable>*) p.v;
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params->at(0).v;
	sort(vect->begin(), vect->end(), TokenSorter_a);
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *newvector = new vector<FuzuliVariable> ();
	for (unsigned int i = 0; i < vect->size(); i++) {
		newvector->push_back(vect->at(i));
	}
	result.v = newvector;
	return (result);
}

FuzuliVariable sortd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *params = (vector<FuzuliVariable>*) p.v;
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params->at(0).v;
	sort(vect->begin(), vect->end(), TokenSorter_d);
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *newvector = new vector<FuzuliVariable> ();
	for (unsigned int i = 0; i < vect->size(); i++) {
		newvector->push_back(vect->at(i));
	}
	result.v = newvector;
	return (result);
}

FuzuliVariable shuffle(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	random_shuffle(vect->begin(), vect->end());
	return (Expression::createNewNull());
}

