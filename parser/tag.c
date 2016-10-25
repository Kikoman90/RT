/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balise.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:25:06 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/16 15:39:20 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static	int		check_check(int *tab, int stop, int nothing, int *check)
{
	int i;

	i = 0;
	while (i < stop)
	{
		if ((i == nothing) && (tab[i] != 0))
			return (-3);
		else if (tab[i] < 1 && i != nothing)
			return (-4);
		else if (tab[i] > 1 && i != nothing)
			return (-2);
		i++;
	}
	*check += 1;
	return (0);
}

static int		check_content(t_env *rt, char *str, int i)
{
	int res;

	if ((ft_strequ(str, "scene")) == 1)
		res = check_check((int*)rt->win.check, 5, -1, &rt->var.check[0]);
	else if ((ft_strequ(str, "camera")) == 1)
		res = check_check((int*)rt->cam.check, 2, -1, &rt->var.check[1]);
	else if ((ft_strequ(str, "light")) == 1)
		res = check_check((int*)rt->li->check, 2, -1, &rt->var.check[2]);
	else if ((ft_strequ(str, "object")) == 1)
	{
		res = check_obj(rt->obj, i);
		if (res == 0)
			rt->var.check[3]++;
	}
	if (res == -4)
		return (exit_error(ft_strjoin("ERROR: missing argument(s) in ",
				ft_strjoin(str, ". line: ", 'N'), 'N'), i));
	else if (res == -2 || res == -1)
		return (exit_error(ft_strjoin("ERROR: too many arguments in ",
				ft_strjoin(str, ". line: ", 'N'), 'N'), i));
		return (0);
}

static	t_bal	*open_tag(t_env *rt, char *line, int i, t_bal *bal)
{
	int	len;

	len = 0;
	if ((ft_strchr(line, '>')) == NULL)
		return (exit_null("ERROR: incomplete tag. line: ", i));
	while (line[len] != '>')
		len++;
	bal->bali[bal->i] = ft_strsub(line, 0, (size_t)len);
	if (ft_malloc_list(rt, bal->bali[bal->i]) == -1)
		return (NULL);
	bal->i++;
	if (bal->i > 2)
		return (exit_null("ERROR: too many tags. line: ", i));
	return (&rt->bal);
}

static	t_bal	*close_tag(t_env *rt, char *line, int i, t_bal *bal)
{
	if ((ft_strchr(line, '>')) == NULL)
		return (exit_null("ERROR: incomplete tag. line: ", i));
	if ((ft_strnequ(line, bal->bali[bal->i - 1],
		(int)ft_strlen(bal->bali[bal->i - 1]))) == 0)
		return (exit_null("ERROR: closing tag does not match. line: ", i));
	else
	{
		if (check_content(rt, bal->bali[bal->i - 1], i) == -1)
			return (NULL);
		free(bal->bali[bal->i - 1]);
		bal->i--;
	}
	return (&rt->bal);
}

t_bal			*check_tag(t_env *rt, char *line, int i, t_bal *bal)
{
	if (bal->i == 0)
		if (!(line = ft_strchr(line, '<')))
			return (bal);
	if (*line == '<')
	{
		line++;
		if (*line != '/')
			return (open_tag(rt, line, i, bal));
		else if (*line == '/')
		{
			if (bal->i == 0)
				return (exit_null("ERROR: tag line: ", i));
			line++;
			return (close_tag(rt, line, i, bal));
		}
	}
	return (bal);
}
