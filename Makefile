# Variables

CC = cc
CFLAGS = -Wall -Werror -Wextra
SOURCES = ft_strlen.c ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_memset.c \
ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c	 ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECT = $(SOURCES:.c=.o)
NAME = libft.a


# Regle par defaut
all: $(NAME)

# Lien de l'execution
# $@ -> $(NAME)
# $^ -> $(OBJECT)
$(NAME): $(OBJECT)
	ar rcs $@ $^

# Compilation des fichers .c en .o
# $< -> Premier element des pr
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Declaration des cibles phony
.PHONY: all clean fclean re

# Nettoyage des fichier objects
clean:
	rm -f $(OBJECT)

# Nettoyage complet (fichier object et executable)
fclean: clean
	rm -f $(NAME)

# refaire la compilation
re: fclean all