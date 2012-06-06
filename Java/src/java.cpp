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
#include <stdlib.h>
#include <jni.h>


using namespace std;
using namespace fuzuli;

extern "C" {
Token *java_init(Token *p, Environment *env);
Token *java_static(Token *p, Environment *env);
}


// (java_static jvmenv "class" "method" (list parameters) (
ThreeParameters
Token *java_static(Token *p, Environment *env){
	JNIEnv *javaenv = (JNIEnv*) p->tokens[0]->object;
	jclass clazz = javaenv->FindClass(p->tokens[1]->getContent());
	jmethodID methodid = javaenv->GetMethodID(clazz, p->tokens[2]->getContent(), "");
	Token *params = p->tokens[3];
	jvalue* jv = (jvalue*)malloc (sizeof(jvalue)* params->tokens.size());
	for (int i=0;i<params->tokens.size();i++){
		jv[i].l = javaenv->NewStringUTF(params->tokens[i]->getContent());
	}
    jobject jresult = javaenv->CallStaticObjectMethodA(clazz, methodid, jv);

    Token *result = new Token("",COBJECT);
    result->object = (void*) &jresult;
    return(result);
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
	options[0].optionString="-Djava.class.path=.";
	args.options = options;
	args.ignoreUnrecognized = JNI_TRUE;

	jint res = JNI_CreateJavaVM(&vm, (void **)&jenv, &args);

	Token *result = new Token("@FuzuliJVM", COBJECT);
	result->object = (void *) jenv;
	return (result);
}
