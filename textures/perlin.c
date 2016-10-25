/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 13:16:24 by sganon            #+#    #+#             */
/*   Updated: 2016/09/29 13:16:28 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "perlin.h"

static int		g_p[B + B + 2];
static float	g_g3[B + B + 2][3];
static int		g_start = 1;

static void	normalize3(float v[3])
{
	float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

static int	shuffle_it(int i)
{
	int k;
	int j;

	while (--i)
	{
		k = g_p[i];
		j = random() % B;
		g_p[i] = g_p[j];
		g_p[j] = k;
	}
	return (i);
}

static void	init(void)
{
	int i;
	int	j;
	int	k;

	i = -1;
	while (++i < B)
	{
		g_p[i] = i;
		j = -1;
		while (++j < 3)
			g_g3[i][j] = (float)((random() % (B + B)) - B) / B;
		normalize3(g_g3[i]);
	}
	i = shuffle_it(i);
	while (i++ < B + 2)
	{
		g_p[B + i] = g_p[i];
		j = -1;
		while (++j < 3)
			g_g3[B + i][j] = g_g3[i][j];
	}
	g_start = 0;
}

float		noise3(float vec[3])
{
	t_noise	n;
	int		i;
	int		j;

	if (g_start)
		init();
	setup_x(&n, vec);
	setup_y(&n, vec);
	setup_z(&n, vec);
	i = g_p[n.bx0];
	j = g_p[n.bx1];
	n.b00 = g_p[i + n.by0];
	n.b10 = g_p[j + n.by0];
	n.b01 = g_p[i + n.by1];
	n.b11 = g_p[j + n.by1];
	n.t = S_CURVE(n.rx0);
	n.sy = S_CURVE(n.ry0);
	n.sz = S_CURVE(n.rz0);
	get_a(&n, 1, g_g3);
	get_c(&n, g_g3);
	get_a(&n, 2, g_g3);
	get_d(&n, g_g3);
	return (LERP(n.sz, n.c, n.d));
}
