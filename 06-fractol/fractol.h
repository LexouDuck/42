/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2018/10/18 17:44:48 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <time.h>

# include <mlx.h>
# include "../mlx_events.h"

# include "libft/libft.h"
# include "libft/libft_char.h"
# include "libft/libft_memory.h"
# include "libft/libft_string.h"
# include "libft/libft_convert.h"
# include "libft/libft_list.h"
# include "libft/libft_io.h"

# define WIN_W	640
# define WIN_H	480

# define MAX_ZOOM	64

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
void			complex_add(t_complex *result,
	t_complex const c1, t_complex const c2);
void			complex_sub(t_complex *result,
	t_complex const c1, t_complex const c2);
void			complex_mul(t_complex *result,
	t_complex const c1, t_complex const c2);
void			complex_div(t_complex *result,
	t_complex const c1, t_complex const c2);
void			complex_pow(t_complex *result, t_complex const c, int n);

/*
**	====	color.c
*/
t_u32			color_new(t_u8 a, t_u8 r, t_u8 g, t_u8 b);
t_u8			color_get_a(t_u32 color);
t_u8			color_get_r(t_u32 color);
t_u8			color_get_g(t_u32 color);
t_u8			color_get_b(t_u32 color);

/*
**	====	render.c
*/

int				handle_expose(void *param);
void			render(t_mlx *mlx);

/*
**	====	palette.c
*/
int				event_key_palette(t_mlx *mlx, int key);
t_u32			palette_getcolor(t_palette const palette, int i, double n);
t_channel		palette_set_channel(
	int			center,
	int			amplitude,
	double		phase,
	double		frequency);

/*
**	====	fractal.c
*/
t_u32			render_julia(
	t_fractol *fractol, t_complex *z, t_complex *c);
t_u32			render_fatou(
	t_fractol *fractol, t_complex *z, t_complex *c);
t_u32			render_mandelbrot(
	t_fractol *fractol, t_complex *z, t_complex *c);
t_u32			render_burningship(
	t_fractol *fractol, t_complex *z, t_complex *c);
t_u32			render_newton(
	t_fractol *fractol, t_complex *z, t_complex *c);

/*
**	====	event.c
*/
int				setup_events(t_mlx *mlx);

#endif
