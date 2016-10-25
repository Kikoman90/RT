/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:40:18 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 14:54:02 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	str = (char*)malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	if (!str)
		return (NULL);
	str[i] = '\0';
	return (str);
}
