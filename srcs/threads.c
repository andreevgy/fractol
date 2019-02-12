/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:07:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 20:35:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>


void calculate_each_pixel(t_fract *fract, t_pixel start, t_pixel end)
{
	t_pixel *iter;

	iter = create_pixel(start.x, start.y, 0);
	while (iter->y < end.y)
	{
		iter->x = start.x;
		while (iter->x < end.x)
		{
			calculate_pixel(fract, fract->calc, *iter);
			iter->x++;
		}
		iter->y++;
	}
}


void	*calculate_zone_thread(void *param)
{
	t_thread_args *args;

	args = (t_thread_args *)param;
	calculate_zone(args->fract, args->start, args->end);
	//calculate_each_pixel(args->fract, args->start, args->end);
	pthread_exit(NULL);
}

t_thread_args *create_args(t_fract *fract, t_pixel start, t_pixel end)
{
	t_thread_args *args;

	args = ft_memalloc(sizeof(t_thread_args));
	args->fract = fract;
	args->start = start;
	args->end = end;
	return (args);
}

void fill_black(t_fract *fractal)
{
	int bits_per_pixel;
	int endian;
	int i;
	int end;
	int	*data_addr;

	fractal->data_addr = mlx_get_data_addr(fractal->img_ptr, &bits_per_pixel,
			&(fractal->size_line), &endian);
	data_addr = (int *)fractal->data_addr;
	i = -1;
	end = W * H * bits_per_pixel / 32;
	while (++i < end - 1)
	{
		data_addr[i] = 0;
	}
}

void	*draw_threads(t_fract *fractal)
{
	t_thread_args	*args;
	t_pixel			start;
	t_pixel			end;
	pthread_t 		id_arr[THREADS];
	int				i;

	fill_black(fractal);
	i = 0;
	start.x = 0;
	start.y = 0;
	end.x = W / THREADS;
	end.y = H;
	while (i < THREADS)
	{

		args = create_args(fractal, start, end);
		pthread_create(&(id_arr[i]), NULL, &calculate_zone_thread, args);
		start.x = end.x;
		end.x = end.x + W / THREADS;
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(id_arr[i], NULL);
		i++;
	}
	return (NULL);
}
