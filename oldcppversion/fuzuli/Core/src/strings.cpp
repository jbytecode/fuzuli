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
#include <algorithm>
#include <openssl/md5.h>

using namespace std;
using namespace fuzuli;


extern "C" {
FuzuliVariable ltrim(FuzuliVariable params, Environment *env);
FuzuliVariable rtrim(FuzuliVariable params, Environment *env);
FuzuliVariable strcatd(FuzuliVariable params, Environment *env);
FuzuliVariable lcase(FuzuliVariable params, Environment *env);
FuzuliVariable ucase(FuzuliVariable params, Environment *env);
FuzuliVariable left(FuzuliVariable params, Environment *env);
FuzuliVariable right(FuzuliVariable params, Environment *env);
FuzuliVariable strlend(FuzuliVariable params, Environment *env);
FuzuliVariable substrd(FuzuliVariable params, Environment *env);
FuzuliVariable strreverse(FuzuliVariable params, Environment *env);
FuzuliVariable instr(FuzuliVariable params, Environment *env);
FuzuliVariable chr(FuzuliVariable params, Environment *env);
FuzuliVariable ord(FuzuliVariable params, Environment *env);
FuzuliVariable md5(FuzuliVariable params, Environment *env);
FuzuliVariable urldecode(FuzuliVariable params, Environment *env);
FuzuliVariable levenshtein(FuzuliVariable params, Environment *env);
FuzuliVariable str_replace(FuzuliVariable params, Environment *env);
FuzuliVariable str_shuffle(FuzuliVariable params, Environment *env);
FuzuliVariable isdigitd(FuzuliVariable params, Environment *env);
FuzuliVariable isalphad(FuzuliVariable params, Environment *env);
FuzuliVariable isalnumd(FuzuliVariable params, Environment *env);
FuzuliVariable islowerd(FuzuliVariable params, Environment *env);
FuzuliVariable isupperd(FuzuliVariable params, Environment *env);
FuzuliVariable iscntrld(FuzuliVariable params, Environment *env);
FuzuliVariable isgraphd(FuzuliVariable params, Environment *env);
FuzuliVariable isprintd(FuzuliVariable params, Environment *env);
FuzuliVariable ispunctd(FuzuliVariable params, Environment *env);
FuzuliVariable isspaced(FuzuliVariable params, Environment *env);
}


int min3(int p1, int p2, int p3) {
	int m = (int) (fmin(fmin(p1, p2), p3));
	return (m);
}

