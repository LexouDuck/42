/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 23:33:28 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 21:17:18 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	ft_putnbr(int nb)
{
	char	digits[10];
	long	n;
	int		i;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	else if (n == 0)
		ft_putchar('0');
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i--)
		ft_putchar(digits[i]);
}
