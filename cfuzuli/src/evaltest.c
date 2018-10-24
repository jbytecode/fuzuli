#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../src/fuzulitypes.h"
#include "../src/linkedlist.h"
#include "../src/constants.h"
#include "../src/stringexpression.h"
#include "../src/printexpression.h"
#include "../src/eval.h"

void stringexpression_new_test1(){
    Expression *strexpr = string_expression_new("Hello");
    FuzuliValue *returnvalue = eval(strexpr);
    assert(strcmp(returnvalue->svalue->chars, "Hello") == 0);
}

void printexpression_new_test1(){
    LinkedList *args = LinkedListNew();
    LinkedListAdd(args, FuzuliValueCreateString("\n *** PrintExpression Test ***\n"));
    Expression *printexpr = print_expression_new(args);
    FuzuliValue *returnvalue = eval(printexpr);
    assert(returnvalue->uvalue == TRUE);
}

int main(int argc, char **argv){
	puts("Eval test");
    stringexpression_new_test1();
    printexpression_new_test1();
	return 0;
}
