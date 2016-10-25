/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 12:58:54 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/06 19:41:47 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_light	*check_list_light(t_env *rt)
{
	t_light	*new_li;
	t_light	*ptr;

	ptr = rt->headli;
	if (!(new_li = (t_light*)malloc(sizeof(t_light))))
		return (exit_null("ERROR: malloc error", -1));
	ft_memset_int((int*)new_li->check, 0, 2);
	new_li->next = NULL;
	if (rt->headli == NULL)
	{
		rt->headli = new_li;
		rt->var.nbli += 1;
		return (rt->headli);
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_li;
		rt->var.nbli += 1;
		return (ptr->next);
	}
}

static	void	put_null_obj(t_obj *obj)
{
	obj->type = 0;
	ft_vec_para(&obj->pos, 0.0, 0.0, 0.0);
	ft_vec_para(&obj->dir, 0.0, 0.0, 0.0);
	obj->rayon = 0.0;
	ft_vec_para(&obj->pos, 0.0, 0.0, 0.0);
	obj->offset_x = 0;
	obj->offset_y = 0;
	obj->scale = 1;
	obj->reflect = 0;
	obj->coef_refl = 0.0;
	obj->spec = 0;
	obj->hauteur = 0.0;
	obj->refr = 0.0;
	obj->ind_refr = 0.0;
	obj->text_on = 0;
	obj->coef_refr = 0.0;
	obj->texture = NULL;
	obj->bmp = NULL;
	ft_memset_int((int*)obj->check, 0, 10);
	obj->next = NULL;
}

static t_obj	*check_list_obj(t_env *rt)
{
	t_obj	*new_obj;
	t_obj	*ptr;

	ptr = rt->headobj;
	if (!(new_obj = (t_obj*)malloc(sizeof(t_obj))))
		return (exit_null("ERROR: malloc error", -1));
	put_null_obj(new_obj);
	if (rt->headobj == NULL)
	{
		rt->headobj = new_obj;
		rt->var.nbobj += 1;
		return (rt->headobj);
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_obj;
		rt->var.nbobj += 1;
		return (ptr->next);
	}
}

int				ft_malloc_list(t_env *rt, char *str)
{
	if ((ft_strequ(str, "light")) == 1)
	{
		if (!(rt->li = check_list_light(rt)))
			return (-1);
	}
	else if ((ft_strequ(str, "object")) == 1)
	{
		if (!(rt->obj = check_list_obj(rt)))
			return (-1);
	}
	return (0);
}

char			*check_double(char *line, double *radius, int i, int opt)
{
	int	verif;
	int	j;

	verif = 0;
	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	while (0 == (ft_isalpha(line[j])) && 0 == (ft_isdigit(line[j]))
		&& line[j] != '-')
		j++;
	*radius = check_value((line + j), &verif, i, -1);
	if (verif > 0)
		return (exit_null("ERROR: incorrect value for radius. line: ", i));
	if ((*radius <= 0.00000000 && opt == 0) || ((*radius < 0.00000000 ||
		*radius > 1.00000000) && opt == 1))
		return (exit_null("ERROR: incorrect value. line: ", i));
	while (line[j] != '}')
		j++;
	return (ft_strchr(line, '}'));
}
