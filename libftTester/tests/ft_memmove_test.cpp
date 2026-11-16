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
	title("ft_memmove\t: ")
	
	char s[] = {65, 66, 67, 68, 69, 0, 45};
	char s0[] = { 0,  0,  0,  0,  0,  0, 0};
	char sCpy[] = {65, 66, 67, 68, 69, 0, 45};
	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};

	/* 1 */ check(ft_memmove(s0, s, 7) == s0 && !memcmp(s, s0, 7)); showLeaks(); //Post 0
	/* 2 */ check(ft_memmove(s, s + 2, 0) && !memcmp(s, sCpy, 7)); showLeaks(); //0 move
	/* 3 */ check(ft_memmove(s, s + 2, 2) == s && !memcmp(s, sResult, 7)); showLeaks(); //forward
	/* 4 */ check(ft_memmove(sResult + 1, sResult, 2) == sResult + 1 && !memcmp(sResult, sResult2, 7)); showLeaks(); //reverse
	char b1[] = "0123456789";
	/* 5 */ check(ft_memmove(b1 + 2, b1, 5) == b1 + 2 && !strcmp(b1, "0101234789")); showLeaks(); //Overlap, dest > src
	char b2[] = "0123456789";
	/* 6 */ check(ft_memmove(b2, b2 + 3, 5) == b2 && !strcmp(b2, "3456756789")); showLeaks(); //Overlap, dest < src
	char b3[] = "0123456789";
	/* 7 */ check(ft_memmove(b3, b3, 10) == b3 && !strcmp(b3, "0123456789")); showLeaks(); //dest == src
	char b4[] = "0123456789";
	/* 8 */ check(ft_memmove(b4 + 5, b4, 0) == b4 + 5 && !strcmp(b4, "0123456789")); showLeaks();
	char b5[10]; memset(b5, 'A', 10);
	/* 9 */ check(ft_memmove(b5 + 1, "xyz", 3) == b5 + 1 && !memcmp(b5, "AxyzAAAAAA", 10)); showLeaks(); //No overlap
	/* 10 */ check(ft_memmove(NULL, NULL, 0) == NULL); showLeaks();
	{
		bool ok = true; //Every dest/src offset combination compared to the libc
		for (int dOff = 0; dOff < 40; dOff += 3)
			for (int sOff = 0; sOff < 40; sOff += 5)
			{
				unsigned char x[100], y[100];
				for (int i = 0; i < 100; ++i) x[i] = y[i] = i;
				ft_memmove(x + dOff, x + sOff, 50);
				memmove(y + dOff, y + sOff, 50);
				if (memcmp(x, y, 100)) ok = false;
			}
		/* 11 */ check(ok); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}