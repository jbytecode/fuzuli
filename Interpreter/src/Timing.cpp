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
#include <ctime>

namespace fuzuli {

using namespace std;

TimingExpression::TimingExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = TIMING_EXPRESSION;
}

TimingExpression::~TimingExpression() {

}

Token *TimingExpression::eval(Environment *env) {
	Token *result = env->newToken(0.0, FLOAT);
	clock_t clock_start = clock();
	clock_t clock_end;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		this->expressions->at(i)->eval(env);
	}
	clock_end = clock();
	result->setFloatValue(((double) (clock_end - clock_start)) / 1000.0);
	return (result);
}

} /* namespace fuzuli */
