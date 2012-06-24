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
#include <happycoders/socket/tcpsocket.hh>


using namespace std;
using namespace fuzuli;
using namespace Network;

extern "C"{
Token *fsockopen(Token *p, Environment *env);
Token *fsockread(Token *p, Environment *env);
Token *fsockwrite(Token *p, Environment *env);
Token *fsockclose(Token *p, Environment *env);
Token *fsocklisten(Token *p, Environment *env);
}


Token *fsocklisten(Token *p, Environment *env){
	TcpSocket *clientsocket = new TcpSocket(V4);
	TcpSocket *serversocket = new TcpSocket(V4);
	Token *port = p->tokens[0];
	serversocket->connect(port->getIntValue());

	clientsocket = serversocket->accept();

	Token *result = env->newToken("@FuzuliSocket",COBJECT);
	result->object = (void*) clientsocket;
	return(result);
}

OneParameters
Token *fsockclose(Token *p, Environment *env) {
	TcpSocket *socket = (TcpSocket*) p->tokens[0]->object;
	socket->close();
	return (Token::NULL_TOKEN);
}

TwoParameters
Token *fsockwrite(Token *p, Environment *env) {
	TcpSocket *socket = (TcpSocket*)(p->tokens[0]->object);
	Token *subject = p->tokens[1];
	const string str_subject = string(subject->getContent());
	socket->write(str_subject);
	return (Token::NULL_TOKEN);
}

TwoParameters
Token *fsockread(Token *p, Environment *env) {
	TcpSocket *socket = (TcpSocket*) p->tokens[0]->object;
	if (!socket->connected()) {
		return (Token::NULL_TOKEN);
	}
	Token *n = p->tokens[1];
	try {
		string str_read = socket->readn((unsigned int) n->getIntValue());
		Token *result = env->newToken(str_read.c_str(), STRING);
		return (result);
	} catch (Exception e) {
		return (Token::NULL_TOKEN);
	}
	return (Token::NULL_TOKEN);
}

TwoParameters
Token *fsockopen(Token *p, Environment *env) {
	TcpSocket *socket = new TcpSocket(V4);
	Token *host = p->tokens[0];
	Token *port = p->tokens[1];
	const string str_host = string(host->getContent());
	socket->connect(str_host, port->getIntValue());

	Token *result = env->newToken("@FuzuliClientSocket", COBJECT);
	result->object = (void*)(socket);
	return (result);
}

