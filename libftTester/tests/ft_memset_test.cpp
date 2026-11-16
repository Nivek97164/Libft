extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include <unistd.h>
#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);  
	title("ft_memset\t: ")

	char tab[100];
	memset(tab, 0, 100);
	ft_memset(tab, 'A', 0);
	/* 1 */ check(tab[0] == 0); showLeaks();
	ft_memset(tab, 'A', 42);
	int i = 0;
	for (; i < 100 && tab[i] == 'A'; ++i)
		;
	/* 2 */ check(i == 42 && tab[42] == 0); showLeaks();
	/* 3 */ check(ft_memset(tab, 'A', '4') == tab);
	char t2[10]; memset(t2, 0, 10);
	/* 4 */ check(ft_memset(t2, 'B' + 256, 5) == t2 && t2[0] == 'B' && t2[4] == 'B' && t2[5] == 0); showLeaks(); //Cast check
	unsigned char t3[10]; memset(t3, 0, 10);
	ft_memset(t3, 200, 10);
	/* 5 */ check(t3[0] == 200 && t3[9] == 200); showLeaks();
	unsigned char t4[4] = {0};
	ft_memset(t4, -1, 4);
	/* 6 */ check(t4[0] == 255 && t4[3] == 255); showLeaks();
	char t5[10]; memset(t5, 'A', 10);
	ft_memset(t5 + 2, 'Z', 3);
	/* 7 */ check(!memcmp(t5, "AAZZZAAAAA", 10)); showLeaks(); //No write outside [2, 5)
	/* 8 */ check(ft_memset(t5, 'Q', 0) == t5 && t5[0] == 'A'); showLeaks();
	ft_memset(t5, 0, 10);
	/* 9 */ check(!memcmp(t5, "\0\0\0\0\0\0\0\0\0\0", 10)); showLeaks();
	char * heap = (char *)malloc(100000);
	ft_memset(heap, 'x', 100000);
	bool memsetOk = true;
	for (int i = 0; i < 100000; ++i) if (heap[i] != 'x') memsetOk = false;
	/* 10 */ check(memsetOk); free(heap); showLeaks();

	write(1, "\n", 1);
	return (0);
}