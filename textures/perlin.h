/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:45:19 by sganon            #+#    #+#             */
/*   Updated: 2016/10/17 13:45:22 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H
# define B 0x100
# define BM 0xff
# define N 0x1000
# define NP 12
# define NM 0xfff
# define S_CURVE(t) ( t * t * (3. - 2. * t) )
# define LERP(t, a, b) ( a + t * (b - a) )
# define AT3(rx,ry,rz) ( rx * n.q[0] + ry * n.q[1] + rz * n.q[2] )
# define AT3_POINT(rx,ry,rz) ( rx * n->q[0] + ry * n->q[1] + rz * n->q[2] )

typedef struct	s_noise
{
	int			bx0;
	int			bx1;
	int			by0;
	int			by1;
	int			bz0;
	int			bz1;
	int			b00;
	int			b01;
	int			b11;
	int			b10;
	float		rx0;
	float		rx1;
	float		ry0;
	float		ry1;
	float		rz0;
	float		rz1;
	float		*q;
	float		sy;
	float		sz;
	float		a;
	float		b;
	float		c;
	float		d;
	float		t;
	float		u;
	float		v;
}				t_noise;

void			setup_x(t_noise *n, float vec[3]);
void			setup_y(t_noise *n, float vec[3]);
void			setup_z(t_noise *n, float vec[3]);
void			get_a(t_noise *n, int i, float g_g3[B + B + B + 2][3]);
void			get_c(t_noise *n, float g_g3[B + B + B + 2][3]);
void			get_d(t_noise *n, float g_g3[B + B + B + 2][3]);
#endif
