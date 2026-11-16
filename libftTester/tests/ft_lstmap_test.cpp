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
void * addOne(void * p) {void * r = malloc(sizeof(int)); *(int*)r = *(int*)p + 1; return (r);}

int iTest = 1;
static int g_fCalls;
static void * doubleIt(void * p) { int * r = (int*)malloc(sizeof(int)); *r = *(int*)p * 2; return r; }
static void * failThird(void * p) { if (++g_fCalls == 3) return NULL; return doubleIt(p); }

int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstmap\t: ")

	int tab[] = {0, 1, 2, 3};
	t_list * l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list * m = ft_lstmap(l, addOne, free);
	t_list * tmp = l;
	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
	{
		check(*(int*)tmp->content == i);
		tmp = (t_list *)tmp->next;
	}
	tmp = m;
	/* 5 6 7 8 */ for (int i = 0; i < 4; ++i)
	{
		check(*(int*)tmp->content == i + 1);
		tmp = (t_list *)tmp->next;
	}
	freeList(l); ft_lstclear(&m, free); showLeaks();
	{
		int v[] = {1, 2, 3};
		t_list * l3 = ft_lstnew(v);
		ft_lstadd_back(&l3, ft_lstnew(v + 1)); ft_lstadd_back(&l3, ft_lstnew(v + 2));
		t_list * m3 = ft_lstmap(l3, doubleIt, free);
		bool ok = m3 != NULL && m3 != l3;
		t_list * it = m3; int count = 0;
		for (; it; it = (t_list *)it->next, ++count)
			if (count < 3 && *(int*)it->content != v[count] * 2) ok = false; //2 4 6, same order
		/* 9 */ check(ok && count == 3);
		/* 10 */ check(v[0] == 1 && v[1] == 2 && v[2] == 3 && l3->content == v); //Original list untouched
		freeList(l3); ft_lstclear(&m3, free); showLeaks();
	}
	{
		int v = 21;
		t_list * l1 = ft_lstnew(&v);
		t_list * m1 = ft_lstmap(l1, doubleIt, free);
		/* 11 */ check(m1 != NULL && *(int*)m1->content == 42 && m1->next == 0);
		freeList(l1); ft_lstclear(&m1, free); showLeaks();
	}
	/* 12 */ check(ft_lstmap(NULL, doubleIt, free) == NULL); showLeaks(); //Robustness: empty list
	{
		int v[] = {1, 2, 3, 4, 5};
		t_list * l5 = NULL;
		for (int i = 0; i < 5; ++i) ft_lstadd_back(&l5, ft_lstnew(v + i));
		g_fCalls = 0;
		t_list * mf = ft_lstmap(l5, failThird, free); //f fails on the 3rd element: NULL and no leak
		/* 13 */ check(mf == NULL); showLeaks();
		freeList(l5);
	}

	write(1, "\n", 1);
	return (0);
}
