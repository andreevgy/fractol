/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:07:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 13:46:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	*calculate_zone_thread(void *param)
{
	t_thread_args *args;

	args = (t_thread_args *)param;
	calculate_zone(args->fract, args->start, args->end);
	return (NULL);
}

t_thread_args *create_args(t_fract *fract, t_pixel *start, t_pixel *end)
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
	t_pixel			*start;
	t_pixel			*end;
	pthread_t 		id_arr[8];
	int				i;

	//fill_black(fractal);
	i = 0;
	start = create_pixel(0, 0, 0);
	end = create_pixel(W / 2, H, 0);
	while (i < 2)
	{
		args = create_args(fractal, start, end);
		pthread_create(&(id_arr[0]), NULL, &calculate_zone_thread, args);
		printf("start: x: %d, y: %d, end: x: %d, y: %d\n", start->x, start->y, end->x, end->y);
		start = create_pixel(end->x, 0, 0);
		end = create_pixel(end->x + W / 2, H, 0);
		//start->x = end->x;
		//end->x += W / 8;
		i++;
	}

	i = 0;
	while (i < 2)
	{
		pthread_join(id_arr[i], NULL);
		i++;
	}
	return (NULL);
}
