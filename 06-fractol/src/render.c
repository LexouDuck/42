/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	render_debug(t_mlx *mlx, t_complex *complex)
{
	int index;
	char *c_real = ft_ftoa(complex->x, 3);
	char *c_imag = ft_ftoa(complex->y, 3);
	int c_real_length = ft_strlen(c_real);
	int c_imag_length = ft_strlen(c_imag);
	char *c;

	if (!(c = (char *)malloc(c_real_length + c_imag_length + 8)))
		return;
	index = 0;
	c[index++] = 'c';
	c[index++] = ':';
	c[index++] = ' ';
	ft_memcpy(c + index, c_real, c_real_length);
	index += c_real_length;
	c[index++] = ' ';
	if (ft_isdigit(c_imag[0]))
		c[index++] = '+';
	ft_memcpy(c + index, c_imag, c_imag_length);
	index += c_imag_length;
	c[index++] = 'i';
	c[index++] = '\0';
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 20, 0xFFFFFF, c);
	free(c_real);
	free(c_imag);
	free(c);
	c = ft_ftoa(mlx->fractol->zoom, 2);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, 0xFFFFFF, c);
	free(c);
}

static inline int	render_julia(t_complex *z, t_complex *c, int max, float radius)
{
	t_complex tmp;
	int i;

	i = 0;
	while (i < max) 
	{
		tmp.x = z->x * z->x - z->y * z->y + c->x;
		tmp.y = 2 * z->x * z->y + c->y;
		if (tmp.x * tmp.x + tmp.y * tmp.y > radius)
		{
			return (color_new(0, i << 8, i << 4, i << 2));
		}
		z->x = tmp.x;
		z->y = tmp.y;
		++i;
	}
	return (0);
}

static inline int	render_fatou(t_complex *z, t_complex *c, int max, float radius)
{
	t_complex tmp;
	int i;

	i = 0;
	while (i < max) 
	{
		tmp.x = z->x * z->x - z->y * z->y + c->x;
		tmp.y = 2 * z->x * z->y + c->y;
		if (tmp.x * tmp.x + tmp.y * tmp.y > radius)
		{
			return (0);
		}
		z->x = tmp.x;
		z->y = tmp.y;
		++i;
	}
	i = 16 * (tmp.x * tmp.x + tmp.y * tmp.y);
	return color_new(0, 255 - i, i << 4, i << 2);
}

static inline int	render_mandelbrot(t_complex *z, int max, float radius)
{
	t_complex c;
	t_complex tmp;
	int i;

	c.x = 0;
	c.y = 0;
	i = 0;
	while (i < max) 
	{
		tmp.x = c.x * c.x - c.y * c.y + z->x;
		tmp.y = 2 * c.x * c.y + z->y;
		if (tmp.x * tmp.x + tmp.y * tmp.y > radius)
		{
			return (color_new(0, 255 - i, i << 6, i << 2));
		}
		c.x = tmp.x;
		c.y = tmp.y;
		++i;
	}
	return (0);
}

void				render(t_mlx *mlx)
{
	float		radius2;
	float		scale;
	t_point		pos;
	t_complex	z;
	t_complex	c;

	ft_bzero(mlx->image->buffer, WIN_H * mlx->image->line);
	radius2 = mlx->fractol->radius * mlx->fractol->radius;
	scale = mlx->fractol->zoom * mlx->fractol->radius;
	pos.y = -1;
	while (++pos.y < WIN_H)
	{
		pos.x = -1;
		while (++pos.x < WIN_W)
		{
			z.x = scale * ((float)pos.x - mlx->fractol->anchor.x) / WIN_H;
			z.y = scale * ((float)pos.y - mlx->fractol->anchor.y) / WIN_H;
			pos.color = 0;
			if (mlx->fractol->type == mandelbrot)
				pos.color = render_mandelbrot(&z, 28, radius2);
			else
			{
				c.x = ((float)mlx->fractol->mouse.x / (float)WIN_W) * 2 - 1;
				c.y = ((float)mlx->fractol->mouse.y / (float)WIN_H);
				if (mlx->fractol->type == julia)
					pos.color = render_julia(&z, &c, 32, radius2);
				if (mlx->fractol->type == fatou)
					pos.color = render_fatou(&z, &c, 32, radius2);
			}
			if (pos.color)
				set_pixel(mlx->image, &pos);
		}
	}
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	render_debug(mlx, &c);
}
