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
	title("ft_strrchr\t: ")
	char s[] = "tripouille";
	char s2[] = "ltripouiel";
	char s3[] = "";
	/* 1 */ check(ft_strrchr(s, 't') == s); showLeaks();
	/* 2 */ check(ft_strrchr(s, 'l') == s + 8); showLeaks();
	/* 3 */ check(ft_strrchr(s2, 'l') == s2 + 9); showLeaks();
	/* 4 */ check(ft_strrchr(s, 'z') == NULL); showLeaks();
	/* 5 */ check(ft_strrchr(s, 0) == s + strlen(s)); showLeaks();
	/* 6 */ check(ft_strrchr(s, 't' + 256) == s); showLeaks();
	char * empty = (char*)calloc(1, 1);
	/* 7 aperez-b */ check(ft_strrchr(empty, 'V') == NULL); free(empty); showLeaks();
	/* 8 */ check(ft_strrchr(s3, 0) == s3); showLeaks();
	char s4[] = "abcabcabc";
	/* 9 */ check(ft_strrchr(s4, 'a') == s4 + 6); showLeaks();
	/* 10 */ check(ft_strrchr(s4, 'c') == s4 + 8); showLeaks(); //Last char
	/* 11 */ check(ft_strrchr(s4, 0) == s4 + 9); showLeaks();
	/* 12 */ check(ft_strrchr(s4, 'z') == NULL); showLeaks();
	/* 13 */ check(ft_strrchr(s4, 'a' + 256) == s4 + 6); showLeaks(); //Cast check
	/* 14 */ check(ft_strrchr(s4, 0 + 256) == s4 + 9); showLeaks();
	char one[] = "x";
	/* 15 */ check(ft_strrchr(one, 'x') == one); showLeaks();
	char withNul[] = "ab\0ab";
	/* 16 */ check(ft_strrchr(withNul, 'b') == withNul + 1); showLeaks(); //Must stop at '\0'
	{
		bool ok = true; //Every value compared to the libc
		for (int c = 0; c < 512; ++c)
			if (ft_strrchr(s4, c) != strrchr(s4, c)) ok = false;
		/* 17 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
