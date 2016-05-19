/* rd_strcut: removes the item at the 'index' index
 * of array 's', and returns the length of the mutated string 
 * on success, -1 on failure.
 *
 * e.g. 
 * 	s[] = "foobar";
 * 	rd_strcut(s, 3);
 *	puts(s); // would print 'fooar', return 5. 
 *
 * 	rd_strcut(s, 7);
 *	puts(s); // would print 'foobar', return -1. 
 */

#include <stdio.h>
#include <string.h>
 
size_t 
rd_strcut(char *s, const int index)
{
	char *sp = &s[index];
	
	if (s[index] == '\0' || index > strlen(s))
		return -1;
		
	while (*sp++ = *sp)
		;
		
	return (sp - s - 1);
}

/* ??? rd_strcutv: va_list to allow user to cut as many indices
 * as desired
 */
 
 
int
main(int argc, char *argv[]) 
{
	char s[] = "Stand by me";
	char t[] = "Stinker";
	char *u[] = { "I won't cry", "I won't shed a tear" };
	char v[] = "H";
	
	size_t nlen;
	printf("\'%s\', strlen: %d\n", s, strlen(s));
	
	printf("\'%s\'\n", s);
	nlen = rd_strcut(s, 2);
	printf("\'%s\', nlen: %d\n", s, nlen);
	
	nlen = rd_strcut(s, -2);
	printf("Neg index: \'%s\', nlen: %d\n", s, nlen);
	
	nlen = rd_strcut(t, 6);
	printf("nlen: %d ; \'%s\'\n", nlen, t);
	
	nlen = rd_strcut(t, 12);
	printf("nlen: %d ; \'%s\'\n", nlen, t);
	
	nlen = rd_strcut(v, 0);
	printf("nlen: %d ; \'%s\'\n", nlen, v);
	
	/* 2D arrays break it */
	/*
	printf("\'%s\', strlen: %d\n", u[0], strlen(u[0]));
	printf("\'%s\', strlen: %d\n", u[1], strlen(u[1]));
	printf("nlen: %d ; \'%s\'\n", rd_strcut(*u, 0), u[0]);
	*/
	
	return 0;
}