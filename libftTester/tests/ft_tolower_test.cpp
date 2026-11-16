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
	title("ft_tolower\t: ")
	
	/* 1 */ check(ft_tolower('A' - 1) == 'A' - 1); showLeaks();
	/* 2 */ check(ft_tolower('A') == 'a'); showLeaks();
	/* 3 */ check(ft_tolower('Z' + 1) == 'Z' + 1); showLeaks();
	/* 4 */ check(ft_tolower('Z') == 'z'); showLeaks();
	/* 5 */ check(ft_tolower('M') == 'm'); showLeaks();
	/* 6 */ check(ft_tolower('m') == 'm'); showLeaks();
	/* 7 */ check(ft_tolower('0') == '0'); showLeaks();
	/* 8 */ check(ft_tolower(' ') == ' '); showLeaks();
	/* 9 */ check(ft_tolower(0) == 0); showLeaks();
	/* 10 */ check(ft_tolower(127) == 127); showLeaks();
	/* 11 */ check(ft_tolower(200) == 200); showLeaks();
	/* 12 */ check(ft_tolower(255) == 255); showLeaks();
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (ft_tolower(c) != tolower(c)) ok = false;
		/* 13 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}