OneParameters
FuzuliVariable isspaced(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	int int_result = std::isspace((int) vect->at(0).s [0]);
	if (int_result != 0) {
		int_result = 1;
	}
	return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable ispunctd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::ispunct((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isprintd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isprint((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isgraphd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isgraph((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable iscntrld(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::iscntrl((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable islowerd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::islower((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isupperd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isupper((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isalnumd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isalnum((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isalphad(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isalpha((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable isdigitd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
		int int_result = std::isdigit((int) vect->at(0).s [0]);
		if (int_result != 0) {
			int_result = 1;
		}
		return Expression::createNewInt(int_result);
}

OneParameters
FuzuliVariable str_shuffle(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	string str = string(vect->at(0).s);
	for (unsigned int i = 0; i < str.length(); i++) {
		int index1 = rand() % str.length();
		int index2 = rand() % str.length();
		char c = str[index1];
		str[index1] = str[index2];
		str[index2] = c;
	}
	return Expression::createNewString(str.c_str());
}

ThreeParameters
FuzuliVariable str_replace(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	FuzuliVariable mainstr = vect->at(0);
	FuzuliVariable find = vect->at(1);
	FuzuliVariable to = vect->at(2);
	string s_mainstr = string(mainstr.s);
	string s_find = string(find.s);
	string s_to = string(to.s);
	stringstream ss;
	for (unsigned int i = 0; i < s_mainstr.length(); i++) {
		string part = s_mainstr.substr(i, s_find.length());
		if (part == s_find) {
			ss << s_to;
			i += s_find.length() - 1;
		} else {
			ss << s_mainstr.substr(i, 1);
		}
	}
	return Expression::createNewString(ss.str().c_str());
}

TwoParameters
FuzuliVariable levenshtein(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *str1 = vect->at(0).s;
	const char *str2 = vect->at(1).s;
	const int m = strlen(str1);
	const int n = strlen(str2);
	int **d = new int*[m];
	for (int i = 0; i < m; i++) {
		d[i] = new int[n];
	}

	for (int i = 0; i < m; i++) {
		d[i][0] = i;
	}
	for (int j = 0; j < n; j++) {
		d[0][j] = j;
	}
	for (int j = 1; j < n; j++) {
		for (int i = 1; i < m; i++) {
			if (str1[i] == str2[j]) {
				d[i][j] = d[(i - 1)][(j - 1)];
			} else {
				d[i][j] = min3(d[(i - 1)][j] + 1, d[i][(j - 1)] + 1,
						d[(i - 1)][(j - 1)] + 1);
			}
		}
	}
	delete[] d;
	return  Expression::createNewInt(d[m - 1][n - 1]);
}

OneParameters
FuzuliVariable urldecode(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *source = vect->at(0).s;
	int len = strlen(vect->at(0).s);
	stringstream ss;
	for (int i = 0; i < len; i++) {
		char c = source[i];
		if (c == '%') {
			unsigned int value = 0;
			stringstream xcode;
			xcode << "0x" << source[i + 1] << source[i + 2];
			sscanf(xcode.str().c_str(), "%x", &value);
			ss << (char) value;
			i += 2;
		} else if (c == '+') {
			ss << " ";
		} else {
			ss << c;
		}
	}
	return Expression::createNewString(ss.str().c_str());
}

OneParameters
FuzuliVariable md5(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *source = vect->at(0).s;
	unsigned char* md5char = MD5((const unsigned char*) source,
			strlen(source), NULL);
	stringstream ss;
	int len = strlen((const char*) md5char);
	for (int i = 0; i < len; i++) {
		int num = (unsigned int) md5char[i];
		if (num < 10) {
			ss << std::hex << "0" << num;
		} else {
			ss << std::hex << num;
		}
	}
	return Expression::createNewString(ss.str().c_str());
}

OneParameters
FuzuliVariable ord(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	char c = vect->at(0).s[0];
	stringstream ss;
	ss << (unsigned int) c;
	return Expression::createNewString(ss.str().c_str());
}

OneParameters
FuzuliVariable chr(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	int value = Expression::getIntValue(vect->at(0));
	stringstream ss;
	ss << (char) value;
	return Expression::createNewString(ss.str().c_str());
}

TwoParameters
FuzuliVariable instr(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	string first = string(vect->at(0).s);
	string second = string(vect->at(1).s);
	int pos = first.find(second);
	return Expression::createNewInt(pos);
}

OneParameters
FuzuliVariable strreverse(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	string s = string(vect->at(0).s);
	std::reverse(s.begin(), s.end());
	return Expression::createNewString(s.c_str());
}

ThreeParameters
FuzuliVariable substrd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	FuzuliVariable param = vect->at(0);
	FuzuliVariable start = vect->at(1);
	FuzuliVariable stop = vect->at(2);
	int _start = Expression::getIntValue(start);
	int _stop = Expression::getIntValue(stop);
	string s = string(param.s);
	return( Expression::createNewString (s.substr(_start, (_stop) - (_start)).c_str()));
}

OneParameters
FuzuliVariable strlend(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	return Expression::createNewInt(strlen(vect->at(0).s));
}

TwoParameters
FuzuliVariable right(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	FuzuliVariable str = vect->at(0);
	FuzuliVariable n = vect->at(1);
	string s = string(str.s);
	string s1 = s.substr(strlen(str.s) - Expression::getIntValue(n),
			Expression::getIntValue(n));
	return Expression::createNewString(s1.c_str());
}

TwoParameters
FuzuliVariable left(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	FuzuliVariable str = vect->at(0);
	FuzuliVariable n = vect->at(1);

    string s = string(str.s).substr(0, Expression::getIntValue(n));
	FuzuliVariable result = Expression::createNewString(s.c_str());
	return(result);
}

OneParameters
FuzuliVariable ucase(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *content = vect->at(0).s;
	unsigned int len = strlen(content);
	char *newcontent = (char*) malloc(len * sizeof(char));
	for (unsigned int i = 0; i < len; i++) {
		newcontent[i] = toupper(content[i]);
	}
	newcontent[len] = '\0';
	return Expression::createNewString(newcontent);
}

OneParameters
FuzuliVariable lcase(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *content = vect->at(0).s;
	unsigned int len = strlen(content);
	char *newcontent = (char*) malloc(len * sizeof(char));
	for (unsigned int i = 0; i < len; i++) {
		newcontent[i] = tolower(content[i]);
	}
	newcontent[len] = '\0';
	return Expression::createNewString(newcontent);
}

OneParameters
FuzuliVariable strcatd(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *allparams = (vector<FuzuliVariable>*) params.v;
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*)allparams->at(0).v;
	stringstream ss;
	for (unsigned int i = 0; i < vect->size(); i++) {
		ss << vect->at(i).s;
	}
	return Expression::createNewString(ss.str().c_str());
}

OneParameters
FuzuliVariable ltrim(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *content = vect->at(0).s;
	char *pointer = (char*) content;
	unsigned int index = 0;
	while (isspace(*pointer)) {
		if (*pointer == '\0') {
			break;
		}
		pointer++;
		index++;
	}
	string s = string(content);
	return Expression::createNewString(s.substr(index, s.size() - index).c_str());
}

OneParameters
FuzuliVariable rtrim(FuzuliVariable params, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) params.v;
	const char *content = vect->at(0).s;
	char *pointer = (char*) content;
	pointer += strlen(content) - 1;
	unsigned int index = strlen(content);
	while (isspace(*pointer)) {
		if (*pointer == '\0') {
			break;
		}
		pointer--;
		index--;
	}
	string s = string(content);
	return Expression::createNewString(s.substr(0, index).c_str());
}

