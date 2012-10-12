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

#ifndef SERIALIZATION_H_
#define SERIALIZATION_H_

#include <iostream>
#include <ostream>

using namespace std;

namespace fuzuli {

class Serializer {
public:
	Serializer();
	~Serializer();
	void serializeFile(string infile, stringstream& channel);
	void serializeExpression(Expression *expr, stringstream& channel);
	void setByteCode(char* bc);
	char *getByteCode();
	Expression* getNextExpression();
	static void IntToChars(int value, stringstream& channel);
	static void DoubleToChars(double value, stringstream& channel);
	static void StringToChars(string value, stringstream& channel);
	static void CharArrayToChars(const char *value, stringstream& channel);
private:
	SourceCode *code;
	AstBuilder *builder;
	char *bytecode;
	unsigned int code_index;
};

} /* end of namespace fuzuli */

#endif /* SERIALIZATION_H_ */
