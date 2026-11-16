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
	title("ft_isascii\t: ")

	/* 1 */ check(!ft_isascii(-1)); showLeaks();
	/* 2 */ check(ft_isascii(0)); showLeaks();
	/* 3 */ check(!ft_isascii(128)); showLeaks();
	/* 4 */ check(ft_isascii(127)); showLeaks();
	/* 5 */ check(ft_isascii('A')); showLeaks();
	/* 6 */ check(ft_isascii(' ')); showLeaks();
	/* 7 */ check(!ft_isascii(255)); showLeaks();
	/* 8 */ check(!ft_isascii(256)); showLeaks();
	/* 9 */ check(!ft_isascii(-128)); showLeaks();
	/* 10 */ check(!ft_isascii(1000)); showLeaks();
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (!!ft_isascii(c) != !!isascii(c)) ok = false;
		/* 11 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}