/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:04:41 by ghan              #+#    #+#             */
/*   Updated: 2021/12/14 01:34:50 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	fill_cy_circle(t_cy	*cy, double *cam_o_v)
{
	if (dot_product(cy->o_vect, cam_o_v) > 0)
		vect_copy(cy->circle_center, cy->center);
	else
		get_pt_on_line(cy->circle_center, cy->center,
			cy->o_vect, cy->height);
	if (dot_product(cy->o_vect, cam_o_v) < 0)
		vect_copy(cy->circle_o_v, cy->o_vect);
	else
		get_pt_on_line(cy->circle_o_v, NULL, cy->o_vect, -1);
}

static void	fill_cy_center(t_cy *new_cy, char **info, int cv_flag)
{
	char	**center_arr;
	int		i;

	center_arr = trail_n_cons_del_split(info[0], ',');
	if (ft_strsetlen(center_arr) != 3)
		is_error("Invalid configuration (CY CENTER)", NULL, EXIT_FAILURE);
	i = -1;
	while (center_arr[++i])
	{
		new_cy->center[i] = ft_atod(center_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (CY CENTER)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)center_arr);
}

static void	fill_cy_o_vect(t_cy *new_cy, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = trail_n_cons_del_split(info[1], ',');
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration (CY O_VECT)", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		new_cy->o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || new_cy->o_vect[i] < -1 || new_cy->o_vect[i] > 1)
			is_error("Invalid configuration (CY O_VECT)", NULL, EXIT_FAILURE);
	}
	normalize_vect(new_cy->o_vect);
	free_double_ptr((void **)o_vect_arr);
}

static void	fill_cy_color(t_cy *new_cy, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = trail_n_cons_del_split(info[4], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (CY COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		new_cy->color[i] = ft_pos_atoi(color_arr[i]);
		if ((new_cy->color[i] == 0 && color_arr[i][0] != '0')
			|| new_cy->color[i] < 0 || new_cy->color[i] > 255)
			is_error("Invalid configuration (CY COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_cylinder(t_obj_lst **hd, char **info, int cv_flag)
{
	t_cy	*new_cy;

	if (ft_strsetlen(info) != 5)
		is_error("Invalid configuration (CY ARGC)", NULL, EXIT_FAILURE);
	new_cy = (t_cy *)ft_calloc(1, sizeof(t_cy));
	obj_lst_addback(hd, obj_lst_new((void *)new_cy, CYLINDER));
	fill_cy_center(new_cy, info, 0);
	fill_cy_o_vect(new_cy, info, 0);
	new_cy->diameter = ft_atod(info[2], &cv_flag) * 10;
	new_cy->radius = new_cy->diameter / 2;
	if (cv_flag || new_cy->diameter < 0)
		is_error("Invalid configuration (CY DIAMETER)", NULL, EXIT_FAILURE);
	new_cy->height = ft_atod(info[3], &cv_flag) * 10;
	if (cv_flag || new_cy->height < 0)
		is_error("Invalid configuration (CY HEIGHT)", NULL, EXIT_FAILURE);
	fill_cy_color(new_cy, info);
}
