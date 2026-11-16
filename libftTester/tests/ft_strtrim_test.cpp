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
	title("ft_strtrim\t: ")

	char * s = ft_strtrim("   xxxtripouille", " x");
	/* 1 */ check(!strcmp(s, "tripouille"));
	/* 2 */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	s = ft_strtrim("tripouille   xxx", " x");
	/* 3 */ check(!strcmp(s, "tripouille"));
	/* 4 */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();

	s = ft_strtrim("   xxxtripouille   xxx", " x");
	/* 5 */ check(!strcmp(s, "tripouille"));
	/* 6 */ mcheck(s, strlen("tripouille") + 1); free(s); showLeaks();
	
	s = ft_strtrim("   xxx   xxx", " x");
	/* 7 */ check(!strcmp(s, ""));
	/* 8 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_strtrim("", "123");
	/* 9 */ check(!strcmp(s, ""));
	/* 10 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_strtrim("123", "");
	/* 11 */ check(!strcmp(s, "123"));
	/* 12 */ mcheck(s, 4); free(s); showLeaks();

	s = ft_strtrim("", "");
	/* 13 */ check(!strcmp(s, ""));
	/* 14 */ mcheck(s, 1); free(s); showLeaks();
	
	s = ft_strtrim("abcdba", "acb");
	/* opsec-infosec 15 */ check(!strcmp(s, "d"));
 	/* opsec-infosec 16 */ mcheck(s, 2); free(s); showLeaks();

	s = ft_strtrim("ababa", "a");
	/* mogiyadev 17 */ check(!strcmp(s, "bab"));
 	/* mogiyadev 18 */ mcheck(s, 4); free(s); showLeaks();

	s = ft_strtrim("xxhixx", "x");
	/* 19 */ check(!strcmp(s, "hi"));
	/* 20 */ mcheck(s, 3); free(s); showLeaks();

	s = ft_strtrim("hello", "xyz"); //Nothing to trim
	/* 21 */ check(!strcmp(s, "hello"));
	/* 22 */ mcheck(s, 6); free(s); showLeaks();

	s = ft_strtrim("xxxx", "x"); //Everything trimmed
	/* 23 */ check(!strcmp(s, ""));
	/* 24 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_strtrim("\t\n hello \n\t", " \t\n");
	/* 25 */ check(!strcmp(s, "hello"));
	/* 26 */ mcheck(s, 6); free(s); showLeaks();

	s = ft_strtrim("xaxbx", "x"); //Inner chars are kept
	/* 27 */ check(!strcmp(s, "axb"));
	/* 28 */ mcheck(s, 4); free(s); showLeaks();

	s = ft_strtrim("hello", "h"); //Start only
	/* 29 */ check(!strcmp(s, "ello"));
	/* 30 */ mcheck(s, 5); free(s); showLeaks();

	s = ft_strtrim("hello", "o"); //End only
	/* 31 */ check(!strcmp(s, "hell"));
	/* 32 */ mcheck(s, 5); free(s); showLeaks();

	s = ft_strtrim("hello", "hello");
	/* 33 */ check(!strcmp(s, ""));
	/* 34 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_strtrim("a", "a");
	/* 35 */ check(!strcmp(s, ""));
	/* 36 */ mcheck(s, 1); free(s); showLeaks();

	s = ft_strtrim("a", "b");
	/* 37 */ check(!strcmp(s, "a"));
	/* 38 */ mcheck(s, 2); free(s); showLeaks();

	s = ft_strtrim("hello world", "dh");
	/* 39 */ check(!strcmp(s, "ello worl"));
	/* 40 */ mcheck(s, 10); free(s); showLeaks();

	s = ft_strtrim("abcXabc", "cba"); //Order of the set doesn't matter
	/* 41 */ check(!strcmp(s, "X"));
	/* 42 */ mcheck(s, 2); free(s); showLeaks();

	char src[] = "  hi  ";
	s = ft_strtrim(src, " ");
	/* 43 */ check(!strcmp(s, "hi") && !strcmp(src, "  hi  ")); //src untouched
	/* 44 */ mcheck(s, 3); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}
