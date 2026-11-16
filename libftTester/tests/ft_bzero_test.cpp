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
	title("ft_bzero\t: ")
	
	char tab[100];
	memset(tab, 'A', 100);
	ft_bzero(tab, 0);
	/* 1 */ check(tab[0] == 'A'); showLeaks();
	ft_bzero(tab, 42);
	int i = 0;
	for (; i < 100 && tab[i] == 0; ++i)
		;
	/* 2 */ check(i == 42 && tab[42] == 'A'); showLeaks();
	memset(tab, 'A', 100); tab[0] = 0;
	ft_bzero(tab, 42);
	i = 0;
	for (; i < 100 && tab[i] == 0; ++i)
		;
	/* 3 */ check(i == 42); showLeaks();
	char t2[10]; memset(t2, 'A', 10);
	ft_bzero(t2, 1);
	/* 4 */ check(t2[0] == 0 && t2[1] == 'A'); showLeaks();
	ft_bzero(t2, 10);
	bool allZero = true;
	for (int j = 0; j < 10; ++j) if (t2[j] != 0) allZero = false;
	/* 5 */ check(allZero); showLeaks();
	memset(t2, 'A', 10);
	ft_bzero(t2 + 3, 4);
	/* 6 */ check(!memcmp(t2, "AAA\0\0\0\0AAA", 10)); showLeaks(); //Only [3, 7)
	char * heap = (char *)malloc(100000);
	memset(heap, 'x', 100000);
	ft_bzero(heap, 100000);
	bool heapZero = true;
	for (int j = 0; j < 100000; ++j) if (heap[j] != 0) heapZero = false;
	/* 7 */ check(heapZero); free(heap); showLeaks();

	write(1, "\n", 1);
	return (0);
}