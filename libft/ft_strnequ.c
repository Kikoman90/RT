/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 22:10:07 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/06 16:07:08 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			if (s1[i] == 0 && s2[i] == 0)
				return (1);
			i++;
		}
		return (1);
	}
	return (0);
}
