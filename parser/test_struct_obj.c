/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_struct_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:04:19 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/10 12:04:45 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static	int	check_obj2(t_obj *obj, int i, int line)
{
	while (++i <= 6)
	{
		if (obj->check[i] < 1)
			return (-4);
		else if (obj->check[i] > 1)
			return (-2);
	}
	if (obj->check[7] > 0 && (obj->type == 4 || obj->type == 5))
		return (exit_error("spec doesn't work on plane and disk ", -1));
	else if (obj->check[7] < 0 && obj->type < 4)
		return (-4);
	else if (obj->check[7] > 1 && (obj->type != 4 || obj->type != 5))
		return (-2);
	if ((obj->check[8] < 0 || obj->check[8] > 1))
		return (-2);
	if ((obj->text_on == 3 && obj->type != 1) && obj->check[8] == 1)
		return (exit_error("texture work only on sphere ", -1));
	if ((obj->check[9] < 0 || obj->check[9] > 1) || (obj->check[9] == 1 &&
		(obj->type == 4 || obj->type == 5)))
		return (-2);
	return (0);
}

int			check_obj(t_obj *obj, int line)
{
	int	i;

	i = 0;
	if (obj->check[0] > 1)
		return (-2);
	if (obj->check[0] < 1)
		return (-4);
	while (++i <= 3)
	{
		if (obj->check[i] < 1)
			return (-1);
		else if (obj->check[i] > 1)
			return (-2);
	}
	if (obj->check[4] != 0 && obj->type == 4)
		return (exit_error("ERROR: plane don't need radius ", line));
	else if (obj->check[4] < 1 && obj->type != 4)
		return (-4);
	else if (obj->check[4] > 1 && obj->type != 4)
		return (-2);
	return (check_obj2(obj, 4, line));
}

double		get_value(char *val, int j, int *verif)
{
	char	*tmp;
	double	res;

	if (!(tmp = ft_strsub(val, 0, j)))
	{
		*verif += 1;
		return (0);
	}
	res = ft_atof(tmp);
	if (tmp)
		free(tmp);
	return (res);
}
