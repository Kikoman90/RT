/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:34:24 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/06 19:11:56 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void	cpy_obj_to_tobj(t_obj *src, t_obj *dst, t_env *rt, int i)
{
	while (++i < rt->var.nbobj)
	{
		dst[i].type = src->type;
		ft_vec_para(&dst[i].pos, src->pos.x, src->pos.y, src->pos.z);
		ft_vec_para(&dst[i].dir, src->dir.x, src->dir.y, src->dir.z);
		dst[i].rayon = src->rayon;
		ft_rgb_para(&dst[i].rgb, src->rgb.r, src->rgb.g, src->rgb.b);
		ft_rgb_para(&dst[i].rgb_save, src->rgb.r, src->rgb.g, src->rgb.b);
		dst[i].reflect = src->reflect;
		dst[i].spec = src->spec;
		dst[i].refr = src->refr;
		dst[i].ind_refr = src->ind_refr;
		dst[i].coef_refr = src->coef_refr;
		dst[i].coef_refl = src->coef_refl;
		dst[i].text_on = src->text_on;
		dst[i].hauteur = src->hauteur;
		dst[i].bmp = src->bmp;
		dst[i].offset_x = src->offset_x;
		dst[i].offset_y = src->offset_y;
		dst[i].scale = src->scale;
		dst[i].next = NULL;
		src = src->next;
	}
}

static void	cpy_li_to_tli(t_light *src, t_light *dst, t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->var.nbli)
	{
		ft_vec_para(&dst[i].pos, src->pos.x, src->pos.y, src->pos.z);
		ft_rgb_para(&dst[i].rgb, src->rgb.r, src->rgb.g, src->rgb.b);
		src = src->next;
		dst[i].next = NULL;
		i++;
	}
}

static void	free_all_light(t_light *li)
{
	t_light *del;
	t_light *tmp;

	del = li;
	while (li)
	{
		li = li->next;
		tmp = li;
		free(tmp);
	}
	free(del);
}

static void	free_all_obj(t_obj *obj)
{
	t_obj	*del;
	t_obj	*tmp;

	del = obj;
	while (obj)
	{
		obj = obj->next;
		tmp = obj;
		free(tmp);
	}
	free(del);
}

int			list_to_tab(t_env *rt)
{
	if (!(rt->tobj = (t_obj*)malloc(sizeof(t_obj) * rt->var.nbobj)))
		return (exit_error("ERROR: malloc error", -1));
	if (rt->var.nbli > 0)
	{
		if (!(rt->tli = (t_light*)malloc(sizeof(t_light) * rt->var.nbli)))
			return (exit_error("ERROR: malloc error", -1));
		cpy_li_to_tli(rt->headli, rt->tli, rt);
	}
	cpy_obj_to_tobj(rt->headobj, rt->tobj, rt, -1);
	free_all_light(rt->headli);
	free_all_obj(rt->headobj);
	return (0);
}
