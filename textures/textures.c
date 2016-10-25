/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 18:49:46 by sganon            #+#    #+#             */
/*   Updated: 2016/09/29 18:49:47 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double	*ft_perlin(t_th *rt, int o, t_vec pos, double *tmp)
{
	double	noise_coef;
	double	fr;
	int		level;
	float	vec[3];

	noise_coef = 0;
	vec[0] = pos.x * 0.5;
	vec[1] = pos.y * 0.5;
	vec[2] = pos.z * 0.5;
	level = 1;
	while (++level < 10)
	{
		noise_coef += (1.0 / level) * fabs(noise3(vec));
	}
	noise_coef = 0.8 * cos((pos.x + pos.y + pos.z) * 0.05 + noise_coef) + 0.9;
	tmp[0] = rt->tobj[o].rgb_save.r / 255 * noise_coef;
	tmp[1] = rt->tobj[o].rgb_save.g / 255 * noise_coef;
	tmp[2] = rt->tobj[o].rgb_save.b / 255 * noise_coef;
	return (tmp);
}

double	*ft_chess(t_th *rt, int o, t_vec pos, double *tmp)
{
	if (((int)(pos.x + 99999) / 2 + (int)(pos.y * 2 + 99999) / 2) % 2 == 0)
	{
		tmp[0] = rt->tobj[o].rgb_save.r / 255 / 2;
		tmp[1] = rt->tobj[o].rgb_save.g / 255 / 2;
		tmp[2] = rt->tobj[o].rgb_save.b / 255 / 2;
	}
	else
	{
		tmp[0] = rt->tobj[o].rgb_save.r / 255;
		tmp[1] = rt->tobj[o].rgb_save.g / 255;
		tmp[2] = rt->tobj[o].rgb_save.b / 255;
	}
	return (tmp);
}

double	*ft_texture_map(t_th *rt, int o, t_vec pos, double *tmp)
{
	double	u;
	double	v;
	t_color	color;
	Uint32	pixel;

	if (rt->tobj[o].type != 1)
		return (tmp);
	rt->var.norm = get_norm(rt, rt->tobj[o], pos);
	u = ((0.5 + atanf(rt->var.norm.x / -rt->var.norm.z) /
		(2 * M_PI)) * rt->tobj[o].bmp->w + rt->tobj[o].offset_x) /
		rt->tobj[o].scale;
	v = ((0.5 - asin(rt->var.norm.y) / M_PI) *
		rt->tobj[o].bmp->h + rt->tobj[o].offset_y) / rt->tobj[o].scale;
	u = fmod(u, rt->tobj[o].bmp->w - 1);
	v = fmod(v, rt->tobj[o].bmp->h - 1);
	pixel = *((Uint32 *)(rt->tobj[o].bmp->pixels +
		(Uint32)v * (Uint32)rt->tobj[o].bmp->pitch +
		(Uint32)u * rt->tobj[o].bmp->format->BytesPerPixel));
	color.color = pixel;
	tmp[0] = ((double)color.rgb.b - 20) / 255;
	tmp[1] = ((double)color.rgb.g - 20) / 255;
	tmp[2] = ((double)color.rgb.r - 20) / 255;
	return (tmp);
}

double	*ft_texture(t_th *rt, int o, double *tmp, t_vec pos)
{
	if (rt->tobj[o].text_on)
	{
		if (rt->tobj[o].text_on == 3)
			tmp = ft_texture_map(rt, o, pos, tmp);
		if (rt->tobj[o].text_on == 1)
			tmp = ft_chess(rt, o, pos, tmp);
		if (rt->tobj[o].text_on == 2)
			tmp = ft_perlin(rt, o, pos, tmp);
		rt->tobj[o].rgb.r = 0;
		rt->tobj[o].rgb.g = 0;
		rt->tobj[o].rgb.b = 0;
	}
	if (!rt->var.text_bool)
		tmp = get_tabs(rt, &pos, tmp, 0);
	return (tmp);
}
