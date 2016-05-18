#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Item Item;
struct Item {
	char *name;
	int value;
};

struct Garray {
	int nval;
	int max;
	Item *item;
} Garray;

enum { TABINIT = 1, TABGROW = 2 };

/* addname: add new name and value to nvtab */
int addname(Item newname) 
{
	Item *ip;
	
	if (Garray.item == NULL) { /* First time */
		Garray.item = (Item *) malloc(TABINIT * sizeof(Item));
		if (Garray.item == NULL)
			return -1;
		Garray.max = TABINIT;
		Garray.nval = 0;
	} else if (Garray.nval >= Garray.max) { 
		ip = (Item *) realloc(Garray.item, 
			(TABGROW * Garray.max) * sizeof(Item));
		if (ip == NULL)
			return -1;
		Garray.max *= TABGROW;
		Garray.item = ip;
	}
	Garray.item[Garray.nval] = newname;
	return Garray.nval++;
}
