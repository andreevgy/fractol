/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:23 by marvin            #+#    #+#             */
/*   Updated: 2019/02/09 18:40:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H

# define FT_FRACTOL_H

# include <mlx.h>
# include <math.h>
# include "libft.h"

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 700

typedef	struct	s_fract
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			size_line;
	int			zoom;
	int			updated;
	int			max_iters;
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

typedef struct s_thread_args
{
	t_fract		*fract;
	void		(*calc)(void);
	t_pixel		*start;
	t_pixel		*end;
}				t_thread_args;


t_fract		*create_fractol(void);
void		*create_new_image(t_fract *fract);
void		set_pixel_to_image(char *data_addr, int size_line, t_pixel *pixel);
void		get_data_addr(t_fract *fract);
t_complex	*create_complex(double real, double i);
void 		draw_fract(t_fract *fract);
int			key_release(int keycode, void *param);
t_pixel		*create_pixel(int x, int y, int color);
int			julia(t_pixel *pixel, int zoom, int max_iters);
int			mandelbroot(t_pixel *pixel, int zoom, int max_iters);
int			burningship(t_pixel *pixel, int zoom, int max_iters);
int			mouse_release(int button, int x, int y, t_fract *fract);
int			key_press(int keycode, t_fract *fractol);
void		calculate_pixel(t_fract *fract, int (*calc)(t_pixel *pixel, int zoom, int max_iters), t_pixel *pixel);
int			hsv(int h, int s, int v);
void		calculate_zone(t_fract *fractal, int (*calc)(t_pixel *pixel, int zoom, int max_iters), t_pixel *start, t_pixel *end);


#endif
