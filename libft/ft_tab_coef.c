/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_coef.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 18:47:18 by fsidler           #+#    #+#             */
/*   Updated: 2016/10/03 18:47:30 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		*ft_tab_coef(double *tab, double coef, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] *= coef;
		i++;
	}
	return (tab);
}
