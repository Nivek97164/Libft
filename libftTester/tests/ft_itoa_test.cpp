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
#include <climits>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_itoa\t\t: ")

	char * s = ft_itoa(INT_MAX);
	/* 1 */ check(!strcmp(s, to_string(INT_MAX).c_str()));
	/* 2 */ mcheck(s, strlen(to_string(INT_MAX).c_str()) + 1); free(s); showLeaks();

	s = ft_itoa(INT_MIN);
	/* 3 */ check(!strcmp(s, to_string(INT_MIN).c_str()));
	/* 4 */ mcheck(s, strlen(to_string(INT_MIN).c_str()) + 1); free(s); showLeaks();

	s = ft_itoa(0);
	/* 5 */ check(!strcmp(s, to_string(0).c_str()));
	/* 6 */ mcheck(s, strlen(to_string(0).c_str()) + 1); free(s); showLeaks();
	s = ft_itoa(1);
	/* 7 */ check(!strcmp(s, to_string(1).c_str()));
	/* 8 */ mcheck(s, strlen(to_string(1).c_str()) + 1); free(s); showLeaks();
	s = ft_itoa(-1);
	/* 9 */ check(!strcmp(s, to_string(-1).c_str()));
	/* 10 */ mcheck(s, strlen(to_string(-1).c_str()) + 1); free(s); showLeaks();

	s = ft_itoa(42);
	/* 11 */ check(!strcmp(s, to_string(42).c_str()));
	/* 12 */ mcheck(s, strlen(to_string(42).c_str()) + 1); free(s); showLeaks();
	{
		int vals[] = {2, 9, 10, 11, 99, 100, 101, 999, 1000, 12345, 100000, 999999999, 1000000000, 2147483646, 1234567890,
					  -2, -9, -10, -11, -99, -100, -101, -12345, -1000000000, -2147483647};
		bool ok = true;
		for (size_t i = 0; i < sizeof(vals) / sizeof(*vals); ++i)
		{
			s = ft_itoa(vals[i]);
			if (!s || strcmp(s, to_string(vals[i]).c_str())) ok = false;
			free(s);
		}
		/* 13 */ check(ok); showLeaks();
	}
	{
		bool ok = true; //Range around 0 + sweep of the whole int range
		for (int v = -1000; v <= 1000; ++v)
		{
			s = ft_itoa(v);
			if (!s || strcmp(s, to_string(v).c_str())) ok = false;
			free(s);
		}
		for (long long v = INT_MIN; v <= INT_MAX; v += 1000003)
		{
			s = ft_itoa((int)v);
			if (!s || strcmp(s, to_string((int)v).c_str())) ok = false;
			free(s);
		}
		/* 14 */ check(ok); showLeaks();
	}
	s = ft_itoa(-2147483647);
	/* 15 */ mcheck(s, strlen("-2147483647") + 1); free(s); showLeaks();
	s = ft_itoa(100);
	/* 16 */ mcheck(s, strlen("100") + 1); free(s); showLeaks();
	s = ft_itoa(-100);
	/* 17 */ mcheck(s, strlen("-100") + 1); free(s); showLeaks();

	write(1, "\n", 1);
	return (0);
}