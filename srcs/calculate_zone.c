/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:00:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 20:53:18 by marvin           ###   ########.fr       */
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
			set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
			//fractal->pixels[iter.y][iter.x] = i;
			iter.x++;
		}
		iter.y++;
	}
	iter.x = start.x;
	iter.y = start.y;
	iter.color = 0xFFFFFFF;
	/*while(iter.x < end.x)
	{
		set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
		iter.x++;
	}
	while (iter.y < end.y)
	{
		set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
		iter.y++;
	}
	while (iter.x > start.x)
	{
		set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
		iter.x--;
	}
	while (iter.y > start.y)
	{
		set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
		iter.y--;
	}*/
}

void	split(t_pixel start, t_pixel end, t_fract *fractal)
{
	t_pixel	middle1;
	t_pixel	middle2;

	if (end.x - start.x > end.y - start.y)
	{
		middle1.x = (end.x + start.x) / 2;
		middle1.y = end.y;
		middle2.x = (end.x + start.x) / 2;
		middle2.y = start.y;
	}
	else
	{
		middle1.x = end.x + 1;
		middle1.y = (end.y + start.y) / 2;
		middle2.x = start.x - 1;
		middle2.y = (end.y + start.y) / 2;
	}
	calculate_zone(fractal, start, middle1);
	calculate_zone(fractal, middle2, end);
	return ;
}

void	calculate_each_pixel_in_zone(t_fract *fr, t_pixel start, t_pixel end)
{
	t_pixel	iter;

	iter.x = start.x;
	iter.y = start.y;
	while (iter.y < end.y)
	{
		iter.x = start.x;
		while (iter.x < end.x)
		{
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
			iter.x++;
		}
		iter.y++;
	}
}

int		calculate_borders(t_fract *fr, t_pixel start, t_pixel end)
{
	t_pixel iter;
	int		i;
	int		flag;
	int		tempx;
	int		tempy;


	flag = 0;
	iter.x = start.x;
	iter.y = start.y;
	tempx = end.x;
	tempy = end.y;
	i = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
	while(iter.x < end.x - 1)
	{
		if (end.x == W)
			end.x = W - 1;
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.x++;
	}
	while (iter.y < end.y - 1)
	{
		if (end.y == H)
			end.y = H - 1;
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.y++;
	}
	while (iter.x > start.x)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.x--;
	}
	iter.x++;
	while (iter.y > start.y)
	{
		if (fr->pixels[iter.y][iter.x] == -1)
			fr->pixels[iter.y][iter.x] = fr->calc(iter, fr->zoom, fr->max_iters, fr->move);
		if (fr->pixels[iter.y][iter.x] != i)
			return (1);
		iter.y--;
	}
	return (0);
}

void	calculate_zone(t_fract *fr, t_pixel start, t_pixel end)
{
	if (start.x == 0 && start.y == 0 && end.x == W && end.y == H)
		split(start, end, fr);
	//if (end.x - start.x < 5 && end.y - start.y < 5)
		//calculate_each_pixel_in_zone(fr, start, end);
 	else if (calculate_borders(fr, start, end))
		return (split(start, end, fr));
	else
		fill_zone(fr, start, end);
}
