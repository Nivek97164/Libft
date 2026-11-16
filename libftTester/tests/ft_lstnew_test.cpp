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
	title("ft_lstnew\t: ")

	t_list * l =  ft_lstnew((void*)42);
	/* 1 */ check(l->content == (void*)42);
	/* 2 */ check(l->next == 0);
	/* 3 */ mcheck(l, sizeof(t_list)); free(l); showLeaks();
	l = ft_lstnew(NULL);
	/* 4 */ check(l != NULL && l->content == NULL);
	/* 5 */ check(l->next == 0);
	/* 6 */ mcheck(l, sizeof(t_list)); free(l); showLeaks();

	char * str = strdup("hi");
	l = ft_lstnew(str);
	/* 7 */ check(l->content == str && !strcmp((char *)l->content, "hi")); //Pointer stored, not copied
	free(l); free(str); showLeaks();

	t_list * l1 = ft_lstnew((void*)1); t_list * l2 = ft_lstnew((void*)2);
	/* 8 */ check(l1 != l2 && l1->content == (void*)1 && l2->content == (void*)2 && l1->next == 0 && l2->next == 0);
	free(l1); free(l2); showLeaks();

	write(1, "\n", 1);
	return (0);
}