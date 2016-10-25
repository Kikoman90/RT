/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 17:19:56 by fsidler           #+#    #+#             */
/*   Updated: 2016/10/06 19:12:36 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int		exit_free(t_env *rt, char *str, int r)
{
	if (r == 1)
		ft_putendl(str);
	if (rt->bal.bali)
		free(rt->bal.bali);
	return (-1);
}

int		exit_error(char *str, int line)
{
	if (line == -1)
		ft_putendl(str);
	else
		ft_putendl(ft_strjoin(str, ft_itoa(line), 'N'));
	return (-1);
}

void	*exit_null(char *str, int line)
{
	if (line == -1)
		ft_putendl(str);
	else
		ft_putendl(ft_strjoin(str, ft_itoa(line), 'R'));
	return (NULL);
}

void	cpy_env_to_th(t_env *rt, t_th *th)
{
	th->win.res[0] = rt->win.res[0];
	th->win.res[1] = rt->win.res[1];
	th->win.aa = rt->win.aa;
	th->cam = rt->cam;
	th->var = rt->var;
	th->tli = rt->tli;
	th->tobj = rt->tobj;
}
