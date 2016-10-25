/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 13:23:05 by jfortin           #+#    #+#             */
/*   Updated: 2016/10/17 13:23:43 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	draw_line_load(int x, int y, t_tab_th *tab, SDL_Rect *pos)
{
	pos[0] = (SDL_Rect){pos[0].x + ((int)y / (int)(tab->rt->win.res[0] / 2)),
		LOAD_Y + 2, 1, LOAD_H - 4};
	SDL_FillRect(tab->rt->win.load, &pos[0], LOAD_COLOR);
	SDL_UpdateWindowSurfaceRects(tab->rt->win.win, pos, 1);
}
