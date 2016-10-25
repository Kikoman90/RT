/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:17:18 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:58:22 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void *str;

	if (!src)
		return (NULL);
	str = (char*)malloc(sizeof(char) * len);
	ft_memcpy(str, src, len);
	ft_memcpy(dst, str, len);
	if (!str)
		return (NULL);
	free(str);
	return (dst);
}
