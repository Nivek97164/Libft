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
#include <limits.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_strncmp\t: ")
	
	/* 1 */ check(ft_strncmp("t", "", 0) == 0); showLeaks();
	/* 2 */ check(ft_strncmp("1234", "1235", 3) == 0); showLeaks();
	/* 3 */ check(ft_strncmp("1234", "1235", 4) < 0); showLeaks();
	/* 4 */ check(ft_strncmp("1234", "1235", -1) < 0); showLeaks();
	/* 5 */ check(ft_strncmp("", "", 42) == 0); showLeaks();
	/* 6 */ check(ft_strncmp("Tripouille", "Tripouille", 42) == 0); showLeaks();
	/* 7 */ check(ft_strncmp("Tripouille", "tripouille", 42) < 0); showLeaks();
	/* 8 */ check(ft_strncmp("Tripouille", "TriPouille", 42) > 0); showLeaks();
	/* 9 */ check(ft_strncmp("Tripouille", "TripouillE", 42) > 0); showLeaks();
	/* 10 */ check(ft_strncmp("Tripouille", "TripouilleX", 42) < 0); showLeaks();
	/* 11 */ check(ft_strncmp("Tripouille", "Tripouill", 42) > 0); showLeaks();
	/* 12 */ check(ft_strncmp("", "1", 0) == 0); showLeaks();
	/* 13 */ check(ft_strncmp("1", "", 0) == 0); showLeaks();
	/* 14 */ check(ft_strncmp("", "1", 1) < 0); showLeaks();
	/* 15 */ check(ft_strncmp("1", "", 1) > 0); showLeaks();
	/* 16 */ check(ft_strncmp("", "", 1) == 0); showLeaks();

	/* ohaponiuk */
	/* Check correct behavior for negative char values.
	 * This matches the behavior of libc strncmp.*/
	signed char	str1[] = "test";
	signed char	str2[] = "test";
	size_t		len = strlen((const char *)str1);
	auto sign = [](int x) { return (x > 0) - (x < 0); };
	str2[3] = SCHAR_MIN;
	/* 17 */ check(sign(ft_strncmp((const char *)str1, (const char *)str2, len)) == sign(strncmp((const char *)str1, (const char *)str2, len))); showLeaks();
	str2[3] = -42;
	/* 18 */ check(sign(ft_strncmp((const char *)str1, (const char *)str2, len)) == sign(strncmp((const char *)str1, (const char *)str2, len))); showLeaks();

	/* 19 */ check(ft_strncmp("abc", "abc", 3) == 0); showLeaks();
	/* 20 */ check(ft_strncmp("abc", "abd", 2) == 0); showLeaks(); //Difference is after n
	/* 21 */ check(ft_strncmp("abc", "abd", 3) < 0); showLeaks();
	/* 22 */ check(ft_strncmp("abd", "abc", 3) > 0); showLeaks();
	/* 23 */ check(ft_strncmp("abc", "abcd", 3) == 0); showLeaks();
	/* 24 */ check(ft_strncmp("abc", "abcd", 4) < 0); showLeaks();
	/* 25 */ check(ft_strncmp("abcd", "abc", 4) > 0); showLeaks();
	char nulA[] = {'a', 'b', 0, 'c', 'd', 0}, nulB[] = {'a', 'b', 0, 'c', 'e', 0};
	/* 26 */ check(ft_strncmp(nulA, nulB, 5) == 0); showLeaks(); //Must stop at '\0'
	char hiA[] = {(char)0x80, 0}, hiB[] = {0x7f, 0};
	/* 27 */ check(ft_strncmp(hiA, hiB, 1) > 0); showLeaks(); //Unsigned comparison
	/* 28 */ check(ft_strncmp(hiB, hiA, 1) < 0); showLeaks();
	/* 29 */ check(ft_strncmp(hiA, "", 1) > 0); showLeaks();
	{
		bool ok = true; //Every pair of chars compared to the libc
		for (int i = 0; i < 256; ++i)
			for (int j = 0; j < 256; ++j)
			{
				char a[2] = {(char)i, 0}, b[2] = {(char)j, 0};
				if (sign(ft_strncmp(a, b, 2)) != sign(strncmp(a, b, 2))) ok = false;
				if (sign(ft_strncmp(a, b, 1)) != sign(strncmp(a, b, 1))) ok = false;
			}
		/* 30 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
