/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 19:18:51 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/11 17:44:49 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		resolve(int sudoku[9][9])
{
	int possible[9];
	int i;
	int x;
	int y;

	y = -1;
	while (++y < 9)
	{
		x = -1;
		while (++x < 9)
		{
			if (sudoku[y][x] == 0)
			{
				i = 0;
				while (i < 9)
					possible[i++] = 1;
				resolve_row(sudoku, y, possible);
				resolve_column(sudoku, x, possible);
				resolve_square(sudoku, x, y, possible);
				if (resolve_possibilities(sudoku, x, y, possible))
					return (1);
			}
		}
	}
	return (0);
}

void	resolve_row(int sudoku[9][9], int y, int possible[9])
{
	int num;
	int i;

	i = 0;
	while (i < 9)
	{
		num = sudoku[y][i];
		if (num != 0)
			possible[num - 1] = 0;
		i++;
	}
}

void	resolve_column(int sudoku[9][9], int x, int possible[9])
{
	int num;
	int i;

	i = 0;
	while (i < 9)
	{
		num = sudoku[i][x];
		if (num != 0)
			possible[num - 1] = 0;
		i++;
	}
}

void	resolve_square(int sudoku[9][9], int x, int y, int possible[9])
{
	int offset_x;
	int offset_y;
	int num;
	int i;

	offset_x = (x / 3) * 3;
	offset_y = (y / 3) * 3;
	i = 0;
	while (i < 9)
	{
		num = sudoku[offset_y + (i / 3)][offset_x + (i % 3)];
		if (num != 0)
			possible[num - 1] = 0;
		i++;
	}
}

int		resolve_possibilities(int sudoku[9][9], int x, int y, int possible[9])
{
	int count;
	int num;
	int i;

	count = 0;
	i = 0;
	while (i < 9)
	{
		if (possible[i])
		{
			count++;
			num = 1 + i;
		}
		i++;
	}
	if (count == 1)
	{
		sudoku[y][x] = num;
		return (0);
	}
	else if (count == 0)
		return (1);
	else
		return (0);
}
