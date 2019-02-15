/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:07:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/15 15:11:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			fill_black(t_fract *fractal, t_pixel start, t_pixel end)
{
	int		bits_per_pixel;
	int		endian;
	t_pixel	iter;

	fractal->data_addr = mlx_get_data_addr(fractal->img_ptr, &bits_per_pixel,
			&(fractal->size_line), &endian);
	iter.y = start.y;
	while (iter.y < end.y)
	{
		iter.x = start.x;
		while (iter.x < end.x)
		{
			set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
			fractal->pixels[iter.y][iter.x] = -1;
			iter.x++;
		}
		iter.y++;
	}
}

void			*calculate_zone_thread(void *param)
{
	t_thread_args *args;

	args = (t_thread_args *)param;
	fill_black(args->fract, args->start, args->end);
	calculate_zone(args->fract, args->start, args->end);
	pthread_exit(NULL);
}

t_thread_args	*create_args(t_fract *fract, t_pixel start, t_pixel end)
{
	t_thread_args *args;

	args = ft_memalloc(sizeof(t_thread_args));
	args->fract = fract;
	args->start = start;
	args->end = end;
	return (args);
}

void			*draw_threads(t_fract *fractal)
{
	t_thread_args	*args;
	t_pixel			start;
	t_pixel			end;
	pthread_t		id_arr[THREADS];
	int				i;

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
	i = -1;
	while (++i < THREADS)
		pthread_join(id_arr[i], NULL);
	return (NULL);
}
