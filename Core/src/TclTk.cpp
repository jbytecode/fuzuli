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
#include <tcl/tcl.h>
#include <tk/tk.h>

namespace fuzuli {

extern "C" {
Token *tcltk_init(Token* params, Environment *env);
Token *tcltk_run(Token* params, Environment *env);
Token *tcltk_doevents(Token* params, Environment *env);
}

using namespace std;

static Tcl_Interp *interpreter;

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
	return (result);
}

void registerEvents() {
	cout << "Registering events" << endl;
}

Token *tcltk_run(Token* params, Environment *env) {
	int ti = Tcl_Eval(interpreter, params->tokens[0]->getContent());
	Token *result = env->newToken(0.0, INTEGER);
	result->setIntValue(ti);
	cout << "Returning " << ti << " for command "
			<< params->tokens[0]->getContent() << endl;
	return (result);
}

Token *tcltk_doevents(Token* params, Environment *env) {
	Tk_DoOneEvent(TCL_ALL_EVENTS);
	return (Token::NULL_TOKEN);
}

}

