/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:09:35 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:37:05 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tab;
	unsigned char	ch;
	unsigned int	i;

	i = 0;
	ch = (unsigned char)c;
	tab = (unsigned char *)b;
	while (i < len)
	{
		tab[i] = ch;
		i++;
	}
	return (b);
}
