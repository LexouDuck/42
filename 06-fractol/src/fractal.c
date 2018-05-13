/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	render_julia(int max, double radius, t_complex *z, t_complex *c)
{
	double	x;
	double	y;
	int		i;

	i = 0;
	while (i < max) 
	{
		x = z->x * z->x - z->y * z->y + c->x;
		y = 2 * z->x * z->y + c->y;
		if (x * x + y * y > radius)
		{
			return (color_new(0, i << 8, i << 4, i << 2));
		}
		z->x = x;
		z->y = y;
		++i;
	}
	return (0);
}

int	render_fatou(int max, double radius, t_complex *z, t_complex *c)
{
	double	x;
	double	y;
	int		i;

	i = 0;
	while (i < max) 
	{
		x = z->x * z->x - z->y * z->y + c->x;
		y = 2 * z->x * z->y + c->y;
		if (x * x + y * y > radius)
		{
			return (0);
		}
		z->x = x;
		z->y = y;
		++i;
	}
	i = (x * x + y * y) * 20;
	return color_new(0, 255 - i, i << 4, i << 2);
}

int	render_mandelbrot(int max, double radius, t_complex *z)
{
	t_complex	c;
	double		x;
	double		y;
	int			i;

	c.x = 0;
	c.y = 0;
	i = 0;
	while (i < max) 
	{
		x = c.x * c.x - c.y * c.y + z->x;
		y = 2 * c.x * c.y + z->y;
		if (x * x + y * y > radius)
		{
			return (color_new(0, 255 - (i<<1), i<<6, i<<2));
		}
		c.x = x;
		c.y = y;
		++i;
	}
	return (0);
}

int	render_newton(int max, double radius, t_complex *z)
{
	t_complex	tmp;
	t_complex	c1;
	t_complex	c2;
	int			i;

	i = 0;
	while (i < max) 
	{
		complex_pow(&c1, *z, 3);
		c1.x -= 1;
		complex_mul(&c2, *z, *z);
		c2.x *= 3.0;
		c2.y *= 3.0;
		complex_div(&tmp, c1, c2);
		z->x -= tmp.x;
		z->y -= tmp.y;
		if (z->x * z->x + z->y * z->y > radius)
		{
			return (color_new(0, i<<2,  i<<4, i<<6));
		}
		++i;
	}
	return (0);
}
