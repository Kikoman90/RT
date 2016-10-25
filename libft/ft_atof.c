/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:26:30 by joboyer           #+#    #+#             */
/*   Updated: 2016/09/13 19:55:25 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_value(t_info *env)
{
	env->a = 0.0;
	env->e = 0;
	env->sign = 1;
	env->i = 0;
	env->count = 0;
}

static void	check_power(t_info *env, char *s)
{
	if (env->c == '.')
		while ((env->c = *s++) != '\0' && ft_isdigit(env->c))
		{
			env->a = env->a * 10.0 + (env->c - '0');
			env->e = env->e - 1;
		}
	if (env->c == 'e' || env->c == 'E')
	{
		env->c = *s++;
		if (env->c == '+')
			env->c = *s++;
		else if (env->c == '-')
		{
			env->c = *s++;
			env->sign = -1;
		}
		while (ft_isdigit(env->c))
		{
			env->i = env->i * 10 + (env->c - '0');
			env->c = *s++;
		}
		env->e += env->i * env->sign;
	}
}

double		find_double(t_info *env)
{
	while (env->e > 0)
	{
		env->a *= 10.0;
		env->e--;
	}
	while (env->e < 0)
	{
		env->a *= 0.1;
		env->e++;
	}
	if (env->count == 1)
		env->a = env->a * -1;
	return (env->a);
}

double		ft_atof(char *s)
{
	t_info	*env;
	double	res;

	if ((env = malloc(sizeof(t_info))) == NULL)
		return (0);
	init_value(env);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (*s == '-' && *s++)
		env->count = 1;
	while ((env->c = *s++) != 0 && ft_isdigit(env->c))
		env->a = env->a * 10.0 + (env->c - '0');
	check_power(env, s);
	res = find_double(env);
	free(env);
	return (res);
}
