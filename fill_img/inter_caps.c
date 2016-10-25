/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:30:04 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/18 13:30:13 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double	caps(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	t_vec	pos_lim;
	t_vec	new_pos;
	t_vec	cap_p1;
	t_vec	cap_p2;

	if (rt->t0 > 0.)
		pos_lim = ft_vectoradd(tmp.pos, ft_vectorscale(&tmp.dir, tmp.hauteur));
	if ((rt->t0 < rt->t1 && rt->t0 > 0.) && (tmp.type != 3))
	{
		new_pos = ft_vectoradd(pos, ft_vectorscale(&ray, rt->t0));
		cap_p1 = ft_vectorsub(&new_pos, &tmp.pos);
		if (sqrtf(dot(&cap_p1, &cap_p1)) <= rt->radius)
			return (rt->t0);
	}
	else if (rt->t1 < rt->t0 && rt->t1 > 0.)
	{
		new_pos = ft_vectoradd(pos, ft_vectorscale(&ray, rt->t1));
		cap_p2 = ft_vectorsub(&new_pos, &pos_lim);
		if (sqrtf(dot(&cap_p2, &cap_p2)) <= rt->radius)
			return (rt->t1);
	}
	return (-1);
}

double	inter_caps(t_var *rt, t_obj tmp, t_vec ray, t_vec pos)
{
	t_vec	pos_lim;
	t_vec	new_pos;
	t_vec	cap_p1;
	t_vec	cap_p2;

	if (rt->t0 > 0.)
	{
		pos_lim = ft_vectoradd(tmp.pos, ft_vectorscale(&tmp.dir, tmp.hauteur));
		new_pos = ft_vectoradd(pos, ft_vectorscale(&ray, rt->t0));
		cap_p1 = ft_vectorsub(&new_pos, &tmp.pos);
		cap_p2 = ft_vectorsub(&new_pos, &pos_lim);
		if (dot(&tmp.dir, &cap_p1) > 0. &&
				dot(&tmp.dir, &cap_p2) < 0.)
			return (rt->t0);
	}
	rt->radius = tmp.rayon;
	if (tmp.type == 3)
		rt->radius = tan(tmp.rayon * (PI / 180.0f)) * tmp.hauteur;
	rt->t0 = ((dot(&tmp.dir, &tmp.pos) -
				dot(&tmp.dir, &pos)) / dot(&tmp.dir, &ray));
	rt->t1 = ((dot(&tmp.dir, &pos_lim) -
				dot(&tmp.dir, &pos)) / dot(&tmp.dir, &ray));
	return (caps(rt, tmp, ray, pos));
}
