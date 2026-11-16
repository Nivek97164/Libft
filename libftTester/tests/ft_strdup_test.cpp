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
	title("ft_strdup\t: ")

	char * s = ft_strdup((char*)"coucou");
	/* 1 */ check(!strcmp(s, "coucou"));
	/* 2 */ mcheck(s, strlen("coucou") + 1); free(s); showLeaks();
	
	s = ft_strdup((char*)"");
	/* 3 */ check(!strcmp(s, ""));
	/* 4 */ mcheck(s, 1); free(s); showLeaks();
	char orig[] = "hello";
	s = ft_strdup(orig);
	/* 5 */ check(s != orig && !strcmp(s, "hello"));
	orig[0] = 'J';
	/* 6 */ check(!strcmp(s, "hello")); //Independent copy
	/* 7 */ mcheck(s, 6); free(s); showLeaks();

	string big(100000, 'x');
	s = ft_strdup((char *)big.c_str());
	/* 8 */ check(strlen(s) == 100000 && !strcmp(s, big.c_str()));
	/* 9 */ mcheck(s, 100001); free(s); showLeaks();

	char withNul[] = "ab\0cd";
	s = ft_strdup(withNul);
	/* 10 */ check(!strcmp(s, "ab") && s[2] == 0);
	/* 11 */ mcheck(s, 3); free(s); showLeaks();

	s = ft_strdup((char *)"\xc3\xa9t\xc3\xa9");
	/* 12 */ check(!strcmp(s, "\xc3\xa9t\xc3\xa9"));
	/* 13 */ mcheck(s, 6); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}