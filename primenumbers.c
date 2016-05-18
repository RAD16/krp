/*
 *	Calculates the large prime numbers 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* isprime: returns 1 if p is a prime number, 0 otherwise */
int
isprime(int p)
{
	int pc = p, c = 2;
	
	if (p <= 0)
		return 0;
	
	while (pc-- && c != p) {
		if ((p % c++) == 0) 
			return 0;
	}
	return 1;
}

/* runprime: prints prime numbers up to n
 * returns the number of primes printed. 
 */
int
runprime(int n)
{
	int c = 0, p = 1;
	if (n <= 0)
		return 0;
		
	while (n--) {
		if (isprime(p)) {
			printf("%d\t", p);	
			c++;
		}
		p++;
	}
	printf("\n");
	return c;
}

int
main(int argc, char *argv[]) 
{
	int a;
	int n = atoi(argv[1]);
	
	a = isprime(n);
	
	printf("%d ->", n);
	printf("%s!\n", a ? "Prime!!!" : "bust");
	
	printf("Prime Count: %d\n", runprime(n));

	return 0;
}