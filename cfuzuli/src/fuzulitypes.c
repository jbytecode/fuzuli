#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "fuzulitypes.h"
#include "ferror.h"
#include "linkedlist.h"
#include "fmemory.h"

FuzuliValue *FuzuliValueCreateNull()
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_NULL;
    //value->svalue = StringNew("NULL");
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateString(const char *c)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_STRING;
    value->svalue = StringNew(c);
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateInteger(int i)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_INT;
    value->ivalue = i;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateDouble(double d)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_DOUBLE;
    value->dvalue = d;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateUnsignedInteger(unsigned int i)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_UINT;
    value->uvalue = i;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateLong(long l)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_LONG;
    value->lvalue = l;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreatePointer(void *v)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_POINTER;
    value->vvalue = v;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateFloat(float f)
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_FLOAT;
    value->fvalue = f;
    value->links = 0;
    value->tag = NULL;
    value->protected = 0;
    return (value);
}

FuzuliValue *FuzuliValueCreateList()
{
    FuzuliValue *value = (FuzuliValue *)fmalloc(sizeof(FuzuliValue));
    value->type = FTYPE_LIST;
    value->tag = NULL;
    value->protected = 0;
    return value;
}

void FuzuliValueSetTag(FuzuliValue *val, char *tag)
{
    if (!tag)
    {
        val->tag = NULL;
        return;
    }
    val->tag = (char *)fmalloc(strlen(tag));
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
        destination->tag = (char *)fmalloc(strlen(source->tag));
        strcpy(destination->tag, source->tag);
    }
    destination->type = source->type;
    destination->links = source->links;
    destination->protected = 0;
}

FuzuliValue *FuzuliValueDuplicate(FuzuliValue *value)
{
    FuzuliValue *newf = FuzuliValueCreateNull();
    switch (value->type)
    {
    case FTYPE_DOUBLE:
        newf->dvalue = value->dvalue;
        break;
    case FTYPE_FLOAT:
        newf->fvalue = value->fvalue;
        break;
    case FTYPE_INT:
        newf->ivalue = value->ivalue;
        break;
    case FTYPE_LONG:
        newf->lvalue = value->lvalue;
        break;
    case FTYPE_POINTER:
        newf->vvalue = value->vvalue;
        break;
    case FTYPE_STRING:
        newf->svalue = value->svalue;
        break;
    case FTYPE_LIST:
        newf->vvalue = value->vvalue;
        break;
    case FTYPE_UINT:
        newf->uvalue = value->uvalue;
        break;
    case FTYPE_NULL:
        FuzuliValueSetTag(newf, value->tag);
        break;
    }
    newf->type = value->type;
    newf->links = value->links;
    newf->protected = 0;
    //newf->tag = NULL;
    FuzuliValueSetTag(newf, value->tag);
    return (newf);
}

void FuzuliValueFree(FuzuliValue *value)
{
    if (value == NULL)
    {
        return;
    }
    if (value->protected != 0)
    {
        return;
    }
    if (value->links != 0)
    {
        return;
    }
    //printf("*Deleting fvalue\n");
    if (value->type == FTYPE_DOUBLE || value->type == FTYPE_INT || value->type == FTYPE_FLOAT || value->type == FTYPE_LONG || value->type == FTYPE_NULL || value->type == FTYPE_UINT)
    {
        ffree(value);
    }
    else if (value->type == FTYPE_POINTER)
    {
        if (value->vvalue != NULL)
        {
            ffree(value->vvalue);
        }
        ffree(value);
    }
    else if (value->type == FTYPE_STRING)
    {
        //printf("*** freeing %s\n", value->svalue->chars);
        StringClear(value->svalue);
        ffree(value);
    }
    else if (value->type == FTYPE_LIST)
    {
        if (value->vvalue != NULL)
        {
            LinkedListFreeWithFuzuliValueType((LinkedList *)value->vvalue);
        }
    }
    else
    {
        ffree(value);
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
        return (StringEquals(val1->svalue, val2->svalue));
        break;
    case FTYPE_UINT:
        return (val1->uvalue == val2->uvalue);
        break;
    default:
        ErrorAndTerminate("Variable type not found in equality check", -1);
        return -1;
    }
}

void FuzuliValueListPrint(FuzuliValue *value)
{
    LinkedList *list = (LinkedList *)value->vvalue;
    unsigned int len = LinkedListLength(list);
    unsigned int origlen = len;
    printf("[");
    for (unsigned int i = 0; i < len; i++)
    {
        FuzuliValue *val = (FuzuliValue *)LinkedListGet(list, i);
        FuzuliValuePrint(val);
        if (i < len - 1)
        {
            printf(", ");
        }
    }
    printf("]");
    if (len > MAX_PRINT)
    {
        printf("\n *List length is larger than MAX_PRINT = %d, output is truncated.\n", MAX_PRINT);
        len = MAX_PRINT;
    }
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
    case FTYPE_LIST:
        FuzuliValueListPrint(value);
        break;
    default:
        printf("FuzulivaluePrint: type '%u' not found in evaluator.\n", value->type);
        if (value->tag != NULL)
        {
            printf("Tagges as: %s\n", value->tag);
        }
    }
}

void FuzuliValueIncNumeric(FuzuliValue *value)
{
    switch (value->type)
    {
    case FTYPE_DOUBLE:
        value->dvalue++;
        break;
    case FTYPE_FLOAT:
        value->fvalue++;
        break;
    case FTYPE_INT:
        value->ivalue++;
        break;
    case FTYPE_UINT:
        value->uvalue++;
        break;
    case FTYPE_LONG:
        value->lvalue++;
        break;
    default:
        printf("FuzuliValueInc: type '%u' is not numeric.\n", value->type);
        if (value->tag != NULL)
        {
            printf("Tagges as: %s\n", value->tag);
        }
    }
}

