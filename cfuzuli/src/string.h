#ifndef STRING_H
#define STRING_H

typedef struct {
	char *chars;
	unsigned int length;
} String;

String* StringNewFromChar(char c);
String* StringNew(const char *c);
unsigned int StringLength(String *s);
unsigned int StringEquals(String *s1, String *s2);
void StringClear(String *s);
String* StringConcat(String *s1, String *s2);
void StringAppendChar(String *s, char c);
void StringAppendChars(String *s, char *c);
String* StringSubstr(String *s, unsigned int startinclusive, unsigned int stopexclusive);


#endif
