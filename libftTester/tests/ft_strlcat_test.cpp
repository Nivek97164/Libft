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
	title("ft_strlcat\t: ")
	
	char dest[30]; memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	dest[0] = 'B';
	/* 1 */ check(ft_strlcat(dest, src, 0) == strlen(src) && !strcmp(dest, "B")); showLeaks();
	dest[0] = 'B';
	/* 2 */ check(ft_strlcat(dest, src, 1) == 10 && !strcmp(dest, "B")); showLeaks();
	memset(dest, 'B', 4);
	/* 3 */ check(ft_strlcat(dest, src, 3) == 3 + strlen(src) && !strcmp(dest, "BBBB")); showLeaks();
	/* 4 */ check(ft_strlcat(dest, src, 6) == 13 && !strcmp(dest, "BBBBA")); showLeaks();
	memset(dest, 'C', 5);
	/* 5 */ check(ft_strlcat(dest, src, -1) == 14 && !strcmp(dest, "CCCCCAAAAAAAAA")); showLeaks();
	memset(dest, 'C', 15);
	/* 6 */ check(ft_strlcat(dest, src, 17) == 24 && !strcmp(dest, "CCCCCCCCCCCCCCCA")); showLeaks();
	memset(dest, 0, 30);
	/* 7 */ check(ft_strlcat(dest, src, 1) == strlen(src) && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 8 */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 9 */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30); memset(dest, '1', 10);
	/* 10 */ check(ft_strlcat(dest, "", 15) == 10 && !strcmp(dest, "1111111111")); showLeaks();
	memset(dest, 0, 30);
	/* 11 */ check(ft_strlcat(dest, "", 42) == 0 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 12 */ check(ft_strlcat(dest, "", 0) == 0 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 13 */ check(ft_strlcat(dest, "123", 1) == 3 && !strcmp(dest, "")); showLeaks();
	memset(dest, 0, 30);
	/* 14 */ check(ft_strlcat(dest, "123", 2) == 3 && !strcmp(dest, "1")); showLeaks();
	memset(dest, 0, 30);
	/* 15 */ check(ft_strlcat(dest, "123", 3) == 3 && !strcmp(dest, "12")); showLeaks();
	memset(dest, 0, 30);
	/* 16 */ check(ft_strlcat(dest, "123", 4) == 3 && !strcmp(dest, "123")); showLeaks();
	memset(dest, 0, 30);
	/* 17 */ check(ft_strlcat(dest, "123", 0) == 3 && !strcmp(dest, "")); showLeaks();
	char d2[30];
	memset(d2, 0, 30); strcpy(d2, "Hello");
	/* 18 */ check(ft_strlcat(d2, " World", 30) == 11 && !strcmp(d2, "Hello World")); showLeaks();
	memset(d2, 0, 30); strcpy(d2, "Hello");
	/* 19 */ check(ft_strlcat(d2, " World", 12) == 11 && !strcmp(d2, "Hello World")); showLeaks(); //Exact fit
	memset(d2, 0, 30); strcpy(d2, "Hello");
	/* 20 */ check(ft_strlcat(d2, " World", 11) == 11 && !strcmp(d2, "Hello Worl")); showLeaks(); //Truncated by 1
	memset(d2, 0, 30); strcpy(d2, "Hello");
	/* 21 */ check(ft_strlcat(d2, "World", 5) == 10 && !strcmp(d2, "Hello")); showLeaks(); //size == strlen(dst)
	memset(d2, 0, 30); strcpy(d2, "Hello");
	/* 22 */ check(ft_strlcat(d2, "World", 6) == 10 && !strcmp(d2, "Hello")); showLeaks(); //No room left
	memset(d2, 0, 30);
	/* 23 */ check(ft_strlcat(d2, "abc", 30) == 3 && !strcmp(d2, "abc")); showLeaks(); //Empty dst
	memset(d2, 0, 30);
	ft_strlcat(d2, "ab", 30);
	/* 24 */ check(ft_strlcat(d2, "cd", 30) == 4 && !strcmp(d2, "abcd")); showLeaks(); //Two calls in a row
	memset(d2, 'Z', 30); d2[0] = 'a'; d2[1] = 0;
	/* 25 */ check(ft_strlcat(d2, "bcdef", 4) == 6 && !strcmp(d2, "abc") && d2[4] == 'Z'); showLeaks(); //No write past size
	string big(1000, 'x');
	memset(d2, 0, 30);
	/* 26 */ check(ft_strlcat(d2, big.c_str(), 30) == 1000 && strlen(d2) == 29); showLeaks();

	write(1, "\n", 1);
	return (0);
}