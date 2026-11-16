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
#include <stdint.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_substr\t: ")

	char * s = ft_substr("tripouille", 0, 42000);
	/* 1 */ check(!strcmp(s, "tripouille"));
	/* 2 */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	s = ft_substr("tripouille", 1, 1);
	/* 3 */ check(!strcmp(s, "r"));
	/* 4 */ mcheck(s, 2); free(s); showLeaks();

	s = ft_substr("tripouille", 100, 1);
	/* 5 */ check(!strcmp(s, ""));
	/* 6 */ mcheck(s, 1); free(s); showLeaks();

	char * str = strdup("1");
	s = ft_substr(str, 42, 42000000);
	/* 7 */ check(!strcmp(s, ""));
	/* 8 */ mcheck(s, 1); free(s); free(str); showLeaks();

	str = strdup("0123456789");
	s = ft_substr(str, 9, 10);
	/* 9  mbueno-g */ check(!strcmp(s, "9"));
	/* 10  mbueno-g */ mcheck(s, 2); free(s); free(str); showLeaks();

	s = ft_substr("42", 0, 0);
	/* 11  fcaquard */ check(!strcmp(s, ""));
	/* 12  fcaquard */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("BONJOUR LES HARICOTS !", 8, 14);
	/* 13  dfarhi */ check(!strcmp(s, "LES HARICOTS !"));
	/* 14  dfarhi */ mcheck(s, 15); free(s); showLeaks();

	s = ft_substr("test", 1, 2);
	/* 15  dfarhi */ check(!strcmp(s, "es"));
	/* 16  dfarhi */ mcheck(s, 3); free(s); showLeaks();

	s = ft_substr("hello", 0, 5);
	/* 17 */ check(!strcmp(s, "hello"));
	/* 18 */ mcheck(s, 6); free(s); showLeaks();

	s = ft_substr("hello", 0, 3);
	/* 19 */ check(!strcmp(s, "hel"));
	/* 20 */ mcheck(s, 4); free(s); showLeaks();

	s = ft_substr("hello", 2, 2);
	/* 21 */ check(!strcmp(s, "ll"));
	/* 22 */ mcheck(s, 3); free(s); showLeaks();

	s = ft_substr("hello", 4, 10);
	/* 23 */ check(!strcmp(s, "o"));
	/* 24 */ mcheck(s, 2); free(s); showLeaks();

	s = ft_substr("hello", 5, 3); //start == strlen
	/* 25 */ check(!strcmp(s, ""));
	/* 26 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("hello", 6, 3); //start == strlen + 1
	/* 27 */ check(!strcmp(s, ""));
	/* 28 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("", 0, 5);
	/* 29 */ check(!strcmp(s, ""));
	/* 30 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("hello", 1, 0);
	/* 31 */ check(!strcmp(s, ""));
	/* 32 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_substr("hello", 1, SIZE_MAX); //start + len overflow
	/* 33 */ check(!strcmp(s, "ello"));
	/* 34 */ mcheck(s, 5); free(s); showLeaks();

	char src[] = "abcdef";
	s = ft_substr(src, 2, 3);
	/* 35 */ check(!strcmp(s, "cde") && s != src + 2 && !strcmp(src, "abcdef")); //Real copy, src untouched
	/* 36 */ mcheck(s, 4); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
