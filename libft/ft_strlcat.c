/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:47:57 by joboyer           #+#    #+#             */
/*   Updated: 2015/11/29 14:57:37 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lens;
	size_t	lend;
	char	*str;

	lens = 0;
	lend = 0;
	while (src[lens])
		lens++;
	while (dst[lend])
		lend++;
	str = dst;
	if (size < lend + 1)
		return (lens + size);
	ft_memcpy(str + lend, src, sizeof(char) * (size - lend - 1));
	dst[size - 1] = '\0';
	return (lens + lend);
}
