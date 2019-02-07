/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:27:59 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 16:09:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_pixel_to_image(char *data_addr, int size_line, int x, int y)
{
	int *image;

	image = (int *)data_addr;
	if (x >= 0 && x < WINDOW_WIDTH &&
			y >= 0 && y < WINDOW_HEIGHT)
	{
		image[(size_line / 4) * y + x] = 0xFFFFFF;
	}
}

void 		get_data_addr(t_fract *fract)
{
	int bits_per_pixel;
	int endian;

    fract->data_addr = mlx_get_data_addr(fract->img_ptr, &bits_per_pixel, &(fract->size_line), &endian);
}

void		*create_new_image(t_fract *fract)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(fract->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (img_ptr);
}