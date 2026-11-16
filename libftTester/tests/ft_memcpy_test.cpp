extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_memcpy\t: ")
	
	char dest[100];
	memset(dest, 'A', 100);
	ft_memcpy(dest, "coucou", 0);
	/* 1 */ check(dest[0] == 'A'); showLeaks();
	char *rtn = (char *)ft_memcpy(dest, NULL, 0);
	/* 2 */ check(rtn == dest && dest[0] == 'A'); showLeaks();
	char src[] = {0, 0};
	ft_memcpy(dest, src, 2);
	int i = 0;
	for (; i < 100 && dest[i] == 0; ++i)
		;
	/* 3 */ check(i == 2 && dest[2] == 'A'); showLeaks();
	memset(dest, 'A', 100);
	/* 4 */ check(ft_memcpy(dest, "12345", 5) == dest && !memcmp(dest, "12345AAAAA", 10)); showLeaks();
	memset(dest, 'A', 100);
	ft_memcpy(dest + 1, "xyz", 2);
	/* 5 */ check(!memcmp(dest, "AxyAAAAAAA", 10)); showLeaks(); //Copies exactly n bytes
	unsigned char bin[] = {0, 255, 128, 0, 1};
	unsigned char binDest[5];
	ft_memcpy(binDest, bin, 5);
	/* 6 */ check(!memcmp(binDest, bin, 5)); showLeaks(); //Binary data, not a string copy
	/* 7 */ check(ft_memcpy(dest, dest, 10) == dest); showLeaks();
	/* 8 */ check(ft_memcpy(dest, "x", 0) == dest); showLeaks();
	/* 9 */ check(ft_memcpy(NULL, NULL, 0) == NULL); showLeaks();
	unsigned char * bigSrc = (unsigned char *)malloc(100000);
	unsigned char * bigDest = (unsigned char *)malloc(100000);
	for (int j = 0; j < 100000; ++j) bigSrc[j] = j % 251;
	ft_memcpy(bigDest, bigSrc, 100000);
	/* 10 */ check(!memcmp(bigDest, bigSrc, 100000)); free(bigSrc); free(bigDest); showLeaks();

	write(1, "\n", 1);
	return (0);
}
