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

void __readToken(FILE *file, FuzuliVariable &tok);
void __writeToken(FILE *file, FuzuliVariable &tok);
void __readLine(FILE *file, FuzuliVariable &tok);
FILE *__determine_File(const char *name, const char *mode);

extern "C" {
FuzuliVariable dir(FuzuliVariable p, Environment *env);
FuzuliVariable getpwd(FuzuliVariable p, Environment *env);
FuzuliVariable chdird(FuzuliVariable p, Environment *env);
FuzuliVariable unlinkd(FuzuliVariable p, Environment *env);
FuzuliVariable renamed(FuzuliVariable p, Environment *env);
FuzuliVariable tmpfiled(FuzuliVariable p, Environment *env);
FuzuliVariable tmpnamed(FuzuliVariable p, Environment *env);
FuzuliVariable datetime(FuzuliVariable p, Environment *env);
FuzuliVariable asctimed(FuzuliVariable p, Environment *env);
FuzuliVariable sleepd(FuzuliVariable p, Environment *env);
FuzuliVariable getenvd(FuzuliVariable p, Environment *env);
FuzuliVariable setenvd(FuzuliVariable p, Environment *env);
FuzuliVariable rnd(FuzuliVariable p, Environment *env);
FuzuliVariable fopend(FuzuliVariable p, Environment *env);
FuzuliVariable fclosed(FuzuliVariable p, Environment *env);
FuzuliVariable fwrited(FuzuliVariable p, Environment *env);
FuzuliVariable freadd(FuzuliVariable p, Environment *env);
FuzuliVariable feofd(FuzuliVariable p, Environment *env);
FuzuliVariable fflushd(FuzuliVariable p, Environment *env);
FuzuliVariable popend(FuzuliVariable p, Environment *env);
FuzuliVariable pclosed(FuzuliVariable p, Environment *env);
FuzuliVariable exitd(FuzuliVariable p, Environment *env);
FuzuliVariable is_dir(FuzuliVariable p, Environment *env);
FuzuliVariable timed(FuzuliVariable p, Environment *env);
FuzuliVariable randomize(FuzuliVariable p, Environment *env);
FuzuliVariable putsd(FuzuliVariable p, Environment *env);
FuzuliVariable fputsd(FuzuliVariable p, Environment *env);
FuzuliVariable fgetcd(FuzuliVariable p, Environment *env);
FuzuliVariable ftelld(FuzuliVariable p, Environment *env);
FuzuliVariable readlined(FuzuliVariable p, Environment *env);
}

NoParameters
FuzuliVariable readlined(FuzuliVariable p, Environment *env) {
	string str;
	std::getline(cin, str);
	FuzuliVariable result = Expression::createNewString(str.c_str());
	return (result);
}

OneParameters
FuzuliVariable ftelld(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE *file = (FILE*) vect->at(0).v;
	long int lint_result = ftell(file);
	stringstream ss;
	ss << ((double) lint_result);
	FuzuliVariable result = Expression::createNewString(ss.str().c_str());
	return (result);
}

TwoParameters
FuzuliVariable fgetcd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE *file = (FILE*) vect->at(0).v;
	int int_result = fgetc(file);
	stringstream ss;
	ss << ((char) int_result);
	FuzuliVariable result = Expression::createNewString(ss.str().c_str());
	return (result);
}

TwoParameters
FuzuliVariable fputsd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE *f = (FILE*) vect->at(0).v;
	FuzuliVariable par = vect->at(1);
	fputs(par.s, f);
	return (par);
}

OneParameters
FuzuliVariable putsd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable par = vect->at(0);
	puts(par.s);
	return (par);
}

OneParameters
FuzuliVariable randomize(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable par = vect->at(0);
	srand((unsigned int) Expression::getDoubleValue(vect->at(0)));
	return (par);
}

NoParameters
FuzuliVariable timed(FuzuliVariable p, Environment *env) {
	FuzuliVariable result = Expression::createNewDouble(
			((double) time(NULL)) * 1.0);
	return (result);
}

