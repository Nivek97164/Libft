*This activity has been created as part of the 42 curriculum by kevberna*

## Description

This repo contain the `libft` project, which is a collection of functions coded in C language prefixed with `ft_`, such as `ft_calloc`, `ft_strchr`, ...

Here are the said functions :

| **function name** | **prototype** | **external functions** |
|-------------------|---------------|------------------------|
| ft_isalnum | `int ft_isalnum(int c)` | None |
| ft_isdigit | `int ft_isdigit(int c)` | None |
| ft_isalpha | `int ft_isalpha(int c)` | None |
| ft_isascii | `int ft_isascii(int c)` | None |
| ft_isprint | `int ft_isprint(int c)` | None |
| ft_tolower | `int ft_tolower(int c)`| None |
| ft_toupper | `int ft_toupper(int c)` | None |
| ft_strlen | `size_t ft_strlen(const char *s)` | None |
| ft_strchr | `char *ft_strchr(const char *s, int c)` | None |
| ft_strrchr | `char *ft_strrchr(const char *s, int c)` | None |
| ft_strncmp | `int ft_strncmp(const char *s1, const char *s2, size_t n)` | None |
| ft_strlcpy | `size_t ft_strlcpy(char *dst, const char *src, size_t size)` | None |
| ft_strlcat | `size_t ft_strlcat(char *dst, const char *src, size_t size)` | None |
| ft_strnstr | `char *ft_strnstr(const char *big, const char *little, size_t len)` | None |
| ft_strdup | `char *ft_strdup(const char *s)` | malloc() |
| ft_memset | `void *ft_memset(void *s, int c, size_t n)` | None |
| ft_bzero | `void ft_bzero(void *s, size_t n)` | None |
| ft_memchr | `void *ft_memchr(const void *s, int c, size_t n)` | None |
| ft_memcpy | `void *ft_memcpy(void *dest, const void *src, size_t n)` | None |
| ft_memcmp | `int ft_memcmp(const void *s1, const void *s2, size_t n)` | None |
| ft_memmove | `void *ft_memmove(void *dest, const void *src, size_t n)` | None |
| ft_calloc | `void *ft_calloc(size_t n, size_t size)` | malloc() |
| ft_atoi | `int ft_atoi(const char *nptr)` | None |
| ft_substr | `char *ft_substr(char const *s, unsigned int start, size_t len)` | malloc() |
| ft_strjoin | `char *ft_strjoin(char const *s1, char const *s2)` | malloc() |
| ft_strtrim | `char *ft_strtrim(char const *s1, char const *set)` | malloc() |
| ft_split | `char **ft_split(char const *s, char c)` | malloc(), free() |
| ft_itoa | `char *ft_itoa(int n)` | malloc() |
| ft_strmapi | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | malloc() |
| ft_striteri | `void ft_striteri(char *s, void (*f)(unsigned int, char*))` | None |
| ft_putchar_fd | `void ft_putchar_fd(char c, int fd)` | write() |
| ft_putstr_fd | `void ft_putstr_fd(char *s, int fd)` | write() |
| ft_putendl_fd | `void ft_putendl_fd(char *s, int fd)` | write() |
| ft_putnbr_fd | `void ft_putnbr_fd(int n, int fd)` | write() |
| ft_lstnew | `t_list *ft_lstnew(void *content)` | malloc() |
| ft_lstadd_front | `void ft_lstadd_front(t_list **lst, t_list *new)` | None |
| ft_lstsize | `unsigned int ft_lstsize(t_list *lst)` | None |
| ft_lstadd_back | `void ft_lstadd_back(t_list **lst, t_list *new)` | None |
| ft_lstlast | `t_list *ft_lstlast(t_list *lst)` | None |
| ft_lstdelone | `void ft_lstdelone(t_list *lst, void (*del)(void *))` | free() |
| ft_lstclear | `void ft_lstclear(t_list **lst, void (*del)(void *))` | free() |
| ft_lstiter | `void ft_lstiter(t_list *lst, void (*f)(void *))` | None |
| ft_lstmap | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | malloc(), free() |

## Instructions

The Makefile is in charge of the compilation and cleaning of temporary files, here are the commands :

| command | description |
|---------|-------------|
| `make (all)` | create the archive |
| `make clean` | remove the object files |
| `make fclean` | remove the object files and the archive |
| `make re` | remove the object files, the archive and redo the compilation |

The `libft.h` file contain the functions prototypes and some dependencies.

## Ressources

No AI was used during the making of this project, the main reference was the manual of the fonctions, and a bit of StackOverflow.