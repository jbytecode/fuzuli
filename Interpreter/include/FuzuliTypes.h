/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012 Mehmet Hakan Satman
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


#ifndef FUZULITYPES_H_
#define FUZULITYPES_H_

#define NoParameters
#define OneParameters
#define TwoParameters
#define ThreeParameters
#define MoreThanThreeParameters
#define FuzuliAPI


#include <vector>
#include <iostream>
#include <map>
#include <list>

namespace fuzuli {

struct FuzuliVariable {
	union {
		double d;
		int i;
		float f;
		char c;
		const char *s;
	};
	struct FuzuliVariable* next;
	int type;
};

enum TokenType {

	IDENTIFIER,

	INTEGER, /* 1 */
	FLOAT,   /* 2 */
	STRING,  /* 3 */
	LIST,    /* 4 */
	NULLTOKEN,

	COMMA,
	DOT,
	LPARENTH,
	RPARENTH,
	LBRACK,
	RBRACK,
	COLON,
	SEMICOLON,
	LSET,
	RSET,

	EQUALS,
	PLUS,
	PLUSPLUS,
	MINUS,
	MINUSMINUS,
	ASTERIX,
	DIVIDE,
	INV_DIVIDE,

	LESSTHAN,/* 23 */
	LESSOREQUALTHAN,/* 24 */
	BIGGERTHAN,/* 25 */
	BIGGEROREQUALTHAN,/* 26 */
	BITSHIFTLEFT,
	BITSHIFTRIGHT,
	TILDE,

	PERCENT,/* 27 */
	DOLLAR,/* 28 */
	SHARP,/* 29 */
	HAT,/* 30 */
	AMPERSAND,/* 31 */
	PIPE,

	QUESTION,
	AT,

	EOP,
	BREAKTOKEN,
	PARAMS,/* 37 */
	FUZULIFUNCTION,/* 38 */
	DLL,/* 39 */
	FILETOKEN,/* 40 */
	PACKAGE, /* 41 */
	HTML, /* 42 */
	COBJECT,
	FUZULIOBJECT,

