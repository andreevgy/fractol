/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:18:23 by marvin            #+#    #+#             */
/*   Updated: 2019/02/15 15:53:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_pixel pixel, double zoom, int max_iters, t_complex move)
{
	t_complex	new;
	t_complex	old;
	int			i;

	new.real = 1.5 * (pixel.x - W / 2) / (0.5 * zoom * W) + move.real;
	new.i = (pixel.y - H / 2) / (0.5 * zoom * H) + move.i;
	old.real = new.real;
	old.i = new.i;
	i = 0;
	while (i < max_iters)
	{
		old.real = new.real;
		old.i = new.i;
		new.real = old.real * old.real - old.i * old.i - 0.7;
		new.i = 2 * old.real * old.i + 0.27015;
		if (new.real * new.real + new.i * new.i > 4)
			break ;
		i++;
	}
	return (i);
}

int	mandelbroot(t_pixel pixel, double zoom, int max_iters, t_complex move)
{
	t_complex	new;
	t_complex	old;
	t_complex	c;
	int			i;

	c.real = 1.5 * (pixel.x - W / 2) / (0.5 * zoom * W) + move.real;
	c.i = (pixel.y - H / 2) / (0.5 * zoom * H) + move.i;
	new.real = 0;
	new.i = 0;
	old.real = 0;
	old.i = 0;
	i = 0;
	while (i < max_iters)
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

int	burningship(t_pixel pixel, double zoom, int max_iters, t_complex move)
{
	int			i;
	t_complex	c;
	t_complex	new;
	t_complex	old;

	c.real = 1.5 * (-(pixel.x) + W / 2) / (0.5 * zoom * W) + move.real;
	c.i = (-(pixel.y) + H / 2) / (0.5 * zoom * H) + move. i;
	new.real = 0;
	new.i = 0;
	old.real = 0;
	old.i = 0;
	i = -1;
	while (++i < max_iters)
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
