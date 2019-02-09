/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:27:09 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 19:33:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fract	*create_fractol(char *name)
{
	t_fract *fractol;

	fractol = (t_fract *)ft_memalloc(sizeof(t_fract));
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, W, H, "fractol");
	fractol->img_ptr = create_new_image(fractol);
	fractol->updated = 1;
	fractol->zoom = 1;
	fractol->max_iters = 200;
	if (!ft_strcmp(name, "mandelbroot"))
		fractol->calc = &mandelbroot;
	if (!ft_strcmp(name, "julia"))
		fractol->calc = &julia;
	if (!ft_strcmp(name, "burningship"))
		fractol->calc = &burningship;
	get_data_addr(fractol);
	return (fractol);
}
