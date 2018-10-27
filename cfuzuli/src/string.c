#include "string.h"
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "fmemory.h"


String* StringNewFromChar(char c) {
    String *s = (String*)fmalloc(sizeof(String));
    s->chars = (char*) fmalloc(1);
    s->chars[0] = c;
    s->length = 1;
    return (s);
}


String* StringNew(const char *c) {
    String *s = (String*)fmalloc(sizeof(String));
    s->chars = (char*) fmalloc(strlen(c));
    strcpy(s->chars, c);
    s->length = strlen(c);
    return (s);
}

unsigned int StringLength(String *s) {
    return (s->length);
}

unsigned int StringEquals(String *s1, String *s2) {
    unsigned int len = StringLength(s1);
    for (int i = 0; i < len; i++) {
        if (s1->chars[i] != s2->chars[i]) {
            return (FALSE);
        }
    }
    return (TRUE);
}

void StringClear(String *s) {
    ffree(s->chars);
    s->length = 0;
    ffree(s);
}

String* StringConcat(String *s1, String *s2) {
    unsigned int len1 = StringLength(s1);
    unsigned int len2 = StringLength(s2);
    unsigned int newlen = len1 + len2;
    String* newstr = (String*)fmalloc(sizeof(String));
    char *newchars = (char*) fmalloc(newlen);
    unsigned int m = 0;
    for (int i = 0; i < len1; i++) {
        newchars[m] = s1->chars[m];
        m++;
    }
    for (int i = 0; i < len2; i++) {
        newchars[m] = s2->chars[i];
        m++;
    }
    newstr->chars = newchars;
    newstr->length = newlen;
    return (newstr);
}

void StringAppendChar(String *s, char c) {
    unsigned int len = StringLength(s);
    char *newchars = (char*) fmalloc(sizeof (char) * (len + 2));
    strcpy(newchars, s->chars);
    newchars[len] = c;
    ffree(s->chars);
    s->chars = newchars;
    s->length = len + 1;
    s->chars[len + 1] = '\0';
}

void StringAppendChars(String *s, char *c) {
    unsigned int slen = StringLength(s);
    unsigned int clen = strlen(c);
    unsigned int newlen = slen + clen;
    char *newchars = (char*) fmalloc(sizeof (char) * (slen + clen));
    strcpy(newchars, s->chars);
    ffree(s->chars);
    unsigned int m = 0;
    for (int i = slen; i < newlen; i++) {
        newchars[i] = c[m];
        m++;
    }
    s->chars = newchars;
    s->length = newlen;
}

String* StringSubstr(String *s, unsigned int startinclusive, unsigned int stopexclusive) {
    unsigned int len = stopexclusive - startinclusive;
    char *newchars = (char*) fmalloc(sizeof (char) * len);
    int m = 0;
    for (int i = startinclusive; i < stopexclusive; i++) {
        newchars[m] = s->chars[i];
        m++;
    }
    String* newstr = StringNew(newchars);
    return (newstr);
}


