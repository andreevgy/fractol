/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:03:42 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 18:01:59 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	hsv(int h, int s, int v)
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

int			calculate_color(t_fract *fract, int i)
{
	return (hsv(i % fract->color.x + fract->color.y, fract->color.color,
					255 * (i < fract->max_iters)));
}
