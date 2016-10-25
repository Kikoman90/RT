/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_para2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:56:50 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/07 12:57:00 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

char		*take_para_word(void **tmp, char *line, int i)
{
	int		j;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	line++;
	while (line[j] != '}')
		j++;
	if (j == 0)
	{
		(*tmp) = (char*)malloc(sizeof(char) * 5);
		(*tmp) = "scene";
	}
	else
		(*tmp) = ft_strsub(line, 0, (size_t)j);
	return (ft_strchr(line, '}'));
}

int			light_para(t_env *rt, char *line, int i, t_bal *bal)
{
	while ((*line) != '\0' && bal->i >= 1)
	{
		if ((bal = check_tag(rt, line, i, bal)) == NULL)
			return (-1);
		if ((bal->i == 2 && (ft_strequ("pos", BA)) == 1) && (*line) == '{')
		{
			if ((line = check_vect(line, &rt->li->pos, i)) == NULL)
				return (-1);
			rt->li->check[0] += 1;
		}
		else if ((bal->i == 2 && (ft_strequ("rgb", BA)) == 1) && (*line) == '{')
		{
			if ((line = check_rgb(line, &rt->li->rgb, i)) == NULL)
				return (-1);
			rt->li->check[1] += 1;
		}
		else if (bal->i == 2 && (((ft_strequ("pos", BA)) == 0) &&
			(ft_strequ("rgb", BA)) == 0))
			return (exit_error("ERROR: invalid tag in <light>. line: ", i));
		line++;
	}
	return (0);
}

int			camera_para(t_env *rt, char *line, int i, t_bal *bal)
{
	while ((*line) != '\0' && bal->i >= 1)
	{
		if ((bal = check_tag(rt, line, i, bal)) == NULL)
			return (-1);
		if ((bal->i == 2 && (ft_strequ("pos", BA)) == 1) && (*line) == '{')
		{
			if ((line = check_vect(line, &rt->cam.pos, i)) == NULL)
				return (-1);
			rt->cam.check[0] += 1;
		}
		else if ((bal->i == 2 && (ft_strequ("dir", BA)) == 1) && (*line) == '{')
		{
			if ((line = check_vect(line, &rt->cam.dir, i)) == NULL)
				return (-1);
			rt->cam.check[1] += 1;
		}
		else if (bal->i == 2 && (((ft_strequ("pos", BA)) == 0) &&
			(ft_strequ("dir", BA)) == 0))
			return (exit_error("ERROR: invalid tag in <camera>. line: ", i));
		line++;
	}
	return (0);
}

int			test_scene_bal(t_env *rt, t_bal *bal, char *line, int i)
{
	if ((bal->i == 2 && (ft_strequ("effect", BA)) == 1) && LI == '{')
	{
		if ((line = take_para_effect(line, &rt->var.effect_on, i)) == NULL)
			return (-1);
		rt->win.check[5] += 1;
	}
	if (bal->i == 2 && (((ft_strequ("name", BA)) == 0) &&
	(ft_strequ("res", BA)) == 0 && (ft_strequ("full", BA)) == 0)
	&& ((ft_strequ("AA", BA)) == 0) && (ft_strequ("maxref", BA)) == 0 &&
	(ft_strequ("ambiant", BA)) == 0 && (ft_strequ("effect", BA)) == 0)
		return (exit_error("ERROR: invalid tag in <scene>. line: ", i));
	return (0);
}

int			test_obj_bal(t_env *rt, t_bal *bal, int i)
{
	if (rt->obj->texture != NULL || rt->obj->text_on == 3)
		if (!(rt->obj->bmp = SDL_LoadBMP(rt->obj->texture)))
			return (exit_error("ERROR: loading bmp file. Line", i));
	if (bal->i == 2 && (((ft_strequ("pos", BA)) == 0) &&
			(ft_strequ("rgb", BA)) == 0) && (((ft_strequ("type", BA)) == 0) &&
			(ft_strequ("dir", BA)) == 0) && (ft_strequ("radius", BA)) == 0 &&
			(ft_strequ("reflect", BA)) == 0 && (ft_strequ("spec", BA)) == 0 &&
			(ft_strequ("texture", BA)) == 0 && (ft_strequ("limit", BA)) == 0 &&
			(ft_strequ("refract", BA)) == 0)
		return (exit_error("ERROR: invalid tag in <obj>. line: ", i));
	return (0);
}
