/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/12/16 16:07:24 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_obj_img(t_rt *rt)
{
	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, WIN_W, WIN_H);
	if (!rt->obj_img.img_ptr)
		is_error("Objects image init failed", NULL, EXIT_FAILURE);
	rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr,
			&rt->obj_img.bpp, &rt->obj_img.width, &rt->obj_img.endian);
	if (!rt->obj_img.data)
		is_error("Getting objects image data failed", NULL, EXIT_FAILURE);
}

static void	*ray_tracing_multi(void *arg)
{
	static int	seek = 0;
	t_rt		*rt;
	int			w;
	int			h;
	int			max;

	rt = (t_rt *)arg;
	pthread_mutex_lock(&rt->mutex);
	seek++;
	max = seek * WIN_H / NBR_OF_THREAD;
	h = (seek - 1) * WIN_H / NBR_OF_THREAD - 1;
	if (seek > NBR_OF_THREAD - 1)
		seek = 0;
	pthread_mutex_unlock(&rt->mutex);
	while (++h < max)
	{
		w = -1;
		while (++w < WIN_W)
			rt->obj_img.data[cur_pixel(rt, w, h)]
				= shoot_ray(rt, w - WIN_W / 2, h - WIN_H / 2);
	}
	return (arg);
}

void	ray_tracing(t_rt *rt)
{
	int			err;
	int			idx;
	pthread_t	tid[NBR_OF_THREAD];

	if (NBR_OF_THREAD > WIN_W || NBR_OF_THREAD > WIN_H)
		is_error("Too many thread", NULL, EXIT_FAILURE);
	err = pthread_mutex_init(&rt->mutex, NULL);
	if (err)
		is_error(NULL, strerror(err), EXIT_FAILURE);
	idx = -1;
	while (++idx < NBR_OF_THREAD)
	{
		err = pthread_create(&tid[idx], NULL, ray_tracing_multi, rt);
		if (err)
			is_error(NULL, strerror(err), EXIT_FAILURE);
	}
	idx = -1;
	while (++idx < NBR_OF_THREAD)
	{
		err = pthread_join(tid[idx], NULL);
		if (err)
			is_error(NULL, strerror(err), EXIT_FAILURE);
	}
	pthread_mutex_destroy(&rt->mutex);
}
