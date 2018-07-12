/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:11:49 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 22:01:36 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			solve(t_square *curr_sq, t_tiles *tiles, char **map)
{
	char		**boolmap;
	int			pos;
	t_square	sol_sq;

	sol_sq.size = -1;
	if (!(boolmap = make_boolmap(tiles, map, curr_sq->map_w, curr_sq->map_h)))
		return (ERROR);
	curr_sq->map_size = curr_sq->map_w * curr_sq->map_h;
	curr_sq->tiles = tiles;
	pos = -1;
	while (++pos < curr_sq->map_size)
	{
		curr_sq->y = pos / curr_sq->map_w;
		curr_sq->x = pos % curr_sq->map_w;
		curr_sq->size = 0;
		if (boolmap[curr_sq->y][curr_sq->x])
		{
			*curr_sq = rec_fill(&pos, boolmap, map, curr_sq);
			if (curr_sq->size > sol_sq.size || sol_sq.size == -1)
				sol_sq = *curr_sq;
		}
	}
	(sol_sq.size)--;
	clean_boolmap(boolmap, curr_sq, -1, -1);
	return (show_map_w_sq(map, &sol_sq));
}

char		**make_boolmap(t_tiles *tiles, char **map, int w, int h)
{
	int		x;
	int		y;
	char	*boolrow;
	char	**boolmap;

	if (!(boolmap = (char**)malloc(h * sizeof(long))))
		return (NULL);
	y = 0;
	while (y < h)
	{
		x = 0;
		if (!(boolrow = (char*)malloc(w)))
			return (NULL);
		while (x < w)
		{
			if (map[y][x] == tiles->obst)
				boolrow[x++] = 0;
			else if (map[y][x] == tiles->free)
				boolrow[x++] = 1;
			else
				return (NULL);
		}
		boolmap[y++] = boolrow;
	}
	return (boolmap);
}

void		clean_boolmap(char **boolmap, t_square *bsq, int f_y, int f_x)
{
	int i;
	int j;

	if (f_y < 0 || f_x < 0)
	{
		i = 0;
		while (i < bsq->map_h)
			free(boolmap[i++]);
		free(boolmap);
	}
	else
	{
		i = bsq->y;
		while (i <= f_y)
		{
			j = bsq->x;
			while (j <= f_x)
				boolmap[i][j++] = 0;
			i++;
		}
	}
}

int			iterate_edges(char **map, t_square *bsq, char **boolmap)
{
	int		i;
	int		boolobst;

	boolobst = 0;
	i = bsq->y + bsq->size;
	while (--i >= bsq->y)
		if (map[i][bsq->x + bsq->size - 1] == bsq->tiles->obst)
		{
			boolobst = 1;
			clean_boolmap(boolmap, bsq, i, bsq->x + bsq->size - 1);
			break ;
		}
	i = bsq->x + bsq->size;
	while (--i >= bsq->x)
		if (map[bsq->y + bsq->size - 1][i] == bsq->tiles->obst)
		{
			boolobst = 1;
			clean_boolmap(boolmap, bsq, bsq->y + bsq->size - 1, i);
			break ;
		}
	return (boolobst);
}

t_square	rec_fill(int *pos, char **boolmap, char **map, t_square *bsq)
{
	(bsq->size)++;
	if (bsq->y + bsq->size > bsq->map_h ||
		bsq->x + bsq->size > bsq->map_w)
	{
		clean_boolmap(boolmap, bsq, bsq->map_h - 1, bsq->map_w - 1);
		return (*bsq);
	}
	else if (map[bsq->y + bsq->size - 1]
				[bsq->x + bsq->size - 1] == bsq->tiles->obst)
	{
		clean_boolmap(boolmap, bsq,
				bsq->y + bsq->size - 1,
				bsq->x + bsq->size - 1);
		return (*bsq);
	}
	else
	{
		if (iterate_edges(map, bsq, boolmap))
			return (*bsq);
		else
			rec_fill(pos, boolmap, map, bsq);
	}
	return (*bsq);
}
