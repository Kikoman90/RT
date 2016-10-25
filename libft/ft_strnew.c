/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:22:25 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 15:28:44 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *tab;

	tab = (char*)malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	ft_memset(tab, '\0', size + 1);
	return (tab);
}
