/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:31:26 by fsidler           #+#    #+#             */
/*   Updated: 2016/09/06 16:05:53 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	ft_vectorscale(t_vec *v, float n)
{
	t_vec	res;

	res.x = v->x * n;
	res.y = v->y * n;
	res.z = v->z * n;
	return (res);
}

t_vec	ft_vectorsub(t_vec *v1, t_vec *v2)
{
	t_vec	sub;

	sub.x = v1->x - v2->x;
	sub.y = v1->y - v2->y;
	sub.z = v1->z - v2->z;
	return (sub);
}

t_vec	ft_vectorcross(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}

void	ft_vectornorm(t_vec *v)
{
	double	n;

	n = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= n;
	v->y /= n;
	v->z /= n;
}

void	ft_cosvec(t_vec *vec)
{
	vec->x = cos(vec->x);
	vec->y = cos(vec->y);
	vec->z = cos(vec->z);
}
