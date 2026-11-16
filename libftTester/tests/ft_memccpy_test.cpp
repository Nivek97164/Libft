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
	title("ft_memccpy\t: ")
	
	char dest[100];
	memset(dest, 'A', 100);
	/* 1 */ check(ft_memccpy(dest, "coucou", 0, 0) == 0 && dest[0] == 'A'); showLeaks();
	/* 2 */ check(ft_memccpy(dest, "coucou", 0, 1) == 0 && dest[0] == 'c' && dest[1] == 'A'); showLeaks();
	dest[0] = 'A';
	/* 3 */ check(ft_memccpy(dest, "coucou", 'c', 10) == dest + 1 && dest[0] == 'c' && dest[1] == 'A'); showLeaks();
	dest[0] = 'A';
	/* 4 */ check(ft_memccpy(dest, "B", 0, 10) == dest + 2 && dest[0] == 'B' && dest[1] == 0); showLeaks();
	char src[10];
	memset(src, 0, 10);
	/* 5 */ check(ft_memccpy(dest, src, 'A', 10) == NULL); showLeaks();
	int i = 0;
	for (; i < 100 && dest[i] == 0; ++i)
		;
	/* 6 */ check(i == 10); showLeaks();
	memset(dest, 'A', 100);
	/* 7 ecruz-go */ check(ft_memccpy(dest, "42", '2', 1) == 0 && dest[0] == '4' && dest[1] == 'A'); showLeaks();

	char d2[20]; memset(d2, 'A', 20);
	/* 8 */ check(ft_memccpy(d2, "abc", 'c', 3) == d2 + 3 && !memcmp(d2, "abcAAAA", 7)); showLeaks(); //c is the last copied byte
	memset(d2, 'A', 20);
	/* 9 */ check(ft_memccpy(d2, "abc", 'z', 3) == NULL && !memcmp(d2, "abcAAA", 6)); showLeaks(); //Not found: n bytes copied
	memset(d2, 'A', 20);
	/* 10 */ check(ft_memccpy(d2, "abc", 'b' + 256, 3) == d2 + 2 && !memcmp(d2, "abAA", 4)); showLeaks(); //Cast check
	memset(d2, 'A', 20);
	/* 11 */ check(ft_memccpy(d2, "abc", 'a', 3) == d2 + 1 && d2[0] == 'a' && d2[1] == 'A'); showLeaks(); //Stops on first byte
	unsigned char hiSrc[] = {1, 200, 3}, hiDest[3] = {0};
	/* 12 */ check(ft_memccpy(hiDest, hiSrc, 200, 3) == hiDest + 2 && hiDest[0] == 1 && hiDest[1] == 200 && hiDest[2] == 0); showLeaks();

	write(1, "\n", 1);
	return (0);
}