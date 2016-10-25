/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:17:29 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:39:28 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(s);
	while (i < len && s[i])
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char*)s + i);
	return (NULL);
}
