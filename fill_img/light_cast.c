/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 15:29:14 by sganon            #+#    #+#             */
/*   Updated: 2016/10/17 13:20:52 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double			vector_scalar(t_vec vect1, t_vec vect2)
{
	double		value;
	double		x;
	double		y;
	double		z;

	x = vect1.x * vect2.x;
	y = vect1.y * vect2.y;
	z = vect1.z * vect2.z;
	value = x + y + z;
	return (value);
}

static t_vec	get_normal(t_obj obj, t_env *rt)
{
	t_vec	normal;

	if (obj.type == 1)
		normal = ft_vectorsub(rt->inter, obj.pos);
	return (normalize_vector(normal));
}

static double	non_plane_light_cast(t_env *rt, t_obj obj, t_light light)
{
	t_vec		normal;
	double		cosi;

	rt->inter.x = rt->cam.pos.x + (rt->vector.x * rt->t);
	rt->inter.y = rt->cam.pos.y + (rt->vector.y * rt->t);
	rt->inter.z = rt->cam.pos.z + (rt->vector.z * rt->t);
	rt->lvector.x = light.pos.x - rt->inter.x;
	rt->lvector.y = light.pos.y - rt->inter.y;
	rt->lvector.z = light.pos.z - rt->inter.z;
	normal = get_normal(obj, rt);
	rt->lvector = normalize_vector(rt->lvector);
	cosi = vector_scalar(normal, rt->lvector);
	return (cosi);
}

void			light_cast(t_env *rt, t_obj obj)
{
	double		cosi;
	double		tmp;
	int			i;

	cosi = 0.2;
	i = 0;
	tmp = non_plane_light_cast(rt, obj, rt->tli[i]);
	draw_in_img(rt, tmp, obj);
}
