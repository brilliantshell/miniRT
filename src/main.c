/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:45 by ghan              #+#    #+#             */
/*   Updated: 2021/11/30 10:24:20 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_spec	spec;
	t_rt	rt;

	parse_config(argc, argv, &spec);
	init_rt_struct(&rt, &spec);
	view_transform(&rt);
	// put_data_to_img();
	// put_img_to_window();
	hook_minirt(&rt);

	// get_obj_img(&rt);
	// draw();
	// mlx_put_image_to_window(rt.mlx_ptr, rt.win_ptr, rt.bg_img.img_ptr, 0, 0);
	// mlx_put_image_to_window(rt.mlx_ptr, rt.win_ptr, rt.obj_img.img_ptr, 0, 0);
	mlx_loop(rt.mlx_ptr);
	return (EXIT_SUCCESS);
}
