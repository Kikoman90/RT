/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 16:15:25 by fsidler           #+#    #+#             */
/*   Updated: 2016/10/12 19:10:45 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void			set_system(t_env *rt)
{
	rt->cam.k = (t_vec){rt->cam.dir.x, rt->cam.dir.y, rt->cam.dir.z};
	ft_vectornorm(&rt->cam.k);
	rt->cam.i = ft_vectorcross(&(t_vec){0.0, 1.0, 0.0}, &rt->cam.k);
	ft_vectornorm(&rt->cam.i);
	rt->cam.j = ft_vectorcross(&rt->cam.k, &rt->cam.i);
	ft_vectornorm(&rt->cam.j);
}
