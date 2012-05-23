/*
 * main.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: hako
 */

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "FuzuliTypes.h"



using namespace std;
using namespace fuzuli;

static int a_argc;
static char **a_argv;

void doRepl(){
	SourceCode *source = new SourceCode();
	Environment *env = new Environment();
	AstBuilder *ast;
	Expression *expr;
	Token *tok;
	string line;

	env->setFirst();
	env->setArgcArgv(a_argc, a_argv);
	char *buffer = (char*)malloc(1024);
	while(1){
		cout << "F: ";
		cin.getline(buffer,1023);
		line = string(buffer); line.append("\r\n");
		source->readFromText(&line);
		source->reset();
		ast = new AstBuilder(source);
		while( 1 ){
				expr = ast->getNextExpression();
				if(!expr) break;
				tok = expr->eval(env);
				cout << tok->getContent() << endl;
				//Environment::GCEnvironment->GC();
		}
	}
}

int main(int argc, char** argv){
	a_argc = argc;
	a_argv = argv;
	if(argc == 1){
		cout << "Fuzuli build " << __DATE__ << " " << __TIME__ << endl;
		cout << "usage:" << endl;
		cout << " fuzuli source"<< endl;
		cout << " fuzuli --repl"<< endl;
		exit(0);
	}else if(argc == 2 && strcmp(argv[1], "--repl")==0){
		doRepl();
		exit(0);
	}
	SourceCode *s = new SourceCode();
	s->readFromFile(argv[1]);
	//cout << s->getSourceCode()->c_str() << endl;

	s->reset();

	AstBuilder *b = new AstBuilder(s);
	Environment *globalEnvironment = new Environment();
	globalEnvironment->setFirst();
	globalEnvironment->setArgcArgv(argc, argv);
	Expression *ex;


	while( 1 ){
		ex = b->getNextExpression();
		if(!ex) break;
		ex->eval(globalEnvironment);
		//Environment::GCEnvironment->GC();
	}

	//Token *t = new Token("...",STRING);
	//t->toString();

}




