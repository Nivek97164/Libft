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
	title("ft_strjoin\t: ")

	char * s = ft_strjoin("tripouille", "42");
	/* 1 */ check(!strcmp(s, "tripouille42"));
	/* 2 */ mcheck(s, strlen("tripouille") + strlen("42") + 1); free(s); showLeaks();

	s = ft_strjoin("", "42");
	/* 3 */ check(!strcmp(s, "42"));
	/* 4 */ mcheck(s, strlen("") + strlen("42") + 1); free(s); showLeaks();

	s = ft_strjoin("42", "");
	/* 5 */ check(!strcmp(s, "42"));
	/* 6 */ mcheck(s, strlen("42") + strlen("") + 1); free(s); showLeaks();

	s = ft_strjoin("", "");
	/* 7 */ check(!strcmp(s, ""));
	/* 8 */ mcheck(s, strlen("") + strlen("") + 1); free(s); showLeaks();
	s = ft_strjoin("a", "b");
	/* 9 */ check(!strcmp(s, "ab"));
	/* 10 */ mcheck(s, 3); free(s); showLeaks();

	s = ft_strjoin("Hello ", "World");
	/* 11 */ check(!strcmp(s, "Hello World"));
	/* 12 */ mcheck(s, 12); free(s); showLeaks();

	s = ft_strjoin(" ", " ");
	/* 13 */ check(!strcmp(s, "  "));
	/* 14 */ mcheck(s, 3); free(s); showLeaks();

	char a[] = "abc", b[] = "def";
	s = ft_strjoin(a, b);
	/* 15 */ check(!strcmp(s, "abcdef") && !strcmp(a, "abc") && !strcmp(b, "def")); //Inputs untouched
	/* 16 */ mcheck(s, 7); free(s); showLeaks();

	string big1(50000, 'a'), big2(50000, 'b');
	s = ft_strjoin(big1.c_str(), big2.c_str());
	/* 17 */ check(strlen(s) == 100000 && s[49999] == 'a' && s[50000] == 'b');
	/* 18 */ mcheck(s, 100001); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}