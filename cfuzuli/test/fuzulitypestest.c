#include <stdio.h>
#include <assert.h>
#include "../src/linkedlist.h"
#include "../src/constants.h"
#include "../src/fuzulitypes.h"
#include "testconstants.h"


void getNumericValue1(){
  FuzuliValue *fval1 = FuzuliValueCreateInteger(10);
  FuzuliValue *fval2 = FuzuliValueCreateDouble(10.0);
  assert(FuzuliValueGetNumericValue(fval1) == FuzuliValueGetNumericValue(fval2));
  printf("%s\n",passed);
}

void getNumericValue2(){
  FuzuliValue *fval1 = FuzuliValueCreateLong(10);
  FuzuliValue *fval2 = FuzuliValueCreateDouble(10.0);
  assert(FuzuliValueGetNumericValue(fval1) == FuzuliValueGetNumericValue(fval2));
  printf("%s\n",passed);
}


int main(int argc, char **argv){
	puts("FuzuliTypes test: ");
	getNumericValue1();
  getNumericValue2();
	return 0;
}
