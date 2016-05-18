/*
 *	quicksort: simple array sorting algorithm
 *
 *	derived from:
 *	"The Practice of Programming"
 *	Brian Kernighan and Rob Pike
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
swap(int v[], int i, int j)
{
	int temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void
quicksort(int v[], int n)
{
	int pivot, i, last;
	
	if (n <= 1)
		return;
/*	swap(v, 0, rand() % n);  original */
	pivot = (n / 2);
	swap(v, 0, pivot);
	last = 0;
	for (i = 1; i < n; i++)
		if (v[i] < v[0])
			swap(v, ++last, i);
	swap(v, 0, last);
	quicksort(v, last);
	quicksort(v+last+1, n-last-1);
}
