/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:45:21 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 19:48:02 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calculate_1(t_fract *fr, t_pixel start, t_pixel end, int i)
{
	t_pixel iter;
	int		flag;

	flag = 0;
	iter.x = start.x;
	iter.y = start.y;
	while (iter.x < end.x)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr);
		if (fr->pixels[iter.y][iter.x] != i && fr->pixels[iter.y][iter.x] != -1)
			flag = 1;
		iter.x++;
	}
	while (iter.y < end.y - 1)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr);
		if (fr->pixels[iter.y][iter.x] != i && fr->pixels[iter.y][iter.x] != -1)
			flag = 1;
		iter.y++;
	}
	return (flag);
}

static int		calculate_2(t_fract *fr, t_pixel start, t_pixel end, int i)
{
	t_pixel	iter;
	int		flag;

	flag = 0;
	iter.x = end.x;
	iter.y = end.y;
	while (iter.x > start.x)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr);
		if (fr->pixels[iter.y][iter.x] != i)
			flag = 1;
		iter.x--;
	}
	while (iter.y > start.y)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr);
		if (fr->pixels[iter.y][iter.x] != i)
			flag = 1;
		iter.y--;
	}
	return (flag);
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
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr);
			iter.color = calculate_color(fr, fr->pixels[iter.y][iter.x]);
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
	i = fr->calc(iter, fr);
	if ((start.x == end.x && start.y == end.y)
		|| (end.x - start.x <= 1 || end.y - start.y <= 1))
	{
		calculate_each_pixel_in_zone(fr, start, end);
		return (-1);
	}
	return (calculate_1(fr, start, end, i) || calculate_2(fr, start, end, i));
}
