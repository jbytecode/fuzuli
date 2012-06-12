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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <ncurses.h>

using namespace std;
using namespace fuzuli;

extern "C" {
Token *initscrd (Token *p, Environment *env);
Token *printwd (Token *p, Environment *env);
Token *refreshd(Token *p, Environment *env);
Token *getchd(Token *p, Environment *env);
Token *endwind(Token *p, Environment *env);
Token *initpaird(Token *p, Environment *env);
Token *startcolord(Token *p, Environment *env);
Token *setcolorpair(Token *p, Environment *env);
Token *newwinp(Token *p, Environment *env);
Token *boxp(Token *p, Environment *env);
Token *wrefreshd(Token *p, Environment *env);
Token *delwind(Token *p, Environment *env);
Token *wborderd(Token *p, Environment *env);
}

MoreThanThreeParameters
Token *wborderd(Token *p, Environment *env){
	WINDOW *win = (WINDOW*)p->tokens[0]->object;
	unsigned int c1 = (unsigned int) p->tokens[1]->getIntValue();
	unsigned int c2 = (unsigned int) p->tokens[2]->getIntValue();
	unsigned int c3 = (unsigned int) p->tokens[3]->getIntValue();
	unsigned int c4 = (unsigned int) p->tokens[4]->getIntValue();
	unsigned int c5 = (unsigned int) p->tokens[5]->getIntValue();
	unsigned int c6 = (unsigned int) p->tokens[6]->getIntValue();
	unsigned int c7 = (unsigned int) p->tokens[7]->getIntValue();
	unsigned int c8 = (unsigned int) p->tokens[8]->getIntValue();
	wborder(win,c1,c2,c3,c4,c5,c6,c7,c8);
	return(Token::NULL_TOKEN);
}

OneParameters
Token *delwind(Token *p, Environment *env){
	WINDOW *win = (WINDOW*)p->tokens[0]->object;
	Token *result = new Token(delwin(win), INTEGER);
	return(result);
}

OneParameters
Token *wrefreshd(Token *p, Environment *env){
	WINDOW *win = (WINDOW*) p->tokens[0]->object;
	return(new Token(wrefresh(win), INTEGER));
}

ThreeParameters
Token *boxp (Token *p , Environment *env){
	WINDOW *win = (WINDOW*) p->tokens[0]->object;
	unsigned int param1 = (unsigned int)p->tokens[1]->getIntValue();
	unsigned int param2 = (unsigned int)p->tokens[2]->getIntValue();
	return(new Token(box(win, param1, param2), INTEGER));
}

MoreThanThreeParameters
Token *newwinp(Token *p, Environment *env){
	int height = p->tokens[0]->getIntValue();
	int width = p->tokens[1]->getIntValue();
	int starty = p->tokens[2]->getIntValue();
	int startx = p->tokens[3]->getIntValue();
	WINDOW *window = newwin(height, width, starty, startx);
	Token *result = new Token("@WINDOW", COBJECT);
	result->object = window;
	return(result);
}

OneParameters
Token *setcolorpair(Token *p, Environment *env){
	attron(COLOR_PAIR(p->tokens[0]->getIntValue()));
	return(Token::NULL_TOKEN);
}

NoParameters
Token *startcolord(Token *p, Environment *env){
	start_color();
	return(Token::NULL_TOKEN);
}

ThreeParameters
Token *initpaird(Token *p, Environment *env){
	short num = (short) p->tokens[0]->getIntValue();
	short col1 = (short) p->tokens[1]->getIntValue();
	short col2 = (short) p->tokens[2]->getIntValue();
	int int_res = init_pair(num, col1, col2);
	Token *result = new Token(int_res, INTEGER);
	return(result);
}

Token *endwind(Token *p, Environment *env){
	Token *result = new Token (endwin(), INTEGER);
	return(result);
}

Token *getchd(Token *p, Environment *env){
	getch();
	return(Token::NULL_TOKEN);
}

Token *refreshd(Token *p, Environment *env){
	Token *result = new Token(refresh(), INTEGER);
	return(result);
}


Token *printwd (Token *p, Environment *env){
	printw(p->tokens[0]->getContent());
	return(Token::NULL_TOKEN);
}

Token *initscrd (Token *p, Environment *env){
	WINDOW *win = initscr();
	Token *result = new Token("@NCursesWindow", COBJECT);
	result->object = (void*)win;
	return(result);
}


