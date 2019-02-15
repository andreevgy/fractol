/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:10:43 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 20:38:02 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	change_colors(int keycode, t_fract *fractal)
{
	if (keycode == 6)
	{
		if (fractal->color.x + 60 > 360)
			fractal->color.x = 60;
		else
			fractal->color.x += 60;
	}
	if (keycode == 7)
	{
		if (fractal->color.y + 60 > 360)
			fractal->color.y = 0;
		else
			fractal->color.y += 60;
	}
	if (keycode == 8)
	{
		if (fractal->color.color + 64 > 255)
			fractal->color.color = 0;
		else
			fractal->color.color += 64;
	}
	return (0);
}

int	key_press(int keycode, t_fract *fractol)
{
	fractol->updated = 1;
	if (keycode == 69)
		fractol->max_iters += 5;
	if (keycode == 4)
		fractol->interface = !fractol->interface;
	if (keycode == 46)
		fractol->move_julia = !fractol->move_julia;
	if (keycode == 126)
		(fractol->move).i -= 0.1 / fractol->zoom;
	if (keycode == 125)
		(fractol->move).i += 0.1 / fractol->zoom;
	if (keycode == 124)
		(fractol->move).real += 0.1 / fractol->zoom;
	if (keycode == 123)
		(fractol->move).real -= 0.1 / fractol->zoom;
	if (keycode == 78)
		if (fractol->max_iters >= 10)
			fractol->max_iters -= 5;
	change_colors(keycode, fractol);
	if (keycode == 53)
		close_window(0);
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fract *fr)
{
	if (x < W && x >= 0 && y < H && y >= 0)
	{
		if (button == 4)
		{
			fr->updated = 1;
			fr->move.real += (((x > W / 2) ? ((double)x / (double)W - 0.5) :
				-(0.5 - (double)x / (double)W)) / fr->zoom);
			fr->move.i += (((y > H / 2) ? 0.67 * ((double)y / (double)H - 0.5) :
				-0.67 * (0.5 - (double)y / (double)H)) / fr->zoom);
			fr->max_iters += 2;
			fr->zoom *= 1.5;
		}
		else if (button == 5)
		{
			fr->updated = 1;
			fr->max_iters -= 1;
			fr->zoom /= 1.5;
			fr->move.real -= (((x > W / 2) ? ((double)x / (double)W - 0.5) :
				-(0.5 - (double)x / (double)W)) / fr->zoom);
			fr->move.i -= (((y > H / 2) ? 0.67 * ((double)y / (double)H - 0.5) :
				-0.67 * (0.5 - (double)y / (double)H)) / fr->zoom);
		}
	}
	return (0);
}

int	mouse_move(int x, int y, t_fract *fractal)
{
	if (fractal->move_julia)
	{
		fractal->updated = 1;
		fractal->julia_c.i = ((double)y / (double)H - 0.5) * 2;
		fractal->julia_c.real = ((double)x / (double)W * 2) - 1.5;
	}
	return (0);
}
