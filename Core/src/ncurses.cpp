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
Token *ncinitscrd (Token *p, Environment *env);
Token *ncprintwd (Token *p, Environment *env);
Token *ncrefreshd(Token *p, Environment *env);
Token *ncgetchd(Token *p, Environment *env);
Token *ncendwind(Token *p, Environment *env);
Token *ncinitpaird(Token *p, Environment *env);
Token *ncstartcolord(Token *p, Environment *env);
Token *ncsetcolorpair(Token *p, Environment *env);
}

OneParameters
Token *ncsetcolorpair(Token *p, Environment *env){
	attron(COLOR_PAIR(p->tokens[0]->getIntValue()));
	return(Token::NULL_TOKEN);
}

NoParameters
Token *ncstartcolord(Token *p, Environment *env){
	start_color();
	return(Token::NULL_TOKEN);
}

ThreeParameters
Token *ncinitpaird(Token *p, Environment *env){
	short num = (short) p->tokens[0]->getIntValue();
	short col1 = (short) p->tokens[1]->getIntValue();
	short col2 = (short) p->tokens[2]->getIntValue();
	int int_res = init_pair(num, col1, col2);
	Token *result = new Token(int_res, INTEGER);
	return(result);
}

Token *ncendwind(Token *p, Environment *env){
	Token *result = new Token (endwin(), INTEGER);
	return(result);
}

Token *ncgetchd(Token *p, Environment *env){
	getch();
	return(Token::NULL_TOKEN);
}

Token *ncrefreshd(Token *p, Environment *env){
	Token *result = new Token(refresh(), INTEGER);
	return(result);
}


Token *ncprintwd (Token *p, Environment *env){
	printw(p->tokens[0]->getContent());
	return(Token::NULL_TOKEN);
}

Token *ncinitscrd (Token *p, Environment *env){
	WINDOW *win = initscr();
	Token *result = new Token("@NCursesWindow", COBJECT);
	result->object = (void*)win;
	return(result);
}


