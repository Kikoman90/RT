/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 14:04:06 by fsidler           #+#    #+#             */
/*   Updated: 2016/10/19 16:59:47 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int		get_shadow(t_th *rt, int tmp, int l, t_vec pos)
{
	t_vec	dist;
	int		i;
	double	a;

	i = -1;
	dist = ft_vectorsub(&rt->tli[l].pos, &pos);
	rt->ray.t = sqrtf(dot(&dist, &dist));
	ft_vectornorm(&dist);
	while (++i < rt->var.nbobj)
	{
		if (i != tmp)
		{
			if (rt->tobj[i].type == 1)
				a = inter_sphere(&rt->var, rt->tobj[i], dist, pos);
			else if (rt->tobj[i].type == 2)
				a = inter_cylinder(&rt->var, rt->tobj[i], dist, pos);
			else if (rt->tobj[i].type == 3)
				a = inter_cone(&rt->var, rt->tobj[i], dist, pos);
			else if (rt->tobj[i].type == 4 || rt->tobj[i].type == 5)
				a = inter_plane(&rt->var, rt->tobj[i], dist, pos);
			if (a > 0.1 && a < rt->ray.t)
				return (i);
		}
	}
	return (0);
}

static double	*get_spec(t_th *rt, int i, double d, double *tab)
{
	float	spec;
	float	tmp;
	t_vec	ref;
	t_vec	dist;

	dist = ft_vectorsub(&rt->tli[i].pos, rt->var.pos);
	spec = 0.0;
	ref = ft_vectorscale(&rt->var.norm,
		(2.0 * dot(&dist, &rt->var.norm)));
	ref = ft_vectorsub(&dist, &ref);
	ft_vectornorm(&ref);
	if ((tmp = dot(&ref, &rt->ray.ray_dir)) > 0.0)
	{
		spec = pow(tmp, 20.0) * 4 * d;
		spec = ft_clamp(spec, 0.0, 1.0);
	}
	tab[0] += (rt->tobj[O].spec == 1 && rt->tobj[O].type != 4) ?
		(spec * (rt->tli[i].rgb.r / 255)) : 0.;
	tab[1] += (rt->tobj[O].spec == 1 && rt->tobj[O].type != 4) ?
		(spec * (rt->tli[i].rgb.g / 255)) : 0.;
	tab[2] += (rt->tobj[O].spec == 1 && rt->tobj[O].type != 4) ?
		(spec * (rt->tli[i].rgb.b / 255)) : 0.;
	return (tab);
}

static double	*get_ambiant(t_th *rt, double *tab)
{
	if (rt->var.nbli == 0)
	{
		LAMBERT = rt->var.ambiant;
		rt->var.text_bool = 1;
		if (rt->tobj[rt->var.o].text_on)
			ft_texture(rt, rt->var.o, tab, *rt->var.pos);
		tab[0] = ft_clamp(LAMBERT * (rt->tobj[rt->var.o].rgb.r / 255), 0., 1.);
		tab[1] = ft_clamp(LAMBERT * (rt->tobj[rt->var.o].rgb.g / 255), 0., 1.);
		tab[2] = ft_clamp(LAMBERT * (rt->tobj[rt->var.o].rgb.b / 255), 0., 1.);
	}
	return (tab);
}

static double	*clamp_tab_diff(t_light light, double *tab, double d, t_th *rt)
{
	LAMBERT = ft_clamp(LAMBERT * 4.0 * d, 0.0, 1.0);
	rt->var.text_bool = 1;
	if (rt->tobj[rt->var.o].text_on)
		ft_texture(rt, rt->var.o, tab, *rt->var.pos);
	tab[0] += ft_clamp(LAMBERT *
		(rt->tobj[rt->var.o].rgb.r / 255) * (light.rgb.r / 255), 0., 1.);
	tab[1] += ft_clamp(LAMBERT *
		(rt->tobj[rt->var.o].rgb.g / 255) * (light.rgb.g / 255), 0., 1.);
	tab[2] += ft_clamp(LAMBERT *
		(rt->tobj[rt->var.o].rgb.b / 255) * (light.rgb.b / 255), 0., 1.);
	return (tab);
}

double			*get_diffuse(t_th *rt, int o, t_vec *pos, double *tab)
{
	int		sh_ob;
	int		i;
	t_vec	dist;
	double	d;
	double	spec;

	i = -1;
	rt->var.o = o;
	rt->var.pos = pos;
	while (++i < rt->var.nbli)
	{
		LAMBERT = 0.15;
		dist = ft_vectorsub(&rt->tli[i].pos, pos);
		d = ft_clamp(1.0 / sqrtf(sqrtf(dot(&dist, &dist))), 0.0, 1.0);
		ft_vectornorm(&dist);
		if ((sh_ob = get_shadow(rt, o, i, *pos)) == 0)
			LAMBERT += ft_clamp(dot(&dist, &rt->var.norm), 0.0, 1.0);
		else
			LAMBERT += (rt->tobj[sh_ob].refr > 0.0) ? rt->tobj[sh_ob].coef_refr
				* ft_clamp(dot(&dist, &rt->var.norm), 0.0, 1.0) : 0;
		tab = clamp_tab_diff(rt->tli[i], tab, d, rt);
		tab = get_spec(rt, i, d, tab);
	}
	get_ambiant(rt, tab);
	return (tab);
}
