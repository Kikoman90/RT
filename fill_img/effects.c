/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:41:47 by sganon            #+#    #+#             */
/*   Updated: 2016/10/17 17:42:01 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void			grayscale(double *res)
{
	double gray;

	gray = res[0] * 0.3 + res[1] * 0.3 + res[2] * 0.11;
	res[0] = ft_clamp(gray, 0.0, 1.0);
	res[1] = ft_clamp(gray, 0.0, 1.0);
	res[2] = ft_clamp(gray, 0.0, 1.0);
}

static void			sepia(double *r)
{
	r[0] = ft_clamp(r[0] * 0.393 + r[1] * 0.769 + r[2] * 0.189, 0.0, 1.0);
	r[1] = ft_clamp(r[0] * 0.349 + r[1] * 0.686 + r[2] * 0.168, 0.0, 1.0);
	r[2] = ft_clamp(r[0] * 0.272 + r[1] * 0.534 + r[2] * 0.131, 0.0, 1.0);
}

void				effect(double *res, int effect)
{
	if (effect == 1)
		grayscale(res);
	else if (effect == 2)
		sepia(res);
}
