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
#include <cstdlib>
#include <cstring>
#include <jni.h>

using namespace std;
using namespace fuzuli;

extern "C" {
Token *java_init(Token *p, Environment *env);
Token *java_FindClass(Token *p, Environment *env);
Token *java_GetMethodID(Token *p, Environment *env);
Token *java_NewObject(Token *p, Environment *env);
Token *jvalued (Token *p, Environment *env);
}

Token *jvalued (Token *p, Environment *env){
	JNIEnv *javaenv = (JNIEnv*) p->tokens[0]->object;
	Token *param = p->tokens[1];
	Token *result = env->newToken("@JavaObject", COBJECT);
	return(result);
	jvalue jval;
	switch(param->getType()){
	case INTEGER:
		jval.i = param->getIntValue();
		break;

	case FLOAT:
		jval.d = param->getFloatValue();
		break;

	case STRING:
		jval.l = javaenv->NewStringUTF(param->getContent());
		break;

	case COBJECT:
		jval.l = (jobject&)param->object;
		break;

	default:
		cout << "This kind of objects can not be passed to jvalue"<<endl;
		exit(0);
	}

	result->object = (void*)&jval;
	return(result);
}

/*
 * (C javalib "java_NewObject" jvm clazz methodid valuelist)
 */
Token *java_NewObject(Token *p, Environment *env) {

	JNIEnv *javaenv = (JNIEnv*) p->tokens[0]->object;
	jclass clazz = (jclass) p->tokens[1]->object;
	jmethodID methodid = (jmethodID) p->tokens[2]->object;
	jobject obj = NULL;
	cout << "New Obj:" << endl;
	Token *otherparams = p->tokens[3];

	if(otherparams->tokens.size()==1){
		cout << "Converting "<< otherparams->tokens[0]->getContent()<<endl;
		//jstring js = javaenv->NewStringUTF(otherparams->tokens[0]->getContent());
		jvalue val;
		val.i = 9;
		obj = javaenv->NewObject(clazz, methodid, val);
	}
	Token *result = new Token("@JavaObject", COBJECT);
	result->object = (void*)obj;
	return (result);
}

/*
 * (C javalib "java_getMethodID" jvm clazz name sig)
 */
Token *java_GetMethodID(Token *p, Environment *env) {
	JNIEnv *javaenv = (JNIEnv*) p->tokens[0]->object;
	jclass clazz = (jclass) p->tokens[1]->object;
	const char *name = p->tokens[2]->getContent();
	const char *sig = p->tokens[3]->getContent();
	jmethodID methodid = javaenv->GetMethodID(clazz, name, sig);
	Token *result = new Token("@JavaMethodId", COBJECT);
	result->object = (void*)methodid;
	return (result);
}

/*
 * (C javalib "java_FindClass jvm clazz)
 */
TwoParameters
Token *java_FindClass(Token *p, Environment *env) {
	JNIEnv *javaenv = (JNIEnv*) p->tokens[0]->object;
	jclass clazz = javaenv->FindClass(p->tokens[1]->getContent());
	Token *result = new Token("@JavaClass", COBJECT);
	result->object = (void*)clazz;
	return (result);
}



//to-do
//Class path info did not added.
NoParameters
Token *java_init(Token *p, Environment *env) {
	JNIEnv *jenv;
	JavaVM *vm;
	JavaVMInitArgs args;
	JavaVMOption options[1];
	args.version = 0x00010002;
	//args.version = JNI_VERSION_1_6;
	args.nOptions = 1;
	options[0].optionString = "-Djava.class.path=.";
	args.options = options;
	args.ignoreUnrecognized = JNI_TRUE;

	JNI_CreateJavaVM(&vm, (void **) &jenv, &args);

	Token *result = new Token("@FuzuliJVM", COBJECT);
	result->object = (void *) jenv;
	return (result);
}
