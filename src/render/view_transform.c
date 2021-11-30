/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:08:46 by yongjule          #+#    #+#             */
/*   Updated: 2021/11/30 12:37:17 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_coord_system(t_spec *spec, double *transf)
{
	double	ref[4];
	double	x_axis[4];
	double	y_axis[4];

	ft_bzero(transf, sizeof(double) * 16);
	fill_vect(ref, 0, 0, 1);
	update_vect(transf, spec->cam.o_vect, Z, 4);
	if (!spec->cam.o_vect[X] && !spec->cam.o_vect[Y]
		&& (spec->cam.o_vect[Z] == 1 || spec->cam.o_vect[Z] == -1))
		return ;
	cross_product(x_axis, ref, spec->cam.o_vect);
	normalize_vect(x_axis);
	update_vect(transf, x_axis, X, 4);
	cross_product(y_axis, spec->cam.o_vect, x_axis);
	normalize_vect(y_axis);
	update_vect(transf, y_axis, Y, 4);
}

static void	get_transf_matrix(double *vp, double *transf)
{
	double	ref[4];

	fill_vect(ref, transf[X], transf[X + 1], transf[X + 2]);
	transf[3] = -1 * dot_product(ref, vp);
	fill_vect(ref, transf[Y * 4], transf[Y * 4 + 1], transf[Y * 4 + 1]);
	transf[7] = -1 * dot_product(ref, vp);
	fill_vect(ref, transf[Z * 4], transf[Z * 4 + 1], transf[Z * 4 + 2]);
	transf[11] = -1 * dot_product(ref, vp);
	fill_vect(ref, 0, 0, 0);
	update_vect(transf, ref, W, 4);
	transf[15] = 1;
}

void	multiply_vect(double *transf, double *dst)
{
	double	homo_v[4];
	int		row;

	fill_vect(homo_v, dst[X], dst[Y], dst[Z]);
	homo_v[W] = 1; // NOTE homo_v[3] may have to be 0 for o_vects
	row = 0;
	while (row < 3)
	{
		dst[row] = transf[row * 4 + X] * homo_v[X]
			+ transf[row * 4 + Y] * homo_v[Y]
			+ transf[row * 4 + Z] * homo_v[Z]
			+ transf[row * 4 + W] * homo_v[W];
		row++;
	}
}

void	transf_obj(t_spec *spec, double *transf)
{
	t_obj_lst	*cur;

	cur = spec->obj_lst->next;
	while (cur)
	{
		if (cur->type == SPHERE)
			multiply_vect(transf, cur->obj.sph->center);
		else if (cur->type == PLANE)
		{
			multiply_vect(transf, cur->obj.pl->center);
			multiply_vect(transf, cur->obj.pl->o_vect);
		}
		else if (cur->type == CYLINDER)
		{
			multiply_vect(transf, cur->obj.cy->center);
			multiply_vect(transf, cur->obj.cy->o_vect);
		}
		cur = cur->next;
	}
}

void	view_transform(t_rt *rt)
{
	double	transf[16];

	get_coord_system(rt->spec, transf);
	get_transf_matrix(rt->spec->cam.vp, transf);
	// transf_objs(rt->spec, transf);
	// transf_light(rt->spec, transf);
}
