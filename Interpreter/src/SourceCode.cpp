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
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <cstring>
#include <cstdlib>
#include <sstream>

namespace fuzuli {

using namespace std;

SourceCode::SourceCode() {
	// TODO Auto-generated constructor stub
}

SourceCode::~SourceCode() {

}

void SourceCode::readFromText(string *code) {
	this->code = code;
}

void SourceCode::readFromFile(const char *filename) {
	this->code = new string();
	char c[2];
	c[1] = '\0';

	ifstream myfile(filename, ios::in);
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			myfile.get(c[0]);
			this->code->append(c);
		}
		myfile.close();
	} else {
		cout << "File " << string(filename) << " can not be opened" << endl;
	}
}

string *SourceCode::getSourceCode() {
	return (this->code);
}

void SourceCode::reset() {
	this->counter = 0;
	this->oldcounter = 0;
	this->currentLine = 1;
}

char SourceCode::eat() {
	if (this->counter == this->code->length() - 1) {
		return ('\0');
	}
	char c = this->code->c_str()[this->counter];
	this->counter++;
	return (c);
}

void SourceCode::putback() {
	if (this->counter == 0) {
		return;
	}
	this->counter--;
}

char SourceCode::look() {
	if (this->counter == this->code->length()) {
		return ('\0');
	}
	char c = this->code->c_str()[this->counter];
	return (c);
}

void SourceCode::pushBackToken() {
	this->counter = this->oldcounter;
}

unsigned int SourceCode::getCurrentLine() {
	return (this->currentLine);
}

void SourceCode::setCounter(unsigned int val){
	this->oldcounter = this->counter;
	this->counter = val;
}

unsigned int SourceCode::getCounter(){
	return(this->counter);
}

