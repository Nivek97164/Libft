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
	title("ft_lstadd_front\t: ")

	t_list * l =  NULL;
	ft_lstadd_front(&l, ft_lstnew((void*)1));
	/* 1 */ check(l->content == (void*)1);
	/* 2 */ check(l->next == 0);

	ft_lstadd_front(&l, ft_lstnew((void*)2));
	/* 3 */ check(l->content == (void*)2);
	/* 4 */ check(((t_list *)l->next)->content == (void*)1);
	/* 5 */ check(((t_list *)l->next)->next == 0);
	freeList(l); showLeaks();
	t_list * lf = NULL;
	for (long i = 1; i <= 5; ++i)
		ft_lstadd_front(&lf, ft_lstnew((void*)i));
	bool orderOk = true; long expected = 5; int count = 0;
	for (t_list * it = lf; it; it = (t_list *)it->next, --expected, ++count)
		if (it->content != (void*)expected) orderOk = false;
	/* 6 */ check(orderOk && count == 5); //5 4 3 2 1
	freeList(lf); showLeaks();

	t_list * oldHead = ft_lstnew((void*)1); t_list * newHead = ft_lstnew((void*)2);
	t_list * head = oldHead;
	ft_lstadd_front(&head, newHead);
	/* 7 */ check(head == newHead && head->next == oldHead && oldHead->next == 0); //The head pointer is updated
	freeList(head); showLeaks();

	write(1, "\n", 1);
	return (0);
}
