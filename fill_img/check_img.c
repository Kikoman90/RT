/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 16:46:38 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/14 16:17:40 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void			set_ray(t_th *rt, double *tmp, double x, double y)
{
	double	u;
	double	v;

	u = (x * 2.0 - (double)rt->win.res[1]) / (double)rt->win.res[0];
	v = ((double)rt->win.res[0] - y * 2.0) / (double)rt->win.res[1];
	rt->ray.ray_dir.x = u * I.x + v * J.x + FOV * K.x;
	rt->ray.ray_dir.y = u * I.y + v * J.y + FOV * K.y;
	rt->ray.ray_dir.z = u * I.z + v * J.z + FOV * K.z;
	ft_vectornorm(&rt->ray.ray_dir);
	rt->var.prim = 0;
	ft_dzero(tmp, 4);
}

static	void		call_inter(t_th *rt, t_obj *obj, double *tmp, double *res)
{
	int		o;
	t_vec	pos;

	if ((o = ft_intersection(rt, obj, rt->ray.ray_dir, rt->cam.pos)) > -1)
	{
		ft_vec_para(&pos, rt->cam.pos.x + rt->ray.t * rt->ray.ray_dir.x,
		rt->cam.pos.y + rt->ray.t * rt->ray.ray_dir.y, rt->cam.pos.z +
		rt->ray.t * rt->ray.ray_dir.z);
		rt->var.text_bool = 0;
		rt->var.o = o;
		tmp = ft_texture(rt, rt->var.o, tmp, pos);
		res[0] += ft_clamp(tmp[0], 0.0, 1.0);
		res[1] += ft_clamp(tmp[1], 0.0, 1.0);
		res[2] += ft_clamp(tmp[2], 0.0, 1.0);
		if (rt->var.effect_on > 0)
			effect(res, rt->var.effect_on);
	}
}

static unsigned int	raytrace(double x, double y, t_th *rt, t_obj *obj)
{
	double	res[3];
	double	*tmp;
	double	p;
	t_color	u;
	double	d;

	d = 255.;
	ft_dzero(res, 3);
	tmp = (double *)malloc(sizeof(double) * 4);
	p = 0.;
	while (y < rt->var.s_y + 1 && (x = rt->var.s_x) > -1)
	{
		while (x < rt->var.s_x + 1 && ++p)
		{
			set_ray(rt, tmp, x, y);
			call_inter(rt, obj, tmp, res);
			x = x + (1.0 / AA);
		}
		y = y + (1.0 / AA);
	}
	u.rgb = (t_rgb2){(res[2] / p) * d, (res[1] / p) * d, (res[0] / p) * d};
	free(tmp);
	return (u.color);
}

static int			my_thread_process(void *arg)
{
	double			x;
	double			y;
	t_tab_th		*tab;
	t_th			th;
	SDL_Rect		pos[1];

	tab = (t_tab_th *)arg;
	cpy_env_to_th(tab->rt, &th);
	y = -1;
	pos[0].x = th.win.res[0] / 4 + 1;
	while (++y < tab->rt->win.res[1])
	{
		x = (tab->i * tab->rt->win.res[0] / NB_THREAD);
		x += (tab->rt->speed && (int)x % 2 ^ (int)y % 2) ? 1 : 0;
		while (x < (tab->i + 1) * tab->rt->win.res[0] / NB_THREAD)
		{
			th.var.s_x = (int)x;
			th.var.s_y = (int)y;
			draw_in_img(x, y, raytrace(x, y, &th, th.tobj), tab->rt->win.surf);
			x += tab->rt->speed + 1;
		}
		if (tab->i == 0 && (int)y / (int)(th.win.res[0] / 2))
			draw_line_load(x, y, tab, &pos[0]);
	}
	return (0);
}

void				check_img(t_env *rt)
{
	SDL_Thread		*thread[NB_THREAD];
	t_tab_th		*tab;
	int				i;
	int				ret;

	tab = (t_tab_th *)malloc(sizeof(t_tab_th) * NB_THREAD);
	i = -1;
	while (++i < NB_THREAD)
	{
		tab[i].i = i;
		tab[i].rt = rt;
		thread[i] = SDL_CreateThread(my_thread_process, NULL, &tab[i]);
	}
	i = -1;
	while (++i < NB_THREAD)
		SDL_WaitThread(thread[i], &ret);
	if (rt->speed)
		draw_average_color(rt);
	free(tab);
}
