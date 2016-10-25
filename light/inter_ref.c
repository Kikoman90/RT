/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_ref.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 17:08:28 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/18 17:08:41 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	refr_inter(t_th *rt, int i, t_obj *obj, t_vec pos)
{
	int		ob;
	double	dist;

	ob = -1;
	while (++i < rt->var.nbobj)
	{
		if (obj[i].type == 1)
			dist = inter_sphere(&rt->var, obj[i], rt->var.ref, pos);
		else if (obj[i].type == 2)
			dist = inter_cylinder(&rt->var, obj[i], rt->var.ref, pos);
		else if (obj[i].type == 3)
			dist = inter_cone(&rt->var, obj[i], rt->var.ref, pos);
		else if (obj[i].type == 4 || obj[i].type == 5)
			dist = inter_plane(&rt->var, obj[i], rt->var.ref, pos);
		if (dist > 0.1 && dist < rt->ray.t)
		{
			ob = i;
			rt->ray.t = dist;
		}
	}
	return (ob);
}
