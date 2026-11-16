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

void freeList(t_list *head) {if (head) freeList((t_list *)head->next); free(head);}

int iTest = 1;
static int g_delCalls;
static void countDel(void * p) { ++g_delCalls; free(p); }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstclear\t: ")

	t_list * l =  ft_lstnew(malloc(1));
	for (int i = 0; i < 10; ++i)
		ft_lstadd_front(&l, ft_lstnew(malloc(1)));
	ft_lstclear(&l, free);
	/* 1 */ check(l == 0); showLeaks();
	/* All other checks are done by valgrind */
	{
		t_list * l5 = NULL;
		for (int i = 0; i < 5; ++i) ft_lstadd_front(&l5, ft_lstnew(malloc(1)));
		g_delCalls = 0;
		ft_lstclear(&l5, countDel);
		/* 2 */ check(l5 == NULL && g_delCalls == 5); showLeaks(); //del called on every node
	}
	{
		t_list * l1 = ft_lstnew(malloc(1));
		g_delCalls = 0;
		ft_lstclear(&l1, countDel);
		/* 3 */ check(l1 == NULL && g_delCalls == 1); showLeaks();
	}
	{
		t_list * empty = NULL;
		g_delCalls = 0;
		ft_lstclear(&empty, countDel); //Empty list: nothing to do, no crash
		/* 4 */ check(empty == NULL && g_delCalls == 0); showLeaks();
	}
	{
		t_list * big = NULL;
		for (int i = 0; i < 1000; ++i) ft_lstadd_front(&big, ft_lstnew(malloc(1)));
		g_delCalls = 0;
		ft_lstclear(&big, countDel);
		/* 5 */ check(big == NULL && g_delCalls == 1000); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
