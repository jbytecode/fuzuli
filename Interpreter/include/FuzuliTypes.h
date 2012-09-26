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
#include <sstream>

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
	FLOAT, /* 2 */
	STRING, /* 3 */
	LIST, /* 4 */
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
	JAVASCRIPT,
	COBJECT,
	FUZULIOBJECT,

	EXCLAMATION,
	NOTEQUALS

};

enum ExpressionType {
	UNDEFINED_EXPRESSION,
	IDENTIFIER_EXPRESSION,
	STRING_EXPRESSION,
	INTEGER_EXPRESSION,
	FLOAT_EXPRESSION,
	INTEGERCONSTANT_EXPRESSION,
	FLOATCONSTANT_EXPRESSION,
	VARIABLE_EXPRESSION,
	TYPEOF_EXPRESSION,
	TYPE_EXPRESSION,
	AND_EXPRESSION,
	OR_EXPRESSION,
	ASTERIX_EXPRESSION,
	DIVISION_EXPRESSION,
	NOT_EXPRESSION,
	PLUS_EXPRESSION,
	INC_EXPRESSION,
	DEC_EXPRESSION,
	SUBTRACTION_EXPRESSION,
	EQUALS_EXPRESSION,
	NOTEQUALS_EXPRESSION,
	LESS_EXPRESSION,
	LESSOREQUAL_EXPRESSION,
	BIGGER_EXPRESSION,
	BIGOREQUAL_EXPRESSION,
	MODULA_EXPRESSION,
	BITAND_EXPRESSION,
	BITNOT_EXPRESSION,
	BITOR_EXPRESSION,
	BITXOR_EXPRESSION,
	BITSHIFTLEFT_EXPRESSION,
	BITSHIFTRIGHT_EXPERSSION,
	SETPRECISION_EXPRESSION,
	SETEPSILON_EXPRESSION,
	BLOCK_EXPRESSION,
	GROUP_EXPRESSION,
	DYNLOAD_EXPRESSION,
	C_EXPRESSION,
	DUMP_EXPRESSION,
	GC_EXPRESSION,
	DELETE_EXPRESSION,
	EVAL_EXPRESSION,
	EXPRESSION_EXPRESSION,
	FUNCTION_EXPRESSION,
	FUNCTIONCALL_EXPRESSION,
	PARAMS_EXPRESSION,
	RETURN_EXPRESSION,
	IF_EXPRESSION,
	SWITCH_EXPERSSION,
	CASE_EXPRESSION,
	PRINT_EXPRESSION,
	PRINTLN_EXPRESSION,
	REQUIRE_EXPRESSION,
	LET_EXPRESSION,
	DEF_EXPRESSION,
	CLONE_EXPRESSION,
	LIST_EXPRESSION,
	LENGTH_EXPRESSION,
	NTH_EXPRESSION,
	SET_EXPRESSION,
	FILL_EXPRESSION,
	EXPLODE_EXPRESSION,
	COLON_EXPRESSION,
	APPEND_EXPRESSION,
	PREPEND_EXPRESSION,
	REMOVE_EXPRESSION,
	FIND_EXPRESSION,
	FIRST_EXPRESSION,
	LAST_EXPRESSION,
	FOR_EXPRESSION,
	FOREACH_EXPRESSION,
	DOTIMES_EXPRESSION,
	WHILE_EXPRESSION,
	BREAK_EXPRESSION,
	CLASS_EXPRESSION,
	NEW_EXPRESSION,
	TIMING_EXPRESSION,
	WEB_EXPRESSION,
	REQUEST_EXPRESSION,
	SETCOOKIE_EXPRESSION,
	GETCOOKIE_EXPRESSION,
	INCLUDE_EXPRESSION,
	ISSET_EXPRESSION,

};


/* CLASSES */

class Token;
class Environment;

using namespace std;

class Expression {
public:
	Expression();
	virtual ~Expression();
	void setExpressions(vector<Expression*> *expressions);
	virtual Token *eval(Environment *env);
	const char* toString();
	vector<Expression*> *expressions;
	Token *resultToken;
	enum ExpressionType type;
private:

};


class AndExpression: public Expression {
public:
	AndExpression(vector<Expression*> *expr);
	virtual ~AndExpression();
	Token *eval(Environment *env);
};

