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

t_u32	render_julia(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
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
			return (palette_getcolor(fractol->palette, i, n));
		}
		z.x = tmp.x;
		z.y = tmp.y;
		++i;
	}
	return (0);
}

t_u32	render_fatou(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
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
			return (0);
		z.x = tmp.x;
		z.y = tmp.y;
		++i;
	}
	i = n * 20;
	return (color_new(0,
		fractol->palette.r.center + i * fractol->palette.r.amplitude,
		fractol->palette.g.center + i * fractol->palette.g.amplitude,
		fractol->palette.b.center + i * fractol->palette.b.amplitude));
}

t_u32	render_mandelbrot(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
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
			return (palette_getcolor(fractol->palette, i, n));
		}
		c.x = tmp.x;
		c.y = tmp.y;
	}
	return (0);
}

t_u32	render_burningship(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
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
			return (palette_getcolor(fractol->palette, i, n));
		}
		c.x = tmp.x;
		c.y = tmp.y;
	}
	return (0);
}

t_u32	render_newton(t_fractol *fractol, t_complex *z_ptr, t_complex *c_ptr)
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
	return (color_new(0, i << 4, i << 2, i << 6));
}
