/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	draw_line_h(t_mlx *mlx, t_point *pos1, t_point *pos2)
{
	int		increment;
	int		e;
	int		dx;
	int		dy;

	dx = (pos2->x - pos1->x);
	dy = (pos2->y - pos1->y);
	increment = (dx > 0 ? 1 : -1);
	e = dx;
	dx *= 2;
	dy *= 2;
	while (is_in_window(pos1->x, pos1->y))
	{
		set_pixel(mlx->image, pos1);
		if ((pos1->x += increment) == pos2->x)
			break ;
		e -= abs(dy) * increment;
		if (dx < 0 ? e > 0 : e < 0)
		{
			pos1->y += (dy > 0 ? 1 : -1);
			e += dx;
		}
	}
}

static void	draw_line_v(t_mlx *mlx, t_point *pos1, t_point *pos2)
{
	int		increment;
	int		e;
	int		dx;
	int		dy;

	dx = (pos2->x - pos1->x);
	dy = (pos2->y - pos1->y);
	increment = (dy > 0 ? 1 : -1);
	e = dy;
	dx *= 2;
	dy *= 2;
	while (is_in_window(pos1->x, pos1->y)) 
	{
		set_pixel(mlx->image, pos1);
		if ((pos1->y += increment) == pos2->y)
			break ;
		e -= abs(dx) * increment;
		if (dy < 0 ? e > 0 : e < 0)
		{
			pos1->x += (dx > 0 ? 1 : -1);
			e += dy;
		}
	}
}

static void	draw_line_s_h(t_mlx *mlx, t_point *pos1, t_point *pos2)
{
	int		increment;

	increment = (pos2->x > pos1->x ? 1 : -1);
	while (is_in_window(pos1->x, pos1->y))
	{
		set_pixel(mlx->image, pos1);
		if ((pos1->x += increment) == pos2->x)
			break ;
	}
}

static void	draw_line_s_v(t_mlx *mlx, t_point *pos1, t_point *pos2)
{
	int		increment;

	increment = (pos2->y > pos1->y ? 1 : -1);
	while (is_in_window(pos1->x, pos1->y))
	{
		set_pixel(mlx->image, pos1);
		if ((pos1->y += increment) == pos2->y)
			break ;
	}
}

void		draw_line(t_mlx *mlx, t_point *pos1, t_point *pos2)
{
	t_point	*tmp;
	int		dx;
	int		dy;

	if (!is_in_window(pos1->x, pos1->y))
	{
		if (!is_in_window(pos2->x, pos2->y))
			return ;
		tmp = pos1;
		pos1 = pos2;
		pos2 = tmp;
	}
	dx = (pos2->x - pos1->x);
	dy = (pos2->y - pos1->y);
	if (dx == 0 && dy == 0)
		return ;
	else if (dx == 0)
		draw_line_s_v(mlx, pos1, pos2);
	else if (dy == 0)
		draw_line_s_h(mlx, pos1, pos2);
	else if (abs(dx) >= abs(dy))
		draw_line_h(mlx, pos1, pos2);
	else
		draw_line_v(mlx, pos1, pos2);
}
