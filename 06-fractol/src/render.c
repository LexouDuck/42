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

void	render_debug_complex(t_mlx *mlx, t_complex *complex, t_point p)
{
	char *result;
	char *c_real;
	char *c_imag;
	t_point c;

	c_real = ft_ftoa(complex->x, 3);
	c_imag = ft_ftoa(complex->y, 3);
	c.x = ft_strlen(c_real);
	c.y = ft_strlen(c_imag);
	if (!(result = (char *)malloc(c.x + c.y + 4)))
		return;
	c.color = 0;
	ft_memcpy(result + c.color, c_real, c.x);
	c.color += c.x;
	result[c.color++] = ' ';
	if (ft_isdigit(c_imag[0]))
		result[c.color++] = '+';
	ft_memcpy(result + c.color, c_imag, c.y);
	c.color += c.y;
	result[c.color++] = 'i';
	result[c.color] = '\0';
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, p.x, p.y, p.color, result);
	free(c_real);
	free(c_imag);
	free(result);
}

void	render_debug(t_mlx *mlx, t_complex *complex)
{
	t_point pos;
	char *c;

	pos.color = 0xFFFFFF;
	c = ft_ftoa(mlx->fractol->radius, 4);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, pos.color, "RADIUS:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 40, pos.color, c);
	free(c);
	c = ft_ftoa(mlx->fractol->zoom, 4);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, pos.color, "ZOOM:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 60, pos.color, c);
	free(c);
	pos.x = 10;
	pos.y = 20;
	render_debug_complex(mlx, complex, pos);
	pos.y = 80;
	render_debug_complex(mlx, &mlx->fractol->anchor, pos);
}

void				render(t_mlx *mlx)
{
	double		radius2;
	double		scale;
	t_point		pos;
	t_complex	z;
	t_complex	c;

	ft_bzero(mlx->image->buffer, WIN_H * mlx->image->line);
	radius2 = mlx->fractol->radius * mlx->fractol->radius;
	scale = mlx->fractol->radius * mlx->fractol->zoom;
	pos.y = -1;
	while (++pos.y < WIN_H)
	{
		pos.x = -1;
		while (++pos.x < WIN_W)
		{
			z.x = scale * (double)(pos.x - WIN_W / 2) / WIN_H + mlx->fractol->anchor.x;
			z.y = scale * (double)(pos.y - WIN_H / 2) / WIN_H + mlx->fractol->anchor.y;
			pos.color = 0;
			if (mlx->fractol->type == mandelbrot)
				pos.color = render_mandelbrot(28, radius2, &z);
			else if (mlx->fractol->type == newton)
				pos.color = render_newton(32, radius2, &z);
			else
			{
				c.x = ((double)mlx->fractol->mouse.x / (double)WIN_W) * 2 - 1;
				c.y = ((double)mlx->fractol->mouse.y / (double)WIN_H);
				if (mlx->fractol->type == julia)
					pos.color = render_julia(32, radius2, &z, &c);
				if (mlx->fractol->type == fatou)
					pos.color = render_fatou(32, radius2, &z, &c);
			}
			if (pos.color)
				set_pixel(mlx->image, &pos);
		}
	}
	pos.x = WIN_W / 2 + mlx->fractol->anchor.x * mlx->fractol->zoom;
	pos.y = WIN_H / 2 + mlx->fractol->anchor.y * mlx->fractol->zoom;
	pos.color = 0xFFFFFF;
	set_pixel(mlx->image, &pos);
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	render_debug(mlx, &c);
}
