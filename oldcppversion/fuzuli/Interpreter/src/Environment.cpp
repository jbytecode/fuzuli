/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012,2013 Mehmet Hakan Satman <mhsatman@yahoo.com>
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
#include <sstream>
#include <vector>
#include <list>

namespace fuzuli {

using namespace std;

bool Environment::isAutomaticGC = true;

Environment::Environment() {

}

Environment::Environment(Environment *base) {

}

Environment::~Environment() {

}

void Environment::registerGlobals() {
	FuzuliVariable intf1 = Expression::createNewInt(1);
	FuzuliVariable intf2 = Expression::createNewInt(2);
	FuzuliVariable intf3 = Expression::createNewInt(3);
	FuzuliVariable intf4 = Expression::createNewInt(4);
	FuzuliVariable intf5 = Expression::createNewInt(5);

	FuzuliVariable intf6 = Expression::createNewInt(1);
	FuzuliVariable intf7 = Expression::createNewInt(0);

	this->setVariable("INTEGER", intf1);
	this->setVariable("FLOAT", intf2);
	this->setVariable("STRING", intf3);
	this->setVariable("LIST", intf4);
	this->setVariable("NULL", intf5);
	this->setVariable("true", intf6);
	this->setVariable("false", intf7);
	Token::NULL_TOKEN->setKillable(false);
}

void Environment::setVariableInThisScope(const char *name,
		FuzuliVariable value) {
	Expression::setVariableName(name, value);
	this->variables.push_back(value);
}

FuzuliVariable Environment::getVariableInThisScope(const char *name) {
	for (int i = this->variables.size() - 1; i >= 0; i--) {
		FuzuliVariable f = this->variables[i];
		if (strcmp(f.name, "-") == 0) {
			break;
		} else if (strcmp(f.name, name) == 0) {
			return (f);
		}

	}
	FuzuliVariable result;
	result.type = NULLTOKEN;
	return (result);
}

void Environment::setVariable(const char *name, FuzuliVariable value) {
	int pos = getVariablePosition(name);
	if (pos == -1) {
		Expression::setVariableName(name, value);
		this->variables.push_back(value);
	} else {
		Expression::setVariableName(name, value);
		this->variables[pos] = value;
	}
}

void Environment::updateVariable(const char *name, FuzuliVariable value) {
	for (int i = this->variables.size() - 1; i >= 0; i--) {
		FuzuliVariable f = this->variables.at(i);
		if (strcmp(f.name, name) == 0) {
			this->variables[i] = value;
			return;
		}
	}

}

int Environment::getVariablePosition(const char *name) {
	for (int i = this->variables.size() - 1; i >= 0; i--) {
		FuzuliVariable f = this->variables.at(i);
		if (strcmp(f.name, name) == 0) {
			return (i);
		}
	}
	return (-1);
}

FuzuliVariable Environment::getVariable(const char *name) {
	for (int i = this->variables.size() - 1; i >= 0; i--) {
		FuzuliVariable f = this->variables.at(i);
		if (strcmp(f.name, name) == 0) {
			return (f);
		}
	}
	FuzuliVariable result;
	result.type = NULLTOKEN;
	return (result);
}

void Environment::createLocal() {
	FuzuliVariable f;
	f.name = "-";
	this->variables.push_back(f);
}

void Environment::deleteLocal() {
	for (int i = this->variables.size() - 1; i >= 0; i--) {
		FuzuliVariable f = this->variables.at(i);
		if (strcmp(f.name, "-") == 0) {
			this->variables.resize(i);
			break;
		}
	}
}

FuzuliFunction *Environment::searchFuncBackEnvironments(const char *name) {
	return (this->fuzuliFunctions[string(name)]);
}

void Environment::setFunction(const char *name, FuzuliFunction *value) {
	FuzuliFunction *existing = searchFuncBackEnvironments(name);
	if (!existing) {
		this->fuzuliFunctions[string(name)] = value;
	} else {
		existing->name = value->name;
		existing->environment = value->environment;
		existing->name = value->name;
		existing->params = value->params;
		existing->body = value->body;
	}
}

void Environment::setVariableForFunctionParams(const char* name,
		FuzuliVariable f) {

}

FuzuliFunction *Environment::getFunction(const char *name) {
	return (searchFuncBackEnvironments(name));
}

void Environment::setArgcArgv(int argc, char **argv) {
	FuzuliVariable fargc = Expression::createNewInt(argc);
	this->setVariable("argc", fargc);

	FuzuliVariable tok;
	tok.type = STRING;
	tok.s = "ARGV is not implemented yet";
	this->setVariable("argv", tok);
}

void Environment::dump() {
	for (unsigned int i = 0; i < this->variables.size(); i++) {
		FuzuliVariable f = this->variables.at(i);
		cout << i << ") " << f.name;
		if (f.type == INTEGER) {
			cout << f.i;
		} else if (f.type == FLOAT) {
			cout << f.d;
		}
		cout << endl;
	}
}

bool Environment::variableExists(const char *name) {
	FuzuliVariable f = this->getVariable(name);
	if (f.type == NULLTOKEN) {
		return (true);
	} else {
		return (false);
	}
}

DumpExpression::DumpExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DUMP_EXPRESSION;
}

DumpExpression::~DumpExpression() {

}

FuzuliVariable DumpExpression::eval(Environment *env) {
	env->dump();
	FuzuliVariable f = Expression::createNewInt(env->variables.size());
	return (f);
}

GCExpression::GCExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = GC_EXPRESSION;
}

GCExpression::~GCExpression() {

}

FuzuliVariable GCExpression::eval(Environment *env) {
	cout << "Gargabe Collection utility is not implemented yet" << endl;
	return (Expression::createNewInt(-1));
}

DeleteExpression::DeleteExpression(vector<Expression*> *expr) {
	this->expressions = expr;
	this->type = DELETE_EXPRESSION;
}

DeleteExpression::~DeleteExpression() {

}

FuzuliVariable DeleteExpression::eval(Environment *env) {
	cout << "Delete expression is not implemented yet "<<endl;
	return(Expression::createNewInt(-1));
}

} /* namespace fuzuli */
