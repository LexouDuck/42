/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 23:33:28 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/05 12:50:57 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putnbr(int nb);

void	ft_putnbr(int nb)
{
	char	digits[10];
	int		i;

	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-');
	}
	else if (nb == 0)
		ft_putchar('0');
	i = 0;
	while (nb > 0)
	{
		digits[i++] = nb % 10 + '0';
		nb /= 10;
	}
	while (i > -1)
	{
		ft_putchar(digits[i--]);
	}
}
