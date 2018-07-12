/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 13:19:27 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/11 17:43:35 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "header.h"

int		main(int argc, char **argv)
{
	int sudoku[9][9];

	if (argc != 10)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (setup(sudoku, argv))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	while (!is_solved(sudoku))
	{
		if (resolve(sudoku))
		{
			write(1, "Error\n", 6);
			return (1);
		}
	}
	display(sudoku);
}

int		setup(int sudoku[9][9], char **argv)
{
	char	c;
	int		x;
	int		y;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
		{
			c = argv[1 + y][x];
			if (c == '.')
				c = 0;
			else if ('1' <= c && c <= '9')
				c -= '0';
			else
				return (1);
			sudoku[y][x] = c;
			x++;
		}
		y++;
	}
	return (0);
}

int		is_solved(int sudoku[9][9])
{
	int digits[9];
	int x;
	int y;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
			digits[x++] = 0;
		x = 0;
		while (x < 9)
			digits[sudoku[y][x++] - 1] = 1;
		x = 0;
		while (x < 9)
			if (digits[x++] == 0)
				return (0);
		y++;
	}
	return (1);
}

void	display(int sudoku[9][9])
{
	char	c;
	int		x;
	int		y;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
		{
			c = sudoku[y][x] + '0';
			write(1, &c, 1);
			c = (x == 8) ? '\n' : ' ';
			write(1, &c, 1);
			x++;
		}
		y++;
	}
}
