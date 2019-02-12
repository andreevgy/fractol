/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:29:20 by marvin            #+#    #+#             */
/*   Updated: 2019/02/12 20:15:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

void	draw_pixels(t_fract *fract)
{
	t_pixel	iter;
	int		i;

	iter.x = 0;
	iter.y = 0;
	while (iter.y < H)
	{
		iter.x = 0;
		while (iter.x < W)
		{
			i = fract->pixels[iter.y][iter.x];
			if (i != 0)
			{
				iter.color = hsv(i % 60 + 60, i % 255, 255 * (i < fract->max_iters));
				//set_pixel_to_image(fract->data_addr, fract->size_line, iter);
			}
			iter.x++;
		}
		iter.y++;
	}
}

void fill_pixels(int (*pixels)[H][W])
{
	int y;
	int x;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			(*pixels)[y][x] = -1;
			x++;
		}
		y++;
	}
}

void clean_screen(t_fract *fractal)
{
	int bits_per_pixel;
	int endian;
	int i;
	int end;
	int	*data_addr;

	fractal->data_addr = mlx_get_data_addr(fractal->img_ptr, &bits_per_pixel,
			&(fractal->size_line), &endian);
	data_addr = (int *)fractal->data_addr;
	i = -1;
	end = H * W * bits_per_pixel / 32;
	while (++i < end - 1)
		data_addr[i] = 0;
}

int	draw_on_update(t_fract *fractal)
{
	if (fractal->updated)
	{
		fill_pixels(&(fractal->pixels));
		clean_screen(fractal);
		draw_threads(fractal);
		//draw_pixels(fractal);
		/*t_pixel start;
		t_pixel end;
		start.x = 0;
		start.y = 0;
		end.x = W - 1;
		end.y = H - 1;
		calculate_zone(fractal, start, end);*/
		mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
								fractal->img_ptr, 0, 0);
		fractal->updated = 0;
	}
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
