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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;
using namespace fuzuli;


void __readToken(FILE *file, Token *tok);
void __writeToken(FILE *file, Token *tok);
void __readLine(FILE *file, Token *tok);
FILE *__determine_File(const char *name, const char *mode);

extern "C" {
Token *dir(Token* path, Environment *env);
Token *getpwd(Token* p, Environment *env);
Token *chdird(Token* p, Environment *env);
Token *unlinkd(Token* p, Environment *env);
Token *renamed(Token* p, Environment *env);
Token *tmpfiled(Token* p, Environment *env);
Token *tmpnamd(Token* p, Environment *env);
Token *datetime(Token* p, Environment *env);
Token *asctimed(Token* p, Environment *env);
Token *sleepd(Token* p, Environment *env);
Token *getenvd(Token* p, Environment *env);
Token *rnd(Token *p, Environment *env);
Token *fopend(Token* p, Environment *env);
Token *fclosed(Token *p, Environment *env);
Token *fwrited(Token *p, Environment *env);
Token *freadd(Token *p, Environment *env);
Token *feofd(Token *p, Environment *env);
Token *fflushd(Token *p, Environment *env);
Token *print_r(Token *p, Environment *env);
Token *popend(Token *p, Environment *env);
Token *pclosed(Token *p, Environment *env);
Token *exitd(Token *p, Environment *env);
Token *is_dir (Token *p, Environment *env);
Token *timed (Token *p, Environment *env);
Token *randomize(Token *p, Environment *env);
Token *putsd(Token *p, Environment *env);
Token *fputsd(Token *p, Environment *env);
Token *fgetcd(Token *p, Environment *env);
Token *ftelld(Token *p, Environment *env);
}

OneParameters
Token *ftelld(Token *p, Environment *env){
	FILE *file = (FILE*)p->tokens[0]->object;
	long int lint_result = ftell(file);
	stringstream ss; ss << ((double) lint_result);
	Token *result = new Token(ss.str().c_str(), FLOAT);
	return(result);
}

TwoParameters
Token *fgetcd(Token *p, Environment *env){
	FILE *file = (FILE*)p->tokens[0]->object;
	int int_result = fgetc(file);
	stringstream ss; ss<< ( (char) int_result);
	Token *result = new Token(ss.str().c_str(), STRING);
	return(result);
}

TwoParameters
Token *fputsd(Token *p, Environment *env){
	FILE *f = (FILE*) (p->tokens[0]->object);
	Token *par = p->tokens[1];
	fputs(par->getContent(), f);
	return(Token::NULL_TOKEN);
}

OneParameters
Token *putsd(Token *p, Environment *env){
	puts(p->tokens[0]->getContent());
	return(Token::NULL_TOKEN);
}

OneParameters
Token *randomize(Token *p, Environment *env){
	srand((unsigned int) p->tokens[0]->getFloatValue());
	return(Token::NULL_TOKEN);
}


NoParameters
Token *timed (Token *p, Environment *env){
	Token *result = new Token(((double)time(NULL)) * 1.0, FLOAT);
	return(result);
}

OneParameters
Token *is_dir (Token *p, Environment *env){
	struct stat st;
	int code = stat(p->tokens[0]->getContent(), &st);
	if(code == -1){
		cout << "Can not define whether "<<p->tokens[0]->getContent()<<" is dir"<<endl;
	}
	int int_result = 0;
	if(S_ISDIR(st.st_mode)){
		int_result = 1;
	}
	Token *result = new Token (int_result, INTEGER);
	return(result);
}


OneParameters
Token *pclosed(Token *p, Environment *env){
	Token *pclose_result = new Token(-1, INTEGER);
	FILE *process = (FILE*)p->tokens[0]->object;
	int res = pclose(process);
	pclose_result->setIntValue(res);
	return(pclose_result);
}

