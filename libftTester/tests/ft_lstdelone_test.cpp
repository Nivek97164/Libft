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
static int g_delCalls; static void * g_delArg;
static void countDel(void * p) { ++g_delCalls; g_delArg = p; free(p); }

int main(void)
{
	signal(SIGSEGV, sigsegv); (void)iTest;
	title("ft_lstdelone\t: ");

	t_list * l =  ft_lstnew(malloc(1));
	ft_lstdelone(l, free); l = 0;
	showLeaks();
	{
		void * content = malloc(4);
		t_list * n = ft_lstnew(content);
		g_delCalls = 0; g_delArg = NULL;
		ft_lstdelone(n, countDel);
		/* 1 */ check(g_delCalls == 1 && g_delArg == content); showLeaks(); //del called once on the content, node freed
	}
	{
		t_list * a = ft_lstnew(malloc(1)); t_list * b = ft_lstnew(malloc(1));
		a->next = b;
		void * bContent = b->content;
		g_delCalls = 0;
		ft_lstdelone(a, countDel);
		/* 2 */ check(g_delCalls == 1 && b->content == bContent); //Following nodes are untouched
		ft_lstdelone(b, free); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
