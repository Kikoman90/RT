/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 11:08:35 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/04 14:43:36 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n, int i)
{
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static char	*ft_print_itoa(int n)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = ft_itoa_len(n, 0);
	str = (char*)malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	j = i - 1;
	while (j >= 0)
	{
		str[j] = '0' + (n % 10);
		n = n / 10;
		j--;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	if (n >= 0)
		str = ft_print_itoa(n);
	else
	{
		n = -n;
		i = ft_itoa_len(n, 1);
		str = (char*)malloc(sizeof(char) * i);
		if (!str)
			return (NULL);
		str[0] = '-';
		str[i] = '\0';
		i = i - 1;
		while (i > 0)
		{
			str[i--] = '0' + (n % 10);
			n = n / 10;
		}
	}
	return (str);
}
