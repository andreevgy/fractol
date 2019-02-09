/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:18:23 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 19:14:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_pixel *pixel, int zoom, int max_iters)
{
	t_complex	*new;
	t_complex	*old;
	int			i;

	new = create_complex(1.5 * (pixel->x - W / 2) / (0.5 * zoom * W),
						(pixel->y - H / 2) / (0.5 * zoom * H));
	old = create_complex(new->real, new->i);
	i = 0;
	while (i < max_iters)
	{
		old->real = new->real;
		old->i = new->i;
		new->real = old->real * old->real - old->i * old->i - 0.7;
		new->i = 2 * old->real * old->i + 0.27015;
		if (new->real * new->real + new->i * new->i > 4)
			break ;
		i++;
	}
	free(new);
	free(old);
	return (i);
}

int	mandelbroot(t_pixel *pixel, int zoom, int max_iters)
{
	t_complex	*new;
	t_complex	*old;
	t_complex	*c;
	int			i;

	c = create_complex(1.5 * (pixel->x - W / 2) / (0.5 * zoom * W),
								(pixel->y - H / 2) / (0.5 * zoom * H));
	new = create_complex(0, 0);
	old = create_complex(0, 0);
	i = 0;
	while (i < max_iters)
	{
		old->real = new->real;
		old->i = new->i;
		new->real = old->real * old->real - old->i * old->i + c->real;
		new->i = 2 * old->real * old->i + c->i;
		if (new->real * new->real + new->i * new->i > 4)
			break ;
		i++;
	}
	free(c);
	free(new);
	free(old);
	return (i);
}

int	burningship(t_pixel *pixel, int zoom, int max_iters)
{
	int			i;
	t_complex	*c;
	t_complex	*new;
	t_complex	*old;

	c = create_complex(1.5 * (-(pixel->x) + W / 2) / (0.5 * zoom * W),
						(-(pixel->y) + H / 2) / (0.5 * zoom * H));
	new = create_complex(0, 0);
	old = create_complex(0, 0);
	i = -1;
	while (++i < max_iters)
	{
		old->i = new->i;
		old->real = new->real;
		new->i = fabs(2 * old->i * old->real) - c->i;
		new->real = old->real * old->real - old->i * old->i - c->real;
		if (new->i * new->i + new->real * new->real > 4)
			break ;
	}
	free(c);
	free(new);
	free(old);
	return (i);
}
