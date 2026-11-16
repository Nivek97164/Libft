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
	title("ft_toupper\t: ")
	
	/* 1 */ check(ft_toupper('a' - 1) == 'a' - 1); showLeaks();
	/* 2 */ check(ft_toupper('a') == 'A'); showLeaks();
	/* 3 */ check(ft_toupper('z' + 1) == 'z' + 1); showLeaks();
	/* 4 */ check(ft_toupper('z') == 'Z'); showLeaks();
	/* 5 */ check(ft_toupper('m') == 'M'); showLeaks();
	/* 6 */ check(ft_toupper('M') == 'M'); showLeaks();
	/* 7 */ check(ft_toupper('0') == '0'); showLeaks();
	/* 8 */ check(ft_toupper(' ') == ' '); showLeaks();
	/* 9 */ check(ft_toupper(0) == 0); showLeaks();
	/* 10 */ check(ft_toupper(127) == 127); showLeaks();
	/* 11 */ check(ft_toupper(200) == 200); showLeaks();
	/* 12 */ check(ft_toupper(255) == 255); showLeaks();
	{
		bool ok = true;
		for (int c = 0; c < 256; ++c)
			if (ft_toupper(c) != toupper(c)) ok = false;
		/* 13 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}