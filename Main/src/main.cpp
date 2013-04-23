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

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstring>
#include <readline/readline.h>
#include <readline/history.h>
#include "FuzuliTypes.h"
#include "../include/serialization.h"

using namespace std;
using namespace fuzuli;

static int a_argc;
static char **a_argv;

void doRepl();
int calculateNumberOfParanthesis(const char *);
void doSerialize(char *);
void printFuzuliVariable(FuzuliVariable &f);

void doSerialize(char *filename) {
	cout << "Serializer is not implemented yet" << endl;
	/*
	 Serializer *s = new Serializer();
	 stringstream channel;
	 s->serializeFile(filename, channel);
	 cout << channel.str().c_str()<<endl;
	 */
}

void printFuzuliVariable(FuzuliVariable &f) {
	if (f.type == INTEGER) {
		cout << f.i << endl;
	} else if (f.type == FLOAT) {
		cout << f.d << endl;
	} else if (f.type == STRING) {
		cout << f.s << endl;
	} else if (f.type == LIST) {
		vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) f.v;
		for (unsigned int i = 0; i < vect->size(); i++) {
			printFuzuliVariable(vect->at(i));
			cout << " ";
		}
	}
}

int calculateNumberOfParanthesis(const char *c) {
	int num = 0;
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		if (c[i] == '(') {
			num++;
		} else if (c[i] == ')') {
			num--;
		}
	}
	return (num);
}

void doRepl() {
	SourceCode *source = new SourceCode();
	Environment *env = new Environment();
	AstBuilder *ast;
	Expression *expr;
	FuzuliVariable result;

	env->setArgcArgv(a_argc, a_argv);
	env->registerGlobals();

	char* input;
	stringstream ss;

	add_history("(require");
	add_history("(print");
	add_history("(let");

	while (1) {

		rl_bind_key('\t', rl_complete);

		input = readline("F: ");

		if (!input) {
			break;
		}

		add_history(input);

		ss << string(input) << " ";

		if (calculateNumberOfParanthesis(ss.str().c_str()) == 0) {
			string code = ss.str() + "\r\n";
			source->readFromText(&code);
			source->reset();
			ast = new AstBuilder(source);
			expr = ast->getNextExpression();
			if (!expr) {
				ss.str("");
				break;
			}
			result = expr->eval(env);
			printFuzuliVariable(result);
			free(input);
			ss.str("");
		}
	}

}

int main(int argc, char** argv) {
	a_argc = argc;
	a_argv = argv;
	if (argc == 1) {
		cout << "Fuzuli build " << __DATE__ << " " << __TIME__ << endl;
		cout << "usage:" << endl;
		cout << " fuzuli source" << endl;
		cout << " fuzuli --repl" << endl;
		cout << " fuzuli --serialize source" << endl;
		exit(0);
	} else if (argc == 2 && strcmp(argv[1], "--repl") == 0) {
		doRepl();
		exit(0);
	} else if (argc == 3 && strcmp(argv[1], "--serialize") == 0) {
		doSerialize(argv[2]);
		exit(0);
	}
	SourceCode *s = new SourceCode();
	s->readFromFile(argv[1]);
	//cout << s->getSourceCode()->c_str() << endl;

	s->reset();

	AstBuilder *b = new AstBuilder(s);
	Environment *globalEnvironment = new Environment();

	globalEnvironment->setArgcArgv(argc, argv);
	globalEnvironment->registerGlobals();
	Expression *ex;

	while (1) {
		ex = b->getNextExpression();
		if (!ex) {
			break;
		}
		ex->eval(globalEnvironment);
	}

	//Token *t = new Token("...",STRING);
	//t->toString();

}

