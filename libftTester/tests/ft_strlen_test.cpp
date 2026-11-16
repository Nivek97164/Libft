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
	title("ft_strlen\t: ")

	/* 1 */ check(ft_strlen((char *)"123") == 3); showLeaks();
	/* 2 */ check(ft_strlen((char *)"") == 0); showLeaks();
	/* 3 */ check(ft_strlen((char *)"a") == 1); showLeaks();
	/* 4 */ check(ft_strlen((char *)"tripouille") == 10); showLeaks();
	/* 5 */ check(ft_strlen((char *)"42 \t\n") == 5); showLeaks();
	char withNul[] = "abc\0def";
	/* 6 */ check(ft_strlen(withNul) == 3); showLeaks();
	string big(100000, 'x');
	/* 7 */ check(ft_strlen((char *)big.c_str()) == 100000); showLeaks();
	char * heap = strdup("heap");
	/* 8 */ check(ft_strlen(heap) == 4); free(heap); showLeaks();

	write(1, "\n", 1);
	return (0);
}