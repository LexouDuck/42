/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 18:44:24 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/03 18:44:28 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rush_corners(int x, int y, int longueur, int largeur);

void	rush(int x, int y)
{
	int x_i;
	int y_i;

	y_i = 0;
	while (y_i < y)
	{
		x_i = 0;
		while (x_i < x)
		{
			if (x_i == 0 || x_i == x - 1 || y_i == 0 || y_i == y - 1)
			{
				rush_corners(x_i, y_i, x, y);
			}
			else
			{
				ft_putchar(' ');
			}
			x_i++;
		}
		ft_putchar('\n');
		y_i++;
	}
}

void	rush_corners(int x, int y, int longueur, int largeur)
{
	if ((x == 0 && y == 0) ||
		(x == 0 && y == largeur - 1) ||
		(x == longueur - 1 && y == 0) ||
		(x == longueur - 1 && y == largeur - 1))
		ft_putchar('o');
	else if (x == 0 || x == longueur - 1)
		ft_putchar('|');
	else
		ft_putchar('-');
}
