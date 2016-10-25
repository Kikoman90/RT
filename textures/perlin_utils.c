/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 14:16:49 by sganon            #+#    #+#             */
/*   Updated: 2016/10/17 14:17:13 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "perlin.h"

void		get_a(t_noise *n, int i, float g_g3[B + B + 2][3])
{
	if (i == 1)
	{
		n->q = g_g3[n->b00 + n->bz0];
		n->u = AT3_POINT(n->rx0, n->ry0, n->rz0);
		n->q = g_g3[n->b10 + n->bz0];
		n->v = AT3_POINT(n->rx1, n->ry0, n->rz0);
		n->a = LERP(n->t, n->u, n->v);
	}
	else if (i == 2)
	{
		n->q = g_g3[n->b00 + n->bz1];
		n->u = AT3_POINT(n->rx0, n->ry0, n->rz1);
		n->q = g_g3[n->b10 + n->bz1];
		n->v = AT3_POINT(n->rx1, n->ry0, n->rz1);
		n->a = LERP(n->t, n->u, n->v);
	}
}

void		get_c(t_noise *n, float g_g3[B + B + 2][3])
{
	n->q = g_g3[n->b01 + n->bz0];
	n->u = AT3_POINT(n->rx0, n->ry1, n->rz0);
	n->q = g_g3[n->b11 + n->bz0];
	n->v = AT3_POINT(n->rx1, n->ry1, n->rz0);
	n->b = LERP(n->t, n->u, n->v);
	n->c = LERP(n->sy, n->a, n->b);
}

void		get_d(t_noise *n, float g_g3[B + B + 2][3])
{
	n->q = g_g3[n->b01 + n->bz1];
	n->u = AT3_POINT(n->rx0, n->ry1, n->rz1);
	n->q = g_g3[n->b11 + n->bz1];
	n->v = AT3_POINT(n->rx1, n->ry1, n->rz1);
	n->b = LERP(n->t, n->u, n->v);
	n->d = LERP(n->sy, n->a, n->b);
}
