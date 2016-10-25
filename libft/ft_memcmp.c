/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:06:16 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 13:53:58 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				c;
	unsigned char	*tab;
	unsigned char	*tob;

	tab = (unsigned char*)s1;
	tob = (unsigned char*)s2;
	c = 0;
	while (n)
	{
		if (tab[c] != tob[c])
			return ((int)tab[c] - tob[c]);
		if (n)
		{
			c++;
			n--;
		}
	}
	return (0);
}
