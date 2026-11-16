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
	title("ft_isprint\t: ")

	/* 1 */ check(!ft_isprint(' ' - 1)); showLeaks();
	/* 2 */ check(ft_isprint(' ')); showLeaks();
	/* 3 */ check(!ft_isprint('~' + 1)); showLeaks();
	/* 4 */ check(ft_isprint('~')); showLeaks();
	/* 5 */ check(!ft_isprint(-1)); showLeaks();
	/* 6 */ check(!ft_isprint(0)); showLeaks();
	/* 7 */ check(!ft_isprint(31)); showLeaks();
	/* 8 */ check(!ft_isprint(127)); showLeaks();
	/* 9 */ check(!ft_isprint(128)); showLeaks();
	/* 10 */ check(!ft_isprint(255)); showLeaks();
	/* 11 */ check(!ft_isprint('A' + 256)); showLeaks(); //Out of the unsigned char range
	/* 12 */ check(ft_isprint('A')); showLeaks();
	/* 13 */ check(ft_isprint('0')); showLeaks();
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (!!ft_isprint(c) != !!isprint(c)) ok = false;
		/* 14 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}