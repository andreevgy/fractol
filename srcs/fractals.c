/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:18:23 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 20:06:20 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_pixel pixel, t_fract *fractal)
{
	t_complex	new;
	t_complex	old;
	int			i;

	new.real = 1.5 * (pixel.x - W / 2) / (0.5 * fractal->zoom * W)
						+ fractal->move.real;
	new.i = (pixel.y - H / 2) / (0.5 * fractal->zoom * H) + fractal->move.i;
	old.real = new.real;
	old.i = new.i;
	i = 0;
	while (i < fractal->max_iters)
	{
		old.real = new.real;
		old.i = new.i;
		new.real = old.real * old.real - old.i * old.i + fractal->julia_c.real;
		new.i = 2 * old.real * old.i + fractal->julia_c.i;
		if (new.real * new.real + new.i * new.i > 4)
			break ;
		i++;
	}
	return (i);
}

int	mandelbroot(t_pixel pixel, t_fract *fractal)
{
	t_complex	new;
	t_complex	old;
	t_complex	c;
	int			i;

	c.real = 1.5 * (pixel.x - W / 2) / (0.5 * fractal->zoom * W)
					+ fractal->move.real;
	c.i = (pixel.y - H / 2) / (0.5 * fractal->zoom * H) + fractal->move.i;
	new.real = 0;
	new.i = 0;
	old.real = 0;
	old.i = 0;
	i = 0;
	while (i < fractal->max_iters)
	{
		old.real = new.real;
		old.i = new.i;
		new.real = old.real * old.real - old.i * old.i + c.real;
		new.i = 2 * old.real * old.i + c.i;
		if (new.real * new.real + new.i * new.i > 4)
			break ;
		i++;
	}
	return (i);
}

int	burningship(t_pixel pixel, t_fract *fractal)
{
	int			i;
	t_complex	c;
	t_complex	new;
	t_complex	old;

	c.real = 1.5 * (-(pixel.x) + W / 2) / (0.5 * fractal->zoom * W)
											- fractal->move.real;
	c.i = (-(pixel.y) + H / 2) / (0.5 * fractal->zoom * H) - fractal->move.i;
	new.real = 0;
	new.i = 0;
	old.real = 0;
	old.i = 0;
	i = -1;
	while (++i < fractal->max_iters)
	{
		old.i = new.i;
		old.real = new.real;
		new.i = fabs(2 * old.i * old.real) - c.i;
		new.real = old.real * old.real - old.i * old.i - c.real;
		if (new.i * new.i + new.real * new.real > 4)
			break ;
	}
	return (i);
}
