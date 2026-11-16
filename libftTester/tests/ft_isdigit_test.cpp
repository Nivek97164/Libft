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
	title("ft_isdigit\t: ")

	/* 1 */ check(!ft_isdigit('0' - 1)); showLeaks();
	/* 2 */ check(ft_isdigit('0')); showLeaks();
	/* 3 */ check(!ft_isdigit('9' + 1)); showLeaks();
	/* 4 */ check(ft_isdigit('9')); showLeaks();
	/* 5 */ check(!ft_isdigit(-1)); showLeaks();
	/* 6 */ check(!ft_isdigit(0)); showLeaks();
	/* 7 */ check(!ft_isdigit('a')); showLeaks();
	/* 8 */ check(!ft_isdigit(' ')); showLeaks();
	/* 9 */ check(ft_isdigit('5')); showLeaks();
	/* 10 */ check(!ft_isdigit(128 + '0')); showLeaks();
	/* 11 */ check(!ft_isdigit(255)); showLeaks();
	/* 12 */ check(!ft_isdigit('5' + 256)); showLeaks(); //Out of the unsigned char range
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (!!ft_isdigit(c) != !!isdigit(c)) ok = false;
		/* 13 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}