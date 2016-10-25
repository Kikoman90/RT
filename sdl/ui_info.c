/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 13:19:25 by sganon            #+#    #+#             */
/*   Updated: 2016/09/16 15:21:49 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static char	*type_to_name(int type)
{
	if (type == 1)
		return ("Sphere");
	else if (type == 2)
		return ("Cylinder");
	else if (type == 3)
		return ("Cone");
	else if (type == 4)
		return ("Plane");
	else if (type == 5)
		return ("Disk");
	else
		return ("Error");
}

SDL_Rect	print_txt(SDL_Surface *dest, char *str, t_vec coord, TTF_Font *font)
{
	SDL_Surface	*txt_surf;
	SDL_Color	txt_color;
	SDL_Rect	text_pos;

	txt_color = (SDL_Color){255, 255, 255, 0};
	if (!str)
		ft_error("text is null", 0);
	txt_surf = TTF_RenderUTF8_Blended(font, str, txt_color);
	text_pos = (SDL_Rect){coord.x, coord.y, txt_surf->w, txt_surf->h};
	if (coord.x < 0 || coord.y < 0)
	{
		text_pos.x = (dest->w - txt_surf->w) / 2;
		text_pos.y = (dest->h - txt_surf->h) / 2;
	}
	SDL_BlitSurface(txt_surf, NULL, dest, &text_pos);
	if (coord.z)
		free(str);
	SDL_FreeSurface(txt_surf);
	return (text_pos);
}

static void	print_cam_inf(SDL_Surface *surf, t_cam cam, TTF_Font *font)
{
	int		y;

	y = 300;
	print_txt(surf, "Camera Position:", (t_vec){50, y, 0}, font);
	print_txt(surf, ft_ftoa(cam.pos.x), (t_vec){300, y, 1}, font);
	print_txt(surf, ft_ftoa(cam.pos.y), (t_vec){350, y, 1}, font);
	print_txt(surf, ft_ftoa(cam.pos.z), (t_vec){400, y, 1}, font);
	print_txt(surf, "Camera Rotation:", (t_vec){47, y + 50, 0}, font);
	print_txt(surf, ft_ftoa(cam.dir.x), (t_vec){300, y + 50, 1}, font);
	print_txt(surf, ft_ftoa(cam.dir.y), (t_vec){350, y + 50, 1}, font);
	print_txt(surf, ft_ftoa(cam.dir.z), (t_vec){400, y + 50, 1}, font);
}

static void	print_obj_inf(SDL_Surface *surf, t_obj tobj, TTF_Font *font)
{
	print_txt(surf, "Object type:", (t_vec){90, 450, 0}, font);
	print_txt(surf, type_to_name(tobj.type), (t_vec){300, 450, 0}, font);
	print_txt(surf, "Object Position:", (t_vec){50, 500, 0}, font);
	print_txt(surf, ft_ftoa(tobj.pos.x), (t_vec){300, 500, 1}, font);
	print_txt(surf, ft_ftoa(tobj.pos.y), (t_vec){350, 500, 1}, font);
	print_txt(surf, ft_ftoa(tobj.pos.z), (t_vec){400, 500, 1}, font);
	print_txt(surf, "Object Rotation:", (t_vec){47, 550, 0}, font);
	print_txt(surf, ft_ftoa(tobj.dir.x), (t_vec){300, 550, 1}, font);
	print_txt(surf, ft_ftoa(tobj.dir.y), (t_vec){350, 550, 1}, font);
	print_txt(surf, ft_ftoa(tobj.dir.z), (t_vec){400, 550, 1}, font);
	if (tobj.type != 4)
	{
		print_txt(surf, "Object Radius:", (t_vec){62, 600, 0}, font);
		print_txt(surf, ft_ftoa(tobj.rayon), (t_vec){300, 600, 1}, font);
	}
}

void		print_infos(t_env *rt, SDL_Surface *surf)
{
	char	*res;

	print_txt(surf, "Name:", (t_vec){150, 20, 0}, rt->font);
	print_txt(surf, rt->win.windname, (t_vec){250, 20, 0}, rt->font);
	print_txt(surf, "Resolution:", (t_vec){98, 60, 0}, rt->font);
	res = ft_strjoin(ft_itoa(rt->win.res[0]), " x ", 'L');
	print_txt(surf, ft_strjoin(res, ft_itoa(rt->win.res[1]), 'B'),
		(t_vec){250, 60, 1}, rt->font);
	print_txt(surf, "Anti Aliasing:", (t_vec){67, 110, 0}, rt->font);
	print_txt(surf, ft_itoa(rt->win.aa), (t_vec){300, 110, 1}, rt->font);
	print_txt(surf, "Max reflexion:", (t_vec){62, 160, 0}, rt->font);
	print_txt(surf, ft_itoa(rt->var.max_ref), (t_vec){300, 160, 1}, rt->font);
	print_txt(surf, "Mode speed:", (t_vec){100, 250, 0}, rt->font);
	print_txt(surf, rt->speed ? "oui" : "non", (t_vec){300, 250, 0}, rt->font);
	print_cam_inf(surf, rt->cam, rt->font);
	if (rt->selection)
		print_obj_inf(surf, rt->tobj[rt->sel_i], rt->font);
}
