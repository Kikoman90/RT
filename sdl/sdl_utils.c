/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 17:07:59 by sganon            #+#    #+#             */
/*   Updated: 2016/10/06 19:38:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int		is_movemement(int key)
{
	if (key == SDLK_w || key == SDLK_a || key == SDLK_d || key == SDLK_s ||
			key == SDLK_q || key == SDLK_e || key == SDLK_RIGHT
			|| key == SDLK_LEFT || key == SDLK_UP || key == SDLK_DOWN)
		return (1);
	else
		return (0);
}

void	update_surface(t_env *rt)
{
	SDL_Rect		pos;

	pos.w = rt->win.res[0] / 2;
	pos = (SDL_Rect){pos.w / 2, LOAD_Y, pos.w + 4, LOAD_H};
	SDL_FillRect(rt->win.load, &pos, 0);
	pos = (SDL_Rect){++pos.x, ++pos.y, pos.w - 2, LOAD_H - 2};
	SDL_FillRect(rt->win.load, &pos, 0xFFFFFF);
	pos = (SDL_Rect){pos.x--, LOAD_Y, pos.w + 2, LOAD_H};
	SDL_UpdateWindowSurfaceRects(rt->win.win, &pos, 1);
	check_img(rt);
	SDL_BlitSurface(rt->win.surf, NULL, rt->win.load, NULL);
	SDL_UpdateWindowSurface(rt->win.win);
	SDL_FillRect(rt->tool.surf, NULL, 0);
	initial_ui_surf(rt);
	print_infos(rt, rt->tool.surf);
	SDL_UpdateWindowSurface(rt->tool.win);
}

void	initial_ui_surf(t_env *rt)
{
	t_gui	*tmp;

	tmp = rt->gui;
	while (tmp)
	{
		SDL_BlitSurface(tmp->img_static, NULL, rt->tool.surf, &tmp->pos);
		tmp = tmp->next;
	}
}

t_gui	*is_on_a_button(int x, int y, t_gui *gui)
{
	while (gui)
	{
		if ((x > gui->pos.x) && (x < gui->pos.x + gui->pos.w)
				&& (y > gui->pos.y) && (y < gui->pos.y + gui->pos.h))
			return (gui);
		gui = gui->next;
	}
	return (NULL);
}

void	clean_quit(t_env *rt)
{
	SDL_FreeSurface(rt->win.load);
	SDL_FreeSurface(rt->win.surf);
	SDL_FreeSurface(rt->tool.surf);
	SDL_DestroyWindow(rt->win.win);
	SDL_DestroyWindow(rt->tool.win);
	TTF_Quit();
	SDL_Quit();
}
