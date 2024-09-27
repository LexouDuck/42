/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_rectangle(t_mlx *mlx, t_rect *rectangle, int color)
{
	int	x;
	int	y;
	int	i;

	x = rectangle->x;
	y = rectangle->y;
	i = -1;
	while (++i < rectangle->width)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x + i, y, color);
	y = rectangle->y + rectangle->height - 1;
	i = -1;
	while (++i < rectangle->width)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x + i, y, color);
	y = rectangle->y;
	i = 0;
	while (++i < rectangle->height - 1)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y + i, color);
	x = rectangle->x + rectangle->width - 1;
	i = 0;
	while (++i < rectangle->height - 1)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y + i, color);
}

void	fill_rectangle(t_mlx *mlx, t_rect *rectangle, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < rectangle->height)
	{
		x = 0;
		while (x < rectangle->width)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
				rectangle->x + x,
				rectangle->y + y,
				color);
			++x;
		}
		++y;
	}
}
