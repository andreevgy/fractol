/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:27:59 by fmacgyve          #+#    #+#             */
/*   Updated: 2019/02/15 16:02:23 by fmacgyve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_pixel_to_image(char *data_addr, int size_line, t_pixel pixel)
{
	int *image;

	image = (int *)data_addr;
	if (pixel.x >= 0 && pixel.x < W &&
			pixel.y >= 0 && pixel.y < H)
	{
		image[(size_line / 4) * pixel.y + pixel.x] = pixel.color;
	}
}

void		get_data_addr(t_fract *fract)
{
	int bits_per_pixel;
	int endian;

	fract->data_addr = mlx_get_data_addr(fract->img_ptr,
							&bits_per_pixel, &(fract->size_line), &endian);
}

void		*create_new_image(t_fract *fract)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(fract->mlx_ptr, W, H);
	return (img_ptr);
}
