/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:55:53 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 21:44:07 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	ft_putnbr(int nb)
{
	int		digits[50];
	int		i;
	long	l_nb;

	i = 0;
	l_nb = (long)nb;
	if (l_nb < 0)
	{
		ft_putchar('-');
		l_nb *= -1;
	}
	if (l_nb == 0)
	{
		ft_putchar('0');
		return ;
	}
	while (l_nb != 0)
	{
		digits[i++] = l_nb % 10;
		l_nb = l_nb / 10;
	}
	while (--i >= 0)
		ft_putchar(digits[i] + 48);
}

int		show_map_w_sq(char **map, t_square *bsq)
{
	int x;
	int y;

	if (bsq == NULL || bsq->size == 0)
		return (ERROR);
	y = 0;
	while (y < bsq->map_h)
	{
		x = 0;
		while (x < bsq->map_w)
		{
			if (bsq->x <= x && x < bsq->x + bsq->size &&
				bsq->y <= y && y < bsq->y + bsq->size)
				ft_putchar(bsq->tiles->fill);
			else
				ft_putchar(map[y][x]);
			x++;
		}
		ft_putchar('\n');
		free(map[y++]);
	}
	free((map - 1)[0]);
	free(map - 1);
	return (OK);
}

void	show_map(char **strls)
{
	int i;

	i = 0;
	while (strls[i])
	{
		ft_putstr(strls[i]);
		ft_putchar('\n');
		i++;
	}
}
