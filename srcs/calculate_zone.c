/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:00:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 18:41:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void fill_zone(t_fract *fractal, t_pixel *start, t_pixel *end, int i)
{
    t_pixel *iter;
    (void)i;
    iter = create_pixel(start->x, start->y, hsv(i % 60 + 60, i % 255, 255 * (i < fractal->max_iters)));
    

    while(iter->y < end->y)
    {
        iter->x = start->x;
        while (iter->x < end->x)
        {
            set_pixel_to_image(fractal->data_addr, fractal->size_line, iter);
            iter->x++;
        }
        iter->y++;
    }
    free(iter);
}

void calculate_zone(t_fract *fractal, int (*calc)(t_pixel *pixel, int zoom, int max_iters), t_pixel *start, t_pixel *end)
{
    t_pixel *iter;
    t_pixel *middle1;
    t_pixel *middle2;
    int i;
    
    
    iter = create_pixel(start->x, start->y, 0xFFFFFF);
    i = calc(iter, fractal->zoom, fractal->max_iters);
    if (start->x == end->x && start->y == end->y)
        return (calculate_pixel(fractal, calc, start));
    if (end->x - start->x == 0 || end->y - start->y == 0 || end->x - start->x == 1 || end->y - start->y == 1 )
    {
        fill_zone(fractal, start, end, i);
        return;
    }
    while (iter->x < end->x)
    {
        
        if (i != calc(iter, fractal->zoom, fractal->max_iters))
        {
            if (end->x - start->x > end->y - start->y)
            {
                middle1 = create_pixel((end->x + start->x) / 2, end->y, 0);            
                middle2 = create_pixel((end->x + start->x) / 2, start->y, 0);
            }
            else
            {
                middle1 = create_pixel(end->x, (end->y + start->y) / 2, 0);
                middle2 = create_pixel(start->x, (end->y + start->y) / 2, 0);
            }
            calculate_zone(fractal, calc, start, middle1);
            calculate_zone(fractal, calc, middle2, end);
            free(middle1);
            free(middle2);
            return;
        }
        iter->x++;
    }
    while (iter->y < end->y)
    {
        if (i != calc(iter, fractal->zoom, fractal->max_iters))
        {

            if (end->x - start->x > end->y - start->y)
            {
                middle1 = create_pixel((end->x + start->x) / 2, end->y, 0);            
                middle2 = create_pixel((end->x + start->x) / 2, start->y, 0);
            }
            else
            {
                middle1 = create_pixel(end->x, (end->y + start->y) / 2, 0);
                middle2 = create_pixel(start->x, (end->y + start->y) / 2, 0);
            }
            calculate_zone(fractal, calc, start, middle1);
            calculate_zone(fractal, calc, middle2, end);
            free(middle1);
            free(middle2);
            return;
        }
        iter->y++;
    }
    while (iter->x > start->x)
    {
        if (i != calc(iter, fractal->zoom, fractal->max_iters))
        {

            if (end->x - start->x > end->y - start->y)
            {
                middle1 = create_pixel((end->x + start->x) / 2, end->y, 0);            
                middle2 = create_pixel((end->x + start->x) / 2, start->y, 0);
            }
            else
            {
                middle1 = create_pixel(end->x, (end->y + start->y) / 2, 0);
                middle2 = create_pixel(start->x, (end->y + start->y) / 2, 0);
            }
            calculate_zone(fractal, calc, start, middle1);
            calculate_zone(fractal, calc, middle2, end);
            free(middle1);
            free(middle2);
            return;
        }
        iter->x--;
    }
    while (iter->y > start->y)
    {

        if (i != calc(iter, fractal->zoom, fractal->max_iters))
        {
            if (end->x - start->x > end->y - start->y)
            {
                middle1 = create_pixel((end->x + start->x) / 2, end->y, 0);            
                middle2 = create_pixel((end->x + start->x) / 2, start->y, 0);
            }
            else
            {
                middle1 = create_pixel(end->x, (end->y + start->y) / 2, 0);
                middle2 = create_pixel(start->x, (end->y + start->y) / 2, 0);
            }
            calculate_zone(fractal, calc, start, middle1);
            calculate_zone(fractal, calc, middle2, end);
            free(middle1);
            free(middle2);
            return;
        }
        iter->y--;
    }
    fill_zone(fractal, start, end, i);
    free(iter);
}