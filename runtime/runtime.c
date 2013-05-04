#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#undef debug

int getIntPart(double d, int i);
double combineInts(int p1, int p2);
long __add(int x1, int x2, int y1, int y2);
void __println(int x1, int x2);


int getIntPart(double d, int i) {
	int *parts = (int*) &d;
	if (i == 1) {
		return (*parts);
	} else {
		parts++;
		return (*parts);
	}
}

double combineInts(int p1, int p2) {
	int arr[2]; arr[0]=p2; arr[1]=p1;
	double *p = (double*)arr;
	#ifdef debug
	printf("combineInts called with %d and %d and returning %f\n",p1,p2,*p);
	#endif
	return (*p);
}

double combineIntsToLong(int p1, int p2){
	int arr[2]; arr[0]=p2; arr[1]=p1;
	long *l = (long*)arr;
	return(*l);
}

long __add(int x1, int x2, int y1, int y2) {
	double d1 = combineInts(x1, x2);
	double d2 = combineInts(y1, y2);
	double result = d1 + d2;
	int part1 = getIntPart(result,1);
	int part2 = getIntPart(result,2);
	#ifdef debug
	printf("Add called with %f and %f. Return value is %f\n",d1,d2,result);
	#endif
	return(combineIntsToLong(part1,part2));
}

void __println(int x1, int x2){
	double d1 = combineInts(x1,x2);
	printf("%f\n",d1);
}