OneParameters
FuzuliVariable is_dir(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable dirname = vect->at(0);
	struct stat st;
	int code = stat(dirname.s, &st);
	if (code == -1) {
		cout << "Can not define whether " << dirname.s << " is dir" << endl;
	}
	int int_result = 0;
	if (S_ISDIR(st.st_mode)) {
		int_result = 1;
	}
	FuzuliVariable result = Expression::createNewInt(int_result);
	return (result);
}

OneParameters
FuzuliVariable pclosed(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable pclose_result = Expression::createNewInt(-1);
	FuzuliVariable pcode = vect->at(0);
	FILE *process = (FILE*) pcode.v;
	int res = pclose(process);
	pclose_result.i = res;
	return (pclose_result);
}

TwoParameters
FuzuliVariable popend(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable processname = vect->at(0);
	FuzuliVariable mode = vect->at(1);
	FuzuliVariable newfile = Expression::createNewCObject(NULL);
	FILE *file = popen(processname.s, mode.s);
	if (!file) {
		cout << "Cannot open process " << processname.s << endl;
		exit(-2);
	}
	newfile.v = (void*) file;
	return (newfile);

}

OneParameters
FuzuliVariable fflushd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable flush_result = Expression::createNewInt(-1);
	FILE *file = (FILE*) vect->at(0).v;
	flush_result.i = fflush(file);
	return (flush_result);
}

OneParameters
FuzuliVariable fclosed(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE* file = (FILE*) vect->at(0).v;
	int res = fclose(file);
	return (Expression::createNewInt(res));
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
FuzuliVariable fopend(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable filename = vect->at(0);
	FuzuliVariable mode = vect->at(1);
	FuzuliVariable newfile = Expression::createNewCObject(NULL);
	FILE *file = __determine_File(filename.s, mode.s);

	if (!file) {
		cout << "Cannot open file " << filename.s << endl;
		exit(-2);
	}
	newfile.v = (void*) file;
	return (newfile);
}

TwoParameters
FuzuliVariable freadd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE *file = (FILE*) vect->at(0).v;
	__readToken(file, vect->at(1));
	return (vect->at(1));
}

TwoParameters
FuzuliVariable fwrited(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FILE *file = (FILE*) vect->at(0).v;
	__writeToken(file, vect->at(1));
	return (vect->at(1));
}

OneParameters
FuzuliVariable feofd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable feofd_return = Expression::createNewInt(0);
	FILE *file = (FILE*) vect->at(0).v;
	feofd_return.i = (feof(file));
	return (feofd_return);
}

void __readToken(FILE *file, FuzuliVariable& tok) {
	size_t dummy_return = 0;
	if (tok.type == INTEGER) {
		int val;
		dummy_return = fread(&val, sizeof(int), 1, file);
		tok.i = val;
	} else if (tok.type == FLOAT) {
		double val;
		dummy_return = fread(&val, sizeof(double), 1, file);
		tok.d = val;
	} else if (tok.type == STRING) {
		char c[strlen(tok.s)];
		c[strlen(tok.s)] = '\0';
		dummy_return = fread(&c, sizeof(char), strlen(tok.s) + 1, file);
		tok = Expression::createNewString(c);
	} else if (tok.type == LIST) {
		vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) tok.v;
		for (unsigned int i = 0; i < vect->size(); i++) {
			FuzuliVariable listelement = vect->at(i);
			__readToken(file, listelement);
		}
	}
	if (dummy_return != 0) {
		//Process return values later if needed
	}
}

void __readLine(FILE *file, FuzuliVariable &tok) {
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
	tok = Expression::createNewString(ss.str().c_str());
	if (dummy_return != 0) {
		//Process return values later if needed
	}
}

void __writeToken(FILE *file, FuzuliVariable &tok) {
	if (tok.type == INTEGER) {
		int val = Expression::getIntValue(tok);
		fwrite(&val, sizeof(int), 1, file);
	} else if (tok.type == FLOAT) {
		double val = Expression::getDoubleValue(tok);
		fwrite(&val, sizeof(double), 1, file);
	} else if (tok.type == STRING) {
		fwrite(tok.s, strlen(tok.s), 1, file);
	} else if (tok.type == LIST) {
		vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) tok.v;
		for (unsigned int i = 0; i < vect->size(); i++) {
			__writeToken(file, vect->at(i));
		}
	}
}

