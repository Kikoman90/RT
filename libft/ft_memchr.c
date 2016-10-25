/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:58:35 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 15:56:10 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char ch;
	char *tab;

	tab = (char *)s;
	ch = (char)c;
	while (n--)
	{
		if (*tab == ch)
			return (tab);
		if (n)
			tab++;
	}
	return (NULL);
}
