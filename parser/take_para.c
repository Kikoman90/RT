/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:32:32 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/13 18:40:30 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

char	*take_para_intaa(char *line, double *dst, int i, int opt)
{
	int	j;
	int	tmp;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	while ((*line < '0' || *line > '9') && (*line != '-' && *line))
		line++;
	if ((ft_isdigit((int)*line)) == 0)
		return (exit_null("ERROR: incorrect value. line: ", i));
	line = ft_matoi(line, &tmp);
	if (tmp != 1 && tmp != 2 && tmp != 4 && tmp != 8 && tmp != 16 && opt == 0)
		return (exit_null("ERROR: wrong format for antialiasing. line: ", i));
	else if (opt == 1 && (tmp < 0 || tmp > 15))
		return (exit_null("ERROR: wrong format for reflect. line: ", i));
	dst[0] = tmp;
	return (ft_strchr(line, '}'));
}

char	*take_para_int(char *line, int *tmp, int i)
{
	int	j;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	while (0 == (ft_isalpha((*line)) && *line) && 0 == (ft_isdigit(*line))
		&& *line != '-')
		line++;
	if ((ft_isdigit((int)*line)) == 0)
		return (exit_null("ERROR: incorrect value. line: ", i));
	line = ft_matoi(line, &tmp[0]);
	if (tmp[0] < 10 || tmp[0] > 2000)
		return (exit_null("ERROR: incorrect value. line: ", i));
	while (0 == (ft_isalpha((*line)) && *line) && 0 == (ft_isdigit(*line))
		&& *line != '-')
		line++;
	if ((ft_isdigit((int)*line)) == 0)
		return (exit_null("ERROR: incorrect value. line: ", i));
	line = ft_matoi(line, &tmp[1]);
	if (tmp[1] < 10 || tmp[1] > 2000)
		return (exit_null("ERROR: incorrect value. line: ", i));
	return (ft_strchr(line, '}'));
}

char	*take_para_on(char *line, int *ref, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	line++;
	while (line[j] != '}')
		j++;
	if (!(tmp = ft_strsub(line, 0, (size_t)j)))
		return (NULL);
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if (ft_strnequ("on", tmp, 2) == 1)
		ref[0] = 1;
	else if (ft_strnequ("off", tmp, 3) == 1)
		ref[0] = 0;
	else
		return (exit_null("ERROR: wrong argument in <reflect>. line: ", i));
	return (ft_strchr(line, '}'));
}

char	*take_para_type(char *line, int *type, int i, int j)
{
	char	*tmp;

	if (!(line = ft_strchr(line, '{')) && (ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '{' not found. line: ", i));
	line++;
	while (line[j] != '}')
		j++;
	tmp = ft_strsub(line, 0, (size_t)j);
	while (0 == (ft_isalpha((*tmp)) && *tmp) && 0 == (ft_isdigit(*tmp)))
		tmp++;
	if ((ft_strnequ("sphere", tmp, 6)) == 1)
		*type = 1;
	else if ((ft_strnequ("cylinder", tmp, 8)) == 1)
		*type = 2;
	else if ((ft_strnequ("cone", tmp, 4)) == 1)
		*type = 3;
	else if ((ft_strnequ("plane", tmp, 5)) == 1)
		*type = 4;
	else if ((ft_strnequ("disk", tmp, 4)) == 1)
		*type = 5;
	else
		return (exit_null("ERROR: incorrect object type. line: ", i));
	return (ft_strchr(line, '}'));
}

char	*take_para_effect(char *line, int *type, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!(line = ft_strchr(line, '{')))
		return (exit_null("ERROR: '{' not found. line: ", i));
	if ((ft_strchr(line, '}')) == NULL)
		return (exit_null("ERROR: '}' not found. line: ", i));
	line++;
	while (line[j] != '}')
		j++;
	tmp = ft_strsub(line, 0, (size_t)j);
	if ((ft_strnequ("black and white", tmp, 15)) == 1 ||
		(ft_strnequ("blackandwhite", tmp, 13)) == 1 ||
		(ft_strnequ("noir et blanc", tmp, 13)) == 1)
		*type = 1;
	else if ((ft_strnequ("sepia", tmp, 5)) == 1)
		*type = 2;
	else
		return (exit_null("ERROR: incorrect object effect. line: ", i));
	ft_strdel(&tmp);
	return (ft_strchr(line, '}'));
}
