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
#include <ctype.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_isalnum\t: ")

	/* 1 */ check(!ft_isalnum('a' - 1)); showLeaks();
	/* 2 */ check(ft_isalnum('a')); showLeaks();
	/* 3 */ check(!ft_isalnum('z' + 1)); showLeaks();
	/* 4 */ check(ft_isalnum('z')); showLeaks();
	/* 5 */ check(!ft_isalnum('A' - 1)); showLeaks();
	/* 6 */ check(ft_isalnum('A')); showLeaks();
	/* 7 */ check(!ft_isalnum('Z' + 1)); showLeaks();
	/* 8 */ check(ft_isalnum('Z')); showLeaks();
	/* 9 */ check(!ft_isalnum('0' - 1)); showLeaks();
	/* 10 */ check(ft_isalnum('0')); showLeaks();
	/* 11 */ check(!ft_isalnum('9' + 1)); showLeaks();
	/* 12 */ check(ft_isalnum('9')); showLeaks();
	/* 13 */ check(!ft_isalnum(-1)); showLeaks();
	/* 14 */ check(!ft_isalnum(0)); showLeaks();
	/* 15 */ check(!ft_isalnum(' ')); showLeaks();
	/* 16 */ check(!ft_isalnum('_')); showLeaks();
	/* 17 */ check(ft_isalnum('m')); showLeaks();
	/* 18 */ check(ft_isalnum('5')); showLeaks();
	/* 19 */ check(!ft_isalnum(127)); showLeaks();
	/* 20 */ check(!ft_isalnum(128)); showLeaks();
	/* 21 */ check(!ft_isalnum(255)); showLeaks();
	/* 22 */ check(!ft_isalnum('a' + 256)); showLeaks(); //Out of the unsigned char range
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (!!ft_isalnum(c) != !!isalnum(c)) ok = false;
		/* 23 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}