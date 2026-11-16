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
void addOne(void * p) {++*(int*)p;}

int iTest = 1;
static int g_calls; static int g_order[16]; static int g_idx;
static void incr(void * p) { ++*(int*)p; }
static void countCalls(void *) { ++g_calls; }
static void recordOrder(void * p) { g_order[g_idx++] = *(int*)p; }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstiter\t: ")

	int tab[] = {0, 1, 2, 3};
	t_list * l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	ft_lstiter(l, addOne);
	t_list * tmp = l;
	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
	{
		check(*(int*)tmp->content == i + 1);
		tmp = (t_list *)tmp->next;
	}
	freeList(l); showLeaks();
	{
		int v[] = {10, 20, 30};
		t_list * l3 = ft_lstnew(v);
		ft_lstadd_back(&l3, ft_lstnew(v + 1)); ft_lstadd_back(&l3, ft_lstnew(v + 2));
		ft_lstiter(l3, incr);
		/* 5 */ check(v[0] == 11 && v[1] == 21 && v[2] == 31);
		freeList(l3); showLeaks();
	}
	{
		t_list * l7 = NULL;
		for (int i = 0; i < 7; ++i) ft_lstadd_back(&l7, ft_lstnew(NULL));
		g_calls = 0;
		ft_lstiter(l7, countCalls);
		/* 6 */ check(g_calls == 7); //f called once per node
		freeList(l7); showLeaks();
	}
	{
		int v[] = {1, 2, 3, 4, 5};
		t_list * lo = NULL;
		for (int i = 0; i < 5; ++i) ft_lstadd_back(&lo, ft_lstnew(v + i));
		g_idx = 0;
		ft_lstiter(lo, recordOrder);
		/* 7 */ check(g_idx == 5 && g_order[0] == 1 && g_order[1] == 2 && g_order[2] == 3 && g_order[3] == 4 && g_order[4] == 5); //Head to tail
		freeList(lo); showLeaks();
	}
	{
		g_calls = 0;
		ft_lstiter(NULL, countCalls); //Robustness: empty list, no crash
		/* 8 */ check(g_calls == 0); showLeaks();
	}

	write(1, "\n", 1);
	return (0);
}
