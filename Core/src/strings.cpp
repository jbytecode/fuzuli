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
Token *ltrim(Token *p, Environment *env);
Token *rtrim(Token *p, Environment *env);
Token *strcatd(Token *p, Environment *env);
Token *lcase(Token *p, Environment *env);
Token *ucase(Token *p, Environment *env);
Token *left(Token *p, Environment *env);
Token *right(Token *p, Environment *env);
Token *strlend(Token *p, Environment *env);
Token *substrd(Token *p, Environment *env);
Token *strreverse(Token *p, Environment *env);
Token *instr(Token *p, Environment *env);
Token *chr(Token *p, Environment *env);
Token *ord(Token *p, Environment *env);
Token *md5(Token *p, Environment *env);
Token *urldecode(Token *p, Environment *env);
Token *levenshtein(Token *p, Environment *env);
Token *str_replace(Token *p, Environment *env);
Token *str_shuffle(Token *p, Environment *env);
Token *isdigitd(Token *p, Environment *env);
Token *isalphad(Token *p, Environment *env);
Token *isalnumd(Token *p, Environment *env);
Token *islowerd(Token *p, Environment *env);
Token *isupperd(Token *p, Environment *env);
Token *iscntrld(Token *p, Environment *env);
Token *isgraphd(Token *p, Environment *env);
Token *isprintd(Token *p, Environment *env);
Token *ispunctd(Token *p, Environment *env);
Token *isspaced(Token *p, Environment *env);
}

int min3(int p1, int p2, int p3) {
	int m = (int) (fmin(fmin(p1, p2), p3));
	return (m);
}

