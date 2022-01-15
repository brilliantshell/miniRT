/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:39:05 by yongjule          #+#    #+#             */
/*   Updated: 2022/01/15 22:37:04 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	hidden_by_pl(t_pt_info *pt_i, double *o_ray, double *n_vect)
{
	double	new_o[3];

	if (pt_i->type == PLANE)
	{
		vect_copy(new_o, n_vect);
		if (dot_product(n_vect, o_ray) < 0)
			get_pt_on_line(new_o, NULL, n_vect, -1);
		if (dot_product(new_o, pt_i->pt) > 0)
			return (1);
	}
	return (0);
}

int	hidden_by_cn(t_pt_info *pt_i, double *lp)
{
	double	new_o[3];
	double	top_to_lp[3];
	t_cn	*cn;

	if (pt_i->type == CONE)
	{
		cn = pt_i->obj.cn;
		get_pt_on_line(new_o, cn->center, cn->o_vect, cn->height);
		sub_vect(top_to_lp, lp, new_o);
		if (fpclassify(vect_size(top_to_lp)) == FP_ZERO)
			return (1);
		if (signbit(atan(cn->radius / cn->height) - acos(-1 * dot_product
					(top_to_lp, cn->o_vect) / vect_size(top_to_lp))))
			return (0);
		if (!signbit(dot_product(top_to_lp, cn->o_vect) + cn->height))
			return (0);
		return (1);
	}
	return (0);
}
