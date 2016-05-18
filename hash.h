/*
 * Hash table
 *	chaining hash table implementation adapted
 *	from Kernighan and Pike's "The Practice of
 *	Programming"
 *	My own algorithms denoted with (rad)
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


/*
 * Kernighan and Pike's hash table implementation
 */
 
#define NHASH 57

typedef struct Nameval Nameval;

struct Nameval {
	char *name;
	char *msg;
	Nameval *next;
};

Nameval *symtab[NHASH]; 

enum { MULTIPLIER = 37 };

/* hash: compute hash value of string */
unsigned int hash(char *s)
{
	unsigned int h;
	unsigned char *p;
	
	h = 0;
	for (p = (unsigned char *) s; *p; p++)
		h = MULTIPLIER * h + *p;
	return h % NHASH;
}

/* lookupc: find name in symtab, with optional create */
Nameval *lookupc(char *name, int create, char *msg)
{
	int h;
	Nameval *sym;
	
	h = hash(name);
	for (sym = symtab[h]; sym != NULL; sym = sym->next)
		if (strcmp(name, sym->name) == 0)
			return sym;
	
	if (create) {
		sym = (Nameval *) emalloc(sizeof(Nameval));
		sym->name = strdup(name);
		sym->msg = msg;
		sym->next = symtab[h];
		symtab[h] = sym;
	}
	return sym;
}

/* hashadd: hash item and add it to the table */
Nameval *hashadd(char *name, char *msg)
{
	int h;
	Nameval *sym;
	
	h = hash(name);
	
	sym = (Nameval *) emalloc(sizeof(Nameval));
	sym->name = strdup(name);
	sym->next = symtab[h];
	symtab[h] = sym;
	
	return sym;
}

/* lookup: find name in symtab */
Nameval *lookup(char *name)
{
	int h;
	Nameval *sym;
	
	h = hash(name);
	for (sym = symtab[h]; sym != NULL; sym = sym->next)
		if (strcmp(name, sym->name) == 0)
			return sym;
	return NULL;
}

/* apply: execute fn for each element of listp */
void apply(Nameval *listp, void (*fn)(Nameval *, void*), void *arg)
{
	for ( ; listp != NULL; listp = listp->next)
		(*fn)(listp, arg);
}

/* printnv: print name and value using format in arg */
void printnv(Nameval *p, void *arg)
{
	char *fmt;
	
	fmt = (char *) arg;
	printf(fmt, p->name, p->msg);
}

/*
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
*/
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
/*
/* copyitem: creates a copy of a list item */
Nameval *copyitem(Nameval *item)
{
	Nameval *newp = malloc(sizeof(Nameval));
	
	newp->name = item->name;
	newp->value = item->value;
	newp->next = NULL;
	
	return newp;
}
*/

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

/*
 * grow array? 
 */
 
 
typedef struct Item Item;
struct Item {
	char *name;
	int value;
};

struct table {
	int nval;
	int max;
	Item *item;
} table;

enum { TABINIT = 1, TABGROW = 2 };

/* addname: add new name and value to nvtab */
int addname(Item newname) 
{
	Item *ip;
	
	if (table.item == NULL) { /* First time */
		table.item = (Item *) emalloc(TABINIT * sizeof(Item));
		if (table.item == NULL)
			return -1;
		table.max = TABINIT;
		table.nval = 0;
	} else if (table.nval >= table.max) { 
		ip = (Item *) realloc(table.item, 
			(TABGROW * table.max) * sizeof(Item));
		if (ip == NULL)
			return -1;
		table.max *= TABGROW;
		table.item = ip;
	}
	table.item[table.nval] = newname;
	return table.nval++;
}
