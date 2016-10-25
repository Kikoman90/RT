/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:57:52 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 15:59:29 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int a;
	int c;
	int i;

	i = 0;
	c = 0;
	a = 0;
	while (dest[a])
		a++;
	while (src[c])
		c++;
	c = c + a;
	while (a < c)
	{
		dest[a] = src[i];
		a++;
		i++;
	}
	dest[a] = '\0';
	return (dest);
}
