/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 10:33:57 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/06 19:14:25 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	draw_in_img(int x, int y, size_t color, SDL_Surface *surf)
{
	*((unsigned int *)(surf->pixels + y * surf->pitch + x *
		surf->format->BytesPerPixel)) = color;
}
