/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:23 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 17:58:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H

# define FT_FRACTOL_H

# include <mlx.h>
# include <math.h>
# include "libft.h"

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

typedef	struct	s_fract
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			size_line;
}				t_fract;

typedef struct s_complex
{
	double		real;
	double		i;
}				t_complex;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

t_fract		*create_fractol(void);
void		*create_new_image(t_fract *fract);
void		set_pixel_to_image(char *data_addr, int size_line, t_pixel *pixel);
void		get_data_addr(t_fract *fract);
t_complex	*create_complex(double real, double i);
void 		draw_fract(t_fract *fract);
int			key_release(int keycode, void *param);
t_pixel		*create_pixel(int x, int y, int color);

#endif
