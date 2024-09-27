/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:56:41 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 21:41:12 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_map(char **strls, t_tiles *charset, int *x, int *y)
{
	int height;

	if (check_tileset(strls, charset, &height))
		return (ERROR);
	if (check_map_dim(strls + 1, charset, x, y))
		return (ERROR);
	if (*y != height)
		return (ERROR);
	return (OK);
}

int		check_tileset(char **strls, t_tiles *charset, int *height)
{
	int		i;

	i = 0;
	*height = 0;
	while ('0' <= strls[0][i] && strls[0][i] <= '9')
	{
		*height *= 10;
		*height += strls[0][i++] - '0';
	}
	if (*height == 0)
		return (ERROR);
	if (!strls[0][i] ||
		!strls[0][i + 1] ||
		!strls[0][i + 2] ||
		strls[0][i + 3] != '\0' ||
		!strls[1] || !strls[1][0])
		return (ERROR);
	charset->free = strls[0][i];
	charset->obst = strls[0][i + 1];
	charset->fill = strls[0][i + 2];
	if (charset->free == charset->obst ||
		charset->obst == charset->fill ||
		charset->fill == charset->free)
		return (ERROR);
	return (OK);
}

int		check_map_dim(char **map, t_tiles *charset, int *x, int *y)
{
	int width;
	int	has_free_tile;

	has_free_tile = ERROR;
	width = 0;
	while (map[0][width])
		width++;
	*y = 0;
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if (check_map_char(map, charset, *x, *y))
				return (ERROR);
			if (map[*y][*x] == charset->free)
				has_free_tile = OK;
			(*x)++;
		}
		if (*x != width)
			return (ERROR);
		(*y)++;
	}
	return (has_free_tile);
}

int		check_map_char(char **map, t_tiles *charset, int x, int y)
{
	if (map[y][x] == charset->free ||
		map[y][x] == charset->obst)
		return (OK);
	else
		return (ERROR);
}
