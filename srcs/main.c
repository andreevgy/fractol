/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:29:20 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 14:38:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

void	draw_pixels(t_fract *fract)
{
	t_pixel	*iter;
	int		i;

	iter = create_pixel(0, 0, 0);
	while (iter->y < H)
	{
		iter->x = 0;
		while (iter->x < W)
		{
			i = fract->pixels[iter->y][iter->x];
			if (i != -1)
			{
				iter->color = hsv(i % 60 + 240, i % 255, 100 * (i < fract->max_iters));
				set_pixel_to_image(fract->data_addr, fract->size_line, iter);
			}
			iter->x++;
		}
		iter->y++;
	}
	free(iter);
}

void fill_pixels(int pixels[H][W])
{
	int y;
	int x;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			pixels[y][x] = -1;
			x++;
		}
		y++;
	}
}

int	draw_on_update(t_fract *fractal)
{
	t_pixel *start;
	t_pixel *end;

	start = NULL;
	end = NULL;
	if (fractal->updated)
	{
		start = create_pixel(0, 0, 0);
		end = create_pixel(W, H, 0);
		fill_pixels(fractal->pixels);
		calculate_zone(fractal, start, end);
		draw_pixels(fractal);
		mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
								fractal->img_ptr, 0, 0);
		fractal->updated = 0;
	}
	if (start)
		free(start);
	if (end)
		free(end);
	return (0);
}

int	print_usage(void)
{
	ft_putendl("usage: ./fractol [mandelbroot, julia, burningship]");
	return (0);
}

int	main(int argc, char **argv)
{
	t_fract *fractol;

	if (argc == 1 || (ft_strcmp(argv[1], "mandelbroot")
						&& ft_strcmp(argv[1], "julia")
						&& ft_strcmp(argv[1], "burningship")))
		return (print_usage());
	fractol = create_fractol(argv[1]);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
							fractol->img_ptr, 0, 0);
	mlx_loop_hook(fractol->mlx_ptr, &draw_on_update, fractol);
	mlx_hook(fractol->win_ptr, 2, 0, &key_press, fractol);
	mlx_hook(fractol->win_ptr, 4, 0, &mouse_release, fractol);
	mlx_hook(fractol->win_ptr, 3, 0, &key_release, NULL);
	mlx_loop(fractol->mlx_ptr);
}
