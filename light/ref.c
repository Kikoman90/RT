/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 16:48:05 by sganon            #+#    #+#             */
/*   Updated: 2016/10/18 14:38:44 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int	init_refr_inter(t_th *rt, int o, t_obj *obj, t_vec pos)
{
	t_vec	new_pos;
	double	d_dot;
	int		ob;

	ob = -1;
	new_pos = ft_vectorsub(&pos, &rt->tobj[o].pos);
	d_dot = (1.0 / sqrtf(sqrtf(dot(&new_pos, &new_pos)))) * 0.01;
	new_pos = pos;
	pos = (t_vec){pos.x - d_dot * rt->var.ref.x, pos.y - d_dot *
		rt->var.ref.y, pos.z - d_dot * rt->var.ref.z};
	ob = refr_inter(rt, -1, obj, pos);
	pos = new_pos;
	return (ob);
}

static int	refl_inter(t_th *rt, int o, t_obj *obj, t_vec pos)
{
	int		i;
	double	dist;
	int		ob;

	i = 0;
	ob = -1;
	while (i < rt->var.nbobj)
	{
		if (obj[i].type == 1 && i != o)
			dist = inter_sphere(&rt->var, obj[i], rt->var.ref, pos);
		else if (obj[i].type == 2 && i != o)
			dist = inter_cylinder(&rt->var, obj[i], rt->var.ref, pos);
		else if (obj[i].type == 3 && i != o)
			dist = inter_cone(&rt->var, obj[i], rt->var.ref, pos);
		else if ((obj[i].type == 4 || obj[i].type == 5) && i != o)
			dist = inter_plane(&rt->var, obj[i], rt->var.ref, pos);
		if (dist > 0.0001 && dist < rt->ray.t && i != o)
		{
			ob = i;
			rt->ray.t = dist;
		}
		i++;
	}
	return (ob);
}

int			refl_init(t_th *rt, int o, t_vec *pos)
{
	int		new;
	int		o_tmp;

	rt->ray.t = 8000.0;
	rt->var.ref = ft_vectorscale(&rt->var.norm,
		(2 * -dot(&rt->ray.ray_dir, &rt->var.norm)));
	rt->var.ref = ft_vectoradd(rt->ray.ray_dir, rt->var.ref);
	ft_vectornorm(&rt->var.ref);
	o_tmp = o;
	if ((new = refl_inter(rt, o, rt->tobj, *pos)) == -1)
		return (-1);
	if (rt->tobj[new].refr == 1)
		rt->var.prim = 0;
	*pos = (t_vec){pos->x + rt->var.ref.x * rt->ray.t, pos->y + rt->var.ref.y *
		rt->ray.t, pos->z + rt->var.ref.z * rt->ray.t};
	rt->ray.ray_dir = (t_vec){rt->var.ref.x, rt->var.ref.y, rt->var.ref.z};
	return (new);
}

void		refr_init_val(t_th *rt, int cpt, int o)
{
	if (rt->var.prim == 0 || cpt == 0)
	{
		rt->var.n1 = 1.0;
		rt->var.n2 = rt->tobj[o].ind_refr;
	}
	else
	{
		rt->var.n1 = rt->tobj[o].ind_refr;
		rt->var.n2 = 1.0;
		rt->var.norm = ft_vectorscale(&rt->var.norm, -1);
		rt->var.prim = 0;
	}
}

int			refr_init(t_th *rt, int o, t_vec *pos, int cpt)
{
	int		new;
	int		o_tmp;

	rt->ray.t = 8000.0;
	refr_init_val(rt, cpt, o);
	rt->var.ref = ft_vectoradd(ft_vectorscale(&rt->ray.ray_dir, rt->var.n1
	/ rt->var.n2), ft_vectorscale(&rt->var.norm, (rt->var.n1 / rt->var.n2) *
	(-dot(&rt->ray.ray_dir, &rt->var.norm)) - sqrtf(1 -
	(powf(rt->var.n1 / rt->var.n2, 2) * (1 -
	powf(dot(&rt->ray.ray_dir, &rt->var.norm), 2))))));
	ft_vectornorm(&rt->var.ref);
	o_tmp = o;
	if ((new = init_refr_inter(rt, o, rt->tobj, *pos)) == -1)
		return (-1);
	if (new == o_tmp)
		rt->var.prim = 1;
	*pos = (t_vec){pos->x + rt->var.ref.x * rt->ray.t, pos->y + rt->var.ref.y *
		rt->ray.t, pos->z + rt->var.ref.z * rt->ray.t};
	rt->ray.ray_dir = (t_vec){rt->var.ref.x, rt->var.ref.y, rt->var.ref.z};
	return (new);
}
