/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:29:20 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 20:41:06 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	draw_interface(t_fract *fractal)
{
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 10,
			0x00FF00, "Controls: H - hide/show");
	if (fractal->interface)
	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 30,
				0x00FF00, "Scroll up/down - zoom");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 50,
				0x00FF00, "Arrows - movement");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 70,
				0x00FF00, "M - stop/enable Julia movement by mouse");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 90,
				0x00FF00, "Colors: Z, X, C");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 110,
				0x00FF00, "Iterations: +/- on numpad");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 30, 130,
				0x00FF00, "Iterations:");
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 150, 130,
				0x00FF00, ft_itoa(fractal->max_iters));
	}
	return (0);
}

int	draw_on_update(t_fract *fractal)
{
	if (fractal->updated)
	{
		draw_threads(fractal);
		mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
								fractal->img_ptr, 0, 0);
		draw_interface(fractal);
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
	mlx_hook(fractol->win_ptr, 6, 0, &mouse_move, fractol);
	mlx_hook(fractol->win_ptr, 17, 0, &close_window, NULL);
	mlx_loop(fractol->mlx_ptr);
}
