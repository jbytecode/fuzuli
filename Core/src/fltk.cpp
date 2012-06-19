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
#include "fltk.h"

#include <stdlib.h>
#include <Fl.H>
#include <Fl_Window.H>
#include <Fl_Button.H>
#include <Fl_Widget.H>
#include <Fl_Input.H>

namespace fuzuli {

using namespace std;

extern "C" {
Token *window_new_3(Token *p, Environment *env);
Token *window_begin(Token *p, Environment *env);
Token *window_end(Token *p, Environment *env);
Token *window_show(Token *p, Environment *env);
Token *window_add(Token *p, Environment *env);

Token *window_main_loop(Token *p, Environment *env);

Token *button_new(Token *p, Environment *env);

Token *input_new(Token *p, Environment *env);
Token *input_settext(Token *p, Environment *env);
Token *input_gettext(Token *p, Environment *env);

Token *progress_new(Token*p, Environment *env);
Token *progress_setvalue(Token *p, Environment *env);
Token *progress_getvalue(Token *p, Environment *env);
}

void default_callback(Fl_Widget* widget, void* p) {
	Environment *env = (Environment*) p;
	Token *details = env->newToken("@LIST", LIST);
	Token *funcname = env->newToken("event", STRING);

	switch (Fl::event()) {
	case FL_PUSH:
		details->tokens.push_back(env->newToken("push", STRING));
		break;

	case FL_RELEASE:
		details->tokens.push_back(env->newToken("release", STRING));
		break;

	case FL_ENTER:
		details->tokens.push_back(env->newToken("enter", STRING));
		break;

	case FL_LEAVE:
		details->tokens.push_back(env->newToken("leave", STRING));
		break;

	case FL_DRAG:
		details->tokens.push_back(env->newToken("drag", STRING));

		break;

	case FL_FOCUS:
		details->tokens.push_back(env->newToken("focus", STRING));

		break;

	case FL_UNFOCUS:
		details->tokens.push_back(env->newToken("unfocus", STRING));

		break;

	case FL_KEYDOWN:
		details->tokens.push_back(env->newToken("keydown", STRING));
		break;

	case FL_KEYUP:
		details->tokens.push_back(env->newToken("keyup", STRING));
		break;

	case FL_CLOSE:
		details->tokens.push_back(env->newToken("close", STRING));
		break;

	case FL_MOVE:
		details->tokens.push_back(env->newToken("move", STRING));
		break;

	case FL_SHORTCUT:
		details->tokens.push_back(env->newToken("shortcut", STRING));
		break;

	case FL_DEACTIVATE:
		details->tokens.push_back(env->newToken("deactivate", STRING));
		break;

	case FL_ACTIVATE:
		details->tokens.push_back(env->newToken("activate", STRING));
		break;

	case FL_HIDE:
		details->tokens.push_back(env->newToken("hide", STRING));
		break;

	case FL_SHOW:
		details->tokens.push_back(env->newToken("show", STRING));
		break;

	case FL_PASTE:
		details->tokens.push_back(env->newToken("paste", STRING));
		break;

	case FL_SELECTIONCLEAR:
		details->tokens.push_back(env->newToken("selectionclear", STRING));
		break;

	case FL_MOUSEWHEEL:
		details->tokens.push_back(env->newToken("mousewheel", STRING));
		break;

	case FL_NO_EVENT:
		details->tokens.push_back(env->newToken("noevent", STRING));
		break;
	}

	details->tokens.push_back(env->newToken(widget->label(), STRING));
	details->tokens.push_back(env->newToken(widget->x(), STRING));
	details->tokens.push_back(env->newToken(widget->y(), STRING));
	details->tokens.push_back(env->newToken(widget->w(), STRING));
	details->tokens.push_back(env->newToken(widget->h(), STRING));
	Token *source = env->newToken("@FuzuliWidget", COBJECT);
	source->object = widget;
	details->tokens.push_back(source);

	vector<Expression*> v;
	v.push_back(new IdentifierExpression(funcname));
	vector<Expression*> vl;
	for (unsigned int i = 0; i < details->tokens.size(); i++) {
		vl.push_back(new StringExpression(details->tokens[i]));
	}
	ListExpression *lst = new ListExpression(vl);
	v.push_back(lst);
	FunctionCallExpression *fce = new FunctionCallExpression(v);
	fce->eval(env);

}

Token *progress_getvalue(Token *p, Environment *env){
	FuzuliProgress *progress = (FuzuliProgress*)p->tokens[0]->object;
	Token *result = env->newToken(progress->value(), FLOAT);
	return(result);
}

Token *progress_setvalue(Token *p, Environment *env){
	FuzuliProgress *progress = (FuzuliProgress*)p->tokens[0]->object;
	double value = p->tokens[1]->getFloatValue();
	progress->value(value);
	return(Token::NULL_TOKEN);
}

Token *progress_new(Token *p, Environment *env){
	int x = p->tokens[0]->getIntValue();
	int y = p->tokens[1]->getIntValue();
	int w = p->tokens[2]->getIntValue();
	int h = p->tokens[3]->getIntValue();
	const char *title = p->tokens[4]->getContent();
	FuzuliProgress *progress = new FuzuliProgress(x, y, w, h, title, env);
	progress->callback(default_callback, env);
	Token *result = env->newToken("@Button", COBJECT);
	result->object = progress;
	return (result);
}

Token *button_new(Token *p, Environment *env) {
	int x = p->tokens[0]->getIntValue();
	int y = p->tokens[1]->getIntValue();
	int w = p->tokens[2]->getIntValue();
	int h = p->tokens[3]->getIntValue();
	const char *title = p->tokens[4]->getContent();
	FuzuliButton *button = new FuzuliButton(x, y, w, h, title, env);
	button->callback(default_callback, env);
	Token *result = env->newToken("@Button", COBJECT);
	result->object = button;
	return (result);
}

Token *input_gettext(Token *p, Environment *env){
	FuzuliInput *input = (FuzuliInput*) p->tokens[0]->object;
		Token *result = env->newToken(input->value(), STRING);
		return(result);
}

Token *input_settext(Token *p, Environment *env){
	FuzuliInput *input = (FuzuliInput*) p->tokens[0]->object;
	const char *text = p->tokens[1]->getContent();
	input->value(text);
	return(Token::NULL_TOKEN);
}

Token *input_new(Token *p, Environment *env) {
	int x = p->tokens[0]->getIntValue();
	int y = p->tokens[1]->getIntValue();
	int w = p->tokens[2]->getIntValue();
	int h = p->tokens[3]->getIntValue();
	const char *title = p->tokens[4]->getContent();
	FuzuliInput *input = new FuzuliInput(x, y, w, h, title, env);
	input->callback(default_callback, env);
	Token *result = env->newToken("@Input", COBJECT);
	result->object = input;
	return (result);
}

TwoParameters
Token *window_add(Token *p, Environment *env) {
	FuzuliWindow *win = (FuzuliWindow*) p->tokens[0]->object;
	FuzuliWidget *wobj = (FuzuliWidget*) p->tokens[1]->object;
	win->add(wobj);
	return (Token::NULL_TOKEN);
}

OneParameters
Token *window_show(Token *p, Environment *env) {
	FuzuliWindow *win = (FuzuliWindow*) p->tokens[0]->object;
	win->show();
	return (Token::NULL_TOKEN);
}

NoParameters
Token *window_main_loop(Token *p, Environment *env) {
	Fl::run();
	return (Token::NULL_TOKEN);
}

OneParameters
Token *window_end(Token *p, Environment *env) {
	FuzuliWindow *win = (FuzuliWindow*) p->tokens[0]->object;
	win->end();
	return (Token::NULL_TOKEN);
}

OneParameters
Token *window_begin(Token *p, Environment *env) {
	FuzuliWindow *win = (FuzuliWindow*) p->tokens[0]->object;
	win->begin();
	return (Token::NULL_TOKEN);
}

ThreeParameters
Token *window_new_3(Token *p, Environment *env) {
	int w = p->tokens[0]->getIntValue();
	int h = p->tokens[1]->getIntValue();
	const char* title = p->tokens[2]->getContent();
	FuzuliWindow *win = new FuzuliWindow(w, h, title, env);
	Token *result = env->newToken("@FLWindow", COBJECT);
	result->object = win;
	return (result);
}

}
