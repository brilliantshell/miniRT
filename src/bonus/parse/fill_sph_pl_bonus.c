/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sph_pl_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:15:55 by ghan              #+#    #+#             */
/*   Updated: 2021/12/19 13:28:52 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_sphere_two(t_sph *new_sph, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = trail_n_cons_del_split(info[2], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (SPH COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		new_sph->color[i] = ft_pos_atoi(color_arr[i]);
		if ((new_sph->color[i] == 0 && color_arr[i][0] != '0')
			|| new_sph->color[i] < 0 || new_sph->color[i] > 255)
			is_error("Invalid configuration (SPH COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_sphere(t_obj_lst **hd, char **info, int cv_flag)
{
	t_sph	*new_sph;
	char	**center_arr;
	int		i;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration (SPH ARGC)", NULL, EXIT_FAILURE);
	new_sph = (t_sph *)ft_calloc(1, sizeof(t_sph));
	obj_lst_addback(hd, obj_lst_new((void *)new_sph, SPHERE));
	center_arr = trail_n_cons_del_split(info[0], ',');
	if (ft_strsetlen(center_arr) != 3)
		is_error("Invalid configuration (SPH CENTER)", NULL, EXIT_FAILURE);
	i = -1;
	while (center_arr[++i])
	{
		new_sph->center[i] = ft_atod(center_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (SPH CENTER)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)center_arr);
	new_sph->diameter = ft_atod(info[1], &cv_flag) * 10;
	new_sph->radius = new_sph->diameter / 2;
	if (cv_flag || new_sph->diameter < 0)
		is_error("Invalid configuration (SPH DIAMETER)", NULL, EXIT_FAILURE);
	fill_vect(new_sph->o_vect, 0, 1, 0);
	fill_sphere_two(new_sph, info);
}

static void	fill_plane_two(t_pl *new_pl, char **info, int cv_flag)
{
	char	**o_vect_arr;
	int		i;

	o_vect_arr = trail_n_cons_del_split(info[1], ',');
	if (ft_strsetlen(o_vect_arr) != 3)
		is_error("Invalid configuration (PL O_VECT)", NULL, EXIT_FAILURE);
	i = -1;
	while (o_vect_arr[++i])
	{
		new_pl->o_vect[i] = ft_atod(o_vect_arr[i], &cv_flag);
		if (cv_flag || new_pl->o_vect[i] < -1 || new_pl->o_vect[i] > 1)
			is_error("Invalid configuration (PL O_VECT)", NULL, EXIT_FAILURE);
	}
	normalize_vect(new_pl->o_vect);
	free_double_ptr((void **)o_vect_arr);
}

static void	fill_plane_three(t_pl *new_pl, char **info)
{
	char	**color_arr;
	int		i;

	color_arr = trail_n_cons_del_split(info[2], ',');
	if (ft_strsetlen(color_arr) != 3)
		is_error("Invalid configuration (PL COLOR)", NULL, EXIT_FAILURE);
	i = -1;
	while (color_arr[++i])
	{
		new_pl->color[i] = ft_pos_atoi(color_arr[i]);
		if ((new_pl->color[i] == 0 && color_arr[i][0] != '0')
			|| new_pl->color[i] < 0 || new_pl->color[i] > 255)
			is_error("Invalid configuration (PL COLOR)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)color_arr);
}

void	fill_plane(t_obj_lst **hd, char **info, int cv_flag)
{
	t_pl	*new_pl;
	char	**center_arr;
	int		i;

	if (ft_strsetlen(info) != 3)
		is_error("Invalid configuration (PL ARGC)", NULL, EXIT_FAILURE);
	new_pl = (t_pl *)ft_calloc(1, sizeof(t_pl));
	obj_lst_addback(hd, obj_lst_new((void *)new_pl, PLANE));
	center_arr = trail_n_cons_del_split(info[0], ',');
	if (ft_strsetlen(center_arr) != 3)
		is_error("Invalid configuration (PL CENTER)", NULL, EXIT_FAILURE);
	i = -1;
	while (center_arr[++i])
	{
		new_pl->center[i] = ft_atod(center_arr[i], &cv_flag) * 10;
		if (cv_flag)
			is_error("Invalid configuration (PL CENTER)", NULL, EXIT_FAILURE);
	}
	free_double_ptr((void **)center_arr);
	fill_plane_two(new_pl, info, 0);
	fill_plane_three(new_pl, info);
}
