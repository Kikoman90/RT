/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:53:23 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/01 15:11:36 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	numb;

	i = 0;
	neg = 0;
	numb = 0;
	while ((str[i] == ' ') || (str[i] == '\f') || (str[i] == '\t')
			|| (str[i] == '\n') || (str[i] == '\r') || (str[i] == '\v'))
		i++;
	if (str[i] == 45)
		neg = 1;
	if ((str[i] == 45) || (str[i] == 43))
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		numb = numb * 10;
		numb = numb + ((int)str[i] - 48);
		i++;
	}
	if (neg == 1)
		return (-numb);
	else
		return (numb);
}
