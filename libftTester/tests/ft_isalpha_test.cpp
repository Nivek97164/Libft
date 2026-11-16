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
	title("ft_isalpha\t: ")

	/* 1 */ check(!ft_isalpha('a' - 1)); showLeaks();
	/* 2 */ check(ft_isalpha('a')); showLeaks();
	/* 3 */ check(!ft_isalpha('z' + 1)); showLeaks();
	/* 4 */ check(ft_isalpha('z')); showLeaks();
	/* 5 */ check(!ft_isalpha('A' - 1)); showLeaks();
	/* 6 */ check(ft_isalpha('A')); showLeaks();
	/* 7 */ check(!ft_isalpha('Z' + 1)); showLeaks();
	/* 8 */ check(ft_isalpha('Z')); showLeaks();
	/* 9 */ check(!ft_isalpha(-1)); showLeaks();
	/* 10 */ check(!ft_isalpha(0)); showLeaks();
	/* 11 */ check(!ft_isalpha('0')); showLeaks();
	/* 12 */ check(!ft_isalpha(' ')); showLeaks();
	/* 13 */ check(!ft_isalpha(127)); showLeaks();
	/* 14 */ check(!ft_isalpha(128)); showLeaks();
	/* 15 */ check(!ft_isalpha(255)); showLeaks();
	/* 16 */ check(!ft_isalpha('a' + 256)); showLeaks(); //Out of the unsigned char range
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (!!ft_isalpha(c) != !!isalpha(c)) ok = false;
		/* 17 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}