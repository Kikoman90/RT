/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:12:18 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/04 15:54:24 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	size_t			len;
	size_t			z;

	i = 0;
	z = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		while (z < len)
		{
			(*f)(i, s);
			i++;
			s++;
			z++;
		}
	}
}
