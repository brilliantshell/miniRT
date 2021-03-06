/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:59:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/12/20 16:11:26 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_diffuse_light(double *o_vect, double *o_ray)
{
	double	diffuse;
	double	bright;

	bright = vect_size(o_ray);
	normalize_vect(o_ray);
	diffuse = dot_product(o_ray, o_vect) / (1 + 0.0001 * bright);
	return (diffuse);
}

int	get_phong_r(t_rt *rt, t_pt_info *pt_info, double diffuse)
{
	double	color;
	double	amb;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[R] / 255));
	color = (diffuse * ((double)pt_info->color[R] / 255)
			* ((double)rt->spec->light.color[R] / 255))
		* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_g(t_rt *rt, t_pt_info *pt_info, double diffuse)
{
	double	color;
	double	amb;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[G] / 255));
	color = (diffuse * ((double)pt_info->color[G] / 255)
			* ((double)rt->spec->light.color[G] / 255))
		* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}

int	get_phong_b(t_rt *rt, t_pt_info *pt_info, double diffuse)
{
	double	color;
	double	amb;

	color = 0;
	if (signbit(diffuse))
		diffuse = 0;
	amb = (rt->spec->amb.ratio * ((double)rt->spec->amb.color[B] / 255));
	color = (diffuse * ((double)pt_info->color[B] / 255)
			* ((double)rt->spec->light.color[B] / 255))
		* rt->spec->light.bright + amb;
	return ((int)(color * 255));
}
