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

void				render_debug_complex(t_mlx *mlx,
	t_complex *complex, t_point p)
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

void				render_debug(t_mlx *mlx, t_complex *complex)
{
	t_point pos;
	char *c;

	pos.color = 0xFFFFFF;
	c = ft_ftoa(mlx->fractol->radius, 8);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, pos.color, "RADIUS:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 40, pos.color, c);
	free(c);
	c = ft_ftoa(mlx->fractol->zoom, 8);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, pos.color, "ZOOM:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 60, pos.color, c);
	free(c);
	pos.x = 10;
	pos.y = 20;
	render_debug_complex(mlx, &mlx->fractol->anchor, pos);
	pos.y = 80;
	if (mlx->fractol->type == julia || mlx->fractol->type == fatou)
		render_debug_complex(mlx, complex, pos);
}

static void			render_fractal(t_mlx *mlx, t_u32 *buffer, t_complex *c,
	int (*get_color)(t_fractol *, t_complex *, t_complex *))
{
	t_complex	anchor;
	double		scale;
	t_point		pos;
	t_complex	z;

	mlx->fractol->max = 
		(mlx->fractol->type == julia || mlx->fractol->type == fatou) ? 32 : 64;
	mlx->fractol->radius2 = (mlx->fractol->type == newton) ?
		0.00001 : mlx->fractol->radius * mlx->fractol->radius;
	scale = mlx->fractol->radius * mlx->fractol->zoom;
	anchor = mlx->fractol->anchor;
	pos.color = 0;
	pos.y = -1;
	while (++pos.y < WIN_H)
	{
		pos.x = -1;
		while (++pos.x < WIN_W)
		{
			z.x = scale * (double)(pos.x - WIN_W / 2) / WIN_H + anchor.x;
			z.y = scale * (double)(pos.y - WIN_H / 2) / WIN_H + anchor.y;
			buffer[pos.color] = (*get_color)(mlx->fractol, &z, c);
			++pos.color;
		}
	}
}

void			render(t_mlx *mlx)
{
	t_complex	c;

//ft_putendl("RENDER: ");
	mlx->rendering = 1;
	ft_bzero(mlx->image->buffer, WIN_H * mlx->image->line);
	c.x = mlx->mouse ? 0 : ((double)mlx->fractol->mouse.x / (double)WIN_W) * 2 - 1;
	c.y = mlx->mouse ? 0 : ((double)mlx->fractol->mouse.y / (double)WIN_H);
	render_fractal(mlx, (t_u32 *)mlx->image->buffer, &c, mlx->render);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	render_debug(mlx, &c);
	mlx->rendering = 0;
//ft_putendl("DONE");
}
