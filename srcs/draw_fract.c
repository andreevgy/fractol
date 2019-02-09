/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:48:20 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 19:49:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		hsv(int h, int s, int v)
{
	float	hh;
	float	ff;
	int		p;
	int		q;
	int		t;

	if (s == 0)
		return ((v << 16) | (v << 8) | v);
	hh = ((h >= 360) ? 0 : (float)h / 60.0);
	ff = hh - (int)hh;
	p = (float)v * (1.0 - (float)s / 255.0);
	q = (float)v * (1.0 - ((float)s / 255.0 * ff));
	t = (float)v * (1.0 - ((float)s / 255.0 * (1.0 - ff)));
	if ((int)hh == 0)
		return ((v << 16) | (t << 8) | p);
	else if ((int)hh == 1)
		return ((q << 16) | (v << 8) | p);
	else if ((int)hh == 2)
		return ((p << 16) | (v << 8) | t);
	else if ((int)hh == 3)
		return ((p << 16) | (q << 8) | v);
	else if ((int)hh == 4)
		return ((t << 16) | (p << 8) | v);
	else
		return ((v << 16) | (p << 8) | q);
}

void	calculate_pixel(t_fract *fract, int (*calc)(t_pixel *pixel,
						int zoom, int max_iters, t_pixel *move), t_pixel *pixel)
{
	int iters;

	iters = calc(pixel, fract->zoom, fract->max_iters, fract->move);
	pixel->color = hsv(iters % 60 + 120, iters % 255,
						255 * (iters < fract->max_iters));
	set_pixel_to_image(fract->data_addr, fract->size_line, pixel);
}
