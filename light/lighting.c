/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joboyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 13:58:04 by joboyer           #+#    #+#             */
/*   Updated: 2016/10/18 14:38:36 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_vec	get_cap_norm(t_th *rt, t_obj obj, t_vec pos, t_vec norm)
{
	t_vec	temp;
	t_vec	temp2;
	t_vec	pos_lim;

	ft_vectornorm(&obj.dir);
	pos_lim = ft_vectoradd(obj.pos, ft_vectorscale(&obj.dir, obj.hauteur));
	temp = ft_vectorsub(&pos, &obj.pos);
	temp2 = ft_vectorsub(&pos, &pos_lim);
	if (dot(&obj.dir, &temp) >= -0.001 &&
		dot(&obj.dir, &temp) <= 0.001)
		norm = ft_vectorscale(&obj.dir, -1.0);
	else if (dot(&obj.dir, &temp2) >= -0.001 &&
		dot(&obj.dir, &temp2) <= 0.001)
		norm = obj.dir;
	return (norm);
}

t_vec			get_norm(t_th *rt, t_obj obj, t_vec pos)
{
	t_vec	norm;
	t_vec	temp;
	t_vec	temp2;
	t_vec	lim;

	if (obj.type == 3 || obj.type == 2)
	{
		ft_vectornorm(&obj.dir);
		temp = ft_vectorsub(&pos, &obj.pos);
		temp2 = ft_vectorscale(&obj.dir, dot(&obj.dir, &temp));
		norm = (t_vec){2 * (temp.x - temp2.x), 2 * (temp.y - temp2.y),
			2 * (temp.z - temp2.z)};
		if (obj.type == 3)
			norm = ft_vectorscale(&norm,
				powf(cosf(obj.rayon * (PI * 180.0f)), 2));
	}
	else if (obj.type == 4 || obj.type == 5)
		norm = obj.dir;
	else if (obj.type == 1)
		norm = ft_vectorsub(&pos, &obj.pos);
	if (obj.hauteur > 0.)
		norm = get_cap_norm(rt, obj, pos, norm);
	ft_vectornorm(&norm);
	return (norm);
}

int				init_var_tabs(t_th *rt, double **tab1, double **tab2,
	t_vec *pos)
{
	*tab1 = (double *)malloc(sizeof(double) * 4);
	*tab2 = (double *)malloc(sizeof(double) * 4);
	ft_dzero(*tab1, 4);
	ft_dzero(*tab2, 4);
	rt->var.norm = get_norm(rt, rt->tobj[O], *pos);
	return (rt->var.o);
}

double			*result_in_tab(t_obj obj, double *tab, double *tab_refl,
	double *tab_refr)
{
	tab = ft_tab_coef(tab, 1 - (obj.coef_refl + obj.coef_refr), 3);
	tab_refl = ft_tab_coef(tab_refl, obj.coef_refl, 3);
	tab_refr = ft_tab_coef(tab_refr, obj.coef_refr, 3);
	tab[0] += (tab_refl[0] + tab_refr[0]);
	tab[1] += (tab_refl[1] + tab_refr[1]);
	tab[2] += (tab_refl[2] + tab_refr[2]);
	free(tab_refl);
	free(tab_refr);
	return (tab);
}

double			*get_tabs(t_th *rt, t_vec *pos, double *tab, size_t cpt)
{
	double			*tab_refl;
	double			*tab_refr;
	int				o_tmp;

	o_tmp = init_var_tabs(rt, &tab_refl, &tab_refr, pos);
	tab = get_diffuse(rt, O, pos, tab);
	if (REFL == 1 && cpt < rt->var.max_ref && rt->tobj[O].coef_refl > 0.0)
	{
		if ((O = refl_init(rt, O, pos)) != -1)
		{
			cpt += 1;
			tab_refl = get_tabs(rt, pos, tab_refl, (cpt));
		}
	}
	O = o_tmp;
	if (REFR == 1 && cpt < rt->var.max_ref && rt->tobj[O].coef_refr > 0.0)
	{
		if ((O = refr_init(rt, O, pos, cpt)) != -1)
		{
			cpt += 1;
			tab_refr = get_tabs(rt, pos, tab_refr, (cpt));
		}
	}
	cpt--;
	return (result_in_tab(rt->tobj[o_tmp], tab, tab_refl, tab_refr));
}
