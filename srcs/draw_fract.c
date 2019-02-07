/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:48:20 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 16:58:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void draw_fract(t_fract *fract)
{
    int x;
    int y;
    t_complex *new;
    t_complex *old;
    int i;

    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            new = create_complex(1.5 * (x - WINDOW_WIDTH / 2) / (0.5 * WINDOW_WIDTH), (y - WINDOW_HEIGHT / 2) / (0.5 * WINDOW_HEIGHT));
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
                set_pixel_to_image(fract->data_addr, fract->size_line, x, y);
            x++;
       }
       y++;
    }
}