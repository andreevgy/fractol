/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:45:21 by marvin            #+#    #+#             */
/*   Updated: 2019/02/15 15:47:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calculate_1(t_fract *fr, t_pixel start, t_pixel end)
{
	t_pixel iter;
	int		i;

	iter.x = start.x;
	iter.y = start.y;
	i = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
	while (iter.x < end.x - 1)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom,
													fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.x++;
	}
	while (iter.y < end.y - 1)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom,
													fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.y++;
	}
	return (0);
}

static int		calculate_2(t_fract *fr, t_pixel start, t_pixel end)
{
	t_pixel iter;
	int		i;

	iter.x = end.x;
	iter.y = end.y;
	i = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
	while (iter.x > start.x)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom,
													fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.x--;
	}
	while (iter.y > start.y)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom,
													fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.y--;
	}
	return (0);
}

static void		calculate_each_pixel_in_zone(t_fract *fr,
												t_pixel start, t_pixel end)
{
	t_pixel	iter;

	iter.x = start.x;
	iter.y = start.y;
	while (iter.y < end.y)
	{
		iter.x = start.x;
		while (iter.x < end.x)
		{
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom,
										fr->max_iters, fr->move);
			iter.color = hsv(fr->pixels[iter.y][iter.x] % 60 + 240,
							fr->pixels[iter.y][iter.x] % 255,
							100 * (fr->pixels[iter.y][iter.x] < fr->max_iters));
			set_pixel_to_image(fr->data_addr, fr->size_line, iter);
			iter.x++;
		}
		iter.y++;
	}
}

int				calculate_borders(t_fract *fr, t_pixel start, t_pixel end)
{
	t_pixel iter;
	int		i;

	iter.x = start.x;
	iter.y = start.y;
	if ((start.x == end.x && start.y == end.y)
		|| (end.x - start.x <= 3 && end.y - start.y <= 3))
	{
		calculate_each_pixel_in_zone(fr, start, end);
		return (-1);
	}
	i = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
	if (calculate_1(fr, start, end))
		return (1);
	if (calculate_2(fr, start, end))
		return (1);
	return (0);
}