TwoParameters
Token *popend(Token *p, Environment *env) {
	Token *processname = p->tokens[0];
	Token *mode = p->tokens[1];
	Token *newfile = new Token("@FuzuliProcess", COBJECT);
	FILE *file = popen(processname->getContent(), mode->getContent());
	if (!file) {
		cout << "Cannot open process " << processname->getContent() << endl;
		exit(-2);
	}
	newfile->object = (void*) file;
	return (newfile);

}

OneParameters
Token *print_r(Token *p, Environment *env) {
	Token *param = p->tokens[0];
	for (unsigned int i = 0; i < param->tokens.size(); i++) {
		cout << param->tokens[i]->getContent();
		if (i < param->tokens.size() - 1) {
			cout << ", ";
		}
	}
	cout << "\n";
	return (p);
}

OneParameters
Token *fflushd(Token *p, Environment *env) {
	Token *flush_result = new Token(-1, INTEGER);
	FILE *file = (FILE*) p->tokens[0]->object;
	flush_result->setIntValue(fflush(file));
	return (flush_result);
}

OneParameters
Token* fclosed(Token* p, Environment *env) {
	FILE* file = (FILE*) p->tokens[0]->object;
	fclose(file);
	return (p);
}

FILE *__determine_File(const char *name, const char* mode) {
	FILE *file;
	if (strcmp(name, "stdout") == 0) {
		file = stdout;
	} else if (strcmp(name, "stdin") == 0) {
		file = stdin;
	} else if (strcmp(name, "stderr") == 0) {
		file = stderr;
	} else {
		file = fopen(name, mode);
	}
	return (file);
}

TwoParameters
Token *fopend(Token*p, Environment *env) {
	Token *filename = p->tokens[0];
	Token *mode = p->tokens[1];
	Token *newfile = new Token("@FuzuliFile", COBJECT);
	FILE *file = __determine_File(filename->getContent(), mode->getContent());

	if (!file) {
		cout << "Cannot open file " << filename->getContent() << endl;
		exit(-2);
	}

	newfile->object = (void*) file;
	return (newfile);
}

TwoParameters
Token *freadd(Token* p, Environment *env) {
	FILE *file = (FILE*) p->tokens[0]->object;
	__readToken(file, p->tokens[1]);
	return (p->tokens[1]);
}

TwoParameters
Token *fwrited(Token *p, Environment *env) {
	FILE *file = (FILE*) p->tokens[0]->object;
	__writeToken(file, p->tokens[1]);
	return (p->tokens[1]);
}

OneParameters
Token *feofd(Token *p, Environment *env) {
	Token *feofd_return = new Token(0.0, INTEGER);
	FILE *file = (FILE*) p->tokens[0]->object;
	feofd_return->setIntValue(feof(file));
	return (feofd_return);
}

void __readToken(FILE *file, Token *tok) {
	size_t dummy_return = 0;
	if (tok->getType() == INTEGER) {
		int val;
		dummy_return = fread(&val, sizeof(int), 1, file);
		tok->setIntValue(val);
	} else if (tok->getType() == FLOAT) {
		double val;
		dummy_return = fread(&val, sizeof(double), 1, file);
		tok->setFloatValue(val);
		tok->setType(FLOAT);
	} else if (tok->getType() == STRING) {
		char c[2];
		dummy_return = fread(&c, sizeof(char), 1, file);
		c[1] = '\0';
		tok->setContent((const char*) &c);
	} else if (tok->getType() == LIST) {
		for (unsigned int i = 0; i < tok->tokens.size(); i++) {
			Token *listelement = tok->tokens[i];
			__readToken(file, listelement);
		}
	}
}

void __readLine(FILE *file, Token *tok) {
	stringstream ss;
	char c;
	size_t dummy_return = 0;
	while (1) {
		dummy_return = fread(&c, 1, 1, file);
		if (c == 13 || c == 10) {
			break;
		}
		ss << c;
	}
	tok->setContent(ss.str().c_str());
}

