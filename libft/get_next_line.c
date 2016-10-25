/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 15:56:28 by joboyer           #+#    #+#             */
/*   Updated: 2016/01/21 17:47:15 by joboyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_get	*ft_freeline(t_get *line1, t_get *line2, t_get **read_line)
{
	if (!line2)
		*read_line = line1->next;
	else
		line2->next = line1->next;
	free(line1->read);
	free(line1);
	if (!line2)
		return (*read_line);
	else
		return (line2->next);
}

static	t_get	*ft_read(int fd)
{
	void	*str_read;
	t_get	*read_line;
	int		stop;

	if (!(read_line = (t_get*)malloc(sizeof(t_get))))
		return (NULL);
	if (!(str_read = malloc(sizeof(char) * BUFF_SIZE)))
	{
		free(read_line);
		return (NULL);
	}
	if ((stop = read(fd, str_read, BUFF_SIZE)) < 0)
	{
		free(str_read);
		free(read_line);
		return (NULL);
	}
	read_line->read = (char*)str_read;
	read_line->fd = fd;
	read_line->nb_read = stop;
	read_line->next = NULL;
	read_line->i = 0;
	return (read_line);
}

static	int		ft_searchbackn(int fd, t_get *new_read)
{
	int		i;
	int		limit;
	t_get	*tmp;

	i = new_read->i;
	limit = 0;
	while (new_read->read[i] != '\n' && i < new_read->nb_read)
	{
		i++;
		limit++;
		if (i == new_read->nb_read && new_read->nb_read == BUFF_SIZE)
		{
			if (!(tmp = ft_read(fd)))
				return (-1);
			tmp->next = new_read->next;
			new_read->next = tmp;
			new_read = tmp;
			i = 0;
		}
	}
	return (limit);
}

static	int		ft_putinline(int limit, t_get **tab, t_get **rd_line, char **li)
{
	char	*tmp;
	int		i;

	if (!tab[0])
		return (-1);
	i = (tab[0])->i;
	if (limit == -1 || !(tmp = (char*)malloc(sizeof(char) * (limit + 1))))
		return (-1);
	*li = tmp;
	while (limit--)
	{
		*tmp++ = (tab[0])->read[i++];
		if (i == (tab[0])->nb_read)
		{
			tab[0] = ft_freeline(tab[0], tab[1], rd_line);
			i = 0;
		}
	}
	*tmp = 0;
	if (!tab[0] || (i == (tab[0])->nb_read && (tab[0])->nb_read < BUFF_SIZE))
		return (1);
	tab[0]->i = i + 1;
	if ((tab[0])->i == tab[0]->nb_read)
		tab[0] = ft_freeline(tab[0], tab[1], rd_line);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static	t_get	*read_line = NULL;
	t_get			*tab[2];
	t_get			*new_read;
	t_get			*line_prev;

	line_prev = NULL;
	if (!read_line)
		read_line = ft_read(fd);
	if (!(new_read = read_line) || fd < 0 || line == NULL)
		return (-1);
	while (new_read->fd != fd)
	{
		if (!(new_read->next))
			new_read->next = ft_read(fd);
		line_prev = new_read;
		new_read = new_read->next;
	}
	if (!new_read || !read_line)
		return (-1);
	tab[0] = new_read;
	tab[1] = line_prev;
	if ((tab[0])->nb_read == 0)
		return (0);
	return (ft_putinline(ft_searchbackn(fd, new_read), tab, &read_line, line));
}
