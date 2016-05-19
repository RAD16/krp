#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


size_t 
rd_arraycut(char *s, const int index)
{
	char *sp, *osp;
	size_t len;
	
	sp = osp = &s[index];
	
	while (*sp++ != '\0')
		;
	len = sp - osp;
	
	while ( --len)
		*osp++ = *osp;
	
	return osp - s - 1;
}

int
main(int argc, char *argv[]) 
{
	char s[] = "Stand by me";
	size_t nlen;
	printf("\'%s\', strlen: %d\n", s, strlen(s));
	
	printf("\'%s\'\n", s);
	nlen = rd_arraycut(s, 2);
	printf("\'%s\', nlen: %d\n", s, nlen);
	
	return 0;
}