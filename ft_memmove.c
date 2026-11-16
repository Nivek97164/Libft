/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevberna <kevberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 16:46:59 by kevberna          #+#    #+#             */
/*   Updated: 2026/11/16 14:49:16 by kevberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	copy_forbackward(unsigned char *d, const unsigned char *s,
				size_t n, int backward)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (backward)
			d[n - 1 - i] = s[n - 1 - i];
		else
			d[i] = s[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
		copy_forbackward(d, s, n, 0);
	else if (d > s)
		copy_forbackward(d, s, n, 1);
	return (dest);
}
