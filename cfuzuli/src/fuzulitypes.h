#ifndef FUZULI_TYPES_H
#define FUZULI_TYPES_H

#include "string.h"

typedef enum {
	FTYPE_UINT, 
	FTYPE_INT, 
	FTYPE_FLOAT, 
	FTYPE_STRING, 
	FTYPE_LONG, 
	FTYPE_DOUBLE, 
	FTYPE_POINTER,
	FTYPE_NULL
} FuzuliType; 

typedef struct {
	FuzuliType type;
    union {
		unsigned int uvalue;
		int ivalue;
		float fvalue;
		String* svalue;
		long lvalue;
		double dvalue;
		void *vvalue;		
	};
	char *tag;	
}FuzuliValue;





FuzuliValue* FuzuliValueCreateString(const char *c);
FuzuliValue* FuzuliValueCreateInteger(int i);
FuzuliValue* FuzuliValueCreateDouble(double d);
FuzuliValue* FuzuliValueCreateFloat(float f);
FuzuliValue* FuzuliValueCreateUnsignedInteger(unsigned int i);
FuzuliValue* FuzuliValueCreateLong(long l);
FuzuliValue* FuzuliValueCreatePointer(void *v);
FuzuliValue* FuzuliValueCreateNull();
void FuzuliValuePrint(FuzuliValue *value);
void FuzuliValuePrintDebugged(FuzuliValue *value);
void FuzuliValueSetTag(FuzuliValue *val, char *tag);
void FuzuliValueCopyContent(FuzuliValue *destination, FuzuliValue *source);
#endif
