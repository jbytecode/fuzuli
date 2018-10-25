#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzulitypes.h"

FuzuliValue* FuzuliValueCreateNull(){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_NULL;
    value->svalue = StringNew("NULL");
    return(value);
}

FuzuliValue* FuzuliValueCreateString(const char *c){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_STRING;
    value->svalue = StringNew(c);
    return(value);
}

FuzuliValue* FuzuliValueCreateInteger(int i){
   FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_INT;
    value->ivalue = i;
    return(value);
}


FuzuliValue* FuzuliValueCreateDouble(double d){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_DOUBLE;
    value->dvalue = d;
    return(value);
}

FuzuliValue* FuzuliValueCreateUnsignedInteger(unsigned int i){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_UINT;
    value->uvalue = i;
    return(value);
}


FuzuliValue* FuzuliValueCreateLong(long l){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_LONG;
    value->lvalue = l;
    return(value);
}


FuzuliValue* FuzuliValueCreatePointer(void *v){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_POINTER;
    value->vvalue = v;
    return(value);
}


FuzuliValue* FuzuliValueCreateFloat(float f){
    FuzuliValue *value = (FuzuliValue*)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_FLOAT;
    value->fvalue = f;
    return(value);
}



void FuzuliValueSetTag(FuzuliValue *val, char *tag){
    val->tag = (char*) malloc(strlen(tag));
    strcpy(val->tag, tag);
}

void FuzuliValueCopyContent(FuzuliValue *destination, FuzuliValue *source){
    destination->dvalue = source->dvalue;
    destination->tag = (char*)malloc(strlen(source->tag));
    strcpy(destination->tag, source->tag);
    destination->type = source->type;
}



void FuzuliValuePrintDebugged(FuzuliValue *value){
    if(value->tag != NULL){
        printf("%s:", value->tag);
    }
    switch(value->type){
        case FTYPE_DOUBLE:
            printf("DBL=%f", value->dvalue);
            break;
        case FTYPE_FLOAT:
            printf("FLT=%f", value->fvalue);
            break;
        case FTYPE_INT:
            printf("INT=%d", value->ivalue);
            break;
        case FTYPE_STRING:
            printf("STR=%s", value->svalue->chars);
            break;
        case FTYPE_UINT:
            printf("UINT=%u", value->uvalue);
            break;
        case FTYPE_LONG:
            printf("LONG=%ld", value->lvalue);
            break;
        case FTYPE_POINTER:
            printf("POI=%p", &value->vvalue);
            break;
        default:
            printf("FV=type not found");
    }
    printf(" ");
}


void FuzuliValuePrint(FuzuliValue *value){
    switch(value->type){
        case FTYPE_DOUBLE:
            printf("%f", value->dvalue);
            break;
        case FTYPE_FLOAT:
            printf("%f", value->fvalue);
            break;
        case FTYPE_INT:
            printf("%d", value->ivalue);
            break;
        case FTYPE_STRING:
            printf("%s", value->svalue->chars);
            break;
        case FTYPE_UINT:
            printf("%u", value->uvalue);
            break;
        case FTYPE_LONG:
            printf("%ld", value->lvalue);
            break;
        case FTYPE_POINTER:
            printf("%p", &value->vvalue);
            break;
	case FTYPE_NULL:
	    printf("NULL");
	    break;
        default:
            printf("FuzulivaluePrint: type '%u' not found in evaluator.\n", value->type);
	    if(value->tag != NULL){
		    printf("Tagges as: %s\n", value->tag);
	    }
    }
    printf(" ");
}