OneParameters
FuzuliVariable chdird(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	int ret = chdir(vect->at(0).s);
	FuzuliVariable result = Expression::createNewInt(ret);
	return (result);
}

NoParameters
FuzuliVariable getpwd(FuzuliVariable p, Environment *env) {
	char *ppath = NULL;
	int len = 0;
	ppath = getcwd(ppath, len);
	FuzuliVariable result = Expression::createNewString(ppath);
	return (result);
}

OneParameters
FuzuliVariable dir(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	FuzuliVariable result = Expression::createNewList();
	vector<FuzuliVariable> *resultvect = (vector<FuzuliVariable>*) result.v;
	DIR *dr;
	struct dirent *dt;
	dr = opendir(vect->at(0).s);
	if (dr != NULL) {
		while ((dt = readdir(dr))) {
			resultvect->push_back(Expression::createNewString(dt->d_name));
		}
	} else {
		cout << "Can not list directory " << vect->at(0).s << endl;
	}
	(void) closedir(dr);
	return (result);
}

OneParameters
FuzuliVariable unlinkd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	int res = unlink(vect->at(0).s);
	FuzuliVariable result = Expression::createNewInt(res);
	return (result);
}

TwoParameters
FuzuliVariable renamed(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	int res = rename(vect->at(0).s, vect->at(1).s);
	FuzuliVariable result = Expression::createNewInt(res);
	return (result);
}

NoParameters
FuzuliVariable tmpfiled(FuzuliVariable p, Environment *env) {
	FuzuliVariable tok = Expression::createNewCObject(NULL);
	tok.v = tmpfile();
	return (tok);
}

NoParameters
FuzuliVariable tmpnamed(FuzuliVariable p, Environment *env) {
	FuzuliVariable result = Expression::createNewCObject(NULL);
	result.v = tmpnam(NULL);
	return (result);
}

NoParameters
FuzuliVariable datetime(FuzuliVariable p, Environment *env) {
	FuzuliVariable returnToken = Expression::createNewList();
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) returnToken.v;
	time_t aTime;
	time(&aTime);
	tm *pTime = gmtime(&aTime);
	vect->push_back(Expression::createNewInt(pTime->tm_year));
	vect->push_back(Expression::createNewInt(pTime->tm_mon));
	vect->push_back(Expression::createNewInt(pTime->tm_mday));
	vect->push_back(Expression::createNewInt(pTime->tm_hour));
	vect->push_back(Expression::createNewInt(pTime->tm_min));
	vect->push_back(Expression::createNewInt(pTime->tm_sec));
	return (returnToken);
}

NoParameters
FuzuliVariable asctimed(FuzuliVariable p, Environment *env) {
	time_t aTime;
	time(&aTime);
	tm *pTime = gmtime(&aTime);
	FuzuliVariable result = Expression::createNewString(asctime(pTime));
	return (result);
}

OneParameters
FuzuliVariable sleepd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	int res = usleep(Expression::getIntValue(vect->at(0)));
	FuzuliVariable result = Expression::createNewInt(res);
	return (result);
}

OneParameters
FuzuliVariable getenvd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	char *envvar = getenv(vect->at(0).s);
	FuzuliVariable result;
	if (envvar == NULL) {
		result = Expression::createNewNull();
	} else {
		result = Expression::createNewString(envvar);
	}
	return (result);
}

OneParameters
FuzuliVariable setenvd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	const char *name = vect->at(0).s;
	const char *value = vect->at(1).s;
	int replace = Expression::getIntValue(vect->at(2));
	int result = setenv(name, value, replace);
	return (Expression::createNewInt(result));
}

NoParameters
FuzuliVariable rnd(FuzuliVariable p, Environment *env) {
	FuzuliVariable result = Expression::createNewDouble(
			((double) rand()) / RAND_MAX);
	return (result);
}

OneParameters
FuzuliVariable exitd(FuzuliVariable p, Environment *env) {
	vector<FuzuliVariable> *vect = (vector<FuzuliVariable>*) p.v;
	exit(Expression::getIntValue(vect->at(0)));
}

