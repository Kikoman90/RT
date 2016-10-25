/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_average_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:24:03 by jfortin           #+#    #+#             */
/*   Updated: 2016/10/17 13:25:21 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static float	*get_color_pixel(SDL_Surface *surface, int x, int y, float *tab)
{
	int		i;

	i = -1;
	while (++i < 3)
		tab[i] = *((unsigned char *)(surface->pixels + y * surface->pitch +
		x * surface->format->BytesPerPixel + i)) / 255.;
	return (tab);
}

static float	*average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
	return (r);
}

static double	add_pixels(int x, int y, t_env *rt, float *r)
{
	double	p;
	float	*tab;

	if (!(tab = (float *)malloc(sizeof(float) * 3)))
		return (1);
	p = 0.0;
	ft_fzero(r, 3);
	if (x > 0 && ++p > 0)
		average(r, get_color_pixel(rt->win.surf, x - 1, y, tab));
	if (x < rt->win.res[0] - 1 && ++p > 0)
		average(r, get_color_pixel(rt->win.surf, x + 1, y, tab));
	if (y > 0 && ++p > 0)
		average(r, get_color_pixel(rt->win.surf, x, y - 1, tab));
	if (y < rt->win.res[1] - 1 && ++p > 0)
		average(r, get_color_pixel(rt->win.surf, x, y + 1, tab));
	free(tab);
	return (p);
}

static int		my_thread_process(void *arg)
{
	t_tab_th	*tab;
	float		r[3];
	double		p;
	int			x;
	int			y;

	tab = (t_tab_th *)arg;
	y = -1;
	while (++y < tab->rt->win.res[1])
	{
		x = tab->i * tab->rt->win.res[0] / NB_THREAD;
		if (!(x % 2 ^ y % 2))
			++x;
		while (x < tab->rt->win.res[0] * (tab->i + 1) / NB_THREAD)
		{
			p = add_pixels(x, y, tab->rt, r);
			draw_in_img(x, y, (((int)(r[2] / p * 255) & 0xff) << 16) +
			(((int)(r[1] / p * 255) & 0xff) << 8) +
			((int)(r[0] / p * 255) & 0xff), tab->rt->win.surf);
			x += 2;
		}
	}
	return (0);
}

void			draw_average_color(t_env *rt)
{
	SDL_Thread	*th[NB_THREAD];
	t_tab_th	tab[NB_THREAD];
	int			ret;
	int			i;

	i = -1;
	while (++i < NB_THREAD)
	{
		tab[i].i = i;
		tab[i].rt = rt;
		th[i] = SDL_CreateThread(my_thread_process, NULL, &tab[i]);
	}
	i = -1;
	while (++i < NB_THREAD)
		SDL_WaitThread(th[i], &ret);
}