FuzuliValue *FuzuliValueSumNumeric(FuzuliValue *val1, FuzuliValue *val2)
{
    switch (val1->type)
    {
    case FTYPE_DOUBLE:
        return FuzuliValueCreateDouble(val1->dvalue + val2->dvalue);
        break;
    case FTYPE_FLOAT:
        return FuzuliValueCreateFloat(val1->fvalue + val2->fvalue);
        break;
    case FTYPE_INT:
        return FuzuliValueCreateInteger(val1->ivalue + val2->ivalue);
        break;
    case FTYPE_LONG:
        return FuzuliValueCreateLong(val1->lvalue + val2->lvalue);
        break;
    case FTYPE_UINT:
        return FuzuliValueCreateUnsignedInteger(val1->uvalue + val2->uvalue);
        break;
    default:
        printf("In FuzuliValueSumNumeric, values \n");
        FuzuliValuePrint(val1);
        printf("\nand\n");
        FuzuliValuePrint(val2);
        printf("have different types.\n");
        ErrorAndTerminate("Type differences.", -1);
        break;
    }
    return FuzuliValueCreateNull();
}

FuzuliValue *FuzuliValueProdNumeric(FuzuliValue *val1, FuzuliValue *val2)
{
    switch (val1->type)
    {
    case FTYPE_DOUBLE:
        return FuzuliValueCreateDouble(val1->dvalue * val2->dvalue);
        break;
    case FTYPE_FLOAT:
        return FuzuliValueCreateFloat(val1->fvalue * val2->fvalue);
        break;
    case FTYPE_INT:
        return FuzuliValueCreateInteger(val1->ivalue * val2->ivalue);
        break;
    case FTYPE_LONG:
        return FuzuliValueCreateLong(val1->lvalue * val2->lvalue);
        break;
    case FTYPE_UINT:
        return FuzuliValueCreateUnsignedInteger(val1->uvalue * val2->uvalue);
        break;
    default:
        printf("In FuzuliValueProdNumeric, values \n");
        FuzuliValuePrint(val1);
        printf("\nand\n");
        FuzuliValuePrint(val2);
        printf("have different types.\n");
        ErrorAndTerminate("Type differences.", -1);
        break;
    }
    return FuzuliValueCreateNull();
}

FuzuliValue *FuzuliValueDivideNumeric(FuzuliValue *val1, FuzuliValue *val2)
{
    switch (val1->type)
    {
    case FTYPE_DOUBLE:
        return FuzuliValueCreateDouble(val1->dvalue / val2->dvalue);
        break;
    case FTYPE_FLOAT:
        return FuzuliValueCreateFloat(val1->fvalue / val2->fvalue);
        break;
    case FTYPE_INT:
        return FuzuliValueCreateInteger(val1->ivalue / val2->ivalue);
        break;
    case FTYPE_LONG:
        return FuzuliValueCreateLong(val1->lvalue / val2->lvalue);
        break;
    case FTYPE_UINT:
        return FuzuliValueCreateUnsignedInteger(val1->uvalue / val2->uvalue);
        break;
    default:
        printf("In FuzuliValueDivideNumeric, values \n");
        FuzuliValuePrint(val1);
        printf("\nand\n");
        FuzuliValuePrint(val2);
        printf("have different types.\n");
        ErrorAndTerminate("Type differences.", -1);
        break;
    }
    return FuzuliValueCreateNull();
}

FuzuliValue *FuzuliValueSubtractNumeric(FuzuliValue *val1, FuzuliValue *val2)
{
    switch (val1->type)
    {
    case FTYPE_DOUBLE:
        return FuzuliValueCreateDouble(val1->dvalue - val2->dvalue);
        break;
    case FTYPE_FLOAT:
        return FuzuliValueCreateFloat(val1->fvalue - val2->fvalue);
        break;
    case FTYPE_INT:
        return FuzuliValueCreateInteger(val1->ivalue - val2->ivalue);
        break;
    case FTYPE_LONG:
        return FuzuliValueCreateLong(val1->lvalue - val2->lvalue);
        break;
    case FTYPE_UINT:
        return FuzuliValueCreateUnsignedInteger(val1->uvalue - val2->uvalue);
        break;
    default:
        printf("In FuzuliValueSubtractNumeric, values \n");
        FuzuliValuePrint(val1);
        printf("\nand\n");
        FuzuliValuePrint(val2);
        printf("have different types.\n");
        ErrorAndTerminate("Type differences.", -1);
        break;
    }
    return FuzuliValueCreateNull();
}

double FuzuliValueGetNumericValue(FuzuliValue *val)
{
    switch (val->type)
    {
    case FTYPE_DOUBLE:
        return val->dvalue;
        break;
    case FTYPE_FLOAT:
        return (double)val->fvalue;
        break;
    case FTYPE_INT:
        return (double)val->ivalue;
        break;
    case FTYPE_LONG:
        return (double)val->lvalue;
        break;
    case FTYPE_UINT:
        return (double)val->uvalue;
        break;
    default:
        printf("In FuzuliValueGetNumericValue,  \n");
        FuzuliValuePrint(val);
        printf("cannot convert to double.\n");
        ErrorAndTerminate("Type is not proper.", -1);
        break;
    }
    return -1;
}