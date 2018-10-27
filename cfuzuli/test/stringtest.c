#include <stdio.h>
#include <assert.h>
#include "../src/string.h"
#include "../src/constants.h"
#include "testconstants.h"

void StringNew_test1(){
	String *s = StringNew("Hello World");
	assert(s->chars != NULL);
	printf("%s\n",passed);
}

void string_length_test(){
	String *s = StringNew("Hello World");
	assert(StringLength(s) == 11);
	printf("%s\n",passed);
}

void string_equals_test(){
	String *s1 = StringNew("Hello World");
	String *s2 = StringNew("Hello World");
	assert(StringEquals(s1, s2));
	printf("%s\n",passed);
}

void string_clear_test(){
	String *s = StringNew("Hello");
	StringClear(s);
	assert(StringLength(s) == 0);
	printf("%s\n",passed);
}

void string_concat_test(){
	String *s1 = StringNew("Hello");
	String *s2 = StringNew(" World!");
	String *expected = StringNew("Hello World!");
	String *actual = StringConcat(s1, s2);
	assert(StringEquals(expected, actual));
	printf("%s\n",passed);
}

void StringAppendChar_test(){
	String *s1 = StringNew("Hello");
	String *expected = StringNew("Hello World");
	StringAppendChar(s1, ' ');
	StringAppendChar(s1, 'W');
	StringAppendChar(s1, 'o');
	StringAppendChar(s1, 'r');
	StringAppendChar(s1, 'l');
	StringAppendChar(s1, 'd');
	assert(StringEquals(s1, expected));
	printf("%s\n",passed);
}

void StringAppendChars_test(){
	String *s1 = StringNew("Hello");
	StringAppendChars(s1, " World");
	String *expected = StringNew("Hello World");
	assert(StringEquals(s1, expected));
	printf("%s\n",passed);
}

void string_substr_test(){
	String *s1 = StringNew("Hello World!");
	String *newstr = StringSubstr(s1, 6, 11);
	String *expected = StringNew("World");
	assert(StringEquals(newstr, expected));
	printf("%s\n",passed);
}


int main(int argc, char **argv){
	puts("String test: ");
	StringNew_test1();
	string_length_test();
	string_equals_test();
	string_clear_test();
	string_concat_test();
	StringAppendChar_test();
	StringAppendChars_test();
	string_substr_test();
	return 0;
}


