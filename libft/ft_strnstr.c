/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:27:01 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 17:01:26 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t z;

	i = 0;
	z = 0;
	if (!s2)
		return ((char*)s1);
	while (i < n && s1[i] != '\0' && s2[z] != '\0')
	{
		if (s1[i] == s2[z])
			z++;
		else
		{
			i = i - z;
			z = 0;
		}
		i++;
	}
	if (i > n)
		i--;
	if (s2[z] == '\0' && s1[i - 1] == s2[z - 1])
		return ((char*)s1 + i - z);
	else
		return (NULL);
}
