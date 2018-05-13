/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <mlx.h>
# include "../mlx_events.h"
# include "libft/libft.h"



# define WIN_W	640
# define WIN_H	480

# define MAX_ZOOM	10000000

typedef struct	s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

typedef struct	s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef enum	e_fractal
{
	julia,
	fatou,
	newton,
	mandelbrot
}				t_fractal;

typedef struct	s_fractol
{
	t_fractal	type;
	double		zoom;
	double		radius;
	t_complex	anchor;
	t_point		mouse;
}				t_fractol;

typedef	struct	s_image
{
	int			bpp;
	int			line;
	int			endian;
	t_u8		*buffer;
}				t_image;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_image		*image;
	t_fractol	*fractol;
}				t_mlx;

/*
**	====	complex.c
*/
void		complex_add(t_complex *result, t_complex const c1, t_complex const c2);
void		complex_sub(t_complex *result, t_complex const c1, t_complex const c2);
void		complex_mul(t_complex *result, t_complex const c1, t_complex const c2);
void		complex_div(t_complex *result, t_complex const c1, t_complex const c2);
void		complex_pow(t_complex *result, t_complex const c, int n);

/*
**	====	color.c
*/
int			color_new(char a, t_u8 r, t_u8 g, t_u8 b);
char		color_get_a(int color);
t_u8		color_get_r(int color);
t_u8		color_get_g(int color);
t_u8		color_get_b(int color);

/*
**	====	window.c
*/
int			is_in_window(int x, int y);
void		bring_into_window(t_point *point);
void		set_pixel(t_image *image, t_point *pos);
int			get_color_mean(int color1, int color2, float ratio);

/*
**	====	render.c
*/
void		render(t_mlx *mlx);

/*
**	====	fractal.c
*/
int			render_newton(int max, double radius, t_complex *z);
int			render_mandelbrot(int max, double radius, t_complex *z);
int			render_fatou(int max, double radius, t_complex *z, t_complex *c);
int			render_julia(int max, double radius, t_complex *z, t_complex *c);

/*
**	====	event.c
*/
int			setup_events(t_mlx *mlx);

#endif