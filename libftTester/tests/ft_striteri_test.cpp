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

void
iter(unsigned int i, char * s) {
	*s += i;
}

static void toUpperIter(unsigned int, char * c) { if (*c >= 'a' && *c <= 'z') *c -= 32; }
static void setIndexIter(unsigned int i, char * c) { *c = '0' + i % 10; }
static int g_calls; static bool g_orderOk;
static void recordIter(unsigned int i, char *) { if (i != (unsigned int)g_calls) g_orderOk = false; ++g_calls; }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_striteri\t: ")

	{
		char s[] = "";
		ft_striteri(s, iter);
		/* 1 */ check(!strcmp(s, ""));
	}

	{
		char s[] = "0";
		ft_striteri(s, iter);
		/* 2 */ check(!strcmp(s, "0"));
	}

	{
		char s[] = "0000000000";
		ft_striteri(s, iter);
		/* 3 */ check(!strcmp(s, "0123456789"));
	}
	{
		char s[] = "hello world";
		ft_striteri(s, toUpperIter);
		/* 4 */ check(!strcmp(s, "HELLO WORLD"));
	}

	{
		char s[] = "aaaaaaaaaaaa";
		ft_striteri(s, setIndexIter); //The index is given to f
		/* 5 */ check(!strcmp(s, "012345678901"));
	}

	{
		char s[] = "abcde";
		g_calls = 0; g_orderOk = true;
		ft_striteri(s, recordIter); //f called once per char, indexes 0, 1, 2...
		/* 6 */ check(g_calls == 5 && g_orderOk && !strcmp(s, "abcde"));
	}

	{
		char s[] = "";
		g_calls = 0; g_orderOk = true;
		ft_striteri(s, recordIter);
		/* 7 */ check(g_calls == 0);
	}

	{
		string big(100000, 'a');
		char * heap = strdup(big.c_str());
		ft_striteri(heap, toUpperIter);
		bool ok = true;
		for (int i = 0; i < 100000; ++i) if (heap[i] != 'A') ok = false;
		/* 8 */ check(ok); free(heap);
	}

	write(1, "\n", 1);
	return (0);
}