/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 12:48:09 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/18 12:48:22 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		handle_events(t_env *rt)
{
	while (1)
	{
		if (SDL_WaitEvent(&rt->event))
		{
			if (rt->event.window.event == SDL_WINDOWEVENT_CLOSE)
				return ;
			if (rt->event.type == SDL_KEYDOWN)
			{
				if (keydown(rt, KEYPRESS))
					return ;
			}
			else if (rt->event.type == SDL_KEYUP && KEYPRESS == SDLK_LSHIFT)
			{
				rt->speed = (rt->speed ? 0 : 1);
				update_surface(rt);
			}
			if ((rt->event.type == SDL_MOUSEMOTION
						|| rt->event.type == SDL_MOUSEBUTTONDOWN)
					&& rt->event.window.windowID == rt->tool.win_id)
				ft_ui(rt);
			if (rt->event.type == SDL_MOUSEBUTTONDOWN
					&& rt->event.window.windowID == rt->win.win_id)
				object_selection(rt);
		}
	}
}

int			handle_pos(t_env *rt, int key)
{
	if (key == SDLK_w)
		calc_key(rt, rt->cam.j, 5, 1);
	else if (key == SDLK_s)
		calc_key(rt, rt->cam.j, -5, 1);
	else if (key == SDLK_a)
		calc_key(rt, rt->cam.i, -5, 1);
	else if (key == SDLK_d)
		calc_key(rt, rt->cam.i, 5, 1);
	else if (key == SDLK_e)
		calc_key(rt, rt->cam.k, 5, 1);
	else if (key == SDLK_q)
		calc_key(rt, rt->cam.k, -5, 1);
	else if (key == SDLK_UP || key == SDLK_DOWN)
		(key == SDLK_UP) ? calc_key(rt, rt->cam.i, -10.0, 2) :
			calc_key(rt, rt->cam.i, 10.0, 2);
	else if (key == SDLK_RIGHT || key == SDLK_LEFT)
		(key == SDLK_LEFT) ? calc_key(rt, rt->cam.j, -10.0, 3) :
			calc_key(rt, rt->cam.j, 10.0, 3);
	update_surface(rt);
	return (1);
}

int			handle_object_pos(t_env *rt, int key)
{
	if ((rt->tobj[rt->sel_i].text_on == 3) && (key == SDLK_u || key == SDLK_i
		|| key == SDLK_j || key == SDLK_j || key == SDLK_o || key == SDLK_p))
		move_n_scale(rt, rt->sel_i, key);
	else if (key == SDLK_w || key == SDLK_s)
		rt->tobj[rt->sel_i].pos.y += key == SDLK_w ? 1 : -1;
	else if (key == SDLK_a || key == SDLK_d)
		rt->tobj[rt->sel_i].pos.x += key == SDLK_a ? -1.00 : 1.00;
	else if (key == SDLK_e || key == SDLK_q)
		rt->tobj[rt->sel_i].pos.z += key == SDLK_e ? 1.00 : -1.00;
	else if (key == SDLK_UP || key == SDLK_DOWN)
		rt->tobj[rt->sel_i].dir = axis_rot(rt->tobj[rt->sel_i].dir,
				rt->cam.i, key == SDLK_UP ? 10 : -10);
	else if (key == SDLK_RIGHT || key == SDLK_LEFT)
		rt->tobj[rt->sel_i].dir = axis_rot(rt->tobj[rt->sel_i].dir,
				rt->cam.j, key == SDLK_RIGHT ? 10 : -10);
	else if ((key == SDLK_COMMA || key == SDLK_PERIOD)
			&& rt->tobj[rt->sel_i].type != 4)
	{
		rt->tobj[rt->sel_i].rayon += (key == SDLK_COMMA ? -1 : 1);
		update_surface(rt);
	}
	if (key != SDLK_COMMA && key != SDLK_PERIOD && is_movemement(key))
		update_surface(rt);
	return (1);
}
