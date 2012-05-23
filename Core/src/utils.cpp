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
#include <cstring>
#include <algorithm>


using namespace std;
using namespace fuzuli;

extern "C" {
Token *shuffle(Token *p, Environment *env);
Token *sortd(Token *p,Environment *env);
Token *sorta(Token *p,Environment *env);
}



bool TokenSorter_a (Token *i,Token *j){
	return (i->getFloatValue() < j->getFloatValue());
}

bool TokenSorter_d (Token *i,Token *j){
	return (i->getFloatValue() > j->getFloatValue());
}


Token *sorta (Token *p,Environment *env){
	sort(p->tokens[0]->tokens.begin(), p->tokens[0]->tokens.end(),TokenSorter_a);
	return(Token::NULL_TOKEN);
}

Token *sortd (Token *p,Environment *env){
	sort(p->tokens[0]->tokens.begin(), p->tokens[0]->tokens.end(),TokenSorter_d);
	return(Token::NULL_TOKEN);
}

Token *shuffle(Token *p,Environment *env){
	random_shuffle(p->tokens[0]->tokens.begin(), p->tokens[0]->tokens.end());
	return(Token::NULL_TOKEN);
}