	EXCLAMATION,
	NOTEQUALS

};


/* CLASSES */


class Token;
class Environment;


using namespace std;


class CppEmitter {
public:
	CppEmitter();
	virtual ~CppEmitter();
	virtual void emitCpp(stringstream *ss);
	static const char *getCppType(TokenType type);
};

class Expression {
public:
	Expression();
	virtual ~Expression();
	void setExpressions(vector<Expression*> expressions);
	virtual Token *eval(Environment *env);
	const char* toString();
	void addExpression(Expression *exp);
	vector<Expression*> expressions;
	Token *resultToken;
private:

};

class CPlusPlusExpression: public Expression {
public:
	CPlusPlusExpression(vector<Expression*> expr);
	virtual ~CPlusPlusExpression();
	Token *eval(Environment *env);
};


class AndExpression: public fuzuli::Expression , public CppEmitter{
public:
	AndExpression(vector<Expression*> expr);
	virtual ~AndExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitShiftLeftExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitShiftLeftExpression(vector<Expression*> expr);
	virtual ~BitShiftLeftExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitShiftRightExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitShiftRightExpression(vector<Expression*> expr);
	virtual ~BitShiftRightExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitAndExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitAndExpression(vector<Expression*> expr);
	virtual ~BitAndExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitOrExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitOrExpression(vector<Expression*> expr);
	virtual ~BitOrExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitNotExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitNotExpression(vector<Expression*> expr);
	virtual ~BitNotExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BitXORExpression: public fuzuli::Expression , public CppEmitter{
public:
	BitXORExpression(vector<Expression*> expr);
	virtual ~BitXORExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};



class AsterixExpression: public Expression , public CppEmitter{
public:
	AsterixExpression(vector<Expression*> expression);
	virtual ~AsterixExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BlockExpression: public Expression, public CppEmitter {
public:
	BlockExpression(vector<Expression*> expr);
	virtual ~BlockExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BreakExpression: public fuzuli::Expression {
public:
	BreakExpression(vector<Expression*> expr);
	virtual ~BreakExpression();
	Token *eval(Environment *env);
};

class DumpExpression: public Expression {
public:
	DumpExpression(vector<Expression*> expr);
	virtual ~DumpExpression();
	Token *eval(Environment *env);
};


class DynLoadExpression: public Expression {
public:
	DynLoadExpression(vector<Expression*> expr);
	virtual ~DynLoadExpression();
	Token *eval(Environment *env);
	void *libraryHandle;
	const char *libraryName;
};

class LessExpression: public Expression, public CppEmitter {
public:
	LessExpression(vector<Expression*> expr);
	virtual ~LessExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class LessOrEqualExpression: public Expression, public CppEmitter {
public:
	LessOrEqualExpression(vector<Expression*> expr);
	virtual ~LessOrEqualExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BiggerExpression: public Expression, public CppEmitter {
public:
	BiggerExpression(vector<Expression*> expr);
	virtual ~BiggerExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class BigOrEqualExpression: public Expression, public CppEmitter {
public:
	BigOrEqualExpression(vector<Expression*> expr);
	virtual ~BigOrEqualExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class CExpression: public Expression {
public:
	CExpression(vector<Expression*> expr);
	virtual ~CExpression();
	Token *eval(Environment *env);
};

class DivisionExpression: public Expression ,public CppEmitter {
public:
	DivisionExpression(vector<Expression*> expr);
	virtual ~DivisionExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class EqualsExpression: public fuzuli::Expression , public CppEmitter{
public:
	EqualsExpression(vector<Expression*> expr);
	virtual ~EqualsExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class NotEqualsExpression: public fuzuli::Expression , public CppEmitter{
public:
	NotEqualsExpression(vector<Expression*> expr);
	virtual ~NotEqualsExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};


class ForExpression: public fuzuli::Expression {
public:
	ForExpression(vector<Expression*> expr);
	virtual ~ForExpression();
	Token *eval(Environment *env);
};


class ForEachExpression : public Expression {
public:
	ForEachExpression(vector<Expression*> expr);
	virtual ~ForEachExpression();
	Token *eval(Environment *env);
};

class DoTimesExpression: public fuzuli::Expression {
public:
	DoTimesExpression(vector<Expression*> expr);
	virtual ~DoTimesExpression();
	Token *eval(Environment *env);
};

class SwitchExpression: public fuzuli::Expression {
public:
	SwitchExpression(vector<Expression*> expr);
	virtual ~SwitchExpression();
	Token *eval(Environment *env);
};

class CaseExpression: public fuzuli::Expression {
public:
	CaseExpression(vector<Expression*> expr);
	virtual ~CaseExpression();
	Token *eval(Environment *env);
};

class FuzuliFunction {
public:
	FuzuliFunction();
	virtual ~FuzuliFunction();
	Expression *name;
	Expression *params;
	Expression *body;
	Environment *environment;
	const char *getStringName();
};

class FunctionExpression: public Expression {
public:
	FunctionExpression(vector<Expression*> expr);
	virtual ~FunctionExpression();
	Token *eval(Environment *env);
	FuzuliFunction *fuzulifunction;
};

class FunctionCallExpression: public Expression {
public:
	FunctionCallExpression(vector<Expression*> expr);
	virtual ~FunctionCallExpression();
	Token *eval(Environment *env);
	Token *evalForClass(Environment *env);
};

class ForkExpression : public Expression {
public:
	ForkExpression(vector<Expression*>expr);
	virtual ~ForkExpression();
	Token *eval(Environment *env);
};

class WaitExpression : public Expression {
public:
	WaitExpression(vector<Expression*>expr);
	virtual ~WaitExpression();
	Token *eval(Environment *env);
};

class RequestExpression : public Expression {
public:
	RequestExpression(vector<Expression*>expr);
	virtual ~RequestExpression();
	Token *eval(Environment *env);
};

class IssetExpression : public Expression {
public:
	IssetExpression(vector<Expression*>expr);
	virtual ~IssetExpression();
	Token *eval(Environment *env);
};


class ParamsExpression: public Expression {
public:
	ParamsExpression(vector<Expression*> expr);
	virtual ~ParamsExpression();
	Token *eval(Environment *env);
	vector<Token*> paramNames;
};

class IdentifierExpression: public Expression , public CppEmitter{
public:
	IdentifierExpression(Token *tok);
	virtual ~IdentifierExpression();
	Token *eval(Environment *env);
	Token *stringToken;
	void emitCpp(stringstream *ss);
};

class IfExpression: public fuzuli::Expression , public CppEmitter{
public:
	IfExpression(vector<Expression*> expr);
	virtual ~IfExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class IntegerExpression: public Expression, public CppEmitter{
public:
	IntegerExpression();
	IntegerExpression(Token *tok);
	virtual ~IntegerExpression();
	Token* eval(Environment *env);
	void emitCpp(stringstream *ss);
	int integerValue;

private:
	Token *token;
};

class FloatExpression: public Expression , public CppEmitter{
public:
	FloatExpression();
	FloatExpression(Token *tok);
	virtual ~FloatExpression();
	Token* eval(Environment *env);
	void emitCpp(stringstream *ss);
	double floatValue;

private:
	Token *token;
};


class DefExpression : public Expression , public CppEmitter {
public:
	DefExpression(vector<Expression*>expr);
	~DefExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class TypeofExpression : public Expression {
public:
	TypeofExpression(vector<Expression*>expr);
	~TypeofExpression();
	Token *eval(Environment *env);
};


class TypeExpression : public Expression {
public:
	TypeExpression(vector<Expression*>expr);
	~TypeExpression();
	Token *eval(Environment *env);
};

class LetExpression: public Expression , public CppEmitter{
public:
	LetExpression(vector<Expression*> expr);
	virtual ~LetExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};


class EvalExpression : public Expression {
public:
	EvalExpression(vector<Expression*>expr);
	virtual ~EvalExpression();
	Token *eval(Environment *env);
};

/* List class */
class ListExpression: public fuzuli::Expression {
public:
	ListExpression(vector<Expression*> expr);
	virtual ~ListExpression();
	Token *eval(Environment *env);
};

/************************/
/* Other List Functions */
/************************/

class LengthExpression: public fuzuli::Expression {
public:
	LengthExpression(vector<Expression*> expr);
	virtual ~LengthExpression();
	Token *eval(Environment *env);
};

class NthExpression: public fuzuli::Expression {
public:
	NthExpression(vector<Expression*> expr);
	virtual ~NthExpression();
	Token *eval(Environment *env);
};

class SetExpression: public fuzuli::Expression {
public:
	SetExpression(vector<Expression*> expr);
	virtual ~SetExpression();
	Token *eval(Environment *env);
};

class ExplodeExpression: public Expression {
public:
	ExplodeExpression(vector<Expression*>expr);
	virtual ~ExplodeExpression();
	Token *eval(Environment *env);
};

class AppendExpression: public Expression {
public:
	AppendExpression(vector<Expression*>expr);
	virtual ~AppendExpression();
	Token *eval(Environment *env);
};


class PrependExpression: public Expression {
public:
	PrependExpression(vector<Expression*>expr);
	virtual ~PrependExpression();
	Token *eval(Environment *env);
};



class NotExpression: public fuzuli::Expression, public CppEmitter {
public:
	NotExpression(vector<Expression*> expr);
	virtual ~NotExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class OrExpression: public fuzuli::Expression , public CppEmitter {
public:
	OrExpression(vector<Expression*> expr);
	virtual ~OrExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class PlusExpression: public Expression , public CppEmitter{
public:
	PlusExpression(vector<Expression*> expr);
	virtual ~PlusExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class ModulaExpression: public Expression , public CppEmitter{
public:
	ModulaExpression(vector<Expression*> expr);
	virtual ~ModulaExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};


class ColonExpression: public Expression {
public:
	ColonExpression(vector<Expression*> expr);
	virtual ~ColonExpression();
	virtual Token *eval(Environment *env);
};

class RemainderExpression: public Expression {
public:
	RemainderExpression(vector<Expression*> expr);
	virtual ~RemainderExpression();
	virtual Token *eval(Environment *env);
};

class IncExpression: public Expression , public CppEmitter {
public:
	IncExpression(vector<Expression*> expr);
	virtual ~IncExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class DecExpression: public Expression , public CppEmitter {
public:
	DecExpression(vector<Expression*> expr);
	virtual ~DecExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class CloneExpression: public Expression , public CppEmitter {
public:
	CloneExpression(vector<Expression*> expr);
	virtual ~CloneExpression();
	virtual Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class RequireExpression: public Expression {
public:
	static vector<string> installedPackages;
	RequireExpression(vector<Expression*> expr);
	virtual ~RequireExpression();
	virtual Token *eval(Environment *env);
};

class ReturnExpression: public Expression {
public:
	ReturnExpression(vector<Expression*> expr);
	virtual ~ReturnExpression();
	virtual Token *eval(Environment *env);
};

class PrintExpression: public Expression, public CppEmitter {
public:
	PrintExpression(vector<Expression*> expr);
	virtual ~PrintExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};


class SourceCode {
public:
	SourceCode();
	virtual ~SourceCode();
	void readFromText(string *code);
	void readFromFile(const char *filename);
	string *getSourceCode();
	Token* getNextToken();
	void pushBackToken();
	void reset();
	char eat();
	char look();
	void putback();
	unsigned int getCurrentLine();
	void setCounter(unsigned int val);
	unsigned int getCounter();

private:
	string *code;
	unsigned int counter;
	unsigned int currentLine;
	unsigned int oldcounter;
};

class SubtractionExpression: public Expression , public CppEmitter{
public:
	SubtractionExpression(vector<Expression*> expr);
	virtual ~SubtractionExpression();
	Token *eval(Environment *env);
	void emitCpp(stringstream *ss);
};

class Token {
public:
	Token();
	Token(string *content, enum TokenType type);
	Token(const char *content, enum TokenType type);
	Token(double num, enum TokenType type);
	virtual ~Token();
	const char* toString();
	enum TokenType getType();
	const char *getContent();
	void setType(enum TokenType type);
	void setContent(const char *content);
	int getIntValue();
	double getFloatValue();
	void setFloatValue(double d);
	void setIntValue(int i);
	int Equal(Token *tok);
	int getLineNumber();
	void setLineNumber(int lineNum);
	void incLineNumber();
	void setKillable(bool killableState);
	bool getKillable();
	Token *clone();
	static Token *NULL_TOKEN;
	static int doubleprecision;
	static double epsilon;
	vector<Token*> tokens;
	Expression *expr;
	Token *returnToken;
	void *object;
	int returnFlag;
	int breakFlag;
private:
	string *content;
	enum TokenType type;
	int line;
	bool killable;
};

class VariableExpression: public fuzuli::Expression {
public:
	VariableExpression(vector<Expression*> expr);
	virtual ~VariableExpression();
	Token *eval(Environment *env);
};

class WhileExpression: public fuzuli::Expression {
public:
	WhileExpression(vector<Expression*> expr);
	virtual ~WhileExpression();
	Token *eval(Environment *env);
};

class StringExpression: public Expression, public CppEmitter {
public:
	StringExpression(Token *tok);
	virtual ~StringExpression();
	Token *eval(Environment *env);
	Token *stringToken;
	string stringValue;
	void emitCpp(stringstream *ss);
};


class WebExpression: public Expression {
public:
	WebExpression(const char *html);
	~WebExpression();
	Token *eval(Environment *env);
	const char *html;
};

class SetCookieExpression: public Expression {
public:
	SetCookieExpression(vector<Expression*> expr);
	~SetCookieExpression();
	Token *eval(Environment *env);
};


class GetCookieExpression: public Expression {
public:
	GetCookieExpression(vector<Expression*> expr);
	~GetCookieExpression();
	Token *eval(Environment *env);
};

class IncludeExpression : public Expression {
public:
	IncludeExpression(vector<Expression*>expr);
	~IncludeExpression();
	Token *eval(Environment *env);
};


class Environment {
public:
	Environment();
	Environment(Environment *base);
	virtual ~Environment();
	map<string, Token*> variables;
	map<string, FuzuliFunction*> fuzuliFunctions;
	list<Token*> garbage;
	Environment *previous;
	Environment *next;

	bool isFirst();
	void setFirst();
	void registerGlobals();

	Token *newToken(double val, TokenType type);
	Token *newToken(const char* val, TokenType type);
	int GC();
	void dump();
	bool variableExists(const char *name);

	void setVariableInThisScope(const char*name, Token *value);
	Token *getVariableInThisScope(const char*name);

	Environment *searchBackEnvironments(const char *name);
	Environment *setVariable(const char *name, Token *value);
	Token *getVariable(const char *name);

	Environment *createNext();

	FuzuliFunction *searchFuncBackEnvironments(const char *name);
	void setFunction(const char *name, FuzuliFunction *value);
	void setVariableForFunctionParams(const char *name, Token *value);
	FuzuliFunction *getFunction(const char *name);
	void setArgcArgv(int argc, char** argv);

	int deep;
private:
	bool first;
};

class AstBuilder {
public:
	AstBuilder(SourceCode *source);
	Expression *getNextExpression();
	virtual ~AstBuilder();
	Expression *fuzuliCall(Token *tok, vector<Expression*> exp);

private:
	SourceCode *code;
};


class GCExpression : public Expression{
public:
	GCExpression(vector<Expression*> expr);
	virtual ~GCExpression();
	Token *eval(Environment *env);
};


class SetPrecisionExpression : public Expression {
public:
	SetPrecisionExpression(vector<Expression*> expr);
	virtual ~SetPrecisionExpression();
	Token *eval(Environment *env);
};


class SetEpsilonExpression : public Expression {
public:
	SetEpsilonExpression(vector<Expression*> expr);
	virtual ~SetEpsilonExpression();
	Token *eval(Environment *env);
};


class FuzuliClass {
public:
	FuzuliClass();
	virtual ~FuzuliClass();
	static map<string,FuzuliClass*> all_classes;
	Expression *body;
	string extends;
	string name;
};


class ClassExpression: public Expression {
public:
	ClassExpression(vector<Expression*> expr);
	virtual ~ClassExpression();
	Token *eval(Environment *env);
};

class NewExpression: public Expression {
public:
	NewExpression (vector<Expression*> expr);
	virtual ~NewExpression();
	Token *eval (Environment *env);
};


}



#endif /* FUZULITYPES_H_ */
