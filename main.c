/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 10:33:57 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/06 19:03:35 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_line(t_env *rt, char *line, int i)
{
	int	res;

	while (*line)
	{
		if (rt->bal.i >= 1)
		{
			if ((ft_strequ("scene", rt->bal.bali[0])) > 0 && rt->bal.i >= 1)
				return (scene_para(rt, line, i, &rt->bal) == -1) ? -1 : 0;
			else if (((ft_strequ("camera", rt->bal.bali[0])) > 0 &&
						rt->bal.i >= 1))
				return (camera_para(rt, line, i, &rt->bal) == -1) ? -1 : 0;
			else if (((ft_strequ("light", rt->bal.bali[0])) > 0 &&
						rt->bal.i >= 1))
				return (light_para(rt, line, i, &rt->bal) == -1) ? -1 : 0;
			else if (((ft_strequ("object", rt->bal.bali[0])) > 0 &&
						rt->bal.i >= 1))
				return (obj_para(rt, line, i, &rt->bal) == -1) ? -1 : 0;
			else
				return (exit_error("ERROR: invalid tag. line: ", (i - 1)));
		}
		else
			return ((check_tag(rt, line, i, &rt->bal)) == NULL) ? -1 : 0;
	}
	return (0);
}

static int	init_struct(t_env *rt)
{
	if (!(rt->bal.bali = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	rt->bal.i = 0;
	rt->var.nbli = 0;
	rt->var.nbobj = 0;
	rt->var.max_ref = 0;
	rt->var.spec = 0.0;
	rt->headli = NULL;
	rt->headobj = NULL;
	rt->selection = 0;
	rt->speed = 0;
	ft_memset_int((int*)rt->win.check, 0, 4);
	ft_memset_int((int*)rt->cam.check, 0, 2);
	ft_memset_int((int*)rt->var.check, 0, 4);
	return (0);
}

static int	verif(int *check)
{
	if (check[0] < 1 || check[0] > 1)
		return (exit_error("ERROR: need one scene in file", -1));
	if (check[1] < 1 || check[1] > 1)
		return (exit_error("ERROR: need one camera in file", -1));
	if (check[2] > 10)
		return (exit_error("ERROR: you can put 10 light max", -1));
	if (check[3] < 1)
		return (exit_error("ERROR: need object in file", -1));
	return (0);
}

static int	init_env(t_env *rt, char *str, int i)
{
	int		fd;
	int		ret;

	if (BUFF_SIZE < 1)
		return (exit_error("ERROR: BUFF_SIZE must be greater than 0", -1));
	if ((fd = open(str, O_RDONLY)) < 3)
		return (exit_error(ft_strjoin("ERROR: ", strerror(errno), 'N'), -1));
	if (init_struct(rt) == -1)
		return (exit_error("ERROR: malloc error", -1));
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		if (get_line(rt, str, i) == -1)
			return (exit_free(rt, str, 0));
		free(str);
		i++;
	}
	if (ret == -1)
		return (exit_free(rt, "ERROR: get_next_line returned -1", 1));
	free(rt->bal.bali);
	if (verif(rt->var.check) == -1)
		return (-1);
	if (list_to_tab(rt) == -1)
		return (-1);
	set_system(rt);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	rt;

	if (ac != 2)
		ft_putendl("usage: ./RT input_file");
	else
	{
		if (init_env(&rt, av[1], 1) == -1)
			return (0);
		create_window(&rt);
	}
	return (0);
}
