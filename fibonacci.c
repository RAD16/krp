/*
 *	Calculates the nth number of a fibonacci sequence
 *	where each new number is the sum of the previous two
 *	i.e. 0,1,1,2,3,5,8,13,21,34...
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
fibindex(int n)
{
	int i = n;
	int a, b, c;
	
	a = 0;
	b = 1;
	
	if (n < 1)
		return a;
	
	while(--i) {	
		c = a;
		a += b;
		b = c;
	}
	return a;
}

int
fibindexr(int n, int a, int b)
{
	int c;	
	--n;
	
	if (n < 1)
		return a;
	else {
		c = a;
		a += b;
		b = c;
	}
		
	return fibindexr(n, a, b);
}

int
runfib(int n)
{
	int c = n;
	int i = 1;
	while(c--) {	
		printf("%d\t", fibindex(i++));
	}
	printf("\n");
}

int
main(int argc, char *argv[]) 
{
	int n = atoi(argv[1]);
	int a, b = 0, c = 1;
	
	a = fibindexr(n, b, c);
	printf("recursive - %d\n", a);
	
	b = 0, c = 1;
	a = fibindex(n);
	
	printf("loop - %d\n", a);
	
	return 0;
}