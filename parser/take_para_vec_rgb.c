/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 18:03:01 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/14 18:49:32 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double		check_value(char *val, int *verif, int i, int j)
{
	int		chk[2];
	double	res;

	ft_memset_int((int*)chk, 0, 2);
	while (val[++j] != ' ' && val[j] != '}')
	{
		if ((val[j] == '-' || val[j] == '.') ||
			(val[j] >= '0' && val[j] <= '9'))
		{
			if (val[j] == '-' && j > 0 && (*verif += 1) > 0)
				return ((double)exit_error("ERROR: invalid value. line: ", i));
			else if (((val[j] == '.' && chk[1] == 1) ||
				(val[j] == '.' && chk[0] == 0)) && (*verif += 1) > 0)
				return ((double)exit_error("ERROR: invalid value. line: ", i));
			else if (val[j] >= '0' && val[j] <= '9')
				chk[0] = 1;
			else if (val[j] == '.')
				chk[1]++;
		}
		else
			*verif += 1;
	}
	if ((val[j - 1] == '.' && (*verif++) > 0) || *verif > 0)
		return ((double)exit_error("ERROR: invalid value . line: ", i));
	return (get_value(val, j, verif));
}

char		*get_vec(char *line, t_vec *vect, int i, int j)
{
	int	verif[6];

	ft_memset_int((int*)verif, 0, 6);
	while (line[++j] != '}' && line[j])
	{
		if (line[j] == 'x')
		{
			vect->x = check_value((line + ++j), &verif[3], i, -1);
			verif[0] += 1;
		}
		else if (line[j] == 'y')
		{
			vect->y = check_value((line + ++j), &verif[4], i, -1);
			verif[1] += 1;
		}
		else if (line[j] == 'z')
		{
			vect->z = check_value((line + ++j), &verif[5], i, -1);
			verif[2] += 1;
		}
	}
	if ((verif[0] != 1) || (verif[1] != 1) || (verif[2] != 1) || (verif[3] > 0)
		|| (verif[4] > 0) || (verif[5] > 0))
		return (exit_null("ERROR: incomplete vector coordinates. line: ", i));
	return ((line + j));
}

char		*check_vect(char *line, t_vec *vect, int i)
{
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	if ((line = get_vec(line, vect, i, -1)) == NULL)
		return (NULL);
	return (line);
}

char		*get_rgb(char *line, t_rgb *rgb, int i, int j)
{
	int	verif[3];

	ft_memset_int((int*)verif, 0, 3);
	while (line[++j] != '}' && line[j])
	{
		if (line[j] == 'r')
		{
			rgb->r = ft_matoi2(line + ++j);
			verif[0] += 1;
		}
		else if (line[j] == 'g')
		{
			rgb->g = ft_matoi2(line + ++j);
			verif[1] += 1;
		}
		else if (line[j] == 'b')
		{
			rgb->b = ft_matoi2(line + ++j);
			verif[2] += 1;
		}
	}
	if ((verif[0] != 1) || (verif[1] != 1) || (verif[2] != 1))
		return (exit_null("ERROR: incomplete color data. line: ", i));
	return ((line + j));
}

char		*check_rgb(char *line, t_rgb *rgb, int i)
{
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	if ((line = get_rgb(line, rgb, i, -1)) == NULL)
		return (NULL);
	if ((rgb->r < 0 || rgb->r > 255) || (rgb->g < 0 || rgb->g > 255) ||
		(rgb->b < 0 || rgb->b > 255))
		return (exit_null("ERROR: invalid RGB values. line: ", i));
	return (line);
}
