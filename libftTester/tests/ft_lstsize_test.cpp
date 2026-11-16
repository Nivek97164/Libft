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
	title("ft_lstsize\t: ")

	t_list * l =  NULL;
	/* 1 */ check(ft_lstsize(l) == 0);
	ft_lstadd_front(&l, ft_lstnew((void*)1));
	/* 2 */ check(ft_lstsize(l) == 1);
	ft_lstadd_front(&l, ft_lstnew((void*)2));
	/* 3 */ check(ft_lstsize(l) == 2);
	freeList(l); showLeaks();
	t_list * one = ft_lstnew(NULL);
	/* 4 */ check(ft_lstsize(one) == 1);
	/* 5 */ check(ft_lstsize(one) == 1); //Calling it twice doesn't change the list
	freeList(one); showLeaks();

	t_list * big = NULL;
	for (int i = 0; i < 100; ++i)
		ft_lstadd_back(&big, ft_lstnew(NULL));
	/* 6 */ check(ft_lstsize(big) == 100);
	ft_lstadd_front(&big, ft_lstnew(NULL));
	/* 7 */ check(ft_lstsize(big) == 101);
	freeList(big); showLeaks();

	write(1, "\n", 1);
	return (0);
}
