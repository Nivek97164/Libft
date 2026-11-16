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
	title("ft_memchr\t: ")
	
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	/* 1 */ check(ft_memchr(s, 0, 0) == NULL); showLeaks();
	/* 2 */ check(ft_memchr(s, 0, 1) == s); showLeaks();
	/* 3 */ check(ft_memchr(s, 2, 3) == s + 2); showLeaks();
	/* 4 */ check(ft_memchr(s, 6, 6) == NULL); showLeaks();
	/* 5 */ check(ft_memchr(s, 2 + 256, 3) == s + 2); showLeaks(); //Cast check
	/* 6 */ check(ft_memchr(s, 5, 6) == s + 5); showLeaks(); //Last byte
	/* 7 */ check(ft_memchr(s, 5, 5) == NULL); showLeaks(); //Just outside n
	/* 8 */ check(ft_memchr(s, 0, 6) == s); showLeaks(); //Looking for a 0 byte
	char abcabc[] = "abcabc";
	/* 9 */ check(ft_memchr(abcabc, 'b', 6) == abcabc + 1); showLeaks(); //First occurrence
	/* 10 */ check(ft_memchr(abcabc, 'c', 2) == NULL); showLeaks();
	/* 11 */ check(ft_memchr(abcabc, 0, 7) == abcabc + 6); showLeaks(); //'\0' reachable when n = len + 1
	char zeroInside[] = {'a', 0, 'b'};
	/* 12 */ check(ft_memchr(zeroInside, 'b', 3) == zeroInside + 2); showLeaks(); //Must not stop at '\0'
	unsigned char hi[] = {1, 128, 255, 3};
	/* 13 */ check(ft_memchr(hi, 128, 4) == hi + 1); showLeaks();
	/* 14 */ check(ft_memchr(hi, 255, 4) == hi + 2); showLeaks();
	/* 15 */ check(ft_memchr(hi, -1, 4) == hi + 2); showLeaks(); //-1 is (unsigned char)255

	write(1, "\n", 1);
	return (0);
}