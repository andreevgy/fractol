/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:27:09 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 16:07:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fract *create_fractol(void)
{
    t_fract *fractol;
    fractol = (t_fract *)ft_memalloc(sizeof(t_fract));
    fractol->mlx_ptr = mlx_init();
    fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fractol");
    fractol->img_ptr = create_new_image(fractol);
    get_data_addr(fractol);
    return (fractol);
}