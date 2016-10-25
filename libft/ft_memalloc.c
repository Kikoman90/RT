/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:17:32 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 16:34:59 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char			*tab;

	if (size > 4294967295)
		return (NULL);
	tab = (char *)malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	ft_memset(tab, '\0', size + 1);
	return ((void*)tab);
}
