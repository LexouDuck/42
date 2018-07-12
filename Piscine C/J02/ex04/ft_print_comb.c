/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 21:59:59 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/14 14:34:52 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	ft_print_comb(void)
{
	int num[3];

	num[2] = 0;
	while (num[2] <= 7)
	{
		num[1] = num[2] + 1;
		while (num[1] <= 8)
		{
			num[0] = num[1] + 1;
			while (num[0] <= 9)
			{
				ft_putchar(num[2] + '0');
				ft_putchar(num[1] + '0');
				ft_putchar(num[0] + '0');
				if (num[2] != 7 || num[1] != 8 || num[0] != 9)
				{
					ft_putchar(',');
					ft_putchar(' ');
				}
				num[0]++;
			}
			num[1]++;
		}
		num[2]++;
	}
}
