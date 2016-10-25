/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:22:27 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:57:40 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				c;
	unsigned char	*tab;
	unsigned char	*tob;

	tab = (unsigned char*)s1;
	tob = (unsigned char*)s2;
	c = 0;
	while (n)
	{
		if (tab[c] == '\0' || tob[c] == '\0')
			return ((int)tab[c] - (int)tob[c]);
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
