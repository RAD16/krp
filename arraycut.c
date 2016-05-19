#include <stdio.h>
#include <string.h>

/* rd_arraycut: removes the item at the 'index' index
 * of array 's', and returns the length of the mutated string 
 *
 * e.g. 
 * 	s[] = "foobar";
 * 	rd_array(s, 3);
 *	puts(s); // would print 'fooar', return 5. 
 */
 
size_t 
rd_arraycut(char *s, const int index)
{
	char *sp, *osp;
	size_t len;
	
	if (s[index] != '\0' && index < strlen(s) - 1) {
		sp = osp = &s[index];
		
		while (*sp++)
			;
		len = sp - osp;
		
		while (--len)
			*osp++ = *osp;
		
		return (osp - s - 1);
	}
	return 0;
}

/* ??? rd_arraycutv: va_list to allow user to cut as many indices
 * as desired
 */
size_t 
rd_arraycutv(char *s, int index[])
{
	printf("strlen(index): %d\n", (int)strlen(*index));
	char *sp, *osp;
	size_t len;
	/*
	if (s[index] != '\0' && index < strlen(s) - 1) {
		sp = osp = &s[index];
		
		while (*sp++)
			;
		len = sp - osp;
		
		while (--len)
			*osp++ = *osp;
		
		return (osp - s - 1);
	}
	*/
	return 0;
}
int
main(int argc, char *argv[]) 
{
	char s[] = "Stand by me";
	char t[] = "Stinker";
	size_t nlen;
	printf("\'%s\', strlen: %d\n", s, strlen(s));
	
	printf("\'%s\'\n", s);
	nlen = rd_arraycut(s, 2);
	printf("\'%s\', nlen: %d\n", s, nlen);
	
	nlen = rd_arraycut(t,12);
	printf("nlen: %d ; \'%s\'\n", rd_arraycut(t, -12), t);
	
	rd_arraycutv(t,12);
	
	return 0;
}