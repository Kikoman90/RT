/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 18:03:57 by sganon            #+#    #+#             */
/*   Updated: 2016/10/06 19:17:20 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void	take_screenshot(t_env *rt)
{
	static int	id = 1;
	char		*filename;
	char		*open;

	filename = ft_strjoin("screenshot", ft_itoa(id), 'R');
	filename = ft_strjoin(filename, ".bmp", 'L');
	SDL_SaveBMP(rt->win.surf, filename);
	system(open = ft_strjoin("open ", filename, 'R'));
	free(open);
	id++;
}

static void	get_action(t_env *rt, t_gui *tmp)
{
	if (!ft_strcmp(tmp->action, "AA+") && rt->win.aa <= 8)
	{
		rt->win.aa *= 2;
		update_surface(rt);
	}
	if (!ft_strcmp(tmp->action, "AA-") && rt->win.aa >= 2)
	{
		rt->win.aa /= 2;
		update_surface(rt);
	}
	if (!ft_strcmp(tmp->action, "Ref+"))
	{
		rt->var.max_ref++;
		update_surface(rt);
	}
	if (!ft_strcmp(tmp->action, "Ref-") && rt->var.max_ref > 0)
	{
		rt->var.max_ref--;
		update_surface(rt);
	}
	if (!strcmp(tmp->action, "Close"))
		ft_error("You've just quit RT, gg!", 0);
	if (!strcmp(tmp->action, "ScreenShot"))
		take_screenshot(rt);
}

void		ft_ui(t_env *rt)
{
	int		x;
	int		y;
	t_gui	*tmp;

	x = rt->event.motion.x;
	y = rt->event.motion.y;
	if ((tmp = is_on_a_button(x, y, rt->gui))
			&& rt->event.window.windowID == rt->tool.win_id)
	{
		if (rt->event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_BlitSurface(tmp->img_active, NULL, rt->tool.surf, &tmp->pos);
			SDL_UpdateWindowSurfaceRects(rt->tool.win, &tmp->pos, 1);
			get_action(rt, tmp);
		}
		SDL_BlitSurface(tmp->img_hover, NULL, rt->tool.surf, &tmp->pos);
	}
	else
		initial_ui_surf(rt);
	SDL_UpdateWindowSurface(rt->tool.win);
}
