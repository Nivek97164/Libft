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
	title("ft_memcmp\t: ")

	char s[] = {'\x80', 0, 127, 0};
	char sCpy[] = {'\x80', 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
	/* 1 */ check(!ft_memcmp(s, sCpy, 4)); showLeaks();
	/* 2 */ check(!ft_memcmp(s, s2, 0)); showLeaks();
	/* 3 */ check(ft_memcmp(s, s2, 1) > 0); showLeaks();
	/* 4 */ check(ft_memcmp(s2, s, 1) < 0); showLeaks();
	/* 5 */ check(ft_memcmp(s2, s3, 4) != 0); showLeaks();
	/* 6 */ check(ft_memcmp("abc", "abc", 3) == 0); showLeaks();
	/* 7 */ check(ft_memcmp("abc", "abd", 2) == 0); showLeaks(); //Difference is after n
	/* 8 */ check(ft_memcmp("abc", "abd", 3) < 0); showLeaks();
	/* 9 */ check(ft_memcmp("abd", "abc", 3) > 0); showLeaks();
	/* 10 */ check(ft_memcmp("a", "b", 1) < 0); showLeaks();
	unsigned char hiA[] = {0x7f, 0x80}, hiB[] = {0x7f, 0x7f};
	/* 11 */ check(ft_memcmp(hiA, hiB, 2) > 0); showLeaks(); //Unsigned comparison
	/* 12 */ check(ft_memcmp(hiB, hiA, 2) < 0); showLeaks();
	char nul1[] = {'a', 'b', 0, 'c', 'd'}, nul2[] = {'a', 'b', 0, 'c', 'e'};
	/* 13 */ check(ft_memcmp(nul1, nul2, 5) < 0); showLeaks(); //Must not stop at '\0'
	/* 14 */ check(ft_memcmp(nul1, nul2, 4) == 0); showLeaks();
	{
		auto sign = [](int x) { return (x > 0) - (x < 0); };
		bool ok = true; //Every pair of bytes compared to the libc
		for (int i = 0; i < 256; ++i)
			for (int j = 0; j < 256; ++j)
			{
				unsigned char a = i, b = j;
				if (sign(ft_memcmp(&a, &b, 1)) != sign(memcmp(&a, &b, 1))) ok = false;
			}
		/* 15 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}