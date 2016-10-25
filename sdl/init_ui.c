/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 15:37:26 by sganon            #+#    #+#             */
/*   Updated: 2016/09/13 15:44:07 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void			get_img(t_env *rt, t_gui *tmp)
{
	tmp->img_static = SDL_CreateRGBSurface(0, tmp->pos.w, tmp->pos.h,
		32, 0, 0, 0, 0);
	SDL_FillRect(tmp->img_static, NULL, 0xBFFF);
	print_txt(tmp->img_static, tmp->action, (t_vec){-1, 0, 0}, rt->font);
	tmp->img_hover = SDL_CreateRGBSurface(0, tmp->pos.w, tmp->pos.h,
		32, 0, 0, 0, 0);
	SDL_FillRect(tmp->img_hover, NULL, 0xD2FF);
	print_txt(tmp->img_hover, tmp->action, (t_vec){-1, 0, 0}, rt->font);
	tmp->img_active = SDL_CreateRGBSurface(0, tmp->pos.w, tmp->pos.h,
		32, 0, 0, 0, 0);
	SDL_FillRect(tmp->img_active, NULL, 0xFA00);
	print_txt(tmp->img_active, tmp->action, (t_vec){-1, 0, 0}, rt->font);
}

static SDL_Rect		get_pos(char *file)
{
	SDL_Rect	pos;

	if (!ft_strcmp(file, "AA-"))
		pos = (SDL_Rect){230, 105, 50, 30};
	else if (!ft_strcmp(file, "AA+"))
		pos = (SDL_Rect){340, 105, 50, 30};
	else if (!ft_strcmp(file, "Ref-"))
		pos = (SDL_Rect){230, 155, 50, 30};
	else if (!ft_strcmp(file, "Ref+"))
		pos = (SDL_Rect){340, 155, 50, 30};
	else if (!ft_strcmp(file, "ScreenShot"))
		pos = (SDL_Rect){180, 650, 140, 30};
	else if (!ft_strcmp(file, "Close"))
		pos = (SDL_Rect){130, 700, 240, 60};
	else
		ft_error("An unexpected error occured", 0);
	return (pos);
}

char				**init_actions(void)
{
	char			**action_tab;
	unsigned int	i;

	i = 0;
	if (!(action_tab = (char **)malloc(sizeof(char *) * 7)))
		return (NULL);
	action_tab[i++] = ft_strdup("AA-");
	action_tab[i++] = ft_strdup("AA+");
	action_tab[i++] = ft_strdup("Ref+");
	action_tab[i++] = ft_strdup("Ref-");
	action_tab[i++] = ft_strdup("ScreenShot");
	action_tab[i++] = ft_strdup("Close");
	action_tab[i++] = NULL;
	return (action_tab);
}

t_gui				*init_ui(t_env *rt, char **action_tab)
{
	t_gui	*gui;

	if (*action_tab)
	{
		if (!(gui = (t_gui *)malloc(sizeof(t_gui))))
			return (NULL);
		gui->action = *action_tab;
		gui->pos = get_pos(gui->action);
		get_img(rt, gui);
		gui->next = init_ui(rt, action_tab + 1);
	}
	else
		gui = NULL;
	return (gui);
}
