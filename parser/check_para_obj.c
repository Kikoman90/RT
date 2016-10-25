/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_para.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:30:22 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/26 15:30:49 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static	int		take_road(char *tmp, void **text)
{
	int		i;
	char	*str;

	i = 1;
	if (!tmp)
		return (-1);
	while ((*tmp) != '"')
		tmp++;
	if ((*tmp) != '"')
		return (-1);
	while (tmp[i] != '"' && tmp[i])
		i++;
	if (tmp[i] != '"')
		return (-1);
	tmp++;
	str = ft_strsub(tmp, 0, (size_t)i - 1);
	text[0] = str;
	return (3);
}

char			*take_t(char *line, int *t, void **text, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!(line = ft_strchr(line, '{')) && (ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '{' not found. line: ", i));
	line++;
	while ((line[j] != ' ' && line[j] != '}') && line[j])
		j++;
	tmp = ft_strsub(line, 0, (size_t)j);
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if ((ft_strnequ("damier", tmp, j)) == 1)
		*t = 1;
	else if ((ft_strnequ("perlin", tmp, j)) == 1)
		*t = 2;
	else if ((ft_strnequ("image", tmp, j)) == 1 && text[0] == NULL)
	{
		if ((*t = take_road(line, &text[0])) == -1)
			return (exit_null("ERROR: incorrect image texture", i));
	}
	else
		return (exit_null("ERROR: incorrect object texture. line: ", i));
	return (ft_strchr(line, '}'));
}

static	char	*take_coef(char *line, double *coef, char c, int i)
{
	int j;
	int verif;

	verif = 0;
	j = 0;
	while (line[j] != c && line[j])
		j++;
	if (line[j] != c)
		return (exit_null("ERROR: invalid value in reflect. line: ", i));
	else
	{
		j++;
		*coef = check_value((line + j), &verif, i, -1);
		if (verif > 0 || *coef < 0.)
			return (NULL);
	}
	return (ft_strchr(line, '}'));
}

char			*take_refl(char *line, t_obj *obj, int i, int j)
{
	char	*tmp;

	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	line++;
	while (line[j] != '}' && line[j])
		j++;
	if (!(tmp = ft_strsub(line, 0, j + 1)))
		return (NULL);
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if ((obj->reflect = ft_strnequ("on", tmp, 2)) == 1)
		tmp = (tmp + 2);
	else if ((obj->reflect = ft_strnequ("off", tmp, 3)) == 1)
		return ((line + j));
	else
		return (exit_null("ERROR: wrong argument in <reflect>. line: ", i));
	if (obj->reflect == 1 &&
		(tmp = take_coef(tmp, &obj->coef_refl, 'c', i)) == NULL)
		return (exit_null("ERROR: wrong argument 'c' in <reflect>. line: ", i));
	return (ft_strchr(line, '}'));
}

char			*take_para_refract(char *line, t_obj *obj, int i, int j)
{
	char	*tmp;

	if (!(line = ft_strchr(line, '{')) && (ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '{' not found. line: ", i));
	line++;
	while (line[j] != '}' && line[j])
		j++;
	if (!(tmp = ft_strsub(line, 0, j + 1)))
		return (NULL);
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if ((obj->refr = ft_strnequ("on", tmp, 2)) == 1)
		tmp = (tmp + 2);
	else if (ft_strnequ("off", tmp, 3) == 1)
		return ((line + j));
	else
		return (exit_null("ERROR: wrong argument in <reflect>. line: ", i));
	if (obj->refr == 1 &&
		(take_coef(tmp, &obj->ind_refr, 'r', i)) == NULL)
		return (exit_null("ERROR: wrong argument 'r' in <reflect>. line: ", i));
	else if (obj->refr == 1 && !(take_coef(tmp, &obj->coef_refr, 'c', i)))
		return (exit_null("ERROR: wrong argument 'c' in <reflect>. line: ", i));
	return (ft_strchr(line, '}'));
}
