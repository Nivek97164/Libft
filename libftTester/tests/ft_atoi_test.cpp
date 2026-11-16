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
	title("ft_atoi\t\t: ")

	char escape[] = {9, 10, 11, 12, 13, 0};
	string e(escape);
	/* 1 */ check(ft_atoi((e + "1").c_str()) == 1); showLeaks();
	/* 2 */ check(ft_atoi((e + "a1").c_str()) == 0); showLeaks();
	/* 3 */ check(ft_atoi((e + "--1").c_str()) == 0); showLeaks();
	/* 4 */ check(ft_atoi((e + "++1").c_str()) == 0); showLeaks();
	/* 5 */ check(ft_atoi((e + "+1").c_str()) == 1); showLeaks();
	/* 6 */ check(ft_atoi((e + "-1").c_str()) == -1); showLeaks();
	/* 7 */ check(ft_atoi((e + "0").c_str()) == 0); showLeaks();
	/* 8 */ check(ft_atoi((e + "+42lyon").c_str()) == 42); showLeaks();
	/* 9 */ check(ft_atoi((e + "+101").c_str()) == 101); showLeaks();
	/* 10 */ check(ft_atoi((e + to_string(INT_MAX)).c_str()) == INT_MAX); showLeaks();
	/* 11 */ check(ft_atoi((e + to_string(INT_MIN)).c_str()) == INT_MIN); showLeaks();
	/* 12 */ check(ft_atoi("-+42") == 0); showLeaks();
	/* 13 */ check(ft_atoi("+-42") == 0); showLeaks();
	/* 14 */ check(ft_atoi((string("+") + e + "42").c_str()) == 0); showLeaks();
	/* 15 */ check(ft_atoi((string("-") + e + "42").c_str()) == 0); showLeaks();
	/* 16 */ check(ft_atoi((string("1") + e + "42").c_str()) == 1); showLeaks();
	/* 17 */ check(ft_atoi((string("-1") + e + "42").c_str()) == -1); showLeaks();
	/* 18 */ check(ft_atoi("") == 0); showLeaks();
	/* 19 */ check(ft_atoi(" ") == 0); showLeaks();
	/* 20 */ check(ft_atoi("+") == 0); showLeaks();
	/* 21 */ check(ft_atoi("-") == 0); showLeaks();
	/* 22 */ check(ft_atoi("-0") == 0); showLeaks();
	/* 23 */ check(ft_atoi("0000042") == 42); showLeaks();
	/* 24 */ check(ft_atoi("-0000042") == -42); showLeaks();
	/* 25 */ check(ft_atoi("42 42") == 42); showLeaks();
	/* 26 */ check(ft_atoi("42abc") == 42); showLeaks();
	/* 27 */ check(ft_atoi("abc42") == 0); showLeaks();
	/* 28 */ check(ft_atoi("- 42") == 0); showLeaks();
	/* 29 */ check(ft_atoi("+ 42") == 0); showLeaks();
	/* 30 */ check(ft_atoi("2147483647") == INT_MAX); showLeaks();
	/* 31 */ check(ft_atoi("-2147483648") == INT_MIN); showLeaks();
	/* 32 */ check(ft_atoi(" \t\n\v\f\r -12abc") == -12); showLeaks();
	{
		bool ok = true; //Every leading char (whitespaces included) compared to the libc
		for (int c = 0; c < 256; ++c)
		{
			string str; str += (char)c; str += "42";
			if (ft_atoi(str.c_str()) != atoi(str.c_str())) ok = false;
		}
		/* 33 */ check(ok); showLeaks();
	}
	{
		bool ok = true; //A range of values and the extremes
		for (long long v = INT_MIN; v <= INT_MAX; v += 1000003)
			if (ft_atoi(to_string(v).c_str()) != (int)v) ok = false;
		for (int v = -1000; v <= 1000; ++v)
			if (ft_atoi(to_string(v).c_str()) != v) ok = false;
		/* 34 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}