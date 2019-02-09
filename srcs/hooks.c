/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:10:43 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 19:45:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_press(int keycode, t_fract *fractol)
{
	fractol->updated = 1;
	if (keycode == 69)
		fractol->max_iters += 5;
	if (keycode == 126)
		fractol->move->x += 10;
	if (keycode == 127)
		fractol->move->y -= 10;
	if (keycode == 124)
		fractol->move->y += 10;
	if (keycode == 123)
		fractol->move->y -= 10;
	if (keycode == 78)
		if (fractol->max_iters >= 10)
			fractol->max_iters -= 5;
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fract *fract)
{
	(void)x;
	(void)y;
	fract->updated = 1;
	if (button == 4)
		fract->zoom++;
	if (button == 5 && fract->zoom > 1)
		fract->zoom--;
	return (0);
}

int	key_release(int keycode, void *param)
{
	if (keycode == 53)
		close_window(param);
	return (0);
}