Token *SourceCode::getNextToken() {
	this->oldcounter = this->counter;
	stringstream tokenvalue;
	enum TokenType tokentype;
	char currentChar, nextChar;

	tokenvalue.clear();

	start: currentChar = eat();

	switch (currentChar) {
	case '\0':
		tokentype = EOP;
		tokenvalue << "@End of Program";
		break;

	case '\n':
		this->currentLine++;
		return (getNextToken());
		break;
	case '\r':
		return (getNextToken());
		break;

	case '\t':
		return (getNextToken());
		break;

	case '#':
		while (1) {
			currentChar = look();
			if (currentChar == '\n' || currentChar == '\r') {
				return (getNextToken());
				break;
			}
			eat();
		}
		break;

	case ' ':
		return (getNextToken());
		break;

	case '(':
		tokentype = LPARENTH;
		tokenvalue << "(";
		break;

	case ')':
		tokentype = RPARENTH;
		tokenvalue << ")";
		break;

	case ':':
		tokentype = COLON;
		tokenvalue << ":";
		break;

	case '+':
		nextChar = look();
		if (nextChar == '+') {
			eat();
			tokentype = PLUSPLUS;
			tokenvalue << "++";
		} else {
			tokentype = PLUS;
			tokenvalue << "+";
		}
		break;

	case '-':
		nextChar = look();
		if (nextChar == '-') {
			eat();
			tokentype = MINUSMINUS;
			tokenvalue << "--";
		} else if (isdigit(nextChar)) {
			tokenvalue << "-";
			goto start;
		} else {
			tokentype = MINUS;
			tokenvalue << "-";
		}
		break;

	case '*':
		tokentype = ASTERIX;
		tokenvalue << "*";
		break;

	case '/':
		tokentype = DIVIDE;
		tokenvalue << "/";
		break;

	case '=':
		tokentype = EQUALS;
		tokenvalue << "=";
		break;

	case '<':
		tokentype = LESSTHAN;
		tokenvalue << "<";
		nextChar = look();
		if (nextChar == '=') {
			tokenvalue << '=';
			tokentype = LESSOREQUALTHAN;
			eat();
		} else if (nextChar == '<') {
			tokenvalue << "<";
			tokentype = BITSHIFTLEFT;
			eat();
		} else if (nextChar == '?') {
			tokenvalue << '?';
			currentChar = eat();
			Token *scriptType = getNextToken();
			if (strcmp(scriptType->getContent(), "html") == 0) {
				tokentype = HTML;
			} else {
				cout << "Script type " << scriptType->getContent()
						<< " is not supported" << endl;
				exit(0);
			}
			this->pushBackToken();
			while (1) {
				currentChar = eat();
				if (currentChar == '?') {
					nextChar = look();
					if (nextChar == '>') {
						eat();
						break;
					}
				}
				tokenvalue << currentChar;
			}

			string temps = tokenvalue.str();
			temps = temps.substr(6, temps.size() - 6);
			tokenvalue.str(temps);
		}
		break;

	case '>':
		tokentype = BIGGERTHAN;
		tokenvalue << ">";
		nextChar = look();
		if (nextChar == '=') {
			tokenvalue << '=';
			tokentype = BIGGEROREQUALTHAN;
			eat();
		} else if (nextChar == '>') {
			tokenvalue << ">";
			tokentype = BITSHIFTRIGHT;
			eat();
		}
		break;

	case '!':
		tokentype = EXCLAMATION;
		tokenvalue << "!";
		nextChar = look();
		if (nextChar == '=') {
			tokenvalue << '=';
			tokentype = NOTEQUALS;
			eat();
		}
		break;

	case '%':
		tokentype = PERCENT;
		tokenvalue << "%";
		break;

	case '$':
		tokentype = DOLLAR;
		tokenvalue << "$";
		break;

	case ';':
		tokentype = SEMICOLON;
		tokenvalue << ";";
		break;

	case '&':
		tokentype = AMPERSAND;
		tokenvalue << "&";
		break;

	case '|':
		tokentype = PIPE;
		tokenvalue << "|";
		break;

	case '~':
		tokentype = TILDE;
		tokenvalue << "~";
		break;

	case '^':
		tokentype = HAT;
		tokenvalue << "^";
		break;

	case 'a':
	case 'A':
	case 'b':
	case 'B':
	case 'c':
	case 'C':
	case 'd':
	case 'D':
	case 'e':
	case 'E':
	case 'f':
	case 'F':
	case 'g':
	case 'G':
	case 'h':
	case 'H':
	case 'i':
	case 'I':
	case 'j':
	case 'J':
	case 'k':
	case 'K':
	case 'l':
	case 'L':
	case 'm':
	case 'M':
	case 'n':
	case 'N':
	case 'o':
	case 'O':
	case 'p':
	case 'P':
	case 'r':
	case 'R':
	case 's':
	case 'S':
	case 't':
	case 'T':
	case 'u':
	case 'U':
	case 'v':
	case 'V':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z':
	case 'q':
	case 'Q':
	case 'w':
	case 'W':
	case 'x':
	case 'X':
		tokentype = IDENTIFIER;
		tokenvalue << currentChar;
		currentChar = look();
		while (isdigit(currentChar) || isalnum(currentChar)
				|| currentChar == '_') {
			currentChar = eat();
			tokenvalue << currentChar;
			currentChar = look();
		}
		break;

	case '"':
		tokentype = STRING;
		currentChar = look();
		if (currentChar == '"') { /*Empty String*/
			eat();
			return (new Token("", tokentype));
		}
		while (currentChar != '"') {
			currentChar = eat();
			if (currentChar == '\\') { /* Escape Character */
				char nextone = look();
				if (nextone == 'n') {
					tokenvalue << endl;
				} else if (nextone == '"') {
					tokenvalue << "\"";
				}
				eat();
			} else {
				tokenvalue << currentChar;
			}
			currentChar = look();
		}
		eat();
		break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		tokentype = INTEGER;
		tokenvalue << currentChar;
		currentChar = look();
		while (isdigit(currentChar) || currentChar == '.' || currentChar == 'E'
				|| currentChar == 'x'
				|| (currentChar >= 'a' && currentChar <= 'f')) {
			currentChar = eat();
			tokenvalue << currentChar;
			if (currentChar == '.') {
				tokentype = FLOAT;
			}
			currentChar = look();
		}
		break;
	default:
		break;
	}

	if (tokenvalue.str().length() == 0) {
		cout << "Unknown token: " << currentChar << " at line "
				<< this->currentLine << endl;
		exit(0);
	}

	return (new Token(tokenvalue.str().c_str(), tokentype));
}

} /* namespace fuzuli */
