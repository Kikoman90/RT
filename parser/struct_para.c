/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_para.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 12:58:04 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/14 18:02:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static	char	*take_obj_para2(t_env *rt, char *line, int i, t_bal *bal)
{
	if ((bal->i == 2 && (ft_strequ("texture", BA)) == 1) && LI == '{')
	{
		if ((line = take_t(line, OB->text_on, (void*)OB->texture, i)) == NULL)
			return (NULL);
		rt->obj->check[8] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("limit", BA)) == 1) && LI == '{')
	{
		if ((line = check_double(line, OB->hauteur, i, 0)) == NULL)
			return (NULL);
		rt->obj->check[9] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("pos", BA)) == 1) && LI == '{')
	{
		if ((line = check_vect(line, OB->pos, i)) == NULL)
			return (NULL);
		rt->obj->check[1] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("radius", BA)) == 1) && LI == '{')
	{
		if ((line = check_double(line, OB->rayon, i, 0)) == NULL)
			return (NULL);
		rt->obj->check[4] += 1;
	}
	return (line);
}

static	char	*take_obj_para(t_env *rt, char *line, int i, t_bal *bal)
{
	if ((bal->i == 2 && (ft_strequ("type", BA)) == 1) && LI == '{')
	{
		if ((line = take_para_type(line, OB->type, i, 0)) == NULL)
			return (NULL);
		rt->obj->check[0] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("dir", BA)) == 1) && LI == '{')
	{
		if ((line = check_vect(line, OB->dir, i)) == NULL)
			return (NULL);
		rt->obj->check[2] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("rgb", BA)) == 1) && LI == '{')
	{
		if ((line = check_rgb(line, OB->rgb, i)) == NULL)
			return (NULL);
		rt->obj->check[3] += 1;
	}
	else if ((bal->i == 2 && ((ft_strequ("spec", BA)) == 1)) && LI == '{')
	{
		if ((line = take_para_on(line, OB->spec, i)) == NULL)
			return (NULL);
		rt->obj->check[7] += 1;
	}
	return (line);
}

int				obj_para(t_env *rt, char *line, int i, t_bal *bal)
{
	while (LI != '\0' && bal->i >= 1)
	{
		if ((bal = check_tag(rt, line, i, bal)) == NULL)
			return (-1);
		if ((line = take_obj_para(rt, line, i, bal)) == NULL)
			return (-1);
		if ((line = take_obj_para2(rt, line, i, bal)) == NULL)
			return (-1);
		if ((bal->i == 2 && ((ft_strequ("reflect", BA)) == 1)) && LI == '{')
		{
			if ((line = take_refl(line, rt->obj, i, 1)) == NULL)
				return (-1);
			rt->obj->check[5] += 1;
		}
		else if ((bal->i == 2 && (ft_strequ("refract", BA)) == 1) && LI == '{')
		{
			if ((line = take_para_refract(line, rt->obj, i, 1)) == NULL)
				return (-1);
			rt->obj->check[6] += 1;
		}
		else if (test_obj_bal(rt, bal, i) == -1)
			return (-1);
		line++;
	}
	return (0);
}

char			*take_scene_para(char *line, t_env *rt, int i, t_bal *bal)
{
	if (bal->i == 2 && (ft_strequ("full", BA)) == 1)
	{
		rt->win.res[0] = 2560;
		rt->win.res[1] = 1440;
		rt->win.check[1] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("AA", BA)) == 1) && LI == '{')
	{
		if ((line = take_para_intaa(line, WI.aa, i, 0)) == NULL)
			return (NULL);
		rt->win.check[2] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("maxref", BA)) == 1) && LI == '{')
	{
		if ((line = take_para_intaa(line, &rt->var.max_ref, i, 1)) == NULL)
			return (NULL);
		rt->win.check[3] += 1;
	}
	else if ((bal->i == 2 && (ft_strequ("ambiant", BA)) == 1) && LI == '{')
	{
		if ((line = check_double(line, &rt->var.ambiant, i, 1)) == NULL)
			return (NULL);
		rt->win.check[4] += 1;
	}
	return (line);
}

int				scene_para(t_env *rt, char *line, int i, t_bal *bal)
{
	while (LI != '\0' && bal->i >= 1)
	{
		if ((bal = check_tag(rt, line, i, bal)) == NULL)
			return (-1);
		if ((line = take_scene_para(line, rt, i, bal)) == NULL)
			return (-1);
		if ((bal->i == 2 && (ft_strequ("name", BA)) == 1) && LI == '{')
		{
			if ((line = take_para_word((void*)WI.windname, line, i)) == NULL)
				return (-1);
			rt->win.check[0] += 1;
		}
		else if ((bal->i == 2 && (ft_strequ("res", BA)) == 1) && LI == '{')
		{
			if ((line = take_para_int(line, (void*)WI.res, i)) == NULL)
				return (-1);
			rt->win.check[1] += 1;
		}
		if (test_scene_bal(rt, bal, line, i) == -1)
			return (-1);
		line++;
	}
	return (0);
}
