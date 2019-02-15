/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:27:09 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 20:33:42 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_fractal(t_fract **fractol, char *name)
{
	if (!ft_strcmp(name, "mandelbroot"))
		(*fractol)->calc = &mandelbroot;
	if (!ft_strcmp(name, "julia"))
	{
		(*fractol)->calc = &julia;
		(*fractol)->julia = 1;
	}
	if (!ft_strcmp(name, "burningship"))
		(*fractol)->calc = &burningship;
}

t_fract		*create_fractol(char *name)
{
	t_fract *fractol;

	NULL_CHECK((fractol = (t_fract *)ft_memalloc(sizeof(t_fract))));
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, W, H,
									ft_strjoin("fractol: ", name));
	fractol->img_ptr = create_new_image(fractol);
	fractol->updated = 1;
	fractol->zoom = 1;
	fractol->max_iters = 200;
	fractol->move.real = 0;
	fractol->interface = 1;
	fractol->move.i = 0;
	fractol->color.x = 60;
	fractol->color.y = 0;
	fractol->color.color = 0;
	fractol->move_julia = 1;
	fractol->julia_c.real = 0.7;
	fractol->julia_c.i = 0.27015;
	fractol->julia = 0;
	set_fractal(&fractol, name);
	get_data_addr(fractol);
	return (fractol);
}
