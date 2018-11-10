#ifndef FUZULI_TYPES_H
#define FUZULI_TYPES_H

#include "string.h"

#ifndef LINKED_LIST_H
#include "linkedlist.h"
#endif

typedef enum {
	FTYPE_UINT, 
	FTYPE_INT, 
	FTYPE_FLOAT, 
	FTYPE_STRING, 
	FTYPE_LONG, 
	FTYPE_DOUBLE, 
	FTYPE_POINTER,
	FTYPE_NULL,
	FTYPE_LIST
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
	int links;	
	char protected;
}FuzuliValue;





FuzuliValue* FuzuliValueCreateString(const char *c);
FuzuliValue* FuzuliValueCreateInteger(int i);
FuzuliValue* FuzuliValueCreateDouble(double d);
FuzuliValue* FuzuliValueCreateFloat(float f);
FuzuliValue* FuzuliValueCreateUnsignedInteger(unsigned int i);
FuzuliValue* FuzuliValueCreateLong(long l);
FuzuliValue* FuzuliValueCreatePointer(void *v);
FuzuliValue* FuzuliValueCreateNull();
FuzuliValue* FuzuliValueCreateList();
FuzuliValue* FuzuliValueDuplicate(FuzuliValue *value);
FuzuliValue* FuzuliValueSumNumeric(FuzuliValue *val1, FuzuliValue *val2);
FuzuliValue* FuzuliValueProdNumeric(FuzuliValue *val1, FuzuliValue *val2);
FuzuliValue* FuzuliValueSubtractNumeric(FuzuliValue *val1, FuzuliValue *val2);
FuzuliValue *FuzuliValueDivideNumeric(FuzuliValue *val1, FuzuliValue *val2);
void FuzuliValueIncNumeric(FuzuliValue *value);
double FuzuliValueGetNumericValue(FuzuliValue *val1);
void FuzuliValuePrint(FuzuliValue *value);
void FuzuliValueListPrint(FuzuliValue *value);
void FuzuliValueSetTag(FuzuliValue *val, char *tag);
void FuzuliValueCopyContent(FuzuliValue *destination, FuzuliValue *source);
void FuzuliValueFree(FuzuliValue *value);
void FuzuliValueForceFree(FuzuliValue *value);
unsigned int FuzuliValueEquals(FuzuliValue *val1, FuzuliValue *val2);

#endif
