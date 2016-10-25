/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:58:38 by sganon            #+#    #+#             */
/*   Updated: 2016/10/17 13:58:40 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

void		setup_x(t_noise *n, float vec[3])
{
	n->t = vec[0] + N;
	n->bx0 = ((int)n->t) & BM;
	n->bx1 = (n->bx0 + 1) & BM;
	n->rx0 = n->t - (int)n->t;
	n->rx1 = n->rx0 - 1.;
}

void		setup_y(t_noise *n, float vec[3])
{
	n->t = vec[1] + N;
	n->by0 = ((int)n->t) & BM;
	n->by1 = (n->by0 + 1) & BM;
	n->ry0 = n->t - (int)n->t;
	n->ry1 = n->ry0 - 1.;
}

void		setup_z(t_noise *n, float vec[3])
{
	n->t = vec[2] + N;
	n->bz0 = ((int)n->t) & BM;
	n->bz1 = (n->bz0 + 1) & BM;
	n->rz0 = n->t - (int)n->t;
	n->rz1 = n->rz0 - 1.;
}
