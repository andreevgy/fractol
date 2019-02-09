/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:00:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 19:30:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	fill_zone(t_fract *fractal, t_pixel *start, t_pixel *end, int i)
{
	t_pixel	*iter;

	iter = create_pixel(start->x, start->y,
			hsv(i % 60 + 60, i % 105, 255 * (i < fractal->max_iters)));
	while (iter->y < end->y)
	{
		iter->x = start->x;
		while (iter->x < end->x)
		{
			set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
			iter->x++;
		}
		iter->y++;
	}
	free(iter);
}

void	split(t_pixel *start, t_pixel *end, t_fract *fractal)
{
	t_pixel	*middle1;
	t_pixel	*middle2;

	if (end->x - start->x > end->y - start->y)
	{
		middle1 = create_pixel((end->x + start->x) / 2, end->y, 0);
		middle2 = create_pixel((end->x + start->x) / 2, start->y, 0);
	}
	else
	{
		middle1 = create_pixel(end->x, (end->y + start->y) / 2, 0);
		middle2 = create_pixel(start->x, (end->y + start->y) / 2, 0);
	}
	calculate_zone(fractal, start, middle1);
	calculate_zone(fractal, middle2, end);
	free(middle1);
	free(middle2);
	return ;
}

void	calculate_zone(t_fract *fractal, t_pixel *start, t_pixel *end)
{
	t_pixel	*iter;
	int		i;

	iter = create_pixel(start->x, start->y, 0xFFFFFF);
	i = fractal->calc(iter, fractal->zoom, fractal->max_iters);
	if (start->x == end->x && start->y == end->y)
		return (calculate_pixel(fractal, fractal->calc, start));
	if (end->x - start->x == 0 || end->y - start->y == 0 ||
		end->x - start->x == 1 || end->y - start->y == 1)
		return (fill_zone(fractal, start, end, i));
	while (iter->x++ <= end->x)
		if (i != fractal->calc(iter, fractal->zoom, fractal->max_iters))
			return (split(start, end, fractal));
	while (iter->y++ <= end->y)
		if (i != fractal->calc(iter, fractal->zoom, fractal->max_iters))
			return (split(start, end, fractal));
	while (iter->x-- >= start->x)
		if (i != fractal->calc(iter, fractal->zoom, fractal->max_iters))
			return (split(start, end, fractal));
	while (iter->y-- >= start->y)
		if (i != fractal->calc(iter, fractal->zoom, fractal->max_iters))
			return (split(start, end, fractal));
	fill_zone(fractal, start, end, i);
	free(iter);
}
