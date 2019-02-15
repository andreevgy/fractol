/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:00:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/15 15:46:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_zone(t_fract *fractal, t_pixel start, t_pixel end)
{
	t_pixel	iter;
	int		i;

	i = 0;
	iter.x = start.x;
	iter.y = start.y;
	i = fractal->calc(iter, fractal->zoom, fractal->max_iters, fractal->move);
	iter.color = hsv(i % 60 + 240, i % 255, 100 * (i < fractal->max_iters));
	while (iter.y < end.y)
	{
		iter.x = start.x;
		while (iter.x < end.x)
		{
			fractal->pixels[iter.y][iter.x] = i;
			set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
			iter.x++;
		}
		iter.y++;
	}
}

void	split(t_pixel start, t_pixel end, t_fract *fractal)
{
	t_pixel	middle1;
	t_pixel	middle2;

	if (end.x - start.x > end.y - start.y)
	{
		middle1.x = (end.x + start.x) / 2;
		middle1.y = end.y;
		middle2.x = middle1.x;
		middle2.y = start.y;
	}
	else
	{
		middle1.x = end.x;
		middle1.y = (end.y + start.y) / 2;
		middle2.x = start.x;
		middle2.y = middle1.y;
	}
	calculate_zone(fractal, start, middle1);
	calculate_zone(fractal, middle2, end);
	return ;
}

void	calculate_zone(t_fract *fr, t_pixel start, t_pixel end)
{
	int res;

	res = calculate_borders(fr, start, end);
	if (res == 1)
		split(start, end, fr);
	else if (res == 0)
		fill_zone(fr, start, end);
	else if (res == -1)
		return ;
}
