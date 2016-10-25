/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:24:08 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/03 14:58:53 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*tbl_d;
	const unsigned char	*tbl_s;

	i = 0;
	tbl_s = (const unsigned char*)src;
	tbl_d = (unsigned char*)dest;
	while (i < n)
	{
		tbl_d[i] = tbl_s[i];
		i++;
	}
	return (dest);
}
