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
	title("ft_strchr\t: ")
	char s[] = "tripouille";
	/* 1 */ check(ft_strchr(s, 't') == s); showLeaks();
	/* 2 */ check(ft_strchr(s, 'l') == s + 7); showLeaks();
	/* 3 */ check(ft_strchr(s, 'z') == 0); showLeaks();
	/* 4 */ check(ft_strchr(s, 0) == s + strlen(s)); showLeaks();
	/* 5 */ check(ft_strchr(s, 't' + 256) == s); showLeaks();
	char s2[] = "tripouille";
	/* 6 */ check(ft_strchr(s2, 'i') == s2 + 2); showLeaks(); //First occurrence
	/* 7 */ check(ft_strchr(s2, 'e') == s2 + 9); showLeaks(); //Last char
	/* 8 */ check(ft_strchr(s2, 'T') == NULL); showLeaks(); //Case sensitive
	/* 9 */ check(ft_strchr(s2, 0 + 256) == s2 + strlen(s2)); showLeaks(); //Cast check on '\0'
	char empty[] = "";
	/* 10 */ check(ft_strchr(empty, 'a') == NULL); showLeaks();
	/* 11 */ check(ft_strchr(empty, 0) == empty); showLeaks();
	char withNul[] = "ab\0cd";
	/* 12 */ check(ft_strchr(withNul, 'c') == NULL); showLeaks(); //Must stop at '\0'
	char highBit[] = "a\xe9z";
	/* 13 */ check(ft_strchr(highBit, 233) == highBit + 1); showLeaks();
	{
		bool ok = true; //Every value compared to the libc
		for (int c = 0; c < 512; ++c)
			if (ft_strchr(s2, c) != strchr(s2, c)) ok = false;
		/* 14 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}