void __writeToken(FILE *file, Token *tok) {
	if (tok->getType() == INTEGER) {
		int val = tok->getIntValue();
		fwrite(&val, sizeof(int), 1, file);
	} else if (tok->getType() == FLOAT) {
		double val = tok->getFloatValue();
		fwrite(&val, sizeof(double), 1, file);
	} else if (tok->getType() == STRING) {
		fwrite(tok->getContent(), strlen(tok->getContent()), 1, file);
	} else if (tok->getType() == LIST) {
		for (unsigned int i = 0; i < tok->tokens.size(); i++) {
			__writeToken(file, tok->tokens[i]);
		}
	}
}

OneParameters
Token *chdird(Token *p, Environment *env) {
	int ret = chdir(p->tokens[0]->getContent());
	Token * result = new Token(ret,INTEGER);
	return (result);
}

NoParameters
Token *getpwd(Token* p, Environment *env) {
	char *ppath = NULL;
	int len = 0;
	ppath = getcwd(ppath, len);
	Token *result = new Token (ppath, STRING);
	return (result);
}

OneParameters
Token *dir(Token* path, Environment *env) {
	Token *result = new Token("@FuzuliList", LIST);
	DIR *dr;
	struct dirent *dt;
	dr = opendir(path->tokens[0]->getContent());
	if (dr != NULL) {
		while ((dt = readdir(dr))) {
			result->tokens.push_back(new Token(dt->d_name, STRING));
		}
	} else {
		cout << "Can not list directory " << path->getContent() << endl;
	}
	(void) closedir(dr);
	return (result);
}

OneParameters
Token *unlinkd(Token *file, Environment *env) {
	int res = unlink(file->tokens[0]->getContent());
	Token *result = new Token(res, INTEGER);
	return (result);
}

TwoParameters
Token *renamed(Token *files, Environment *env) {
	int res = rename(files->tokens[0]->getContent(),
			files->tokens[1]->getContent());
	Token *result = new Token(res, INTEGER);
	return (result);
}

NoParameters
Token *tmpfiled(Token* p, Environment *env) {
	Token *tok = new Token("@FuzuliNativeObject", COBJECT);
	tok->tokens[0]->object = tmpfile();
	return (tok);
}

NoParameters
Token *tmpnamed(Token* p, Environment *env) {
	Token *result = new Token(tmpnam(NULL), STRING);
	return (result);
}

NoParameters
Token *datetime(Token* p, Environment *env) {
	Token *returnToken = new Token("@ListToken", LIST);
	time_t aTime;
	time(&aTime);
	tm *pTime = gmtime(&aTime);
	returnToken->tokens.push_back(new Token(pTime->tm_year, INTEGER));
	returnToken->tokens.push_back(new Token(pTime->tm_mon, INTEGER));
	returnToken->tokens.push_back(new Token(pTime->tm_mday, INTEGER));
	returnToken->tokens.push_back(new Token(pTime->tm_hour, INTEGER));
	returnToken->tokens.push_back(new Token(pTime->tm_min, INTEGER));
	returnToken->tokens.push_back(new Token(pTime->tm_sec, INTEGER));
	return (returnToken);
}

NoParameters
Token *asctimed(Token *p, Environment *env) {
	Token *result = new Token("", STRING);
	time_t aTime;
	time(&aTime);
	tm *pTime = gmtime(&aTime);
	result->setContent(asctime(pTime));
	result->setType(STRING);
	return (result);
}

OneParameters
Token *sleepd(Token *p, Environment *env) {
	int res = usleep(p->tokens[0]->getIntValue());
	Token *result = new Token(res, INTEGER);
	return (result);
}

OneParameters
Token *getenvd(Token *p, Environment *env) {
	Token *result = new Token(getenv(p->tokens[0]->getContent()), STRING);
	return (result);
}

NoParameters
Token *rnd(Token *p, Environment *env) {
	Token *result = new Token(((double) rand()) / RAND_MAX, FLOAT);
	return (result);
}

OneParameters
Token *exitd(Token *p, Environment *env){
	exit(p->tokens[0]->getIntValue());
}
