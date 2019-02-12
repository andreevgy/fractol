/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:00:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 14:39:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_zone(t_fract *fractal, t_pixel *start, t_pixel *end, int i)
{
	t_pixel	*iter;

	iter = create_pixel(start->x, start->y,
			hsv(i % 60 + 240, i % 255, 100 * (i < fractal->max_iters)));
	while (iter->y < end->y)
	{
		iter->x = start->x;
		while (iter->x < end->x)
		{
			iter->color = hsv(i % 60 + 240, i % 255, 100 * (i < fractal->max_iters));
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


void	calculate_zone(t_fract *fr, t_pixel *start, t_pixel *end)
{
	t_pixel	*iter;
	int		i;

	iter = create_pixel(start->x, start->y, 0xFFFFFF);
	i = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
	if (start->x == end->x && start->y == end->y)
		return (calculate_pixel(fr, fr->calc, start));
	if (end->x - start->x == 0 || end->y - start->y == 0 ||
		end->x - start->x == 1 || end->y - start->y == 1)
		return (fill_zone(fr, start, end, i));
	while (iter->x++ <= end->x)
		if (fr->pixels[iter->y][iter->x] == -1)
		{
			fr->pixels[iter->y][iter->x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
			if(i != fr->pixels[iter->y][iter->x])
				return (split(start, end, fr));
		}
	while (iter->y++ <= end->y)
		if (fr->pixels[iter->y][iter->x] == -1)
		{
			fr->pixels[iter->y][iter->x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
			if(i != fr->pixels[iter->y][iter->x])
				return (split(start, end, fr));
		}
	while (iter->x-- > start->x)
		if (fr->pixels[iter->y][iter->x] == -1)
		{
			fr->pixels[iter->y][iter->x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
			if(i != fr->pixels[iter->y][iter->x])
				return (split(start, end, fr));
		}
	while (iter->y-- > start->y)
		if (fr->pixels[iter->y][iter->x] == -1)
		{
			fr->pixels[iter->y][iter->x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
			if(i != fr->pixels[iter->y][iter->x])
				return (split(start, end, fr));
		}
	fill_zone(fr, start, end, i);
	free(iter);
}
