/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:48:20 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 18:00:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calculate_pixel(char *data_addr, int size_line, t_pixel *pixel)
{   
    t_complex   *new;
    t_complex   *old;
    int         i;

    new = create_complex(1.5 * (pixel->x - WINDOW_WIDTH / 2) / (0.5 * WINDOW_WIDTH), (pixel->y - WINDOW_HEIGHT / 2) / (0.5 * WINDOW_HEIGHT));
    i = 0;
    while (i < 200)
    {
        old = create_complex(new->real, new->i);
        new->real = old->real * old->real - old->i * old->i - 0.7;
        new->i = 2 * old->real * old->i + 0.27015;
        if (new->real * new->real + new->i * new->i > 4)
            break;
        i++;
    }
    if (i > 100)
    {   
        set_pixel_to_image(data_addr, size_line, pixel);
    }
}

void draw_fract(t_fract *fract)
{
    t_pixel *iter;
    iter = create_pixel(0, 0, 0);

    while (iter->y < WINDOW_HEIGHT)
    {
        iter->x = 0;
        while (iter->x < WINDOW_WIDTH)
        {
            calculate_pixel(fract->data_addr, fract->size_line, iter);
            iter->x++;
       }
       iter->y++;
    }
}