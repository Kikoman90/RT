/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 15:20:48 by sganon            #+#    #+#             */
/*   Updated: 2016/10/06 18:35:21 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int	single_inter(t_env *rt, t_obj *obj, t_vec ray, t_vec pos)
{
	int		tmp;
	double	dist;
	int		i;

	i = -1;
	tmp = -1;
	rt->ray.t = 80000.0;
	while (++i < rt->var.nbobj)
	{
		if (obj[i].type == 1)
			dist = inter_sphere(&rt->var, obj[i], ray, pos);
		else if (obj[i].type == 2)
			dist = inter_cylinder(&rt->var, obj[i], ray, pos);
		else if (obj[i].type == 3)
			dist = inter_cone(&rt->var, obj[i], ray, pos);
		else if (obj[i].type == 4 || obj[i].type == 5)
			dist = inter_plane(&rt->var, obj[i], ray, pos);
		if (dist > 0.001 && dist < rt->ray.t)
		{
			tmp = i;
			rt->ray.t = dist;
		}
	}
	return (tmp);
}

static void	set_single_ray(t_env *rt, int x, int y, t_vec *tmp_vec)
{
	double	u;
	double	v;

	u = ((double)x * 2.0 - (double)rt->win.res[1]) / (double)rt->win.res[0];
	v = ((double)rt->win.res[0] - (double)y * 2.0) / (double)rt->win.res[1];
	tmp_vec->x = u * I.x + v * J.x + FOV * K.x;
	tmp_vec->y = u * I.y + v * J.y + FOV * K.y;
	tmp_vec->z = u * I.z + v * J.z + FOV * K.z;
	ft_vectornorm(tmp_vec);
}

void		object_selection(t_env *rt)
{
	int		x;
	int		y;
	t_vec	tmp_vec;
	int		o;

	x = rt->event.motion.x;
	y = rt->event.motion.y;
	set_single_ray(rt, x, y, &tmp_vec);
	if ((o = single_inter(rt, rt->tobj, tmp_vec, rt->cam.pos)) > -1)
	{
		rt->selection = (rt->selection && rt->sel_i == o) ? 0 : 1;
		rt->sel_i = o;
	}
	else
		rt->selection = 0;
	SDL_FillRect(rt->tool.surf, NULL, 0);
	initial_ui_surf(rt);
	print_infos(rt, rt->tool.surf);
	SDL_UpdateWindowSurface(rt->tool.win);
}
