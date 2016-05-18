/*
 *	Functions pertaining to the fibonacci sequence,
 *	where each new number is the sum of the previous two
 *	i.e. 0,1,1,2,3,5,8,13,21,34...
 */
 
#include <stdio.h>
#include <stdlib.h>

/* fibindexl: return nth fibonacci number using a loop */
int
fibindexl(int n)
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

/* fibindexr: return the nth fibonacci number using tail recursion */
int
fibindexr(int n, int a, int b)
{
	int c;	
	
	if (--n < 1)
		return a;
	else {
		c = a;
		a += b;
		b = c;
	}
		
	return fibindexr(n, a, b);
}

/* runfib: print n fibonacci numbers */
void
runfib(int n)
{
	int c = n;
	int i = 1;
	
	while(c--) {	
		printf("%d\t", fibindexl(i++));
	}
	printf("\n");
}

/* fibrange: print fibonacci numbers less than or equan to n */
void
fibrange(int n)
{
	int c = n;
	int i = 0;
	
	while(fibindexl(i++) <= n) {	
		if (fibindexl(i) <= n)
			printf("%d\t", fibindexl(i));
		else
			break;
	}
	printf("\n");
}

int
main(int argc, char *argv[]) 
{
	int a, b, c;
	int n = atoi(argv[1]);
	
	printf("Fibonacci Number %d:\n", n);
	
	/* Looping fibindex */
	a = fibindexl(n);
	printf("\t%d (looping)\n", a);
	
	/* Recursive fibindex */
	b = 0, c = 1;
	a = fibindexr(n, b, c);
	printf("\t%d (recursive)\n", a);
	
	/* Print fib numbers <= n */
	printf("Fibonacci Numbers <= %d:\n", n);
	fibrange(n);
	
	/* Print n fib numbers */
	printf("Printing %d Fibonacci Numbers\n", n);
	runfib(n);
	
	return 0;
}