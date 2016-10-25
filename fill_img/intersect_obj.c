/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 14:46:57 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/17 13:26:53 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double	inter_sphere(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	double disc;

	ft_vectornorm(&tmp.dir);
	rt->dist = ft_vectorsub(&pos, &tmp.pos);
	rt->a = dot(&ray, &ray);
	rt->b = 2. * dot(&ray, &rt->dist);
	rt->c = dot(&rt->dist, &rt->dist) - pow(tmp.rayon, 2.);
	if ((disc = rt->b * rt->b - 4. * rt->a * rt->c) < 0. && tmp.hauteur <= 0.)
		return (-1);
	rt->t0 = (disc > 0.) ? (-rt->b + sqrtf(disc)) / (2. * rt->a) : -1.0;
	rt->t1 = (disc > 0.) ? (-rt->b - sqrtf(disc)) / (2. * rt->a) : -1.0;
	if (rt->t0 > rt->t1 && rt->t1 > 0.)
		rt->t0 = rt->t1;
	if (tmp.hauteur > 0.)
		rt->t0 = inter_caps(rt, tmp, ray, pos);
	return (rt->t0);
}

double	inter_cylinder(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	double	disc;
	t_vec	v_tmp;
	t_vec	v_tmp2;

	rt->dist = ft_vectorsub(&pos, &tmp.pos);
	ft_vectornorm(&tmp.dir);
	v_tmp = ft_vectorscale(&tmp.dir, dot(&ray, &tmp.dir));
	v_tmp = ft_vectorsub(&ray, &v_tmp);
	rt->a = dot(&v_tmp, &v_tmp);
	v_tmp2 = ft_vectorscale(&tmp.dir, dot(&rt->dist, &tmp.dir));
	v_tmp2 = ft_vectorsub(&rt->dist, &v_tmp2);
	rt->b = 2. * dot(&v_tmp, &v_tmp2);
	rt->c = dot(&v_tmp2, &v_tmp2) - pow(tmp.rayon, 2.);
	if ((disc = rt->b * rt->b - 4. * rt->a * rt->c) < 0. && tmp.hauteur <= 0.)
		return (-1);
	rt->t0 = (disc > 0.) ? (-rt->b + sqrtf(disc)) / (2. * rt->a) : -1.0;
	rt->t1 = (disc > 0.) ? (-rt->b - sqrtf(disc)) / (2. * rt->a) : -1.0;
	if (rt->t0 > rt->t1 && rt->t1 > 0.)
		rt->t0 = rt->t1;
	if (tmp.hauteur > 0.)
		rt->t0 = inter_caps(rt, tmp, ray, pos);
	return (rt->t0);
}

double	inter_cone(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	double	disc;
	double	rad;
	t_vec	v[2];

	rad = tmp.rayon * (PI / 180.0f);
	rt->dist = ft_vectorsub(&pos, &tmp.pos);
	ft_vectornorm(&tmp.dir);
	v[0] = ft_vectorscale(&tmp.dir, dot(&ray, &tmp.dir));
	v[0] = ft_vectorsub(&ray, &v[0]);
	rt->a = pow(cos(rad), 2.) * dot(&v[0], &v[0]) -
		pow(sin(rad), 2.) * pow(dot(&ray, &tmp.dir), 2.);
	v[1] = ft_vectorscale(&tmp.dir, dot(&rt->dist, &tmp.dir));
	v[1] = ft_vectorsub(&rt->dist, &v[1]);
	rt->b = 2. * pow(cos(rad), 2.) * dot(&v[0], &v[1]) - 2. * pow(sin(
	rad), 2.) * dot(&ray, &tmp.dir) * dot(&rt->dist, &tmp.dir);
	rt->c = pow(cos(rad), 2.) * dot(&v[1], &v[1]) - pow(sin(rad), 2.) *
	pow(dot(&rt->dist, &tmp.dir), 2.);
	if ((disc = rt->b * rt->b - 4. * rt->a * rt->c) < 0. && tmp.hauteur <= 0.)
		return (-1);
	rt->t0 = (disc > 0.) ? (-rt->b + sqrtf(disc)) / (2. * rt->a) : -1.0;
	rt->t1 = (disc > 0.) ? (-rt->b - sqrtf(disc)) / (2. * rt->a) : -1.0;
	rt->t0 = rt->t0 > rt->t1 && rt->t1 > 0. ? rt->t1 : rt->t0;
	if (tmp.hauteur > 0.)
		rt->t0 = inter_caps(rt, tmp, ray, pos);
	return (rt->t0);
}

double	inter_plane(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	t_vec	p;
	t_vec	v;
	double	d;

	rt->t0 = ((dot(&tmp.dir, &tmp.pos) -
				dot(&tmp.dir, &pos)) / dot(&tmp.dir, &ray));
	if (rt->t0 < 0.0001)
		return (-1);
	if (tmp.type == 4)
		return (rt->t0);
	else if (tmp.type == 5)
	{
		ft_vec_para(&p, pos.x + ray.x * rt->t0,
				pos.y + ray.y * rt->t0, pos.z + ray.z * rt->t0);
		v = ft_vectorsub(&p, &tmp.pos);
		d = dot(&v, &v);
		if (sqrtf(d) <= tmp.rayon)
			return (rt->t0);
	}
	return (-1);
}

int		ft_intersection(t_th *rt, t_obj *obj, t_vec ray, t_vec pos)
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
