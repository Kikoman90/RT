/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:52:47 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/04 15:13:30 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char			*tab;
	char			*tob;
	unsigned int	i;
	char			ch;

	ch = (char)c;
	i = 0;
	tab = (char *)src;
	tob = (char *)dest;
	if (dest && src)
	{
		while (i < n)
		{
			tob[i] = tab[i];
			if (tab[i] == ch)
				return ((void*)tob + i + 1);
			i++;
		}
	}
	return (NULL);
}
