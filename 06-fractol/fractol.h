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

# include <stdlib.h>
# include <math.h>

# include <mlx.h>
# include "../mlx_events.h"
# include "libft/libft.h"



# define WIN_W	640
# define WIN_H	480

# define MAX_ZOOM	200

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

typedef struct	s_channel
{
	int			center;
	int			amplitude;
	double		phase;
	double		frequency;
}				t_channel;

typedef struct	s_palette
{
	t_channel	r;
	t_channel	g;
	t_channel	b;
}				t_palette;

typedef enum	e_fractal
{
	julia,
	fatou,
	mandelbrot,
	burningship,
	newton
}				t_fractal;

typedef struct	s_fractol
{
	t_fractal	type;
	int			max;
	double		zoom;
	double		radius;
	double		radius2;
	t_complex	anchor;
	t_point		mouse;
	t_palette	palette;
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
	int			mouse;
	void		*render;
	int			rendering;
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
**	====	render.c
*/
void		render(t_mlx *mlx);

t_channel	palette_set_channel(
	int			center,
	int			amplitude,
	double		phase,
	double		frequency);
int			event_key_palette(t_mlx *mlx, int key);

/*
**	====	fractal.c
*/
int			render_julia(
			t_fractol *fractol, t_complex *z, t_complex *c);
int			render_fatou(
			t_fractol *fractol, t_complex *z, t_complex *c);
int			render_mandelbrot(
			t_fractol *fractol, t_complex *z, t_complex *c);
int			render_burningship(
			t_fractol *fractol, t_complex *z, t_complex *c);
int			render_newton(
			t_fractol *fractol, t_complex *z, t_complex *c);

/*
**	====	event.c
*/
int			setup_events(t_mlx *mlx);

#endif