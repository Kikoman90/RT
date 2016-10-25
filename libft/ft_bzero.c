/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:37:50 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:08:52 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tab;
	unsigned char	ch;
	unsigned int	i;

	i = 0;
	ch = '\0';
	if (n != 0)
	{
		tab = (unsigned char *)s;
		while (i < n)
		{
			tab[i] = ch;
			i++;
		}
	}
}
