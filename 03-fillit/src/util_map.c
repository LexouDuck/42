/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:17:18 by aduquesn          #+#    #+#             */
/*   Updated: 2018/01/16 20:22:26 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

t_point	ft_newpoint(int y, int x)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	return (pt);
}

void	ft_clrpoint(t_point *pt)
{
	pt->x = -1;
	pt->y = -1;
}

int		pt_in_bounds(int map_y, int map_x, int y, int x)
{
	return (0 <= x && x < map_x && 0 <= y && y < map_y);
}

/*
** Returns returns 0 if no match found, returns 1 if perfect match found.
*/

int		str_2d_match(
					const char **part,
					const char **whole,
					t_point dim_p,
					t_point dim_w)
{
	int		i;
	int		j;
	int		p_lines;

	i = 0;
	j = 0;
	while (i + dim_p.y <= dim_w.y)
	{
		j = 0;
		while (j + dim_p.x <= dim_w.x)
		{
			p_lines = 0;
			while (ft_strnequ(part[p_lines], &(whole[i + p_lines][j]), dim_p.x))
			{
				++p_lines;
				if (p_lines == dim_p.y)
					return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}

int		overlap(t_minos tm, t_square sq)
{
	int		i;
	int		j;
	int		tx;
	int		ty;

	tx = tm.pos.x;
	ty = tm.pos.y;
	i = 0;
	if (!pt_in_bounds(sq.size, sq.size, ty, tx) ||
		!pt_in_bounds(sq.size, sq.size, ty + tm.size.y - 1, tx + tm.size.x - 1))
		return (1);
	while (tm.layout[i])
	{
		j = 0;
		while (tm.layout[i][j])
		{
			if (tm.layout[i][j] == '#' && sq.layout[ty + i][tx + j] != '.')
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
