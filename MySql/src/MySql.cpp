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
#include <mysql/mysql.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace fuzuli;

extern "C" {
Token *mysqlconnect(Token *p, Environment *env);
Token *mysqlquery(Token *p, Environment *env);
Token *mysqlfetcharray(Token *p, Environment *env);
Token *mysqlnumfields(Token *p, Environment *env);
Token *mysqlnumrows(Token *p, Environment *env);
Token *mysqlaffectedrows(Token *p, Environment *env);
Token *mysqlgetclientinfo(Token *p, Environment *env);
Token *mysqlclose(Token *p, Environment *env);
Token *mysqlresult(Token *p, Environment *env);
Token *mysqlcharactersetname (Token *p, Environment *env);
Token *mysqlselectdb (Token *p, Environment *env);
Token *mysqlstat (Token *p, Environment *env);
Token *mysqlautocommit(Token *p, Environment *env);
}


Token* mysqlconnect(Token *p, Environment *env) {
	MYSQL *mysql;
	Token *result = env->newToken("", STRING);
	mysql = mysql_init(NULL);
	//p[0]=host, p[1]=user, p[2]=password, p[3]=db, p[4]=port
	//cout << "Connecting " << p->tokens[0]->getContent() << endl;
	if (!mysql_real_connect(mysql, p->tokens[0]->getContent(),
			p->tokens[1]->getContent(), p->tokens[2]->getContent(),
			p->tokens[3]->getContent(), p->tokens[4]->getIntValue(), NULL, 0)) {
		cout << "Cannot connect to mysql " << p->tokens[0]->getContent()
				<< endl;
		result->setContent("NULL");
		result->setType(NULLTOKEN);
		return (result);
	}
	result->object = (void*) mysql;
	result->setType(COBJECT);
	//cout << "Returing from mysql call" << endl;
	return (result);
}

Token* mysqlquery(Token *p, Environment *env) {
	Token *result = env->newToken("@MysqlQueryObject", STRING);
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	//cout << "Running: " << p->tokens[1]->getContent() << endl;
	int qresult = mysql_query(mysql, p->tokens[1]->getContent());
	if (qresult != 0) {
		cout << "mysql_query returned an error: " << endl;
	}
	MYSQL_RES *resultset = mysql_store_result(mysql);
	result->setType(COBJECT);
	result->object = (void*) resultset;
	//cout << "Returning from query()" << endl;
	return (result);
}

Token *mysqlfetcharray(Token *p, Environment *env) {
	//cout << "Fetching" << endl;
	MYSQL_ROW row;
	Token *result = env->newToken("@FuzuliList", fuzuli::LIST);
	MYSQL_RES *query_result = (MYSQL_RES*) p->tokens[0]->object;
	row = mysql_fetch_row(query_result);
	if (row == NULL) {
		//cout << "row is null. returning" << endl;
		result->setType(NULLTOKEN);
		result->setContent("NULL");
		return (result);
	}
	int fields = mysql_num_fields(query_result);
	for (int i = 0; i < fields; i++) {
		if (row[i] == NULL) {
			break;
		}
		result->tokens.push_back(env->newToken((char*) row[i], fuzuli::STRING));
	}
	//cout << "Returing rows with num elemnts " << result->tokens.size() << endl;
	return (result);
}

Token *mysqlresult(Token *p, Environment *env) {
	MYSQL_ROW row;
	Token *result = env->newToken("", STRING);
	MYSQL_RES *query_result = (MYSQL_RES*) p->tokens[0]->object;
	int rownum = p->tokens[1]->getIntValue();
	int fieldnum = p->tokens[2]->getIntValue();
	for (int i = 0; i < rownum; i++) {
		row = mysql_fetch_row(query_result);
		if (row == NULL) {
			result->setType(NULLTOKEN);
			result->setContent("NULL");
			return (result);
		}
	}
	row = mysql_fetch_row(query_result);
	if (row == NULL) {
		result->setType(NULLTOKEN);
		result->setContent("NULL");
		return (result);
	}
	result->setContent(string(row[fieldnum]).c_str());
	return (result);
}

Token *mysqlnumfields(Token *p, Environment *env) {
	MYSQL_RES *query_result = (MYSQL_RES*) p->tokens[0]->object;
	int num = mysql_num_fields(query_result);
	Token *result = env->newToken(num, INTEGER);
	return (result);
}

Token *mysqlnumrows(Token *p, Environment *env) {
	MYSQL_RES *query_result = (MYSQL_RES*) p->tokens[0]->object;
	int num = mysql_num_rows(query_result);
	Token *result = env->newToken(num, INTEGER);
	return (result);
}

Token *mysqlaffectedrows(Token *p, Environment *env) {
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	int num = mysql_affected_rows(mysql);
	Token *result = env->newToken(num, INTEGER);
	return (result);
}

Token *mysqlgetclientinfo(Token *p, Environment *env) {
	Token *tok = env->newToken(mysql_get_client_info(), STRING);
	return (tok);
}

Token *mysqlclose(Token *p, Environment *env) {
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	mysql_close(mysql);
	return (Token::NULL_TOKEN);
}

Token *mysqlcharactersetname (Token *p, Environment *env){
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	Token *result = env->newToken(mysql_character_set_name(mysql), STRING);
	return(result);
}

Token *mysqlselectdb (Token *p, Environment *env){
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	Token *result = env->newToken(mysql_select_db(mysql, p->tokens[1]->getContent()), INTEGER);
	return(result);
}

Token *mysqlstat (Token *p, Environment *env){
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	Token *result = env->newToken(mysql_stat(mysql), STRING);
	return(result);
}

Token *mysqlautocommit(Token *p, Environment *env){
	MYSQL *mysql = (MYSQL*) p->tokens[0]->object;
	Token *booltoken = p->tokens[1];
	Token *result = env->newToken(0.0, INTEGER);
	result->setIntValue(mysql_autocommit(mysql, booltoken->getIntValue()));
	return(result);
}
