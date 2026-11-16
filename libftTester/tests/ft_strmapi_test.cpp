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
#include <climits>

char addOne(unsigned int i, char c) {return (i + c);}

int iTest = 1;
static char mapUpper(unsigned int, char c) { return (c >= 'a' && c <= 'z') ? c - 32 : c; }
static char mapIndex(unsigned int i, char) { return '0' + i % 10; }
static char mapFirst(unsigned int i, char c) { return i == 0 ? 'F' : c; }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_strmapi\t: ")

	char * s = ft_strmapi("1234", addOne);
	/* 1 */ check(!strcmp(s, "1357"));
	/* 2 */ mcheck(s, strlen("1357") + 1); free(s); showLeaks();

	s = ft_strmapi("", addOne);
	/* 3 */ check(!strcmp(s, ""));
	/* 4 */ mcheck(s, strlen("") + 1); free(s); showLeaks();
	s = ft_strmapi("hello world", mapUpper);
	/* 5 */ check(!strcmp(s, "HELLO WORLD"));
	/* 6 */ mcheck(s, 12); free(s); showLeaks();

	s = ft_strmapi("aaaaaaaaaaaa", mapIndex); //The index is given to f
	/* 7 */ check(!strcmp(s, "012345678901"));
	/* 8 */ mcheck(s, 13); free(s); showLeaks();

	s = ft_strmapi("a", mapIndex);
	/* 9 */ check(!strcmp(s, "0"));
	/* 10 */ mcheck(s, 2); free(s); showLeaks();

	s = ft_strmapi("abc", mapFirst); //Index starts at 0
	/* 11 */ check(!strcmp(s, "Fbc"));
	/* 12 */ mcheck(s, 4); free(s); showLeaks();

	char src[] = "abc";
	s = ft_strmapi(src, mapUpper);
	/* 13 */ check(!strcmp(s, "ABC") && s != src && !strcmp(src, "abc")); //src untouched
	/* 14 */ mcheck(s, 4); free(s); showLeaks();

	string big(100000, 'a');
	s = ft_strmapi(big.c_str(), mapUpper);
	/* 15 */ check(strlen(s) == 100000 && s[0] == 'A' && s[99999] == 'A');
	/* 16 */ mcheck(s, 100001); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}