#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzulitypes.h"
#include "ferror.h"

FuzuliValue *FuzuliValueCreateNull()
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_NULL;
    value->svalue = StringNew("NULL");
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateString(const char *c)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_STRING;
    value->svalue = StringNew(c);
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateInteger(int i)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_INT;
    value->ivalue = i;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateDouble(double d)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_DOUBLE;
    value->dvalue = d;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateUnsignedInteger(unsigned int i)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_UINT;
    value->uvalue = i;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateLong(long l)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_LONG;
    value->lvalue = l;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreatePointer(void *v)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_POINTER;
    value->vvalue = v;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

FuzuliValue *FuzuliValueCreateFloat(float f)
{
    FuzuliValue *value = (FuzuliValue *)malloc(sizeof(FuzuliValue));
    value->type = FTYPE_FLOAT;
    value->fvalue = f;
    value->links = 0;
    value->tag = NULL;
    return (value);
}

void FuzuliValueSetTag(FuzuliValue *val, char *tag)
{
    val->tag = (char *)malloc(strlen(tag));
    strcpy(val->tag, tag);
    if (tag != NULL)
    {
        val->links++;
    }
}

void FuzuliValueCopyContent(FuzuliValue *destination, FuzuliValue *source)
{
    if (destination == source)
    {
        return;
    }
    destination->dvalue = source->dvalue;
    if (source->tag != NULL)
    {
        destination->tag = (char *)malloc(strlen(source->tag));
        strcpy(destination->tag, source->tag);
    }
    destination->type = source->type;
    destination->links = 0;
}

FuzuliValue *FuzuliValueDuplicate(FuzuliValue *value)
{
    FuzuliValue *newf = FuzuliValueCreateNull();
    newf->dvalue = value->dvalue;
    newf->svalue = value->svalue;
    newf->type = value->type;
    return (newf);
}

void FuzuliValueFree(FuzuliValue *value)
{
    if (value->links == 0)
    {
        //printf("*Deleting fvalue\n");
        free(value);
    }
    else
    {
        //printf("*will not delete linked value");
    }
}

unsigned int FuzuliValueEquals(FuzuliValue *val1, FuzuliValue *val2)
{
    if (val1->type != val2->type)
    {
        ErrorAndTerminate("Variable types are not same in equality check", -1);
    }
    switch (val1->type)
    {
    case FTYPE_DOUBLE:
        return (val1->dvalue == val2->dvalue);
        break;
    case FTYPE_FLOAT:
        return (val1->fvalue == val2->fvalue);
        break;
    case FTYPE_INT:
        return (val1->ivalue == val2->ivalue);
        break;
    case FTYPE_LONG:
        return (val1->lvalue == val2->lvalue);
        break;
    case FTYPE_NULL:
        return (1);
        break;
    case FTYPE_POINTER:
        return (val1->vvalue == val2->vvalue);
        break;
    case FTYPE_STRING:
        return(val1->svalue == val2->svalue);
        break;
    case FTYPE_UINT:
        return(val1->uvalue == val2->uvalue);
        break;
    default:
        ErrorAndTerminate("Variable type not found in equality check", -1);
    }
}

void FuzuliValuePrintDebugged(FuzuliValue *value)
{
    if (value->tag != NULL)
    {
        printf("%s:", value->tag);
    }
    switch (value->type)
    {
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

void FuzuliValuePrint(FuzuliValue *value)
{
    switch (value->type)
    {
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
        if (value->tag != NULL)
        {
            printf("Tagges as: %s\n", value->tag);
        }
    }
    printf(" ");
}