OneParameters
Token *isspaced(Token *p, Environment *env) {
	int int_result = std::isspace((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}


OneParameters
Token *ispunctd(Token *p, Environment *env) {
	int int_result = std::ispunct((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *isprintd(Token *p, Environment *env) {
	int int_result = std::isprint((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}


OneParameters
Token *isgraphd(Token *p, Environment *env) {
	int int_result = std::isgraph((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *iscntrld(Token *p, Environment *env) {
	int int_result = std::iscntrl((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *islowerd(Token *p, Environment *env) {
	int int_result = std::islower((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *isupperd(Token *p, Environment *env) {
	int int_result = std::isupper((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *isalnumd(Token *p, Environment *env) {
	int int_result = std::isalnum((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *isalphad(Token *p, Environment *env) {
	int int_result = std::isalpha((int) p->tokens[0]->getContent()[0]);
	if (int_result != 0) {
		int_result = 1;
	}
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *isdigitd(Token *p, Environment *env) {
	int int_result = std::isdigit((int) p->tokens[0]->getContent()[0]);
	Token *result = env->newToken(int_result, INTEGER);
	return (result);
}

OneParameters
Token *str_shuffle(Token *p, Environment *env) {
	string str = string(p->tokens[0]->getContent());
	for (unsigned int i = 0; i < str.length(); i++) {
		int index1 = rand() % str.length();
		int index2 = rand() % str.length();
		char c = str[index1];
		str[index1] = str[index2];
		str[index2] = c;
	}
	Token *result = env->newToken(str.c_str(), STRING);
	return (result);
}

ThreeParameters
Token *str_replace(Token *p, Environment *env) {
	Token *mainstr = p->tokens[0];
	Token *find = p->tokens[1];
	Token *to = p->tokens[2];
	string s_mainstr = string(mainstr->getContent());
	string s_find = string(find->getContent());
	string s_to = string(to->getContent());
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
	Token *result = env->newToken(ss.str().c_str(), STRING);
	return (result);
}

TwoParameters
Token *levenshtein(Token *p, Environment *env) {
	const char *str1 = p->tokens[0]->getContent();
	const char *str2 = p->tokens[1]->getContent();
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
	Token *result = env->newToken(d[m - 1][n - 1], INTEGER);
	delete[] d;
	return (result);
}

OneParameters
Token *urldecode(Token *p, Environment *env) {
	const char *source = p->tokens[0]->getContent();
	int len = strlen(source);
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
	Token *result = env->newToken(ss.str().c_str(), STRING);
	return (result);
}


OneParameters
Token *md5(Token *p, Environment *env) {
	const char *source = p->tokens[0]->getContent();
	unsigned char* md5char = MD5((const unsigned char*) source,
			strlen(p->tokens[0]->getContent()), NULL);
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
	Token *result = env->newToken(ss.str().c_str(), STRING);
	return (result);
}

OneParameters
Token *ord(Token *p, Environment *env) {
	char c = p->tokens[0]->getContent()[0];
	stringstream ss;
	ss << (unsigned int) c;
	Token *result = env->newToken(ss.str().c_str(), STRING);
	return (result);
}

OneParameters
Token *chr(Token *p, Environment *env) {
	int value = p->tokens[0]->getIntValue();
	stringstream ss;
	ss << (char) value;
	Token *result = env->newToken(ss.str().c_str(), STRING);
	return (result);
}

TwoParameters
Token *instr(Token *p, Environment *env) {
	string first = string(p->tokens[0]->getContent());
	string second = string(p->tokens[1]->getContent());
	int pos = first.find(second);
	stringstream ss;
	ss << pos;
	Token *result = env->newToken(ss.str().c_str(), INTEGER);
	return (result);
}

OneParameters
Token *strreverse(Token *p, Environment *env) {
	string s = string(p->tokens[0]->getContent());
	std::reverse(s.begin(), s.end());
	Token *result = env->newToken(s.c_str(), STRING);
	return (result);
}

ThreeParameters
Token *substrd(Token *p, Environment *env) {
	Token *result = env->newToken("", STRING);
	Token *param = p->tokens[0];
	Token *start = p->tokens[1];
	Token *stop = p->tokens[2];
	int _start = start->getIntValue();
	int _stop = stop->getIntValue();
	string s = string(param->getContent());
	result->setContent(s.substr(_start, (_stop) - (_start)).c_str());
	return (result);
}

OneParameters
Token *strlend(Token *p, Environment *env) {
	Token *str = p->tokens[0];
	Token *result = env->newToken(strlen(str->getContent()), INTEGER);
	return (result);
}

TwoParameters
Token *right(Token *p, Environment *env) {
	Token *str = p->tokens[0];
	Token *n = p->tokens[1];
	Token *result = env->newToken("", STRING);
	string s = string(str->getContent());
	string s1 = s.substr(strlen(str->getContent()) - n->getIntValue(),
			n->getIntValue());
	result->setContent(s1.c_str());
	return (result);
}

TwoParameters
Token *left(Token *p, Environment *env) {
	Token *str = p->tokens[0];
	Token *n = p->tokens[1];
	Token *result = env->newToken("  ", STRING);
	result->setContent(
			string(str->getContent()).substr(0, n->getIntValue()).c_str());
	return (result);
}

OneParameters
Token *ucase(Token *p, Environment *env) {
	const char *content = p->tokens[0]->getContent();
	char *newcontent = (char*) malloc(strlen(content) * sizeof(char));
	Token *result = env->newToken(content, STRING);
	for (unsigned int i = 0; i < strlen(content); i++) {
		newcontent[i] = toupper(content[i]);
	}
	result->setContent((const char*) newcontent);
	return (result);
}

OneParameters
Token *lcase(Token *p, Environment *env) {
	const char *content = p->tokens[0]->getContent();
	char *newcontent = (char*) malloc(strlen(content) * sizeof(char));
	Token *result = env->newToken(content, STRING);
	for (unsigned int i = 0; i < strlen(content); i++) {
		newcontent[i] = tolower(content[i]);
	}
	result->setContent((const char*) newcontent);
	return (result);
}

MoreThanThreeParameters
Token *strcatd(Token *p, Environment *env) {
	Token *result = env->newToken("", STRING);
	stringstream ss;
	for (unsigned int i = 0; i < p->tokens[0]->tokens.size(); i++) {
		ss << p->tokens[0]->tokens[i]->getContent();
	}
	result->setContent(ss.str().c_str());
	return (result);
}

OneParameters
Token *ltrim(Token *p, Environment *env) {
	Token *result = env->newToken("", STRING);
	const char *content = p->tokens[0]->getContent();
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
	result->setContent(s.substr(index, s.size() - index).c_str());
	return (result);
}

OneParameters
Token *rtrim(Token *p, Environment *env) {
	Token *result = env->newToken("", STRING);
	const char *content = p->tokens[0]->getContent();
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
	result->setContent(s.substr(0, index).c_str());
	return (result);
}

