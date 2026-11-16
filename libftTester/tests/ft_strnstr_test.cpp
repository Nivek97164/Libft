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
#include <stdlib.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_strnstr\t: ")

	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	char * empty = (char*)"";
	/* 1 */ check(ft_strnstr(haystack, needle, 0) == 0); showLeaks();
	/* 2 */ check(ft_strnstr(haystack, needle, -1) == haystack + 1); showLeaks();
	/* 3 */ check(ft_strnstr(haystack, "a", -1) == haystack); showLeaks();
	/* 4 */ check(ft_strnstr(haystack, "c", -1) == haystack + 4); showLeaks();
	/* 5 */ check(ft_strnstr(empty, "", -1) == empty); showLeaks();
	/* 6 */ check(ft_strnstr(empty, "", 0) == empty); showLeaks();
	/* 7 */ check(ft_strnstr(empty, "coucou", -1) == 0); showLeaks();
	/* 8 */ check(ft_strnstr(haystack, "aaabc", 5) == haystack); showLeaks();
	/* 9 */ check(ft_strnstr(empty, "12345", 5) == 0); showLeaks();
	/* 10 */ check(ft_strnstr(haystack, "abcd", 9) == haystack + 5); showLeaks();
	/* 11 */ check(ft_strnstr(haystack, "cd", 8) == NULL); showLeaks();
	/* 12 mbueno-g */ check(ft_strnstr(haystack, "a", 1) == haystack); showLeaks();
	/* 13 opsec-infosec */ check(ft_strnstr("1", "a", 1) == NULL); showLeaks();
	/* 14 opsec-infosec */ check(ft_strnstr("22", "b", 2) == NULL); showLeaks();
	/* 15 */ { const char *h = "22"; check(ft_strnstr(h, "22", 3) == h); } showLeaks();
	/* 16 */ check(ft_strnstr(haystack, "", 0) == haystack); showLeaks();
	char lorem[] = "lorem ipsum dolor sit amet";
	/* 17 */ check(ft_strnstr(lorem, "ipsum", 11) == lorem + 6); showLeaks();
	/* 18 */ check(ft_strnstr(lorem, "ipsum", 10) == NULL); showLeaks(); //Cut by len
	/* 19 */ check(ft_strnstr(lorem, "dolor", 100) == lorem + 12); showLeaks();
	/* 20 */ check(ft_strnstr(lorem, "lorem", 5) == lorem); showLeaks();
	/* 21 */ check(ft_strnstr(lorem, "amet", 26) == lorem + 22); showLeaks(); //End of haystack
	/* 22 */ check(ft_strnstr(lorem, "amet", 25) == NULL); showLeaks();
	/* 23 */ check(ft_strnstr(lorem, "", 5) == lorem); showLeaks(); //Empty needle
	/* 24 */ check(ft_strnstr(lorem, "lorem ipsum dolor sit amet!", 100) == NULL); showLeaks(); //Needle longer
	/* 25 */ check(ft_strnstr(lorem, "z", 100) == NULL); showLeaks();
	char rep[] = "ababababc";
	/* 26 */ check(ft_strnstr(rep, "abc", 100) == rep + 6); showLeaks(); //Partial matches must restart
	/* 27 */ check(ft_strnstr(rep, "abc", 8) == NULL); showLeaks();
	/* 28 */ check(ft_strnstr(rep, "abc", 9) == rep + 6); showLeaks();
	char aab[] = "aaaaab";
	/* 29 */ check(ft_strnstr(aab, "aab", 6) == aab + 3); showLeaks();
	char * noNul = (char *)malloc(3); memcpy(noNul, "abc", 3); //No '\0': reading past len is an invalid read
	/* 30 */ check(ft_strnstr(noNul, "abc", 3) == noNul); showLeaks();
	/* 31 */ check(ft_strnstr(noNul, "abd", 3) == NULL); free(noNul); showLeaks();

	write(1, "\n", 1);
	return (0);
}
