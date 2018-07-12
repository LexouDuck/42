/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 23:21:39 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 12:47:55 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	ft_print_comb2(void)
{
	int num[2];

	num[0] = 0;
	while (num[0] != 99)
	{
		num[1] = num[0] + 1;
		while (num[1] != 100)
		{
			if (num[0] != num[1])
			{
				ft_putchar(num[0] / 10 + '0');
				ft_putchar(num[0] % 10 + '0');
				ft_putchar(' ');
				ft_putchar(num[1] / 10 + '0');
				ft_putchar(num[1] % 10 + '0');
				if (num[0] != 98 || num[1] != 99)
				{
					ft_putchar(',');
					ft_putchar(' ');
				}
			}
			num[1]++;
		}
		num[0]++;
	}
}
