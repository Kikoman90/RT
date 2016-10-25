/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:29:34 by jfortin           #+#    #+#             */
/*   Updated: 2016/10/17 14:03:35 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_vec		axis_rot(t_vec vec, t_vec axis, double ang)
{
	double	rad;
	double	tmp_x;
	double	tmp_y;

	rad = ang * (PI / 180.0f);
	tmp_x = vec.x;
	vec.x = (cos(rad) + (powf(axis.x, 2.) * (1 - cos(rad)))) * vec.x +
		(axis.x * axis.y * (1 - cos(rad)) - (axis.z * sin(rad))) * vec.y +
		(axis.x * axis.z * (1 - cos(rad)) + (axis.y * sin(rad))) * vec.z;
	tmp_y = vec.y;
	vec.y = (axis.y * axis.x * (1 - cos(rad)) + (axis.z * sin(rad))) * tmp_x +
		(cos(rad) + (powf(axis.y, 2.) * (1 - cos(rad)))) * vec.y +
		(axis.y * axis.z * (1 - cos(rad)) - (axis.x * sin(rad))) * vec.z;
	vec.z = (axis.z * axis.x * (1 - cos(rad)) - (axis.y * sin(rad))) * tmp_x +
		(axis.z * axis.y * (1 - cos(rad)) + (axis.x * sin(rad))) * tmp_y +
		(cos(rad) + (powf(axis.z, 2.) * (1 - cos(rad)))) * vec.z;
	ft_vectornorm(&vec);
	return (vec);
}

void		move_n_scale(t_env *rt, int o, int key)
{
	if (key == SDLK_u)
		rt->tobj[o].offset_x += 10;
	if (key == SDLK_i)
	{
		rt->tobj[o].offset_x = rt->tobj[o].offset_x < 10 ?
		rt->tobj[o].bmp->w - 10 : rt->tobj[o].offset_x - 10;
	}
	if (key == SDLK_j)
		rt->tobj[o].offset_y += 10;
	if (key == SDLK_k)
	{
		rt->tobj[o].offset_y = rt->tobj[o].offset_y < 10 ?
		rt->tobj[o].bmp->h - 10 : rt->tobj[o].offset_y - 10;
	}
	if (key == SDLK_o)
		rt->tobj[o].scale += 0.1;
	if (key == SDLK_p)
		rt->tobj[o].scale = rt->tobj[o].scale < 0.2 ?
			rt->tobj[o].scale : rt->tobj[o].scale - 0.1;
	update_surface(rt);
}

void		calc_key(t_env *rt, t_vec axis, double offset, int info)
{
	t_vec	tmp;

	if (info == 1)
		rt->cam.pos = (t_vec){rt->cam.pos.x + offset * axis.x,
			rt->cam.pos.y + offset * axis.y,
			rt->cam.pos.z + offset * axis.z};
	else if (info == 2)
	{
		rt->cam.dir = axis_rot(rt->cam.dir, axis, offset);
		rt->cam.j = axis_rot(rt->cam.j, axis, offset);
		rt->cam.k = axis_rot(rt->cam.k, axis, offset);
	}
	else if (info == 3)
	{
		rt->cam.dir = axis_rot(rt->cam.dir, axis, offset);
		rt->cam.i = axis_rot(rt->cam.i, axis, offset);
		rt->cam.k = axis_rot(rt->cam.k, axis, offset);
	}
}

int			keydown(t_env *rt, int key)
{
	if (key == SDLK_ESCAPE)
		return (1);
	else if (!rt->selection && is_movemement(key))
		handle_pos(rt, key);
	else if (rt->selection)
		handle_object_pos(rt, key);
	else if (key == SDLK_t || (key == SDLK_g && rt->var.max_ref > 0))
	{
		rt->var.max_ref += (key == SDLK_t ? 1 : -1);
		update_surface(rt);
	}
	return (0);
}

void		create_window(t_env *rt)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() < 0)
		ft_error("SDL failed to init", -1);
	rt->win.win = SDL_CreateWindow(rt->win.windname, 200, 200, rt->win.res[0],
			rt->win.res[1], SDL_WINDOW_SHOWN);
	rt->tool.win = SDL_CreateWindow("Tool box",
			210 + rt->win.res[0], 200, 500, 800, SDL_WINDOW_SHOWN);
	if (!rt->win.win || !rt->tool.win)
		ft_error("failed to create windows", -1);
	rt->win.load = SDL_GetWindowSurface(rt->win.win);
	rt->tool.surf = SDL_GetWindowSurface(rt->tool.win);
	if (!rt->win.load || !rt->tool.surf)
		ft_error("failed to create surfaces", -1);
	rt->win.win_id = SDL_GetWindowID(rt->win.win);
	rt->tool.win_id = SDL_GetWindowID(rt->tool.win);
	if (!(rt->win.surf = SDL_CreateRGBSurface(0, rt->win.res[0],
					rt->win.res[1], 32, 0, 0, 0, 0)))
		ft_error("failed to create surface", -1);
	if (!(rt->font = TTF_OpenFont("xerox.ttf", 18)))
		ft_error("Cannot open font", 0);
	rt->gui = init_ui(rt, init_actions());
	update_surface(rt);
	handle_events(rt);
	clean_quit(rt);
}
