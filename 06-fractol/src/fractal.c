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

int			palette_getcolor(t_palette const palette, int i, double n)
{
	int		result;
	double	tmp;

	result = 0;
	n = i - log(log(n)) / log (2.0);
	tmp = palette.r.amplitude * sin(palette.r.phase + palette.r.frequency * n);
	result |= (t_u8)(palette.r.center + tmp) << 16;
	tmp = palette.g.amplitude * sin(palette.g.phase + palette.g.frequency * n);
	result |= (t_u8)(palette.g.center + tmp) << 8;
	tmp = palette.b.amplitude * sin(palette.b.phase + palette.b.frequency * n);
	result |= (t_u8)(palette.b.center + tmp);
	return (result);
}

int	render_julia(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
{
	t_complex	tmp;
	t_complex	z;
	t_complex	c;
	double		n;
	int			i;

	z = *z_ptr;
	c = *c_ptr;
	i = 0;
	while (i < fractol->max) 
	{
		tmp.x = z.x * z.x - z.y * z.y + c.x;
		tmp.y = 2 * z.x * z.y + c.y;
		if ((n = tmp.x * tmp.x + tmp.y * tmp.y) > fractol->radius2)
		{
			//n = i - log(log(n)) / log (2.0);
			return (palette_getcolor(fractol->palette, i, n)); //(color_new(0, i << 8, i << 4, i << 2));
			//	150 + 99 * sin(0.12 * n + 1),
			//	100 + 99 * sin(0.13 * n + 0),
			//	230 + 25 * sin(0.16 * n + 0)));
		}
		z.x = tmp.x;
		z.y = tmp.y;
		++i;
	}
	return (0);
}

int	render_fatou(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
{
	t_complex	tmp;
	t_complex	z;
	t_complex	c;
	double		n;
	int			i;

	z = *z_ptr;
	c = *c_ptr;
	n = 0;
	i = 0;
	while (i < fractol->max) 
	{
		tmp.x = z.x * z.x - z.y * z.y + c.x;
		tmp.y = 2 * z.x * z.y + c.y;
		if ((n = tmp.x * tmp.x + tmp.y * tmp.y) > fractol->radius2)
		{
			return (0);
		}
		z.x = tmp.x;
		z.y = tmp.y;
		++i;
	}
	i = n * 20;
	return color_new(0, i<<6, 200-i, i<<4);
}

int	render_mandelbrot(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
{
	t_complex	tmp;
	t_complex	z;
	t_complex	c;
	double		n;
	int			i;

	z = *z_ptr;
	c = (c_ptr) ? *c_ptr : *z_ptr;
	i = -1;
	while (++i < fractol->max)
	{
		tmp.x = c.x * c.x - c.y * c.y + z.x;
		tmp.y = 2 * c.x * c.y + z.y;
		if ((n = tmp.x * tmp.x + tmp.y * tmp.y) > fractol->radius2)
		{
			return (palette_getcolor(fractol->palette, i, n)); //(color_new(0, i<<4, i<<2, 200-(i<<1)));
		}
		c.x = tmp.x;
		c.y = tmp.y;
	}
	return (0);
}

int	render_burningship(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
{
	t_complex	tmp;
	t_complex	z;
	t_complex	c;
	double		n;
	int			i;

	z = *z_ptr;
	c = (c_ptr) ? *z_ptr : *z_ptr;
	i = -1;
	while (++i < fractol->max)
	{
		tmp.x = fabs((double)(c.x * c.x - c.y * c.y + z.x));
		tmp.y = fabs((double)(2 * c.x * c.y + z.y));
		if ((n = tmp.x * tmp.x + tmp.y * tmp.y) > fractol->radius2)
		{
			return (palette_getcolor(fractol->palette, i, n)); // (color_new(0, 255 - i, i<<4, i<<2));
		}
		c.x = tmp.x;
		c.y = tmp.y;
	}
	return (0);
}

int	render_newton(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
{
	t_complex	z;
	t_complex	c;
	double		tmp;
	int			i;

	z = (c_ptr) ? *z_ptr : *z_ptr;
	i = 0;
	tmp = 1.0;
	while (tmp > fractol->radius2 && ++i < fractol->max)
	{
		c.x = z.x;
		c.y = z.y;
		tmp = (c.x * c.x + c.y * c.y);
		tmp *= tmp;
		z.x = (2 * z.x * tmp + z.x * z.x - z.y * z.y) / (3.0 * tmp);
		z.y = (2 * z.y * (tmp - c.x)) / (3.0 * tmp);
		tmp = (z.x - c.x) * (z.x - c.x) + (z.y - c.y) * (z.y - c.y);
	}
	if (tmp <= fractol->radius2)
		return (0);
	i = (tmp < 255) ? tmp : 255;
	return (color_new(0, i<<4, i<<2, i<<6));
}