class BitShiftLeftExpression: public Expression {
public:
	BitShiftLeftExpression(vector<Expression*> *expr);
	virtual ~BitShiftLeftExpression();
	Token *eval(Environment *env);
};

class BitShiftRightExpression: public Expression {
public:
	BitShiftRightExpression(vector<Expression*> *expr);
	virtual ~BitShiftRightExpression();
	Token *eval(Environment *env);
};

class BitAndExpression: public Expression {
public:
	BitAndExpression(vector<Expression*> *expr);
	virtual ~BitAndExpression();
	Token *eval(Environment *env);
};

class BitOrExpression: public Expression {
public:
	BitOrExpression(vector<Expression*> *expr);
	virtual ~BitOrExpression();
	Token *eval(Environment *env);
};

class BitNotExpression: public Expression {
public:
	BitNotExpression(vector<Expression*> *expr);
	virtual ~BitNotExpression();
	Token *eval(Environment *env);
};

class BitXORExpression: public Expression {
public:
	BitXORExpression(vector<Expression*> *expr);
	virtual ~BitXORExpression();
	Token *eval(Environment *env);
};

class AsterixExpression: public Expression {
public:
	AsterixExpression(vector<Expression*> *expression);
	virtual ~AsterixExpression();
	virtual Token *eval(Environment *env);
};

class BlockExpression: public Expression {
public:
	BlockExpression(vector<Expression*> *expr);
	virtual ~BlockExpression();
	Token *eval(Environment *env);
};

class GroupExpression: public Expression {
public:
	GroupExpression(vector<Expression*> *expr);
	virtual ~GroupExpression();
	Token *eval(Environment *env);
};

class BreakExpression: public Expression {
public:
	BreakExpression(vector<Expression*> *expr);
	virtual ~BreakExpression();
	Token *eval(Environment *env);
};

class DumpExpression: public Expression {
public:
	DumpExpression(vector<Expression*> *expr);
	virtual ~DumpExpression();
	Token *eval(Environment *env);
};

class DynLoadExpression: public Expression {
public:
	DynLoadExpression(vector<Expression*> *expr);
	virtual ~DynLoadExpression();
	Token *eval(Environment *env);
	void *libraryHandle;
	const char *libraryName;
};

class LessExpression: public Expression {
public:
	LessExpression(vector<Expression*> *expr);
	virtual ~LessExpression();
	Token *eval(Environment *env);
};

class LessOrEqualExpression: public Expression {
public:
	LessOrEqualExpression(vector<Expression*> *expr);
	virtual ~LessOrEqualExpression();
	Token *eval(Environment *env);
};

class BiggerExpression: public Expression {
public:
	BiggerExpression(vector<Expression*> *expr);
	virtual ~BiggerExpression();
	Token *eval(Environment *env);
};

class BigOrEqualExpression: public Expression {
public:
	BigOrEqualExpression(vector<Expression*> *expr);
	virtual ~BigOrEqualExpression();
	Token *eval(Environment *env);
};

class CExpression: public Expression {
public:
	CExpression(vector<Expression*> *expr);
	virtual ~CExpression();
	Token *eval(Environment *env);
};

class DivisionExpression: public Expression {
public:
	DivisionExpression(vector<Expression*> *expr);
	virtual ~DivisionExpression();
	Token *eval(Environment *env);
};

class EqualsExpression: public Expression {
public:
	EqualsExpression(vector<Expression*> *expr);
	virtual ~EqualsExpression();
	Token *eval(Environment *env);
};

class NotEqualsExpression: public Expression {
public:
	NotEqualsExpression(vector<Expression*> *expr);
	virtual ~NotEqualsExpression();
	Token *eval(Environment *env);
};

class ForExpression: public Expression {
public:
	ForExpression(vector<Expression*> *expr);
	virtual ~ForExpression();
	Token *eval(Environment *env);
};

class ForEachExpression: public Expression {
public:
	ForEachExpression(vector<Expression*> *expr);
	virtual ~ForEachExpression();
	Token *eval(Environment *env);
};

class DoTimesExpression: public Expression {
public:
	DoTimesExpression(vector<Expression*> *expr);
	virtual ~DoTimesExpression();
	Token *eval(Environment *env);
};

