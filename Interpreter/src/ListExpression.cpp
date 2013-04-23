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
#include <cstdlib>
#include <cstring>
#include <vector>

namespace fuzuli {


using namespace std;

ListExpression::ListExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LIST_EXPRESSION;
}

ListExpression::~ListExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable ListExpression::eval(Environment *env) {
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *v;
	for (unsigned int i = 0; i < this->expressions->size(); i++) {
		FuzuliVariable temp = this->expressions->at(i)->eval(env);
		if (temp.type == BREAKTOKEN) {
			break;
		}
		v = (vector<FuzuliVariable>*)result.v;
		v->push_back(temp);
	}
	return (result);
}


LengthExpression::LengthExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LENGTH_EXPRESSION;
}

LengthExpression::~LengthExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable LengthExpression::eval(Environment *env) {
	FuzuliVariable tok = this->expressions->at(0)->eval(env);
	vector<FuzuliVariable> *v = (vector<FuzuliVariable>*)tok.v;
	FuzuliVariable result = Expression::createNewInt(v->size());
	return (result);
}


NthExpression::NthExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = NTH_EXPRESSION;
}

NthExpression::~NthExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable NthExpression::eval(Environment *env) {
	FuzuliVariable list = this->expressions->at(0)->eval(env);
	FuzuliVariable n = this->expressions->at(1)->eval(env);
	vector <FuzuliVariable> *v = (vector<FuzuliVariable>*) list.v;

	if ((unsigned int)Expression::getIntValue(n) > v->size()) {
		cout << "List index out of bounds of " << Expression::getIntValue(n) << endl;
		exit(-3);
	}
	FuzuliVariable result = v->at(Expression::getIntValue(n));
	return (result);
}


SetExpression::SetExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = SET_EXPRESSION;
}

SetExpression::~SetExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable SetExpression::eval(Environment *env) {
	FuzuliVariable arr = this->expressions->at(0)->eval(env);
	FuzuliVariable n = this->expressions->at(1)->eval(env);
	FuzuliVariable newvalue = this->expressions->at(2)->eval(env);
	int int_n = Expression::getIntValue(n);
	vector<FuzuliVariable> *r_arr = (vector<FuzuliVariable>*) arr.v;
	r_arr->at(int_n) = newvalue;
	return(newvalue);
}


ExplodeExpression::ExplodeExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = EXPLODE_EXPRESSION;
}

ExplodeExpression::~ExplodeExpression() {

}

FuzuliVariable ExplodeExpression::eval(Environment *env) {
	FuzuliVariable source_str = this->expressions->at(0)->eval(env);
	FuzuliVariable delim = this->expressions->at(1)->eval(env);
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) result.v;

	char *temp = (char*) malloc(strlen(source_str.s));
	strcpy(temp, source_str.s);

	char *p = strtok(temp, delim.s);
	while (p) {
		FuzuliVariable tok = Expression::createNewString(p);
		vect->push_back(tok);
		p = strtok(NULL, delim.s);
	}

	free(temp);
	return (result);
}


ColonExpression::ColonExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = COLON_EXPRESSION;
}

ColonExpression::~ColonExpression() {
	cout << "ColonExpression Destructor" << endl;
}

FuzuliVariable ColonExpression::eval(Environment *env) {
	FuzuliVariable num1 = this->expressions->at(0)->eval(env);
	FuzuliVariable num2 = this->expressions->at(1)->eval(env);
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) result.v;

	int start = Expression::getIntValue(num1);
	int stop =  Expression::getIntValue(num2);
	for (int i = start; i <= stop; i++) {
		FuzuliVariable tok = Expression::createNewInt(i);
		vect->push_back(tok);
	}
	return (result);
}


AppendExpression::AppendExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = APPEND_EXPRESSION;
}

AppendExpression::~AppendExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable AppendExpression::eval(Environment *env) {
	FuzuliVariable list = this->expressions->at(0)->eval(env);
		FuzuliVariable element = this->expressions->at(1)->eval(env);
		vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) list.v;
		vect->push_back(element);
		return (list);
}

PrependExpression::PrependExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = PREPEND_EXPRESSION;
}

PrependExpression::~PrependExpression() {
	// TODO Auto-generated destructor stub
}

FuzuliVariable PrependExpression::eval(Environment *env) {
	FuzuliVariable list = this->expressions->at(0)->eval(env);
	FuzuliVariable element = this->expressions->at(1)->eval(env);
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) list.v;
	vect->insert(vect->begin(), element);
	return (list);
}

/*
RemoveExpression::RemoveExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = REMOVE_EXPRESSION;
}

RemoveExpression::~RemoveExpression() {

}

Token *RemoveExpression::eval(Environment *env) {
	Token *arr = this->expressions->at(0)->eval(env);
	Token *n = this->expressions->at(1)->eval(env);
	arr->tokens[n->getIntValue()]->ReduceReferences();
	arr->tokens.erase(arr->tokens.begin() + n->getIntValue());
	return (arr);
}

FindExpression::FindExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FIND_EXPRESSION;
}

FindExpression::~FindExpression() {

}

Token *FindExpression::eval(Environment *env) {
	Token *arr = this->expressions->at(0)->eval(env);
	Token *what = this->expressions->at(1)->eval(env);
	for (unsigned int i = 0; i < arr->tokens.size(); i++) {
		if (*arr->tokens[i] == *what) {
			return (env->newToken(i, INTEGER));
		}
	}
	return (Token::NULL_TOKEN);
}

FillExpression::FillExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FILL_EXPRESSION;
}

FillExpression::~FillExpression() {

}

Token* FillExpression::eval(Environment *env) {
	Token *arr = this->expressions->at(0)->eval(env);
	Token *val = this->expressions->at(1)->eval(env);
	if (arr->getType() == LIST) {
		for (unsigned int i = 0; i < arr->tokens.size(); i++) {
			arr->tokens[i]->setContent(val->getContent());
		}
	} else {
		cout << "Non-array object can not be filled at line "
				<< val->getLineNumber() << endl;
	}
	return (arr);
}

FirstExpression::FirstExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = FIRST_EXPRESSION;
}

FirstExpression::~FirstExpression() {

}

Token *FirstExpression::eval(Environment *env) {
	Token *arr = this->expressions->at(0)->eval(env);
	if (arr->getType() == LIST) {
		return (arr->tokens[0]);
	} else {
		cout << "Array is not a list in (first) expression" << endl;
	}
	return (Token::NULL_TOKEN);
}

LastExpression::LastExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = LAST_EXPRESSION;
}

LastExpression::~LastExpression() {

}

Token *LastExpression::eval(Environment *env) {
	Token *arr = this->expressions->at(0)->eval(env);
	if (arr->getType() == LIST) {
		return (arr->tokens[arr->tokens.size() - 1]);
	} else {
		cout << "Array is not a list in (first) expression" << endl;
	}
	return (Token::NULL_TOKEN);
}


*/
} /* namespace fuzuli */
