/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:50:55 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 13:57:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pixel *create_pixel(int x, int y, int color)
{
    t_pixel *pixel;

    pixel = (t_pixel *)ft_memalloc(sizeof(t_pixel));
    pixel->x = x;
    pixel->y = y;
    pixel->color = color;
    return (pixel);
}