class SwitchExpression: public Expression {
public:
	SwitchExpression(vector<Expression*> *expr);
	virtual ~SwitchExpression();
	Token *eval(Environment *env);
};

class CaseExpression: public Expression {
public:
	CaseExpression(vector<Expression*> *expr);
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
	FunctionExpression(vector<Expression*> *expr);
	virtual ~FunctionExpression();
	Token *eval(Environment *env);
	FuzuliFunction *fuzulifunction;
private:
	stringstream *ss;
};

class FunctionCallExpression: public Expression {
public:
	FunctionCallExpression(vector<Expression*> *expr);
	virtual ~FunctionCallExpression();
	Token *eval(Environment *env);
	Token *evalForClass(Environment *env);
	string str_func_name;
	Token *fname;
	int paramscount;
private:
	stringstream *ss;
};


class RequestExpression: public Expression {
public:
	RequestExpression(vector<Expression*> *expr);
	virtual ~RequestExpression();
	Token *eval(Environment *env);
};

class IssetExpression: public Expression {
public:
	IssetExpression(vector<Expression*> *expr);
	virtual ~IssetExpression();
	Token *eval(Environment *env);
};

class ParamsExpression: public Expression {
public:
	ParamsExpression(vector<Expression*> *expr);
	virtual ~ParamsExpression();
	Token *eval(Environment *env);
	vector<string*> paramNames;
};

class IdentifierExpression: public Expression {
public:
	IdentifierExpression(Token *tok);
	virtual ~IdentifierExpression();
	Token *eval(Environment *env);
	Token *stringToken;
	const char* id;
	Environment *last_envir;
};

class IfExpression: public Expression {
public:
	IfExpression(vector<Expression*> *expr);
	virtual ~IfExpression();
	Token *eval(Environment *env);
};

class IntegerExpression: public Expression{
public:
	IntegerExpression();
	IntegerExpression(Token *tok);
	virtual ~IntegerExpression();
	Token* eval(Environment *env);
	int integerValue;

private:
	Token *token;
};

class FloatExpression: public Expression {
public:
	FloatExpression();
	FloatExpression(Token *tok);
	virtual ~FloatExpression();
	Token* eval(Environment *env);
	double floatValue;
private:
	Token *token;
};

class IntegerConstantExpression: public Expression{
public:
	IntegerConstantExpression();
	IntegerConstantExpression(Token *tok);
	virtual ~IntegerConstantExpression();
	Token* eval(Environment *env);
	int integerValue;

private:
	Token *token;
};

class FloatConstantExpression: public Expression {
public:
	FloatConstantExpression();
	FloatConstantExpression(Token *tok);
	virtual ~FloatConstantExpression();
	Token* eval(Environment *env);
	double floatValue;
private:
	Token *token;
};


class DefExpression: public Expression {
public:
	DefExpression(vector<Expression*> *expr);
	~DefExpression();
	Token *eval(Environment *env);
};

class TypeofExpression: public Expression {
public:
	TypeofExpression(vector<Expression*> *expr);
	~TypeofExpression();
	Token *eval(Environment *env);
};

class TypeExpression: public Expression {
public:
	TypeExpression(vector<Expression*> *expr);
	~TypeExpression();
	Token *eval(Environment *env);
};

class LetExpression: public Expression{
public:
	LetExpression(vector<Expression*> *expr);
	virtual ~LetExpression();
	Token *eval(Environment *env);
};

class EvalExpression: public Expression {
public:
	EvalExpression(vector<Expression*> *expr);
	virtual ~EvalExpression();
	Token *eval(Environment *env);
};

/* List class */
class ListExpression: public Expression {
public:
	ListExpression(vector<Expression*> *expr);
	virtual ~ListExpression();
	Token *eval(Environment *env);
};

/************************/
/* Other List Functions */
/************************/

class LengthExpression: public Expression {
public:
	LengthExpression(vector<Expression*> *expr);
	virtual ~LengthExpression();
	Token *eval(Environment *env);
};

class NthExpression: public Expression {
public:
	NthExpression(vector<Expression*> *expr);
	virtual ~NthExpression();
	Token *eval(Environment *env);
};

class SetExpression: public Expression {
public:
	SetExpression(vector<Expression*> *expr);
	virtual ~SetExpression();
	Token *eval(Environment *env);
};

