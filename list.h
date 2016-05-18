/*
 * List
 * 	singly-linked list implementation adapted
 *	from Kernighan and Pike's "The Practice of 
 *	Programming."
 *	My own algorithms are denoted with (rad)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* emalloc: malloc and report if error */
void *emalloc(size_t n)
{
	void *p;
	
	p = malloc(n);
	if (p == NULL)
		printf("malloc of %u bytes failed:", n);
	return p;
}

typedef struct Nameval Nameval;
struct Nameval {
	char *name;
	int value;
	Nameval *next;
};

/*
 *	Functions for working with lists
 */
 

/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value)
{
	Nameval *newp;
	
	newp = (Nameval *) emalloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->next = NULL;
	
	return newp;
}

/* copyitem: creates a copy of a list item */
Nameval *copyitem(Nameval *item)
{
	Nameval *newp = malloc(sizeof(Nameval));
	
	newp->name = item->name;
	newp->value = item->value;
	newp->next = NULL;
	
	return newp;
}

/* addfront: add newp to front of listp */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
	newp->next = listp;
	return newp;
}

/* addend: add newp to end of listp */
Nameval *addend(Nameval *listp, Nameval *newp)
{
	Nameval *p;

	if (listp == NULL)
		return newp;
	
	for (p = listp; p->next != NULL; p = p->next)
		;
	
	p->next = newp;
	
	return listp;

}

/* addafter: add newp after item in listp (rad) */
void addafter(Nameval *listp, Nameval *item, Nameval *newp)
{
	Nameval *p, *next;
	
	for (p = listp; p; p = p->next) {
		if (strcmp(item->name, p->name) == 0) {
			next = p->next;	
			p->next = newp;
			newp->next = next;
		}
	}
}

/* copylist: create a copy of a list */

/* lookup: sequential search for name in listp */
Nameval *lookup(Nameval *listp, char *name)
{
	for (; listp != NULL; listp = listp->next)
		if (strcmp(name, listp->name) == 0)
			return listp;

	return NULL;
}

/* apply: execute fn for each element of listp */ 
void apply(Nameval *listp, void (*fn)(Nameval *, void *), void *arg)
{
	for ( ; listp != NULL; listp = listp->next)
		(*fn)(listp, arg);
}

/* printnv: print name and value using format in arg */
void printnv(Nameval *p, void *arg)
{
	char *fmt;
	
	fmt = (char *) arg;
	printf(fmt, p->name, p->value);
}

/* inccounter: increment counter *arg */
void inccounter(Nameval *p, void *arg)
{
	int *ip;

	/* p is unused */
	ip = (int *) arg;
	(*ip)++;
}

/* reverse: reverse the order of list elements (rad) */
Nameval *reverse(Nameval *listp)
{
	Nameval *p, *head, *next, *prev;
	
	head = listp;
	prev = NULL;

	for (p = listp; p; p = next) {
		next = p->next;
		if (next == NULL) {
			p->next = prev;
			head->next = NULL;
			return p;
		} else 
			p->next = prev;
		prev = p;
	}
}

/* reverse_2: reverse the order of list elements, recursive (rad) */
Nameval *reverse_2(Nameval *prev, Nameval *listp)
{
	Nameval *next;
	
	next = listp->next;
	listp->next = prev;
	
	if (next == NULL)
		return listp;
	
	reverse_2(listp, next);
}

/* freeall: free all elements of a list */
void freeall(Nameval *listp)
{
	Nameval *next;

	for (; listp != NULL; listp = next) {
		next = listp->next;
		/* assumes name is freed elsewhere */
		free(listp);
	}
}

/* delitem: delete first "name" from listp */
Nameval *delitem(Nameval *listp, char *name)
{
	Nameval *p, *prev;

	prev = NULL;
	for (p = listp; p != NULL; p = p->next) {
		if (strcmp(name, p->name) == 0) {
			if ( prev == NULL)
				listp = p->next;
			else
				prev->next = p->next;
			free(p);
			return listp;
		}
		prev = p;
	}
	printf("delitem: %s not in list", name);
	return NULL;
}

