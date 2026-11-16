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
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_lstadd_back\t: ")

	t_list * l =  NULL; t_list * l2 =  NULL;
	ft_lstadd_back(&l, ft_lstnew((void*)1));
	/* 1 */ check(l->content == (void*)1);
	/* 2 */ check(l->next == 0);

	ft_lstadd_back(&l, ft_lstnew((void*)2));
	/* 3 */ check(l->content == (void*)1);
	/* 4 */ check(((t_list *)(l->next))->content == (void*)2);
	/* 5 */ check(((t_list *)(l->next))->next == 0);

	ft_lstadd_back(&l2, ft_lstnew((void*)3));
	ft_lstadd_back(&l2, ft_lstnew((void*)4));
	ft_lstadd_back(&l, l2);
	/* 6 */ check(l->content == (void*)1);
	/* 7 */ check(((t_list *)(l->next))->content == (void*)2);
	/* 8 */ check(((t_list *)(((t_list *)(l->next))->next))->content == (void*)3);
	/* 9 */ check(((t_list *)((t_list *)(((t_list *)(l->next))->next))->next)->content == (void*)4);
	/* 10 */ check(((t_list *)((t_list *)(((t_list *)(l->next))->next))->next)->next == 0);
	freeList(l); showLeaks();
	t_list * h = NULL; t_list * first = ft_lstnew((void*)1);
	ft_lstadd_back(&h, first);
	/* 11 */ check(h == first && h->next == 0); //Empty list: head is set
	for (long i = 2; i <= 10; ++i)
		ft_lstadd_back(&h, ft_lstnew((void*)i));
	/* 12 */ check(h == first); //Head unchanged on a non-empty list
	bool orderOk = true; long expected = 1; int count = 0;
	for (t_list * it = h; it; it = (t_list *)it->next, ++expected, ++count)
		if (it->content != (void*)expected) orderOk = false;
	/* 13 */ check(orderOk && count == 10); //1 2 3 ... 10
	freeList(h); showLeaks();

	write(1, "\n", 1);
	return (0);
}