class ExplodeExpression: public Expression {
public:
	ExplodeExpression(vector<Expression*> *expr);
	virtual ~ExplodeExpression();
	Token *eval(Environment *env);
};

class AppendExpression: public Expression {
public:
	AppendExpression(vector<Expression*> *expr);
	virtual ~AppendExpression();
	Token *eval(Environment *env);
};

class PrependExpression: public Expression {
public:
	PrependExpression(vector<Expression*> *expr);
	virtual ~PrependExpression();
	Token *eval(Environment *env);
};

class RemoveExpression: public Expression {
public:
	RemoveExpression(vector<Expression*> *expr);
	virtual ~RemoveExpression();
	Token *eval(Environment *env);
};

class FindExpression: public Expression {
public:
	FindExpression(vector<Expression*> *expr);
	virtual ~FindExpression();
	Token *eval(Environment *env);
};

class FillExpression: public Expression {
public:
	FillExpression(vector<Expression*> *expr);
	virtual ~FillExpression();
	Token *eval(Environment *env);
};

class FirstExpression: public Expression {
public:
	FirstExpression(vector<Expression*> *expr);
	virtual ~FirstExpression();
	Token *eval(Environment *env);
};

class LastExpression: public Expression {
public:
	LastExpression(vector<Expression*> *expr);
	virtual ~LastExpression();
	Token *eval(Environment *env);
};

class NotExpression: public Expression {
public:
	NotExpression(vector<Expression*> *expr);
	virtual ~NotExpression();
	Token *eval(Environment *env);
};

class OrExpression: public Expression {
public:
	OrExpression(vector<Expression*> *expr);
	virtual ~OrExpression();
	Token *eval(Environment *env);
};

class PlusExpression: public Expression {
public:
	PlusExpression(vector<Expression*> *expr);
	virtual ~PlusExpression();
	virtual Token *eval(Environment *env);
};

class ModulaExpression: public Expression {
public:
	ModulaExpression(vector<Expression*> *expr);
	virtual ~ModulaExpression();
	virtual Token *eval(Environment *env);
};

class ColonExpression: public Expression {
public:
	ColonExpression(vector<Expression*> *expr);
	virtual ~ColonExpression();
	virtual Token *eval(Environment *env);
};

class RemainderExpression: public Expression {
public:
	RemainderExpression(vector<Expression*> *expr);
	virtual ~RemainderExpression();
	virtual Token *eval(Environment *env);
};

class IncExpression: public Expression {
public:
	IncExpression(vector<Expression*> *expr);
	virtual ~IncExpression();
	virtual Token *eval(Environment *env);
};

class DecExpression: public Expression {
public:
	DecExpression(vector<Expression*> *expr);
	virtual ~DecExpression();
	virtual Token *eval(Environment *env);
};

class CloneExpression: public Expression {
public:
	CloneExpression(vector<Expression*> *expr);
	virtual ~CloneExpression();
	virtual Token *eval(Environment *env);
};

class RequireExpression: public Expression {
public:
	static vector<string> installedPackages;
	RequireExpression(vector<Expression*> *expr);
	virtual ~RequireExpression();
	virtual Token *eval(Environment *env);
};

class ReturnExpression: public Expression {
public:
	ReturnExpression(vector<Expression*> *expr);
	virtual ~ReturnExpression();
	virtual Token *eval(Environment *env);
};

class PrintExpression: public Expression {
public:
	PrintExpression(vector<Expression*> *expr);
	virtual ~PrintExpression();
	Token *eval(Environment *env);
};

class PrintlnExpression: public Expression {
public:
	PrintlnExpression(vector<Expression*> *expr);
	virtual ~PrintlnExpression();
	Token *eval(Environment *env);
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

class SubtractionExpression: public Expression {
public:
	SubtractionExpression(vector<Expression*> *expr);
	virtual ~SubtractionExpression();
	Token *eval(Environment *env);
};

class Token {
public:
	Token();
	Token(string *content, enum TokenType type);
	Token(const char *content, enum TokenType type);
	Token(double num, enum TokenType type);
	virtual ~Token();
	const char* toString();
	const enum TokenType getType();
	const char *getContent();
	void setType(const enum TokenType type);
	void setContent(const char *content);
	int getIntValue();
	double getFloatValue();
	void setFloatValue(const double d);
	void setIntValue(const int i);

