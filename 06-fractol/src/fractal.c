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
	double	tmp;
	double	x;
	double	y;
	int		i;

	i = 0;
	while (i < max) 
	{
		x = z->x * z->x - z->y * z->y + c->x;
		y = 2 * z->x * z->y + c->y;
		if ((tmp = x * x + y * y) > radius)
		{
			tmp = i - log(log(tmp)) / log (2.0);
			return (color_new(0, //i << 8, i << 4, i << 2));
				150 + 99 * sin(0.12 * tmp + 1),
				100 + 99 * sin(0.13 * tmp + 0),
				230 + 25 * sin(0.16 * tmp + 0)));
		}
		z->x = x;
		z->y = y;
		++i;
	}
	return (0);
}

int	render_fatou(int max, double radius, t_complex *z, t_complex *c)
{
	double	tmp;
	double	x;
	double	y;
	int		i;

	i = 0;
	while (i < max) 
	{
		x = z->x * z->x - z->y * z->y + c->x;
		y = 2 * z->x * z->y + c->y;
		if ((tmp = x * x + y * y) > radius)
		{
			return (0);
		}
		z->x = x;
		z->y = y;
		++i;
	}
	i = tmp * 20;
	return color_new(0, i<<6, 200-i, i<<4);
}

int	render_mandelbrot(int max, double radius, t_complex *z, t_complex *c)
{
	double	tmp;
	double	x;
	double	y;
	int		i;

	c->x = 0;
	c->y = 0;
	i = -1;
	while (++i < max)
	{
		x = c->x * c->x - c->y * c->y + z->x;
		y = 2 * c->x * c->y + z->y;
		if ((tmp = x * x + y * y) > radius)
		{
			tmp = i - log(log(tmp)) / log (2.0);
			return (color_new(0, //i<<4, i<<2, 200-(i<<1)));
				100 + 99 * sin(0.13 * tmp + 0),
				150 + 99 * sin(0.12 * tmp + 1),
				230 + 25 * sin(0.16 * tmp + 0)));
		}
		c->x = x;
		c->y = y;
	}
	return (0);
}

int	render_burningship(int max, double radius, t_complex *z, t_complex *c)
{
	double	tmp;
	double	x;
	double	y;
	int		i;

	c->x = z->x;
	c->y = z->y;
	i = -1;
	while (++i < max) 
	{
		x = fabs((double)(c->x * c->x - c->y * c->y + z->x));
		y = fabs((double)(2 * c->x * c->y + z->y));
		if ((tmp = x * x + y * y) > radius)
		{
			tmp = i - log(log(tmp)) / log (2.0);
			return (color_new(0, //255 - i, i<<4, i<<2));
				230 + 25 * sin(0.16 * tmp + 0),
				100 +100 * sin(0.13 * tmp + 1),
				100 + 99 * sin(0.10 * tmp + 2)));
		}
		c->x = x;
		c->y = y;
	}
	return (0);
}

int	render_newton(int max, double radius, t_complex *z, t_complex *c)
{
	double	tmp;
	int		i;

	i = 0;
	tmp = 1.0;
	while (tmp > radius && ++i < max) 
	{
		c->x = z->x;
		c->y = z->y;
		tmp = (c->x * c->x + c->y * c->y);
		tmp *= tmp;
		z->x = (2 * z->x * tmp + z->x * z->x - z->y * z->y) / (3.0 * tmp);
		z->y = (2 * z->y * (tmp - c->x)) / (3.0 * tmp);
		tmp = (z->x - c->x) * (z->x - c->x) + (z->y - c->y) * (z->y - c->y);
	}
	if (tmp <= radius)
		return (0);
	i = (tmp < 255) ? tmp : 255;
	return (color_new(0, i<<4, i<<2, i<<6));
}
