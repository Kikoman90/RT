/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:38:40 by joboyer           #+#    #+#             */
/*   Updated: 2015/12/04 15:16:48 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_trim(char const *s)
{
	int i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\n'
		|| s[i] == '\t') && i < (int)ft_strlen(s))
		i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		j;
	char	*tab;

	if (!s)
		return (NULL);
	j = (int)ft_strlen(s) - 1;
	start = ft_len_trim(s);
	while ((s[j] == ' ' || s[j] == ',' || s[j] == '\n'
		|| s[j] == '\t') && j >= 0)
		j--;
	if (j > 0)
		j++;
	if (start == (int)ft_strlen(s) || j == 0)
	{
		tab = (char*)malloc(sizeof(char) * 1);
		ft_memset(tab, '\0', 1);
		return (tab);
	}
	tab = (char *)malloc(sizeof(char) * j - start);
	if (start < j)
		tab = ft_strsub(s, start, j - start);
	return (tab);
}
