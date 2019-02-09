/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:18:23 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 18:03:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia(t_pixel *pixel, int zoom, int max_iters)
{
    t_complex   *new;
    t_complex   *old;
    int         i;

    new = create_complex(1.5 * (pixel->x - WINDOW_WIDTH / 2) / (0.5 * zoom * WINDOW_WIDTH), (pixel->y - WINDOW_HEIGHT / 2) / (0.5 * zoom * WINDOW_HEIGHT));
    i = 0;
    while (i < max_iters)
    {
        if (old)
            free(old);
        old = create_complex(new->real, new->i);
        new->real = old->real * old->real - old->i * old->i - 0.7;
        new->i = 2 * old->real * old->i + 0.27015;
        if (new->real * new->real + new->i * new->i > 4)
            break;
        i++;
    }
    free(new);
    free(old);
    return (i);
}

int mandelbroot(t_pixel *pixel, int zoom, int max_iters)
{
    t_complex   *new;
    t_complex   *old;
    t_complex   *c;
    int         i;

    c = create_complex(1.5 * (pixel->x - WINDOW_WIDTH / 2) / (0.5 * zoom * WINDOW_WIDTH), (pixel->y - WINDOW_HEIGHT / 2) / (0.5 * zoom * WINDOW_HEIGHT));
    new = create_complex(0, 0);
    old = create_complex(0, 0);
    i = 0;
    while (i < max_iters)
    {
        if (old)
            free(old);
        old = create_complex(new->real, new->i);
        new->real = old->real * old->real - old->i * old->i + c->real;
        new->i = 2 * old->real * old->i + c->i;
        if (new->real * new->real + new->i * new->i > 4)
            break;
        i++;
    }
    free(c);
    free(new);
    free(old);
    return (i);
}

int burningship(t_pixel *pixel, int zoom, int max_iters)
{
    int        i;
    t_complex   *c;
    t_complex   *z;
    double zio;
    double zro;

    c = create_complex(1.5 * (-(pixel->x) + WINDOW_WIDTH / 2) / (0.5 * zoom * WINDOW_WIDTH), (-(pixel->y) + WINDOW_HEIGHT / 2) / (0.5 * zoom * WINDOW_HEIGHT));
    z = create_complex(0, 0);
    i = -1;
    while (++i < max_iters)
    {
        zio = z->i;
        zro = z->real;
        z->i = fabs(2 * zio * zro) - c->i;
        z->real = zro * zro - zio * zio - c->real;
        if (z->i * z->i + z->real * z->real > 4)
            break ;
    }
    free(c);
    free(z);
    return (i);
}
