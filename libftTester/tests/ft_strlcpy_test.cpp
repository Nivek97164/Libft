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
	title("ft_strlcpy\t: ")
	
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);
	/* 1 */ check(ft_strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A'); showLeaks();
	/* 2 */ check(ft_strlcpy(dest, src, 1) == strlen(src) && dest[0] == 0 && dest[1] == 'A'); showLeaks();
	/* 3 */ check(ft_strlcpy(dest, src, 2) == strlen(src) && dest[0] == 'c' && dest[1] == 0  && dest[2] == 'A'); showLeaks();
	/* 4 */ check(ft_strlcpy(dest, src, -1) == strlen(src) && !strcmp(src, dest) && dest[strlen(src) + 1] == 'A'); showLeaks(); memset(dest, 'A', 10);
	/* 5 */ check(ft_strlcpy(dest, src, 6) == strlen(src) && !memcmp(src, dest, 5) && dest[5] == 0); showLeaks(); memset(dest, 'A', 10);
	/* 6 */ check(ft_strlcpy(dest, src, 7) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	/* 7 */ check(ft_strlcpy(dest, src, 8) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	/* 8 */ check(ft_strlcpy(dest, "", 42) == 0 && !memcmp("", dest, 1)); showLeaks(); memset(dest, 0, 10);
	/* 9 */ check(ft_strlcpy(dest, "1", 0) == 1 && dest[0] == 0); showLeaks(); memset(dest, 'A', 10);
	char d2[20]; memset(d2, 'A', 20);
	/* 10 */ check(ft_strlcpy(d2, "hello", 6) == 5 && !strcmp(d2, "hello") && d2[6] == 'A'); showLeaks(); //Exact fit
	memset(d2, 'A', 20);
	/* 11 */ check(ft_strlcpy(d2, "hello", 5) == 5 && !strcmp(d2, "hell") && d2[5] == 'A'); showLeaks(); //Truncated by 1
	memset(d2, 'A', 20);
	/* 12 */ check(ft_strlcpy(d2, "hello", 3) == 5 && !strcmp(d2, "he") && d2[3] == 'A'); showLeaks();
	memset(d2, 'A', 20);
	/* 13 */ check(ft_strlcpy(d2, "", 1) == 0 && d2[0] == 0 && d2[1] == 'A'); showLeaks();
	memset(d2, 'A', 20);
	/* 14 */ check(ft_strlcpy(d2, "", 0) == 0 && d2[0] == 'A'); showLeaks();
	string big(1000, 'x');
	memset(d2, 'A', 20);
	/* 15 */ check(ft_strlcpy(d2, big.c_str(), 10) == 1000 && strlen(d2) == 9 && d2[10] == 'A'); showLeaks(); //Returns the src length
	char srcNul[] = "ab\0cd";
	memset(d2, 'A', 20);
	/* 16 */ check(ft_strlcpy(d2, srcNul, 20) == 2 && !memcmp(d2, "ab\0AAA", 6)); showLeaks(); //Stops at src '\0'

	write(1, "\n", 1);
	return (0);
}