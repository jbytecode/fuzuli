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

#include "FuzuliRunnable.h"
#include <vector>
#include <boost/thread.hpp>

using namespace fuzuli;
using namespace std;

FuzuliRunnable::FuzuliRunnable(){

}

FuzuliRunnable::~FuzuliRunnable(){

}


void FuzuliRunnable::CreateThread(const char *fname, Environment *env){
	this->env = env;
	string strfname = string(fname) + "0";
	this->func = env->getFunction(strfname.c_str());
	vector<Expression*> vect;
	vect.push_back(new IdentifierExpression(env->newToken(fname, IDENTIFIER)));
	this->fcallexpr = new FunctionCallExpression(vect);
	this->t =  boost::thread(&FuzuliRunnable::run, this);
}



void FuzuliRunnable::run(){
	this->fcallexpr->eval(this->env);
}


