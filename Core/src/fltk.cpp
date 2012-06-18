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
#include <stdlib.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>

namespace fuzuli {

using namespace std;

extern "C" {
Token *form_new_3(Token *p, Environment *env);
Token *form_begin(Token *p, Environment *env);
Token *form_end(Token *p, Environment *env);
Token *form_show(Token *p, Environment *env);
Token *form_add(Token *p, Environment *env);

Token *form_main_loop(Token *p, Environment *env);

Token *button_new(Token *p, Environment *env);
}

int fhandle(Fl_Widget *widget, int e, Environment *env, const char *type) {
	int ret =e;
	Token *details = env->newToken("@LIST", LIST);
	Token *funcname = env->newToken(type, STRING);
	switch (e) {
	case FL_PUSH:
		details->tokens.push_back(env->newToken("push", STRING));
		details->tokens.push_back(env->newToken(widget->label(), STRING));
		break;

	case FL_RELEASE:
		break;

	case FL_ENTER:
		break;

	case FL_LEAVE:
		break;

	case FL_DRAG:
		break;

	case FL_FOCUS:
		break;

	case FL_UNFOCUS:
		break;

	case FL_KEYDOWN:
		break;

	case FL_KEYUP:
		break;

	case FL_CLOSE:
		break;

	case FL_MOVE:
		break;

	case FL_SHORTCUT:
		break;

	case FL_DEACTIVATE:
		break;

	case FL_ACTIVATE:
		break;

	case FL_HIDE:
		break;

	case FL_SHOW:
		break;

	case FL_PASTE:
		break;

	case FL_SELECTIONCLEAR:
		break;

	case FL_MOUSEWHEEL:
		break;

	case FL_NO_EVENT:
		break;

	}

	vector<Expression*> v;
	v.push_back(new IdentifierExpression(funcname));
	vector<Expression*> vl;
	for (unsigned int i=0;i<details->tokens.size();i++){
			vl.push_back(new StringExpression(details->tokens[i]));
	}
	ListExpression *lst = new ListExpression(vl);
	v.push_back(lst);
	FunctionCallExpression *fce = new FunctionCallExpression(v);
	fce->eval(env);
	return (ret);
}

class FuzuliButton : public Fl_Button {
public:
	Environment *environment;
	FuzuliButton(int x,int y, int width, int height, const char *t, Environment *env) : Fl_Button(x,y,width,height,t){
		this->environment = env;
	};
	int handle(int e){
		int res = fhandle(this, e, this->environment, "button_event");
		return(e);
	}
};


Token *button_new(Token *p, Environment *env) {
	int x = p->tokens[0]->getIntValue();
	int y = p->tokens[1]->getIntValue();
	int w = p->tokens[2]->getIntValue();
	int h = p->tokens[3]->getIntValue();
	const char *title = p->tokens[4]->getContent();
	FuzuliButton *button = new FuzuliButton(x, y, w, h, title,env);
	Token *result = env->newToken("@Button", COBJECT);
	result->object = button;
	return (result);
}

TwoParameters
Token *form_add(Token *p, Environment *env) {
	Fl_Window *win = (Fl_Window*) p->tokens[0]->object;
	Fl_Button *wobj = (Fl_Button*) p->tokens[1]->object;
	win->add(wobj);
	return (Token::NULL_TOKEN);
}

OneParameters
Token *form_show(Token *p, Environment *env) {
	Fl_Window *win = (Fl_Window*) p->tokens[0]->object;
	win->show();
	return (Token::NULL_TOKEN);
}

NoParameters
Token *form_main_loop(Token *p, Environment *env) {
	Fl::run();
	return (Token::NULL_TOKEN);
}

OneParameters
Token *form_end(Token *p, Environment *env) {
	Fl_Window *win = (Fl_Window*) p->tokens[0]->object;
	win->end();
	return (Token::NULL_TOKEN);
}

OneParameters
Token *form_begin(Token *p, Environment *env) {
	Fl_Window *win = (Fl_Window*) p->tokens[0]->object;
	win->begin();
	return (Token::NULL_TOKEN);
}

ThreeParameters
Token *form_new_3(Token *p, Environment *env) {
	int w = p->tokens[0]->getIntValue();
	int h = p->tokens[1]->getIntValue();
	const char* title = p->tokens[2]->getContent();
	Fl_Window *win = new Fl_Window(w, h, title);
	Token *result = env->newToken("@FLWindow", COBJECT);
	result->object = win;
	return (result);
}

}
