/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:10:43 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 17:31:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	key_release(int keycode, void *param)
{
	if (keycode == 53)
		close_window(param);
	return (0);
}
