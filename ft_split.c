/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevberna <kevberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:23:25 by kevberna          #+#    #+#             */
/*   Updated: 2026/11/16 14:03:59 by kevberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static	void	*free_all(char **tab, size_t n)
{
	while (n > 0)
	{
		n--;
		free(tab[n]);
	}
	free(tab);
	return (NULL);
}

static	char	*next_word(char const *s, char c, size_t *i)
{
	size_t	start;

	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	words = count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		tab[j] = next_word(s, c, &i);
		if (!tab[j])
			return (free_all(tab, j));
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
