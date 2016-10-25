/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matoi2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 19:15:17 by fsidler           #+#    #+#             */
/*   Updated: 2016/09/14 19:15:46 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_matoi2(const char *str)
{
	int	i;
	int	neg;
	int	numb;

	i = 0;
	neg = 0;
	numb = 0;
	if (str[i] == 45)
		neg = 1;
	if (str[i] == 45)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		numb = numb * 10;
		numb = numb + ((int)str[i] - 48);
		i++;
	}
	if (str[i] == '-')
		ft_error("error value", -1);
	if (neg == 1)
		return (-numb);
	else
		return (numb);
}