	int operator==(Token &other);
	int operator<(Token &other);
	int operator<=(Token &other);
	int operator>(Token &other);
	int operator>=(Token &other);
	double operator+(Token &other);
	double operator-(Token &other);
	Token& operator++();
	Token& operator--();

	int getLineNumber();
	void setLineNumber(const int lineNum);
	void incLineNumber();
	void setKillable(const bool killableState);
	bool getKillable() const ;
	void ReduceReferences();
	void IncreaseReferences();
	Token *clone();
	static Token *NULL_TOKEN;
	static int doubleprecision;
	static double epsilon;
	vector<Token*> tokens;
	Expression *expr;
	Token *returnToken;
	Environment *environment;
	void *object;
	int returnFlag;
	int breakFlag;
	int links;
private:
	string *content;
	stringstream *ss;
	enum TokenType type;
	int line;
	bool killable;
};


class WhileExpression: public Expression {
public:
	WhileExpression(vector<Expression*> *expr);
	virtual ~WhileExpression();
	Token *eval(Environment *env);
};

class StringExpression: public Expression {
public:
	StringExpression(Token *tok);
	virtual ~StringExpression();
	Token *eval(Environment *env);
	Token *stringToken;
	string stringValue;
};

class WebExpression: public Expression {
public:
	WebExpression(const char *html);
	~WebExpression();
	Token *eval(Environment *env);
	const char *html;
};

class ExpressionExpression: public Expression {
public:
	ExpressionExpression(vector<Expression*> *expr);
	~ExpressionExpression();
	Token *eval(Environment *env);
};



class SetCookieExpression: public Expression {
public:
	SetCookieExpression(vector<Expression*> *expr);
	~SetCookieExpression();
	Token *eval(Environment *env);
};

class GetCookieExpression: public Expression {
public:
	GetCookieExpression(vector<Expression*> *expr);
	~GetCookieExpression();
	Token *eval(Environment *env);
};

class IncludeExpression: public Expression {
public:
	IncludeExpression(vector<Expression*> *expr);
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
	vector<Environment*> subenvironments;
	Environment *previous;

	static bool isAutomaticGC;
	bool isFirst();
	void setFirst();
	void registerGlobals();

	Token *newToken(double val, TokenType type);
	Token *newToken(const char* val, TokenType type);
	int GC();
	int doAutomaticGC();
	int doAutomaticGCwithProtection(Token *tok);
	void preventGC(bool p);
	bool preventGC();
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
	bool prevent_garbage_collection;
};

class AstBuilder {
public:
	AstBuilder(SourceCode *source);
	Expression *getNextExpression();
	virtual ~AstBuilder();
	Expression *fuzuliCall(Token *tok, vector<Expression*> *exp);

private:
	SourceCode *code;
};

class GCExpression: public Expression {
public:
	GCExpression(vector<Expression*> *expr);
	virtual ~GCExpression();
	Token *eval(Environment *env);
};

class SetPrecisionExpression: public Expression {
public:
	SetPrecisionExpression(vector<Expression*> *expr);
	virtual ~SetPrecisionExpression();
	Token *eval(Environment *env);
};

class SetEpsilonExpression: public Expression {
public:
	SetEpsilonExpression(vector<Expression*> *expr);
	virtual ~SetEpsilonExpression();
	Token *eval(Environment *env);
};

class FuzuliClass {
public:
	FuzuliClass();
	virtual ~FuzuliClass();
	static map<string, FuzuliClass*> all_classes;
	Expression *body;
	string extends;
	string name;
};

class ClassExpression: public Expression {
public:
	ClassExpression(vector<Expression*> *expr);
	virtual ~ClassExpression();
	Token *eval(Environment *env);
};

class NewExpression: public Expression {
public:
	NewExpression(vector<Expression*> *expr);
	virtual ~NewExpression();
	Token *eval(Environment *env);
};

class DeleteExpression: public Expression {
public:
	DeleteExpression(vector<Expression*> *expr);
	virtual ~DeleteExpression();
	Token *eval(Environment *env);
};

class TimingExpression: public Expression {
public:
	TimingExpression(vector<Expression*> *expr);
	virtual ~TimingExpression();
	Token *eval(Environment *env);
};

}

#endif /* FUZULITYPES_H_ */
