/*
 *	Calculates the nth number of a fibonacci sequence
 *	where each new number is the sum of the previous two
 *	i.e. 0,1,1,2,3,5,8,13,21,34...
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "growarray.h"

int
fibcalc(int n)
{
	int a, b, c;
	
	a = 0;
	b = 1;
	
	while(--n) {	
		c = a;
		a += b;
		b = c;
	}
	return a;
}


int
main(int argc, char *argv[]) 
{
	int n = atoi(argv[1]);
	int a;
	a = fibcalc(n);
	
	printf("%d\n", a);
		

	return 0;
}