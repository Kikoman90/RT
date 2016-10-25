/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 19:09:40 by fsidler           #+#    #+#             */
/*   Updated: 2016/09/14 19:09:50 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(char c, const char *str)
{
	char	*tmp;
	size_t	res;

	tmp = (char *)str;
	res = 0;
	if (str == NULL)
		return (0);
	while (*tmp && *tmp != c)
	{
		tmp++;
		res++;
	}
	return (res);
}
