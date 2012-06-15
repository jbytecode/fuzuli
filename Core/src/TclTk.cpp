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
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#ifdef __linux
#include <tcl/tcl.h>
#include <tk/tk.h>
#else
#include <tcl.h>
#include <tk.h>
#endif

namespace fuzuli {

extern "C" {
Token *tcltk_init(Token* params, Environment *env);
Token *tcltk_run(Token* params, Environment *env);
Token *tcltk_add(Token* params, Environment *env);
Token *tcltk_doevents(Token* params, Environment *env);
Token *tcltk_mainloop(Token* params, Environment *env);
Token *tcltk_create_command(Token *params, Environment *env);
Token *tcltk_get_string_result (Token *params, Environment *env);
}

using namespace std;

static Tcl_Interp *interpreter;
static stringstream ss;

class CommandInfo {
public:
	Environment *env;
	const char *command;
};

int DefaultCommand(ClientData clientdata, Tcl_Interp *interpreter,
		int argc, char **argv) {
	CommandInfo *ci = reinterpret_cast<CommandInfo*>(clientdata);
	//cout << "Event Client: "<< ci->command << endl;
	Environment *env = ci->env;

	vector<Expression*> funcvec;
	funcvec.push_back(new IdentifierExpression(env->newToken(ci->command,STRING)));
	FunctionCallExpression *fce = new FunctionCallExpression(funcvec);
	Token *result = fce->eval(env);
    return 0;
}


Token *tcltk_create_command(Token *params, Environment *env){
	const char *commandname = params->tokens[0]->getContent();
	CommandInfo *ci = new CommandInfo();
	ci->env = env;
	ci->command = commandname;
	ClientData cd = reinterpret_cast<ClientData>(ci);
	Tcl_CreateCommand(interpreter, commandname, (Tcl_CmdProc*) DefaultCommand, cd, NULL);
	cout << "Command created "<<commandname<<endl;
	return(Token::NULL_TOKEN);
}


Token *tcltk_init(Token* params, Environment *env) {
	Token *result = env->newToken(0.0, INTEGER);
	interpreter = Tcl_CreateInterp();

	int cc = Tcl_Init(interpreter);
	if (cc != TCL_OK) {
		cout << (interpreter->result) << endl;
	}
	cc = Tk_Init(interpreter);
	if (cc != TCL_OK) {
		cout << (interpreter->result) << endl;
	}
	//registerEvents();
	result->setIntValue(interpreter->errorLine);
	return(result);
}



Token *tcltk_run(Token* params, Environment *env) {
	int ti = Tcl_Eval(interpreter, params->tokens[0]->getContent());
	Token *result = env->newToken(0.0, INTEGER);
	result->setIntValue(ti);
	cout << "Returning " << ti << " for command "
			<< params->tokens[0]->getContent() << endl;
	ss.clear();
	return (result);
}

NoParameters
Token *tcltk_get_string_result (Token *params, Environment *env){
	Token *result = env->newToken(Tcl_GetStringResult(interpreter),STRING);
	return(result);
}

Token *tcltk_doevents(Token* params, Environment *env) {
	Tk_DoOneEvent(TCL_ALL_EVENTS);
	return (Token::NULL_TOKEN);
}


Token *tcltk_mainloop(Token* params, Environment *env){
	Tk_MainLoop();
	return(Token::NULL_TOKEN);
}

}

