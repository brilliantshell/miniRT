/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:53:59 by ghan              #+#    #+#             */
/*   Updated: 2021/12/09 19:31:47 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_conf
{
	char			*elem;
	char			**info;
	struct s_conf	*next;
}	t_conf;

typedef struct s_amb
{
	double	ratio;
	int		color[3];
}	t_amb;

typedef struct s_cam
{
	double	vp[3];
	double	o_vect[3];
	double	fov;
}	t_cam;

typedef struct s_light
{
	double	lp[3];
	double	bright;
	int		color[3];
}	t_light;

typedef struct s_sph
{
	double	center[3];
	double	diameter;
	double	radius;
	int		color[3];
}	t_sph;

typedef struct s_pl
{
	double	center[3];
	double	o_vect[3];
	int		color[3];
}	t_pl;

typedef struct s_cy
{
	double	center[3];
	double	o_vect[3];
	double	diameter;
	double	radius;
	double	height;
	int		color[3];
}	t_cy;

typedef union u_obj
{
	t_sph	*sph;
	t_pl	*pl;
	t_cy	*cy;
}	t_obj;

typedef struct s_obj_lst
{
	int					type;
	t_obj				obj;
	struct s_obj_lst	*next;
}	t_obj_lst;

typedef struct s_spec
{
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_obj_lst	*obj_lst;
}	t_spec;

typedef struct s_img
{
	int		width;
	int		bpp;
	int		endian;
	int		*data;
	void	*img_ptr;
}	t_img;

typedef struct s_rt
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_spec		*spec;
	t_img		obj_img;
	double		c_to_s;
	struct s_rt	*c_rt;
}	t_rt;

typedef struct s_pt_info
{
	int			type;
	double		pt[3];
	t_obj		obj;
	double		c_o_vect[3];
}	t_pt_info;

#endif
