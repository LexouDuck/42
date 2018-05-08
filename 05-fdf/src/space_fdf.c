/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int			fdf_getmap_verts(t_fdf *fdf)
{
	unsigned int	x;
	unsigned int	y;

	fdf->space->vertices = NULL;
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (!add_vertex(fdf->space, x, y, ALT * (float)fdf->map[y][x]))
				return (ERROR);
			++x;
		}
		++y;
	}
	return (OK);
}

static int	fdf_getmap_edges_topleft(t_fdf *fdf, int x, int y)
{
	t_vertex	*vertex;

	if (y == 1)
	{
		vertex = get_vertex(fdf->space, x, 0, ALT * (float)fdf->map[0][x]);
		if (!add_edge(fdf->space, vertex,
		get_vertex(fdf->space, x - 1, 0, ALT * (float)fdf->map[0][x - 1])))
			return (ERROR);
	}
	if (x == 1)
	{
		vertex = get_vertex(fdf->space, 0, y, ALT * (float)fdf->map[y][0]);
		if (!add_edge(fdf->space, vertex,
		get_vertex(fdf->space, 0, y - 1, ALT * (float)fdf->map[y - 1][0])))
			return (ERROR);
	}
	return (OK);
}

int			fdf_getmap_edges(t_fdf *fdf)
{
	t_vertex	*vertex;
	int			x;
	int			y;

	fdf->space->edges = NULL;
	y = fdf->map_height;
	while (--y)
	{
		x = fdf->map_width;
		while (--x)
		{
			vertex = get_vertex(fdf->space, x, y, ALT * (float)fdf->map[y][x]);
			if (!add_edge(fdf->space, vertex,
			get_vertex(fdf->space, x - 1, y, ALT * (float)fdf->map[y][x - 1])))
				return (ERROR);
			if (!add_edge(fdf->space, vertex,
			get_vertex(fdf->space, x, y - 1, ALT * (float)fdf->map[y - 1][x])))
				return (ERROR);
			if (x == 1 || y == 1)
				fdf_getmap_edges_topleft(fdf, x, y);
		}
	}
	return (OK);
}
