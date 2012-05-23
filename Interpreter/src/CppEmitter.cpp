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



#include "../include/FuzuliTypes.h"
#include <sstream>

namespace fuzuli {

CppEmitter::CppEmitter(){

}

CppEmitter::~CppEmitter(){

}

void CppEmitter::emitCpp(stringstream *ss){
	cout << "CppEmitter::emitCpp"<<endl;
}



CPlusPlusExpression::CPlusPlusExpression(vector<Expression*> expr){
	this->expressions = expr;
	this->resultToken = Token::NULL_TOKEN;
}

CPlusPlusExpression::~CPlusPlusExpression(){

}



Token *CPlusPlusExpression::eval(Environment *env){
	stringstream CppCode;
	Token *str_code = this->expressions[0]->eval(env);
	SourceCode *source = new SourceCode();
	string *s = new string(str_code->getContent()); s->append("\n");
	source->readFromText(s);
	source->reset();
	AstBuilder *builder = new AstBuilder(source);
	Expression *expr;
	while (1){
		expr = builder->getNextExpression();
		if(!expr){
			break;
		}
		CppEmitter *ce = dynamic_cast<CppEmitter*>(expr);
		ce->emitCpp(&CppCode);
	}
	this->resultToken->setContent( CppCode.str().c_str() );
	this->resultToken->setType(STRING);
	//cout << this->resultToken->getContent()<<endl;
	return(this->resultToken);
}


}
