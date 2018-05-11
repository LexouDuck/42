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

void	render(t_mlx *mlx)
{
	t_complex z;
	t_complex c;
	t_complex tmp;
	t_point pos;
	int i;
	int max = 128;
	float radius = mlx->fractol->zoom;
	float radius2 = radius * radius;

	ft_bzero(mlx->image->buffer, WIN_H * mlx->image->line);
	c.x = ((float)mlx->fractol->mouse_x / (float)WIN_W) * 2 - 1;
	c.y = ((float)mlx->fractol->mouse_y / (float)WIN_H);
	pos.y = 0;
	while (pos.y < WIN_H)
	{
		pos.x = 0;
		while (pos.x < WIN_W)
		{
			z.x = 2 * radius * ((float)pos.x - (float)WIN_W / 2.0) / WIN_H;
			z.y = 2 * radius * ((float)pos.y - (float)WIN_H / 2.0) / WIN_H;
			i = 0;
			while (i < max) 
			{
				tmp.x = z.x * z.x - z.y * z.y + c.x;
				tmp.y = 2 * z.x * z.y + c.y;
				if (tmp.x * tmp.x + tmp.y * tmp.y > radius2)
				{
					pos.color = color_new(0,
						i << 8,
						i << 4,
						i << 2);
					set_pixel(mlx->image, &pos);
					break ;
				}
				z.x = tmp.x;
				z.y = tmp.y;
				++i;
			}
			++pos.x;
		}
		++pos.y;
	}
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	render_debug(mlx, &c);
}
